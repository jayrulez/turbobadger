#include "tb_types.h"
#include "tb_core.h"
#include "tb_msg.h"
#include "tb_system_interface_glfw.h"
#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "glfw_extra.h"

//void tb::TBSystemInterfaceGlfw::DebugOut(const char* str)
//{
//}

//double tb::TBSystemInterfaceGlfw::GetTimeMS()
//{
//	return 0.0;
//}

/** Reschedule the platform timer, or cancel it if fire_time is TB_NOT_SOON.
	If fire_time is 0, it should be fired ASAP.
	If force is true, it will ask the platform to schedule it again, even if
	the fire_time is the same as last time. */
void tb::TBSystemInterfaceGlfw::ReschedulePlatformTimer(double fire_time, bool force)
{
	static double set_fire_time = -1;
	if (fire_time == TB_NOT_SOON)
	{
		set_fire_time = -1;
		glfwKillTimer();
	}
	else if (fire_time != set_fire_time || force || fire_time == 0)
	{
		set_fire_time = fire_time;
		double delay = fire_time - tb::g_system_interface->GetTimeMS();
		unsigned int idelay = (unsigned int)tb::MAX(delay, 0.0);
		glfwRescheduleTimer(idelay);
	}
}

void tb::TBSystemInterfaceGlfw::RescheduleTimer(double fire_time)
{
	ReschedulePlatformTimer(fire_time, false);
}

//int tb::TBSystemInterfaceGlfw::GetLongClickDelayMS()
//{
//	return 0;
//}
//
//int tb::TBSystemInterfaceGlfw::GetPanThreshold()
//{
//	return 0;
//}
//
//int tb::TBSystemInterfaceGlfw::GetPixelsPerLine()
//{
//	return 0;
//}
//
//int tb::TBSystemInterfaceGlfw::GetDPI()
//{
//	return 0;
//}
