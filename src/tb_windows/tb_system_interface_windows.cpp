#include "tb_system_interface_windows.h"

#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>

void td::TBSystemInterfaceWindows::DebugOut(const char* str)
{
	OutputDebugString(str);
}

double td::TBSystemInterfaceWindows::GetTimeMS()
{
	return timeGetTime();
}

void td::TBSystemInterfaceWindows::RescheduleTimer(double fire_time)
{
}

int td::TBSystemInterfaceWindows::GetLongClickDelayMS()
{
	return 500;
}

int td::TBSystemInterfaceWindows::GetPanThreshold()
{
	return 5 * GetDPI() / 96;
}

int td::TBSystemInterfaceWindows::GetPixelsPerLine()
{
	return 40 * GetDPI() / 96;
}

int td::TBSystemInterfaceWindows::GetDPI()
{
	HDC hdc = GetDC(nullptr);
	int DPI_x = GetDeviceCaps(hdc, LOGPIXELSX);
	ReleaseDC(nullptr, hdc);
#if 0 // TEST CODE!
	DPI_x *= 2;
#endif
	return DPI_x;
}

void td::TBSystemInterfaceWindows::EmptyClipboard()
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}

bool td::TBSystemInterfaceWindows::HasClipboardText()
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

bool td::TBSystemInterfaceWindows::SetClipboardText(const char* text)
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

bool td::TBSystemInterfaceWindows::GetClipboardText(tb::TBStr& text)
{
	bool success = false;
	if (HasClipboardText() && OpenClipboard(NULL))
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
