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
}