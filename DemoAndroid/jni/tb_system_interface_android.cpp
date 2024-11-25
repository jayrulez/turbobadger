#include "tb_system_interface_android.h"

#include <android/log.h>
#include <sys/time.h>
#include <stdio.h>

#define  LOG_TAG    "TB"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void tb::TBSystemInterfaceAndroid::DebugOut(const char* str)
{
	LOGI("%s", str);
}

double tb::TBSystemInterfaceAndroid::GetTimeMS()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return now.tv_usec / 1000 + now.tv_sec * 1000;
}

void tb::TBSystemInterfaceAndroid::RescheduleTimer(double fire_time)
{
}

int tb::TBSystemInterfaceAndroid::GetLongClickDelayMS()
{
	return 500;
}

int tb::TBSystemInterfaceAndroid::GetPanThreshold()
{
	return 5 * GetDPI() / 120;
}

int tb::TBSystemInterfaceAndroid::GetPixelsPerLine()
{
	return 40 * GetDPI() / 120;
}

int tb::TBSystemInterfaceAndroid::GetDPI()
{
	AConfiguration *config = AConfiguration_new();
	AConfiguration_fromAssetManager(config, g_pManager);
	int32_t density = AConfiguration_getDensity(config);
	AConfiguration_delete(config);
	if (density == 0 || density == ACONFIGURATION_DENSITY_NONE)
		return 120;
	return density;
}
