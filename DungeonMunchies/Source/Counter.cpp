#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <ctime>
#include "Counter.h"

namespace game_framework
{
	Counter::Counter()
	{
		startTime = 0;
		finishTime = 0;
	}

	Counter::~Counter()
	{
	}

	void Counter::SetStartTime(clock_t time)
	{
		startTime = time;
	}

	void Counter::SetFinishTime(clock_t time)
	{
		finishTime = time;
	}

	clock_t Counter::GetStartTime()
	{
		return startTime;
	}

	clock_t Counter::GetFinishTime()
	{
		return finishTime;
	}

	void Counter::Start()
	{
		startTime = clock();
	}

	void Counter::Finish()
	{
		finishTime = clock();
	}

	clock_t Counter::GetTime()
	{
		return finishTime - startTime;
	}
	void Counter::CaculateTime(bool* b, int time)
	{
		Finish();
		if (GetTime() / CLOCKS_PER_SEC > time)
		{
			*b = false;
		}
	}
}