// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_core.h"
#include "tb_skin.h"
#include "tb_widgets_reader.h"
#include "tb_language.h"
#include "tb_font_renderer.h"
#include "tb_system_interface.h"
#include "animation/tb_animation.h"
#include "image/tb_image_manager.h"
#include "tb_system_interface.h"
#include "tb_context.h"

namespace tb {

static TBRenderer *g_renderer = nullptr;
static TBSkin *g_tb_skin = nullptr;
static TBWidgetsReader *g_widgets_reader = nullptr;
static TBLanguage *g_tb_lng = nullptr;
static TBFontManager *g_font_manager = nullptr;
static TBSystemInterface *g_system_interface = nullptr;
static TBFileInterface *g_file_interface = nullptr;
static TBContext* g_context;

TB_DLLCLASS TBRenderer* get_renderer() { return g_renderer; }
TB_DLLCLASS TBSkin* get_tb_skin() { return g_tb_skin; }
TB_DLLCLASS TBWidgetsReader* get_widgets_reader() { return g_widgets_reader; }
TB_DLLCLASS TBLanguage* get_tb_lng() { return g_tb_lng; }
TB_DLLCLASS TBFontManager* get_font_manager() { return g_font_manager; }
TB_DLLCLASS TBSystemInterface* get_system_interface() { return g_system_interface; }
TB_DLLCLASS TBFileInterface* get_file_interface() { return g_file_interface; }
TB_DLLCLASS TBContext* get_context() { return g_context; }

TB_DLLCLASS bool tb_core_init(TBRenderer *renderer, TBSystemInterface* system_interface, TBFileInterface* file_interface)
{
	system_interface->DebugPrint("Initiating Turbo Badger - version %s\n", TB_VERSION_STR);
	g_renderer = renderer;
	g_system_interface = system_interface;
	g_file_interface = file_interface;

	g_context = new TBContext;
	g_tb_lng = new TBLanguage;
	g_font_manager = new TBFontManager();
	g_tb_skin = new TBSkin();
	g_widgets_reader = TBWidgetsReader::Create();
#ifdef TB_IMAGE
	g_image_manager = new TBImageManager();
#endif
	return true;
}

TB_DLLCLASS void tb_core_shutdown()
{
	TBAnimationManager::AbortAllAnimations();
#ifdef TB_IMAGE
	delete g_image_manager;
#endif
	delete g_widgets_reader;
	delete g_tb_skin;
	delete g_font_manager;
	delete g_tb_lng;
	delete g_context;
}

TB_DLLCLASS bool tb_core_is_initialized()
{
	return g_widgets_reader ? true : false;
}

} // namespace tb
