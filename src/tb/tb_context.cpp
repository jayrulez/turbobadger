// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_context.h for more information.                 ==
// ================================================================================

#include "tb_context.h"
#include "tb_skin.h"
#include "tb_widgets_reader.h"
#include "tb_language.h"
#include "tb_font_renderer.h"
#ifdef TB_IMAGE
#include "image/tb_image_manager.h"
#endif

namespace tb
{
	TBContext::TBContext(const char* name)
		: m_name(name)
	{
		m_skin = new TBSkin(this);
		m_widgets_reader = TBWidgetsReader::Create(this);
		m_language = new TBLanguage(this);
		m_font_manager = new TBFontManager(this);
#ifdef TB_IMAGE
		m_image_manager = new TBImageManager(this);
#endif
		m_root = new TBWidget();
		m_root->SetContext(this);
	}

	TBContext::~TBContext()
	{
		delete m_root;
#ifdef TB_IMAGE
		delete m_image_manager;
#endif
		delete m_font_manager;
		delete m_language;
		delete m_widgets_reader;
		delete m_skin;
	}

	TBSkin* TBContext::GetSkin() const
	{
		return m_skin;
	}

	TBWidgetsReader* TBContext::GetWidgetsReader() const
	{
		return m_widgets_reader;
	}

	TBLanguage* TBContext::GetLanguage() const
	{
		return m_language;
	}

	TBFontManager* TBContext::GetFontManager() const
	{
		return m_font_manager;
	}
#ifdef TB_IMAGE
	TBImageManager* TBContext::GetImageManager() const
	{
		return m_image_manager;
	}
#endif

	void TBContext::AddWidget(TBWidget* widget)
	{
		m_root->AddChild(widget);
	}

	void TBContext::RemoveWidget(TBWidget* widget)
	{
		m_root->RemoveChild(widget);
	}

	void TBContext::OnWidgetDelete(TBWidget* widget)
	{
		if (widget == m_root)
		{
			//
		}
	}

	void TBContext::InvokeProcess()
	{
		m_root->InvokeProcess();
	}

	void TBContext::InvokeProcessStates(bool force_update)
	{
		m_root->InvokeProcessStates(force_update);
	}

	void TBContext::InvokePaint(const TBWidget::PaintProps& paint_props)
	{
		m_root->InvokePaint(paint_props);
	}

	void TBContext::InvokeFontChanged()
	{
		m_root->InvokeFontChanged();
	}

	bool TBContext::InvokeEvent(TBWidgetEvent& ev)
	{
		return m_root->InvokeEvent(ev);
	}

	bool TBContext::InvokePointerDown(int x, int y, int click_count, MODIFIER_KEYS modifierkeys, bool touch)
	{
		return m_root->InvokePointerDown(x, y, click_count, modifierkeys, touch);
	}

	bool TBContext::InvokePointerUp(int x, int y, MODIFIER_KEYS modifierkeys, bool touch)
	{
		return m_root->InvokePointerUp(x, y, modifierkeys, touch);
	}

	void TBContext::InvokePointerMove(int x, int y, MODIFIER_KEYS modifierkeys, bool touch)
	{
		m_root->InvokePointerMove(x, y, modifierkeys, touch);
	}

	void TBContext::InvokePointerCancel()
	{
		m_root->InvokePointerCancel();
	}

	bool TBContext::InvokeTouchDown(int x, int y, uint32 id, int click_count, MODIFIER_KEYS modifierkeys)
	{
		return m_root->InvokeTouchDown(x, y, id, click_count, modifierkeys);
	}

	bool TBContext::InvokeTouchUp(int x, int y, uint32 id, MODIFIER_KEYS modifierkeys)
	{
		return m_root->InvokeTouchUp(x, y, id, modifierkeys);
	}

	void TBContext::InvokeTouchMove(int x, int y, uint32 id, MODIFIER_KEYS modifierkeys)
	{
		m_root->InvokeTouchMove(x, y, id, modifierkeys);
	}

	void TBContext::InvokeTouchCancel(uint32 id)
	{
		m_root->InvokeTouchCancel(id);
	}

	bool TBContext::InvokeWheel(int x, int y, int delta_x, int delta_y, MODIFIER_KEYS modifierkeys)
	{
		return m_root->InvokeWheel(x, y, delta_x, delta_y, modifierkeys);
	}

	bool TBContext::InvokeKey(int key, SPECIAL_KEY special_key, MODIFIER_KEYS modifierkeys, bool down)
	{
		return m_root->InvokeKey(key, special_key, modifierkeys, down);
	}

	void TBContext::ReleaseCapture()
	{
		m_root->ReleaseCapture();
	}
	void TBContext::ConvertToRoot(int& x, int& y) const
	{
		m_root->ConvertToRoot(x, y);
	}
	void TBContext::ConvertFromRoot(int& x, int& y) const
	{
		m_root->ConvertFromRoot(x, y);
	}
}