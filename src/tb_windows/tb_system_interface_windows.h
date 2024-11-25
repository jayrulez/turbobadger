#pragma once

#include "tb_system_interface.h"

namespace td {
    class TBSystemInterfaceWindows : public tb::TBSystemInterface
    {
    public:
        void DebugOut(const char* str) override;

        double GetTimeMS() override;
        void RescheduleTimer(double fire_time) override;
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