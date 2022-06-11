#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "MapS1.h"
#include <vector>

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

	MapS1::MapS1() : Map(0, 0) //地圖設置：0為不能走、1為可以走、2為傳送門(transGate)
	{
		X = 40;
		Y = 40;
		gridW = 40;
		gridH = 40;
		setFloor(680);
		setMonsterFloor(680);
		int mapGrid_init[100][18];
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		//給予地圖左上角座標及每張小圖寬度
		for (int i = 2; i < 45; i++)
		{
			for (int j = 1; j < 17; j++)
			{
				mapGrid_init[i][j] = 1;
			}
		}

		for (int i = 45; i < 60; i++)
		{
			for (int j = 1; j < 16; j++)
			{
				mapGrid_init[i][j] = 1;
			}
		}

		for (int i = 60; i < 71; i++)
		{
			for (int j = 1; j < 12; j++)
			{
				mapGrid_init[i][j] = 1;
			}
		}

		for (int j = 1; j < 10; j++)
		{
			mapGrid_init[52][j] = 0;
		}

		for (int i = 60; i < 65; i++)
		{
			for (int j = 5; j < 12; j++)
			{
				mapGrid_init[i][j] = 2;
			}
		}

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				mapGrid[i][j] = mapGrid_init[i][j]; //依序填入mapGrid
			}
		}
	}

	MapS1::~MapS1()
	{
	}

	void MapS1::LoadBitmap()
	{
		//white.LoadBitmap(IDB_WHITE);
		//blue.LoadBitmap(IDB_BLUE);
		map.LoadBitmap(".\\res\\map01.bmp");
		exitBitmap.LoadBitmap(IDB_EXIT, RGB(0, 0, 0));
		pressEBitmap.LoadBitmap(IDB_PRESSE, RGB(0, 0, 0));
		message01.LoadBitmap(".\\res\\message0101.bmp");
		message02.LoadBitmap(".\\res\\message0102.bmp");
		message03.LoadBitmap(".\\res\\message0103.bmp");
		message04.LoadBitmap(".\\res\\message0104.bmp");
		//messages.push_back(message01);
		//messages.push_back(message02);
		//messages.push_back(message03);
		//messages.push_back(message04);
		loadMagnifierBitmap();
		loadMessageIconBitmap();
	}

	void MapS1::Initialize()
	{
		setXY(-410, -320);
		setInitialXY(-410, -320);
		setScreenMoving(true);
		setMapName("MapS1");
		setStartPosition(335);
		messageCode = 0;
		canShowMessage = false;
		showMaginifierFlag = false;
		//isMessageShowing = false;
		showMessageIconFlag = false;
		messageCounter = 1;
		messageSize = 4;
		messageEndFlag = false;
	}

	void MapS1::setPos(int x, int y, int n)
	{
		int gridX = x / 40;
		int gridY = y / 40;
		mapGrid[gridX][gridY] = n;
	}

	bool MapS1::isEmpty(int x, int y) const
	{
		int gridX = x / 40;
		int gridY = y / 40;
		if (mapGrid[gridX][gridY] != 0)
		{
			return true;
		}
		return false;
	}

	bool MapS1::isPortal(int x, int y) const
	{
		int gridX = x / 40;
		int gridY = y / 40;
		if (mapGrid[gridX][gridY] == 2)
		{
			return true;
		}
		return false;
	}

	bool MapS1::isBridge(int x, int y) const
	{
		int gridX = x / 40;
		int gridY = y / 40;
		if (mapGrid[gridX][gridY] == 3)
		{
			return true;
		}
		return false;
	}

	bool MapS1::isCraftTable(int x, int y) const
	{
		return false;
	}

	bool MapS1::isTrashCan(int x, int y) const
	{
		return false;
	}

	bool MapS1::isGetHurtPlace(int x, int y) const
	{
		return false;
	}

	void MapS1::onShow()
	{
		map.SetTopLeft(getSX(), getSY());
		map.ShowBitmap();

		if (getPortalOpen())
		{
			exitBitmap.SetTopLeft(2895 + getSX(), 180);
			exitBitmap.ShowBitmap();
			pressEBitmap.SetTopLeft(600, 620);
			pressEBitmap.ShowBitmap();
		}

		if (getShowMaginifierFlag())
		{
			showMaginifier(1615, 845);
		}

		if (getSX() > -1502)
		{
			setFloor(680);
		}
		else if (getSX() > -2081)
		{
			setFloor(600);
		}
		else
		{
			setFloor(460);
		}

		if (getSX() > -425)
		{
			setCeiling(0);
		}
		else if (getSX() > -1865)
		{
			setCeiling(420);
		}
		else
		{
			setCeiling(0);
		}

		for (int i = 0; i < 18; i++)
		{ //往右顯示六張圖
			for (int j = 0; j < 100; j++)
			{ //往下顯示四張圖
				switch (mapGrid[j][i])
				{
				case 0:
					//blue.SetTopLeft(X + (gridW * j), Y + (gridH * i)); //設定每張圖的座標
					//blue.ShowBitmap(); // 顯示設定完的座標
					break;
				case 1:
					//white.SetTopLeft(X + (gridW * j), Y + (gridH * i)); //設定每張圖的座標
					//white.ShowBitmap(); //顯示設定完的座標
					break;
				case 2:
					//blue.SetTopLeft(X + (gridW * i), Y + (gridH * j)); //設定每張圖的座標
					//blue.ShowBitmap(); // 顯示設定完的座標
					break;
				default:
					ASSERT(0); //mapGrid陣列不該出現0,1,2之外的值
				}
			}
		}
	}

	
	void MapS1::monsterFloorChanging(int x)
	{
		if (x < 1750)
		{
			setMonsterFloor(680);
		}
		else if (x < 2500)
		{
			setMonsterFloor(600);
		}
		else
		{
			setMonsterFloor(500);
		}
	}
	int MapS1::screenX(int x)
	{
		return x + getSX();
	}
	int MapS1::screenY(int y)
	{
		return y + getSY();
	}

	void MapS1::messageOnShow()
	{
		if (messageCounter == 1)
		{
			message01.SetTopLeft(173, 535);
			message01.ShowBitmap();
		}
		else if (messageCounter == 2)
		{
			message02.SetTopLeft(173, 535);
			message02.ShowBitmap();
		}
		else if (messageCounter == 3)
		{
			message03.SetTopLeft(173, 535);
			message03.ShowBitmap();
		}
		else if (messageCounter == 4)
		{
			message04.SetTopLeft(173, 535);
			message04.ShowBitmap();
			messageEndFlag = true;
		}
	}
}