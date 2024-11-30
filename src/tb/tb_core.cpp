// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_core.h"
#include "tb_context.h"
#include "tb_skin.h"
#include "tb_widgets_reader.h"
#include "tb_language.h"
#include "tb_font_renderer.h"
#include "platform/tb_system_interface.h"
#include "platform/tb_file_interface.h"
#include "platform/tb_clipboard_interface.h"
#include "animation/tb_animation.h"
#include "image/tb_image_manager.h"
#include "tb_widgets_listener.h"

namespace tb {

TB_API TBRenderer *g_renderer = nullptr;
TB_API TBSkin *g_tb_skin = nullptr;
TB_API TBWidgetsReader *g_widgets_reader = nullptr;
TB_API TBLanguage *g_tb_lng = nullptr;
TB_API TBFontManager *g_font_manager = nullptr;
TB_API TBSystemInterface *g_system_interface = nullptr;
TB_API TBFileInterface *g_file_interface = nullptr;
TB_API TBClipboardInterface *g_clipboard_interface = nullptr;

TB_API bool g_tb_initialized = false;

bool tb_core_init(
	TBRenderer *renderer,
	TBSystemInterface* system_interface,
	TBFileInterface* file_interface,
	TBClipboardInterface* clipboard_interface)
{
	g_renderer = renderer;
	g_system_interface = system_interface;
	g_file_interface = file_interface;
	g_clipboard_interface = clipboard_interface;

	TBDebugPrint("Initiating Turbo Badger - version %s\n", TB_VERSION_STR);

	g_tb_lng = new TBLanguage(nullptr);
	g_font_manager = new TBFontManager(nullptr);
	g_tb_skin = new TBSkin(nullptr);
	g_widgets_reader = TBWidgetsReader::Create(nullptr);
#ifdef TB_IMAGE
	g_image_manager = new TBImageManager(nullptr);
#endif
	g_tb_initialized = true;
	return g_tb_initialized;
}

void tb_core_shutdown()
{
	if (g_tb_initialized)
	{
		TBAnimationManager::AbortAllAnimations();
#ifdef TB_IMAGE
		delete g_image_manager;
#endif
		delete g_widgets_reader;
		delete g_tb_skin;
		delete g_font_manager;
		delete g_tb_lng;
	}
}

bool tb_core_is_initialized()
{
	return g_tb_initialized;
}

TB_API TBContext* tb_create_context(const char* name)
{
	TBContext* context = new TBContext(name);

	TBWidgetListener::AddGlobalListener(context);

	return context;
}

TB_API void tb_destroy_context(TBContext* context)
{
	TBWidgetListener::RemoveGlobalListener(context);

	delete context;
}

} // namespace tb
