#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "MapForBoss.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

	Map::Map(int x, int y)
	{
		sx = x;
		sy = y;
	}
	void Map::addSX(int n)			//sx+=n 表示地圖向左移動n
	{
		sx += n;
	}
	void Map::addSY(int n)			//sx+=n 表示地圖上移動n
	{
		sy += n;
	}
	void Map::setXY(int x, int y)
	{
		sx = x;
		sy = y;
	}
	int Map::getSX()
	{
		return sx;
	}
	int Map::getSY()
	{
		return sy;
	}
}