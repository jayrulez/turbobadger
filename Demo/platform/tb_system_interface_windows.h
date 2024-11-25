#pragma once

#include "platform.h"
#include "tb_system_interface_glfw.h"

#if defined(TB_TARGET_WINDOWS)

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
    };
}

#endif