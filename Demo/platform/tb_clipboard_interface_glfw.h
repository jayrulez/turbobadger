#pragma once

#include "platform/tb_clipboard_interface.h"

namespace tb {
    class TBClipboardInterfaceGlfw : public tb::TBClipboardInterface
    {
    public:
        void Empty() override;
        bool HasText() override;
        bool SetText(const char* text) override;
        bool GetText(tb::TBStr& text) override;
    };
}