#include "tb_system_interface_windows.h"

#if defined(TB_TARGET_WINDOWS)

#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>

void tb::TBSystemInterfaceWindows::DebugOut(const char* str)
{
	OutputDebugString(str);
}

double tb::TBSystemInterfaceWindows::GetTimeMS()
{
	return timeGetTime();
}

//void tb::TBSystemInterfaceWindows::RescheduleTimer(double fire_time)
//{
//}

int tb::TBSystemInterfaceWindows::GetLongClickDelayMS()
{
	return 500;
}

int tb::TBSystemInterfaceWindows::GetPanThreshold()
{
	return 5 * GetDPI() / 96;
}

int tb::TBSystemInterfaceWindows::GetPixelsPerLine()
{
	return 40 * GetDPI() / 96;
}

int tb::TBSystemInterfaceWindows::GetDPI()
{
	HDC hdc = GetDC(nullptr);
	int DPI_x = GetDeviceCaps(hdc, LOGPIXELSX);
	ReleaseDC(nullptr, hdc);
#if 0 // TEST CODE!
	DPI_x *= 2;
#endif
	return DPI_x;
}

#endif
