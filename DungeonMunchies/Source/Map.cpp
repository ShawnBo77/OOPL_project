#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include <vector>

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

	Map::Map(int x, int y)
	{
		sx = x;
		sy = y;
		cyRelativeMovement = 0;
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
	void Map::setSX(int x)
	{
		sx = x;
	}
	void Map::setSY(int y)
	{
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
	int Map::getCharacterYRelativeMovement()
	{
		return cyRelativeMovement;
	}
	void Map::setCharacterYRelativeMovement(int y)
	{
		cyRelativeMovement = y;
	}
	void Map::addCharacterYRelativeMovement(int y)
	{
		cyRelativeMovement += y;
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
		if (screenMoving == false)
		{
			return 10000000;
		}
		else
		{
			return endBoundary;
		}
	}
	bool Map::getCraftTableOpen()
	{
		return craftTableOpen;
	}
	void Map::setCraftTableOpen(bool flag)
	{
		craftTableOpen = flag;
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
	void Map::loadMagnifierBitmap()
	{
		magnifier.LoadBitmap(".\\res\\magnifier.bmp", RGB(0, 0, 0));
	}
	void Map::showMaginifier(int x, int y)
	{
		magnifier.SetTopLeft(x + getSX(), y + getSY());
		magnifier.ShowBitmap();
	}
	void Map::setShowMaginifierFlag(bool flag)
	{
		showMaginifierFlag = flag;
	}
	bool Map::getShowMaginifierFlag()
	{
		return showMaginifierFlag;
	}
	void Map::setCanShowMessage(bool flag)
	{
		canShowMessage = flag;
	}
	bool Map::getCanShowMessage()
	{
		return canShowMessage;
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
	bool Map::getTrashCanOpen()
	{
		return trashCanOpen;
	}
	void Map::setTrashCanOpen(bool flag)
	{
		trashCanOpen = flag;
	}


	void Map::setMessageCounter(int n)
	{
		messageCounter = n;
	}

	int Map::getMessageCounter()
	{
		return messageCounter;
	}

	void Map::setMessageCounterToNext()
	{
		if (messageCounter != messageSize)
		{
			messageCounter += 1;
		}
		else
		{
			messageCounter = 1;
		}
	}

	void Map::setMessageEndFlag(bool flag)
	{
		messageEndFlag = flag;
	}

	bool Map::getMessageEndFlag()
	{
		return messageEndFlag;
	}
	void Map::InitializeMessage()
	{
		messageCounter = 1;
		messageEndFlag = false;
	}

	void Map::messageOnShow()
	{
	}

}