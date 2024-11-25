#include "tb_system_interface_linux.h"

#include <sys/time.h>
#include <stdio.h>

void tb::TBSystemInterfaceLinux::DebugOut(const char* str)
{
	printf("%s", str);
}

double tb::TBSystemInterfaceLinux::GetTimeMS()
{
	struct timeval now;
	gettimeofday(&now, nullptr);
	return now.tv_usec / 1000 + now.tv_sec * 1000;
}

//void tb::TBSystemInterfaceLinux::RescheduleTimer(double fire_time)
//{
//}

int tb::TBSystemInterfaceLinux::GetLongClickDelayMS()
{
	return 500;
}

int tb::TBSystemInterfaceLinux::GetPanThreshold()
{
	return 5 * GetDPI() / 96;
}

int tb::TBSystemInterfaceLinux::GetPixelsPerLine()
{
	return 40 * GetDPI() / 96;
}

int tb::TBSystemInterfaceLinux::GetDPI()
{
	// FIX: Implement!
	return 96;
}

//void tb::TBSystemInterfaceLinux::EmptyClipboard()
//{
//}
//
//bool tb::TBSystemInterfaceLinux::HasClipboardText()
//{
//	return false;
//}
//
//bool tb::TBSystemInterfaceLinux::SetClipboardText(const char* text)
//{
//	return false;
//}
//
//bool tb::TBSystemInterfaceLinux::GetClipboardText(tb::TBStr& text)
//{
//	return false;
//}
