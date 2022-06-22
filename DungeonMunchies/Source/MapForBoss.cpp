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
	MapForBoss::MapForBoss() : Map(0, 0) //地圖設置：0為不能走、1為可以走、2為傳送門、3為橋、4為鍛造台、5為垃圾桶、6為受傷區域
	{
		X = 0;
		Y = 0;
		gridW = 40;
		gridH = 40;
		setFloor(600);
		setMonsterFloor(560);
		int mapGrid_init[40][18];
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				mapGrid_init[i][j] = 0;
			}
		}
		//給予地圖左上角座標及每張小圖寬度
		for (int i = 2; i < 30; i++)
		{
			for (int j = 5; j < 16; j++)
			{
				mapGrid_init[i][j] = 1;
			}
		}
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 18; j++) {
				mapGrid[i][j] = mapGrid_init[i][j]; //依序填入mapGrid
			}
		}
	}
	MapForBoss::~MapForBoss()
	{
	}
	void MapForBoss::LoadBitmap()
	{
		map.LoadBitmap(IDB_MAPFORBOSS);
	}
	void MapForBoss::Initialize()
	{
		setXY(0, 0);
		setInitialXY(0, 0);
		setScreenMoving(false);
		setMapName("MapForBoss");
		startX = 100;
		messageCode = 0;
		canShowMessage = false;
		autoShowMessage = false;
		havePlayedAutoMessage = false;
		showMaginifierFlag = false;
		showMessageIconFlag = false;
		messageCounter = 1;
		messageSize = 0;
		messageEndFlag = false;
	}
	void MapForBoss::setPos(int x, int y, int n)
	{
		int gridX = x / 40;
		int gridY = y / 40;
		mapGrid[gridX][gridY] = n;
	}
	bool MapForBoss::isEmpty(int x, int y) const
	{
		int gridX = x / 40;
		int gridY = y / 40;
		if (mapGrid[gridX][gridY] != 0)
		{
			return true;
		}
		return false;
	}
	bool MapForBoss::isPortal(int x, int y) const
	{
		int gridX = x / 40;
		int gridY = y / 40;
		if (mapGrid[gridX][gridY] == 2)
		{
			return true;
		}
		return false;
	}
	bool MapForBoss::isBridge(int x, int y) const
	{
		int gridX = x / 40;
		int gridY = y / 40;
		if (mapGrid[gridX][gridY] == 3)
		{
			return true;
		}
		return false;
	}
	bool MapForBoss::isCraftTable(int x, int y) const
	{
		return false;
	}
	bool MapForBoss::isTrashCan(int x, int y) const
	{
		return false;
	}
	bool MapForBoss::isGetHurtPlace(int x, int y) const
	{
		return false;
	}
	void MapForBoss::onShow() {
		map.SetTopLeft(getSX(), getSY() + 20);
		map.ShowBitmap();
	}
	void MapForBoss::monsterFloorChanging(int x)
	{
		setMonsterFloor(600);
	}
	int MapForBoss::screenX(int x)
	{
		return x + getSX();
	}
	int MapForBoss::screenY(int y)
	{
		return y + getSY();
	}
}