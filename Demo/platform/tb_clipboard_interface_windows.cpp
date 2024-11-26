#include "tb_clipboard_interface_windows.h"

#if defined(TB_TARGET_WINDOWS)

#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>

void tb::TBClipboardInterfaceWindows::Empty()
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}

bool tb::TBClipboardInterfaceWindows::HasText()
{
	bool has_text = false;
	if (OpenClipboard(NULL))
	{
		has_text = IsClipboardFormatAvailable(CF_TEXT) ||
			IsClipboardFormatAvailable(CF_OEMTEXT) ||
			IsClipboardFormatAvailable(CF_UNICODETEXT);
		CloseClipboard();
	}
	return has_text;
}

bool tb::TBClipboardInterfaceWindows::SetText(const char* text)
{
	if (OpenClipboard(NULL))
	{
		int num_wide_chars_needed = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
		if (HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, num_wide_chars_needed * sizeof(wchar_t)))
		{
			LPWSTR pchData = (LPWSTR)GlobalLock(hClipboardData);
			MultiByteToWideChar(CP_UTF8, 0, text, -1, pchData, num_wide_chars_needed);
			GlobalUnlock(hClipboardData);

			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hClipboardData);
		}

		CloseClipboard();
		return true;
	}
	return false;
}

bool tb::TBClipboardInterfaceWindows::GetText(tb::TBStr& text)
{
	bool success = false;
	if (HasText() && OpenClipboard(NULL))
	{
		if (HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT))
		{
			wchar_t* pchData = (wchar_t*)GlobalLock(hClipboardData);
			int len = WideCharToMultiByte(CP_UTF8, 0, pchData, -1, NULL, 0, NULL, NULL);
			if (char* utf8 = new char[len])
			{
				WideCharToMultiByte(CP_UTF8, 0, pchData, -1, utf8, len, NULL, NULL);
				success = text.Set(utf8);
				delete[] utf8;
			}
			GlobalUnlock(hClipboardData);
		}
		CloseClipboard();
	}
	return success;
}

#endif
