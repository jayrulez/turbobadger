// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include <math.h>
#include "tb_font_renderer.h"
#include "tb_renderer.h"
#include "platform/tb_system_interface.h"
#include "tb_tempbuffer.h"

#ifdef TB_FONT_RENDERER_STB

using namespace tb;

#ifndef TB_NO_STB_TRUETYPE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate 
#endif
#include "thirdparty/stb_truetype.h"

/** STBFontRenderer renders fonts using stb_truetype.h (http://nothings.org/) */

class STBFontRenderer : public TBFontRenderer
{
public:
	STBFontRenderer();
	~STBFontRenderer();

	bool Load(const char *filename, int size);

	virtual TBFontFace *Create(TBFontManager *font_manager, const char *filename,
								const TBFontDescription &font_desc);

	virtual TBFontMetrics GetMetrics();
	virtual bool RenderGlyph(TBFontGlyphData *dst_bitmap, UCS4 cp);
	virtual void GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp);
	virtual int GetAdvance(UCS4 cp1, UCS4 cp2);
private:
	stbtt_fontinfo font;
	TBTempBuffer ttf_buffer;
	unsigned char *render_data;
	float scale;
};

STBFontRenderer::STBFontRenderer()
	: render_data(nullptr)
{
}

STBFontRenderer::~STBFontRenderer()
{
    stbtt_FreeBitmap(render_data, &font);;
}

TBFontMetrics STBFontRenderer::GetMetrics()
{
	TBFontMetrics metrics;
	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
	metrics.ascent = (int) (ascent * scale + 0.5f);
	metrics.descent = (int) ((-descent) * scale + 0.5f);
	metrics.height = (int) ((ascent - descent + lineGap) * scale + 0.5f);
	return metrics;
}

bool STBFontRenderer::RenderGlyph(TBFontGlyphData *data, UCS4 cp)
{
    stbtt_FreeBitmap(render_data, &font);
	render_data = stbtt_GetCodepointBitmap(&font, 0, scale, cp, &data->w, &data->h, 0, 0);
	data->data8 = render_data;
	data->stride = data->w;
	data->rgb = false;
	return data->data8 ? true : false;
}

void STBFontRenderer::GetGlyphMetrics(TBGlyphMetrics *metrics, UCS4 cp)
{
	int advance, leftSideBearing;
	const int gi = stbtt_FindGlyphIndex(&font, cp);
	stbtt_GetGlyphHMetrics(&font, gi, &advance, &leftSideBearing);
	metrics->advance = (int) roundf(advance * scale);

	int ix0, iy0;
	stbtt_GetGlyphBitmapBoxSubpixel(&font, gi, scale, scale, 0.f, 0.f, &ix0, &iy0, 0, 0);
	metrics->x = ix0;
	metrics->y = iy0;
}

int STBFontRenderer::GetAdvance(UCS4 cp1, UCS4 cp2)
{
	int advance, leftSideBearing;
	const int gi1 = stbtt_FindGlyphIndex(&font, cp1);
	stbtt_GetGlyphHMetrics(&font, gi1, &advance, &leftSideBearing);
	if (font.kern)
		advance += stbtt_GetGlyphKernAdvance(&font, gi1, stbtt_FindGlyphIndex(&font, cp2));
	return (int) roundf(advance * scale);
}

bool STBFontRenderer::Load(const char *filename, int size)
{
	if (!ttf_buffer.AppendFile(filename))
		return false;

	const unsigned char *ttf_ptr = (const unsigned char *) ttf_buffer.GetData();
	stbtt_InitFont(&font, ttf_ptr, stbtt_GetFontOffsetForIndex(ttf_ptr, 0));

	scale = stbtt_ScaleForPixelHeight(&font, (float) size);
	return true;
}

TBFontFace *STBFontRenderer::Create(TBFontManager *font_manager, const char *filename, const TBFontDescription &font_desc)
{
	if (STBFontRenderer *fr = new STBFontRenderer())
	{
		if (fr->Load(filename, (int) font_desc.GetSize()))
			if (TBFontFace *font = new TBFontFace(font_manager->GetGlyphCache(), fr, font_desc))
				return font;
		delete fr;
	}
	return nullptr;
}

TB_API void register_stb_font_renderer()
{
	if (STBFontRenderer *fr = new STBFontRenderer)
		g_font_manager->AddRenderer(fr);
}

#endif // TB_FONT_RENDERER_STB
