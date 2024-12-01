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
#include "tb_widgets_listener.h"

namespace tb {
    class TBStr;
    class TBSkin;
    class TBWidgetsReader;
#ifdef TB_IMAGE
    class TBImageManager;
#endif
    class TBWidget;
    class TBWidget::PaintProps;

    class TB_API TBContext : public TBWidgetListener
    {
    public:
        TBContext(const char* name = "");
        ~TBContext();

        TBSkin* GetSkin() const;
        TBWidgetsReader* GetWidgetsReader() const;
#ifdef TB_IMAGE
        TBImageManager* GetImageManager() const;
#endif

        void SetRoot(TBWidget* widget);
        void AddWidget(TBWidget* widget);
        void RemoveWidget(TBWidget* widget);

        void OnWidgetDelete(TBWidget* widget) override;


        // == Misc methods for invoking events. Should normally be called only on the root widget ===============
        //==========================================================//
        /** Calls InvokeProcess on the root widget of this context */
        void InvokeProcess();

        /** Calls InvokeProcessStates on the root widget of this context */
        void InvokeProcessStates(bool force_update = false);

        /** Invoke paint on the root widget of this context */
        void InvokePaint();

        /** Calls InvokeFontChanged on the root widget of this context */
        void InvokeFontChanged();

        /** Calls InvokeEvent on the root widget of this context */
        bool InvokeEvent(TBWidgetEvent& ev);

        bool InvokePointerDown(int x, int y, int click_count, MODIFIER_KEYS modifierkeys, bool touch);
        bool InvokePointerUp(int x, int y, MODIFIER_KEYS modifierkeys, bool touch);
        void InvokePointerMove(int x, int y, MODIFIER_KEYS modifierkeys, bool touch);
        void InvokePointerCancel();

        /** Calls InvokeTouch[Down/Up] on the root widget of this context */
        bool InvokeTouchDown(int x, int y, uint32 id, int click_count, MODIFIER_KEYS modifierkeys);
        bool InvokeTouchUp(int x, int y, uint32 id, MODIFIER_KEYS modifierkeys);

        void InvokeTouchMove(int x, int y, uint32 id, MODIFIER_KEYS modifierkeys);
        void InvokeTouchCancel(uint32 id);

        bool InvokeWheel(int x, int y, int delta_x, int delta_y, MODIFIER_KEYS modifierkeys);

        /** Calls InvokeKey on the root widget of this context */
        bool InvokeKey(int key, SPECIAL_KEY special_key, MODIFIER_KEYS modifierkeys, bool down);

        /** A widget that receive a EVENT_TYPE_POINTER_DOWN event, will stay "captured" until EVENT_TYPE_POINTER_UP
    is received. While captured, all EVENT_TYPE_POINTER_MOVE are sent to it. This method can force release the capture,
    which may happen f.ex if the TBWidget is removed while captured. */
        void ReleaseCapture();

        /** Make x and y (relative to this widget) relative to the upper left corner of the root widget. */
        void ConvertToRoot(int& x, int& y) const;

        /** Make x and y (relative to the upper left corner of the root widget) relative to this widget. */
        void ConvertFromRoot(int& x, int& y) const;
        //==========================================================//

    private:
        TBStr m_name;
        TBSkin* m_skin;
        TBWidgetsReader* m_widgets_reader;
#ifdef TB_IMAGE
        TBImageManager* m_image_manager;
#endif
        TBWidget* m_root;
    };

} // namespace tb

#endif // TB_CONTEXT_H
