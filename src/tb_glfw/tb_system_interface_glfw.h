#pragma once

#include "tb_system_interface.h"

namespace tb {
    class TBSystemInterfaceGlfw : public tb::TBSystemInterface
    {
    public:
        //void DebugOut(const char* str) override;

        //double GetTimeMS() override;

        /** Reschedule the platform timer, or cancel it if fire_time is TB_NOT_SOON.
    If fire_time is 0, it should be fired ASAP.
    If force is true, it will ask the platform to schedule it again, even if
    the fire_time is the same as last time. */
        static void ReschedulePlatformTimer(double fire_time, bool force);

        void RescheduleTimer(double fire_time) override;
        //int GetLongClickDelayMS() override;
        //int GetPanThreshold() override;
        //int GetPixelsPerLine() override;
        //int GetDPI() override;

        void EmptyClipboard()  override;
        bool HasClipboardText()  override;
        bool SetClipboardText(const char* text)  override;
        bool GetClipboardText(tb::TBStr& text)  override;
    };
}