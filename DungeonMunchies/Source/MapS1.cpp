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
        X = 0;
        Y = 0;
        gridW = 40;
        gridH = 40;
        setFloor(560);
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
            for (int j = 5; j < 15; j++)
            {
                mapGrid_init[i][j] = 1;
            }
        }

        for (int i = 0; i < 40; i++)
        {
            for (int j = 0; j < 18; j++)
            {
                mapGrid[i][j] = mapGrid_init[i][j]; //依序填入mapGrid
            }
        }
    }

    MapS1::~MapS1()
    {
    }

    void MapS1::Initialize()
    {
        setXY(0, 0);
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

    void MapS1::LoadBitmap()
    {
        //white.LoadBitmap(IDB_WHITE);
        //blue.LoadBitmap(IDB_BLUE);
        map.LoadBitmap(".\\res\\map01.bmp");
    }

    void MapS1::onShow()
    {
        map.SetTopLeft(getSX(), getSY() + 20);
        map.ShowBitmap();
        for (int i = 0; i < 18; i++)
        { //往右顯示六張圖
            for (int j = 0; j < 40; j++)
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

    void MapS1::setCharacterX(int x)
    {
        characterX = x;
    }
    void MapS1::setCharacterY(int y)
    {
        characterY = y;
    }
    int MapS1::screenX(int x)
    {
        return x + getSX();
    }
    int MapS1::screenY(int y)
    {
        return y + getSY();
    }
}