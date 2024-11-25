#pragma once

#include "tb_glfw/tb_system_interface_glfw.h"

namespace tb {
    class TBSystemInterfaceWindows : public TBSystemInterfaceGlfw
    {
    public:
        void DebugOut(const char* str) override;

        double GetTimeMS() override;
        //void RescheduleTimer(double fire_time) override;
        int GetLongClickDelayMS() override;
        int GetPanThreshold() override;
        int GetPixelsPerLine() override;
        int GetDPI() override;

        void EmptyClipboard()  override;
        bool HasClipboardText()  override;
        bool SetClipboardText(const char* text)  override;
        bool GetClipboardText(tb::TBStr& text)  override;
    };
}