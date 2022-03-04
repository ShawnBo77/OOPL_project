#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的角色人物物件
/////////////////////////////////////////////////////////////////////////////
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

	Map::Map()
		:X(20), Y(40), mapW(120), mapH(100) //給予地圖左上角座標及每張小圖寬度
	{
		int map_init[4][5] = { //給予地圖陣列初值
			{0,0,1,0,0},
			{0,1,2,1,0},
			{1,2,1,2,1},
			{2,1,2,1,2},
		};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++)
				map[i][j] = map_init[i][j]; //依序填入map
		}
	}

	void Map::LoadBitmap() {
		map1.LoadBitmap(IDB_BOSSMAP);
		map2.LoadBitmap(IDB_MAP2);
	}

	void Map::onShow() {
		for (int i = 0; i < 5; i++) { //往右顯示五張圖
			for (int j = 0; j < 4; j++) { //往下顯示四張圖
				switch (map[j][i]) {
				case 0:
					break;
				case 1:
					map1.SetTopLeft(X + (mapW * i), Y + (mapH * j)); //設定每張圖的座標
					map1.ShowBitmap(); //顯示設定完的座標
					break;
				case 2:
					map2.SetTopLeft(X + (mapW * i), Y + (mapH * j)); //設定每張圖的座標
					map2.ShowBitmap(); // 顯示設定完的座標
					break;
				default:
					ASSERT(0); //map陣列不該出現0,1,2之外的值
				}
			}
		}
	}
}