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

    MapForBoss::MapForBoss(): Map(0, 0) //地圖設置：0為不能走、1為可以走、2為傳送門(transGate)
    {
        X = 0;
        Y = 0;
        gridW = 60;
        gridH = 60;
       //給予地圖左上角座標及每張小圖寬度
        int mapGrid_init[4][6] = { //給予地圖陣列初值
            {0,0,0,0,0,0},
            {0,1,1,1,1,0},
            {0,1,1,1,1,0},
            {0,0,0,0,0,0},
        };
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                mapGrid[i][j] = mapGrid_init[i][j]; //依序填入mapGrid
            }
        }
    }

    MapForBoss::~MapForBoss()
    {
    }

    void MapForBoss::Initialize()
    {
        setXY(0, 0);
    }

    void MapForBoss::setPos(int x, int y, int n)
    {
        int gridX = x / 60;
        int gridY = y / 60;
        mapGrid[gridX][gridY] = n;
    }

    bool MapForBoss::isEmpty(int x, int y) const
    {
        int gridX = x / 60;
        int gridY = y / 60;
        if (mapGrid[gridX][gridY] != 0)
        {
            return true;
        }
        return false;
    }

    void MapForBoss::LoadBitmap() {
        white.LoadBitmap(IDB_WHITE);
        blue.LoadBitmap(IDB_BLUE);
        map.LoadBitmap(IDB_BOSSMAP);
    }

    void MapForBoss::onShow() {
        map.SetTopLeft(getSX(), getSY());
        map.ShowBitmap();
        for (int i = 0; i < 6; i++) { //往右顯示六張圖
            for (int j = 0; j < 4; j++) { //往下顯示四張圖
                switch (mapGrid[j][i]) {
                case 0:
                    blue.SetTopLeft(X + (gridW * j), Y + (gridH * i)); //設定每張圖的座標
                    blue.ShowBitmap(); // 顯示設定完的座標
                    break;
                case 1:
                    white.SetTopLeft(X + (gridW * j), Y + (gridH * i)); //設定每張圖的座標
                    white.ShowBitmap(); //顯示設定完的座標
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

    void MapForBoss::getCharacterX(int x)
    {
        characterX = x;
    }
    void MapForBoss::getCharacterY(int y)
    {
        characterY = y;
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