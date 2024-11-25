#include "tb_clipboard_interface_dummy.h"

void tb::TBClipboardInterfaceDummy::Empty()
{
	clipboard.Clear();
}

bool tb::TBClipboardInterfaceDummy::HasText()
{
	return !clipboard.IsEmpty();
}

bool tb::TBClipboardInterfaceDummy::SetText(const char* text)
{
	return clipboard.Set(text);
}

bool tb::TBClipboardInterfaceDummy::GetText(tb::TBStr& text)
{
	return text.Set(clipboard);
}
