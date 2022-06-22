#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "MapS6.h"
#include <vector>
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖構成
	/////////////////////////////////////////////////////////////////////////////
	MapS6::MapS6() : Map(0, 0) //地圖設置：0為不能走、1為可以走、2為傳送門、3為橋、4為鍛造台、5為垃圾桶、6為受傷區域
	{
		X = 20;
		Y = 20;
		gridW = 20;
		gridH = 20;
		startX = 300;
		setFloor(600);
		setCeiling(0);
		setMonsterFloor(600);
		int mapGrid_init[400][70];
		for (int i = 0; i < 400; i++)
		{
			for (int j = 0; j < 70; j++)
			{
				mapGrid_init[i][j] = 1;
			}
		}
		//給予地圖左上角座標及每張小圖寬度
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 70; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		for (int i = 7; i < 23; i++)
		{
			for (int j = 21; j < 38; j++)
			{
				mapGrid_init[i][j] = 2;
			}
		}
		for (int i = 0; i < 400; i++)
		{
			for (int j = 38; j < 70; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		for (int i = 6; i < 22; i++)
		{
			for (int j = 16; j < 21; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		for (int i = 0; i < 400; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		for (int i = 0; i < 82; i++)
		{
			for (int j = 4; j < 16; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		for (int i = 105; i < 400; i++)
		{
			for (int j = 29; j < 38; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		for (int i = 145; i < 153; i++)
		{
			for (int j = 4; j < 29; j++)
			{
				mapGrid_init[i][j] = 5;
			}
		}
		for (int i = 160; i < 170; i++)
		{
			for (int j = 4; j < 29; j++)
			{
				mapGrid_init[i][j] = 4;
			}
		}
		for (int i = 180; i < 200; i++)
		{
			for (int j = 4; j < 29; j++)
			{
				mapGrid_init[i][j] = 2;
			}
		}
		for (int i = 200; i < 400; i++)
		{
			for (int j = 0; j < 70; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		for (int i = 0; i < 400; i++)
		{
			for (int j = 0; j < 70; j++)
			{
				mapGrid[i][j] = mapGrid_init[i][j]; //依序填入mapGrid
			}
		}
	}
	MapS6::~MapS6()
	{
	}
	void MapS6::LoadBitmap()
	{
		map.LoadBitmap(IDB_MAPS6);
		exitBitmap.LoadBitmap(IDB_EXIT, RGB(0, 0, 0));
		pressEBitmap.LoadBitmap(IDB_PRESSE, RGB(0, 0, 0));
		trashCanClosedBitmap.LoadBitmap(IDB_TRASHCANCLOSED, RGB(0, 0, 0));
		trashCanOpenBitmap.LoadBitmap(IDB_TRASHCANOPEN, RGB(0, 0, 0));
		craftingBitmap.LoadBitmap(IDB_CRAFTING, RGB(0, 0, 0));
		bossAssistant.LoadBitmap(".\\res\\boss_assistant.bmp", RGB(0, 0, 0));
		message01.LoadBitmap(".\\res\\message0601.bmp", RGB(0, 0, 0));
		message02.LoadBitmap(".\\res\\message0602.bmp", RGB(0, 0, 0));
		message03.LoadBitmap(".\\res\\message0603.bmp", RGB(0, 0, 0));
		message04.LoadBitmap(".\\res\\message0604.bmp", RGB(0, 0, 0));
	}
	void MapS6::Initialize()
	{
		setXY(100, -260);
		setInitialXY(100, -100);
		setScreenMoving(true);
		setMapName("MapS6");
		setCeiling(0);
		previousFloor = 0;
		targetSY = 0;
		trashCanOpen = false;
		screenUp = screenDown = false;
		messageCode = 0;
		canShowMessage = false;
		autoShowMessage = false;
		havePlayedAutoMessage = false;
		showMaginifierFlag = false;
		showMessageIconFlag = false;
		messageCounter = 1;
		messageSize = 4;
		messageEndFlag = false;
	}
	void MapS6::setPos(int x, int y, int n)
	{
		int gridX = x / 20;
		int gridY = y / 20;
		mapGrid[gridX][gridY] = n;
	}
	bool MapS6::isEmpty(int x, int y) const
	{
		return (blockProperty(x, y) != 0);
	}
	bool MapS6::isPortal(int x, int y) const
	{
		return (blockProperty(x, y) == 2);
	}
	bool MapS6::isBridge(int x, int y) const
	{
		return (blockProperty(x, y) == 3);
	}
	bool MapS6::isCraftTable(int x, int y) const
	{
		return (blockProperty(x, y) == 4);
	}
	bool MapS6::isTrashCan(int x, int y) const
	{
		return (blockProperty(x, y) == 5);
	}
	bool MapS6::isGetHurtPlace(int x, int y) const
	{
		return false;
	}
	int MapS6::blockProperty(int x, int y) const
	{
		int gridX = x / 20;
		int gridY = y / 20;
		return mapGrid[gridX][gridY];
	}
	void MapS6::onShow()
	{
		map.SetTopLeft(getSX(), getSY());
		map.ShowBitmap();
		if (bossAssistantExist)
		{
			bossAssistant.SetTopLeft(3616 + getSX(), 458 + getSY());
			bossAssistant.ShowBitmap();
		}
		syMoving(targetSY);
		if (getPortalOpen())
		{
			if (characterX < 500)
			{
				exitBitmap.SetTopLeft(143 + getSX(), 280);
				pressEBitmap.SetTopLeft(600, 655);
			}
			else
			{
				exitBitmap.SetTopLeft(3614 + getSX(), 255);
				pressEBitmap.SetTopLeft(600, 625);
			}
			exitBitmap.ShowBitmap();
			pressEBitmap.ShowBitmap();
		}
		if (getCraftTableOpen())
		{
			craftingBitmap.SetTopLeft(3165 + getSX(), 280);
			craftingBitmap.ShowBitmap();
			pressEBitmap.SetTopLeft(600, 625);
			pressEBitmap.ShowBitmap();
		}
		if (!getTrashCanOpen())
		{
			trashCanClosedBitmap.SetTopLeft(2770 + getSX(), 664 - 132 + getSY());
			trashCanClosedBitmap.ShowBitmap();
		}
		else
		{
			trashCanOpenBitmap.SetTopLeft(2770 + getSX(), 664 - 180 + getSY());
			trashCanOpenBitmap.ShowBitmap();
		}
	}
	void MapS6::syMoving(int y)
	{
		if (screenUp)
		{
			if (getSY() - 15 > y)
			{
				addSY(-15);
			}
			else
			{
				addSY(y - getSY());
				screenUp = false;
			}
		}
		else if (screenDown)
		{
			if (getSY() + 15 < y)
			{
				addSY(15);
			}
			else
			{
				screenDown = false;
				addSY(y - getSY());
			}
		}
	}
	void MapS6::monsterFloorChanging(int x)
	{
		if (x < 895)
			setMonsterFloor(760);
		else if (x < 2076)
			setMonsterFloor(744);
		else
			setMonsterFloor(566);
	}
	void MapS6::characterFloorAndCeiling()
	{
		if (characterX < 895)
			setFloor(760);
		else if (characterX < 2076)
		{
			setFloor(744);
			if (getSY() != -260)
			{
				screenUp = true;
				targetSY = -260;
			}
		}
		else
		{
			setFloor(566);
			if (getSY() != -100)
			{
				screenDown = true;
				targetSY = -100;
			}
		}
		if (characterX < 460)
			setCeiling(420);
		else if (characterX < 1660)
			setCeiling(335);
		else
			setCeiling(100);
	}
	int MapS6::screenX(int x)
	{
		return x + getSX();
	}
	int MapS6::screenY(int y)
	{
		return y + getSY();
	}
	void MapS6::messageOnShow()
	{
		if (messageCounter == 1)
		{
			message01.SetTopLeft(173, 120);
			message01.ShowBitmap();
		}
		else if (messageCounter == 2)
		{
			message02.SetTopLeft(173, 120);
			message02.ShowBitmap();
		}
		else if (messageCounter == 3)
		{
			message03.SetTopLeft(173, 120);
			message03.ShowBitmap();
		}
		else if (messageCounter == 4)
		{
			message04.SetTopLeft(173, 120);
			message04.ShowBitmap();
			messageEndFlag = true;
		}
	}
	void MapS6::setBossAssistantExist(bool flag)
	{
		bossAssistantExist = flag;
	}
	bool MapS6::getBossAssistantExist()
	{
		return bossAssistantExist;
	}
}