#pragma once

#include "tb_platform.h"
#include "platform/tb_clipboard_interface.h"

#if defined(TB_TARGET_WINDOWS)

namespace tb {
    class TBClipboardInterfaceWindows : public TBClipboardInterface
    {
    public:
        void Empty()  override;
        bool HasText()  override;
        bool SetText(const char* text)  override;
        bool GetText(tb::TBStr& text)  override;
    };
}

#endif