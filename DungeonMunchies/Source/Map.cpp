#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

	Map::Map(int x, int y)
	{
		sx = x;
		sy = y;
		portalOpen = false;
	}
	string Map::getMapName()
	{
		return mapName;
	}
	int Map::getStartPosition()
	{
		return startX;
	}
	int Map::getSX()
	{
		return sx;
	}
	int Map::getSY()
	{
		return sy;
	}
	bool Map::mapScreenMoving()
	{
		return screenMoving;
	}
	int Map::getFloor()
	{
		return floor;
	}
	int Map::getCeiling()
	{
		return ceiling;
	}
	int Map::getEndBoundary()
	{
		if (screenMoving == false) {
			return 10000000;
		}
		else {
			return endBoundary;
		}
	}
	bool Map::getPortalOpen()
	{
		return portalOpen;
	}
	void Map::setMapName(string name)
	{
		mapName = name;
	}
	void Map::setStartPosition(int x)
	{
		startX = x;
	}
	int Map::getMonsterFloor()
	{
		return monsterFloor;
	}
	void Map::setMonsterFloor(int y)
	{
		monsterFloor = y;
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
	void Map::setFloor(int y)
	{
		floor = y;
	}
	void Map::setCeiling(int y)
	{
		ceiling = y;
	}
	void Map::setEndBoundary(int sx)
	{
		endBoundary = sx;
	}
	void Map::setScreenMoving(bool flag)
	{
		screenMoving = flag;
	}
	void Map::setPortalOpen(bool flag)
	{
		portalOpen = flag;
	}
}