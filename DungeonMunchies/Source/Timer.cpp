#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <ctime>
#include "Timer.h"

namespace game_framework
{
	Timer::Timer()
	{
		startTime = 0;
		finishTime = 0;
	}

	Timer::~Timer()
	{
	}

	void Timer::SetStartTime(clock_t time)
	{
		startTime = time;
	}

	void Timer::SetFinishTime(clock_t time)
	{
		finishTime = time;
	}

	clock_t Timer::GetStartTime()
	{
		return startTime;
	}

	clock_t Timer::GetFinishTime()
	{
		return finishTime;
	}

	void Timer::Start()
	{
		startTime = clock();
	}

	void Timer::Finish()
	{
		finishTime = clock();
	}

	clock_t Timer::GetTime()
	{
		return finishTime - startTime;
	}

	void Timer::CaculateTimeForFalse(bool* b, double time)
	{
		Finish();
		if (GetTime() >= time * CLOCKS_PER_SEC)
		{
			*b = false;
		}
	}

	void Timer::CaculateTimeForTrue(bool* b, double time)
	{
		Finish();
		if (GetTime() >= time * CLOCKS_PER_SEC)
		{
			*b = true;
		}
	}
}