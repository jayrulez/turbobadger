// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

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

#define TB_VERSION_MAJOR 0
#define TB_VERSION_MINOR 1
#define TB_VERSION_REVISION 1
#define TB_VERSION_STR "0.1.1"

namespace tb {

	TB_API TBContext* g_tb_context = nullptr;

	TBContext::TBContext(const char* name)
		: m_name(name),
		  m_tb_skin(nullptr),
		  m_widgets_reader(nullptr),
		  m_tb_lng(nullptr),
		  m_font_manager(nullptr),
		  m_renderer(nullptr)
	{
	}

	TBContext::~TBContext()
	{
	}

	bool TBContext::Initialize(TBRenderer* renderer, TBSystemInterface* system_interface, TBFileInterface* file_interface, TBClipboardInterface* clipboard_interface)
	{
		if (g_tb_context == nullptr)
		{
			g_tb_context = this;
		}

		m_renderer = renderer;
		m_system_interface = system_interface;
		m_file_interface = file_interface;
		m_clipboard_interface = clipboard_interface;

		TBDebugPrint("Initiating Turbo Badger - version %s\n", TB_VERSION_STR);

		m_tb_lng = new TBLanguage;
		m_font_manager = new TBFontManager(this);
		m_tb_skin = new TBSkin(this);
		m_widgets_reader = TBWidgetsReader::Create(this);

#ifdef TB_IMAGE
		m_image_manager = new TBImageManager(this);
#endif

		return true;
	}

	void TBContext::Shutdown()
	{
		TBAnimationManager::AbortAllAnimations();
#ifdef TB_IMAGE
		delete m_image_manager;
		m_image_manager = nullptr;
#endif
		delete m_widgets_reader;
		m_widgets_reader = nullptr;
		delete m_tb_skin;
		m_tb_skin = nullptr;
		delete m_font_manager;
		m_font_manager = nullptr;
		delete m_tb_lng;
		m_tb_lng = nullptr;

		if (g_tb_context == this)
		{
			g_tb_context = nullptr;
		}
	}

	bool TBContext::IsInitialized() const { return m_widgets_reader != nullptr; }

	TB_API TBContext* tb_create_context(
		const char* name,
		TBRenderer* renderer,
		TBSystemInterface* system_interface,
		TBFileInterface* file_interface,
		TBClipboardInterface* clipboard_interface
	)
	{
		if (g_tb_context)
		{
			return g_tb_context;
		}

		TBContext* context = new TBContext(name);
		if (!context->Initialize(renderer, system_interface, file_interface, clipboard_interface))
		{
			delete context;
			return nullptr;
		}

		return context;
	}

	TB_API void tb_destroy_context(TBContext* context)
	{
		if (context)
		{
			if (context->IsInitialized())
			{
				context->Shutdown();
			}
			delete context;
		}
	}

} // namespace tb
