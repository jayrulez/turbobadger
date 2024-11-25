#pragma once

#include "tb_system_interface_glfw.h"

#if defined(TB_TARGET_LINUX)

namespace tb {
    class TBSystemInterfaceLinux : public TBSystemInterfaceGlfw
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