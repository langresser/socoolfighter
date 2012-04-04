#include "stdafx.h"
#include "GlobalUtil.h"

uint32 getApplicationStartTime()
{
	static uint32 s_application_start_time = 0;
	if (s_application_start_time == 0) {
		struct timeval start;
		gettimeofday(&start, NULL);
		s_application_start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	}

	return s_application_start_time;
}

// 获取程序开始运行后经过多少毫秒
uint32 getCurrentTime(void)
{
	struct timeval start;
	gettimeofday(&start, NULL);
	uint32 dwTime = start.tv_sec * 1000 + start.tv_usec / 1000 - getApplicationStartTime();
	return dwTime;
}