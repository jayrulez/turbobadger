#pragma once

#include "tb_clipboard_interface.h"
#include "tb_str.h"

namespace tb {
    class TBClipboardInterfaceDummy : public TBClipboardInterface
    {
    public:
        void Empty()  override;
        bool HasText()  override;
        bool SetText(const char* text)  override;
        bool GetText(tb::TBStr& text)  override;
        
    private:
     ///< Obviosly not a full implementation since it ignores the OS :)
        TBStr clipboard;
    };
}