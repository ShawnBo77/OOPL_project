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
	void Map::setCharacterX(int x)
	{
		characterX = x;
	}
	void Map::setCharacterY(int y)
	{
		characterY = y;
	}
	void Map::setXY(int x, int y)
	{
		sx = x;
		sy = y;
	}
	void Map::setInitialX(int x)
	{
		initialX = x;
	}
	int Map::getInitialX()
	{
		return initialX;
	}
	void Map::setInitialY(int y)
	{
		initialY = y;
	}
	int Map::getInitialY()
	{
		return initialY;
	}
	void Map::setInitialXY(int x, int y)
	{
		initialX = x;
		initialY = y;
	}
	int Map::getXMovement()
	{
		return sx - initialX;
	}
	int Map::getYMovement()
	{
		return sy - initialY;
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
	void Map::loadMessageIconBitmap()
	{
		messageIcon.LoadBitmap(".\\res\\message_icon.bmp", RGB(0, 0, 0));
	}
	void Map::showMessageIcon(int x, int y)
	{
		messageIcon.SetTopLeft(x + getSX(), y + getSY());
		messageIcon.ShowBitmap();
	}
	void Map::setShowMessageIconFlag(bool flag)
	{
		showMessageIconFlag = flag;
	}
	bool Map::getShowMessageIconFlag()
	{
		return showMessageIconFlag;
	}

	void Map::setCanShowMessage(bool flag, int code)
	{
		canShowMessage = flag;
		messageCode = code;
	}
	bool Map::getCanShowMessage()
	{
		return canShowMessage;
	}
	//void Map::setIsMessageShowing(bool flag)
	//{
	//	isMessageShowing = flag;
	//}
	//bool Map::getIsMessageShowing()
	//{
	//	return isMessageShowing;
	//}
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