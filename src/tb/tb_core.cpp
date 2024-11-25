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

namespace tb {

TB_DLLCLASS TBRenderer *g_renderer = nullptr;
TB_DLLCLASS TBSkin *g_tb_skin = nullptr;
TB_DLLCLASS TBWidgetsReader *g_widgets_reader = nullptr;
TB_DLLCLASS TBLanguage *g_tb_lng = nullptr;
TB_DLLCLASS TBFontManager *g_font_manager = nullptr;
TB_DLLCLASS TBSystemInterface *g_system_interface = nullptr;
TB_DLLCLASS TBFileInterface *g_file_interface = nullptr;

TB_DLLCLASS bool tb_core_init(TBRenderer *renderer, TBSystemInterface* system_interface, TBFileInterface* file_interface)
{
	system_interface->DebugPrint("Initiating Turbo Badger - version %s\n", TB_VERSION_STR);
	g_renderer = renderer;
	g_system_interface = system_interface;
	g_file_interface = file_interface;

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
}

TB_DLLCLASS bool tb_core_is_initialized()
{
	return g_widgets_reader ? true : false;
}

} // namespace tb
