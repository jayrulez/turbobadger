/** @mainpage Turbo Badger - Fast UI toolkit

Turbo Badger
Copyright (C) 2011-2014 Emil Segerås

License:

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

#ifndef TB_CONTEXT_H
#define TB_CONTEXT_H

#include "tb_types.h"
#include "tb_hash.h"
#include "tb_debug.h"
#include <tb_str.h>


namespace tb {

    class TBRenderer;
    class TBSkin;
    class TBWidgetsReader;
    class TBLanguage;
    class TBFontManager;
    class TBSystemInterface;
    class TBFileInterface;
    class TBClipboardInterface;
    class TBImageManager;
    class TBWidget;

    class TB_API TBContext
    {
    public:
        TBContext(const char* name = "");
        ~TBContext();
        /** Initialize turbo badger. Call this before using any turbo badger API. */
        bool Initialize(TBRenderer* renderer,
            TBSystemInterface* system_interface,
            TBFileInterface* file_interface,
            TBClipboardInterface* clipboard_interface);
        /** Shutdown turbo badger. Call this after deleting the last widget, to free turbo badger internals. */
		void Shutdown();
        /** Returns true if turbo badger is initialized. */
		bool IsInitialized() const;

        const char* GetName() const { return m_name; }

		TBSkin* GetSkin() const { return m_tb_skin; }
		TBWidgetsReader* GetWidgetsReader() const { return m_widgets_reader; }
		TBLanguage* GetLanguage() const { return m_tb_lng; }
		TBFontManager* GetFontManager() const { return m_font_manager; }

		TBRenderer* GetRenderer() const { return m_renderer; }
		TBSystemInterface* GetSystemInterface() const { return m_system_interface; }
		TBFileInterface* GetFileInterface() const { return m_file_interface; }
		TBClipboardInterface* GetClipboardInterface() const { return m_clipboard_interface; }

#ifdef TB_IMAGE
		TBImageManager* GetImageManager() const { return m_image_manager; }
#endif

        // TBWidget related globals
        TBWidget* hovered_widget = nullptr;	///< The currently hovered widget, or nullptr.
        TBWidget* captured_widget = nullptr;	///< The currently captured widget, or nullptr.
        TBWidget* focused_widget = nullptr;	///< The currently focused widget, or nullptr.
        int pointer_down_widget_x = 0;	///< Pointer x position on down event, relative to the captured widget.
        int pointer_down_widget_y = 0;	///< Pointer y position on down event, relative to the captured widget.
        int pointer_move_widget_x = 0;	///< Pointer x position on last pointer event, relative to the captured widget (if any) or hovered widget.
        int pointer_move_widget_y = 0;	///< Pointer y position on last pointer event, relative to the captured widget (if any) or hovered widget.
        bool cancel_click = false;			///< true if the pointer up event should not generate a click event.
        bool update_widget_states = true;	///< true if something has called InvalidateStates() and it still hasn't been updated.
        bool update_skin_states = true;		///< true if something has called InvalidateStates() and skin still hasn't been updated.
        bool show_focus_state = false;		///< true if the focused state should be painted automatically.

    private:
        TBStr m_name;

        TBSkin* m_tb_skin;
        TBWidgetsReader* m_widgets_reader;
        TBLanguage* m_tb_lng;
        TBFontManager* m_font_manager;

        TBRenderer* m_renderer;
        TBSystemInterface* m_system_interface;
        TBFileInterface* m_file_interface;
        TBClipboardInterface* m_clipboard_interface;

#ifdef TB_IMAGE
        TBImageManager* m_image_manager;
#endif
    };

	TB_API extern TBContext* g_tb_context;

    TB_API TBContext* tb_create_context(
        const char* name,
        TBRenderer* renderer,
        TBSystemInterface* system_interface,
        TBFileInterface* file_interface,
        TBClipboardInterface* clipboard_interface);

    TB_API void tb_destroy_context(TBContext* context);

} // namespace tb

#endif // TB_CONTEXT_H
