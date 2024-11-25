#pragma once

#include "platform/tb_system_interface.h"

namespace tb {
    class TBSystemInterfaceAndroid : public TBSystemInterface
    {
    public:
        void DebugOut(const char* str) override;

        double GetTimeMS() override;
        void RescheduleTimer(double fire_time) override;
        int GetLongClickDelayMS() override;
        int GetPanThreshold() override;
        int GetPixelsPerLine() override;
        int GetDPI() override;
    };
}