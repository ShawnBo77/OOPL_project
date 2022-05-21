#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "MapS2.h"
#include <vector>

namespace game_framework
{
    /////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

    MapS2::MapS2() : Map(0, 0) //地圖設置：0為不能走、1為可以走、2為傳送門(transGate)
    {
        X = 20;
        Y = 20;
        gridW = 20;
        gridH = 20;
        setFloor(500);
        setMonsterFloor(500);
        int mapGrid_init[200][36];
        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 36; j++)
            {
                mapGrid_init[i][j] = 1;
            }
        }
        //給予地圖左上角座標及每張小圖寬度
        for (int i = 0; i < 11; i++)
        {
            for (int j = 25; j < 36; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 27; i < 77; i++)
        {
            for (int j = 20; j < 36; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 77; i < 93; i++)
        {  
            mapGrid_init[i][27] = 3;
            mapGrid_init[i][34] = 3;
        }

        //for (int i = 45; i < 60; i++)
        //{
        //    for (int j = 1; j < 15; j++)
        //    {
        //        mapGrid_init[i][j] = 1;
        //    }
        //}

        //for (int i = 60; i < 71; i++)
        //{
        //    for (int j = 1; j < 11; j++)
        //    {
        //        mapGrid_init[i][j] = 1;
        //    }
        //}

        //for (int j = 1; j < 9; j++) {
        //    mapGrid_init[52][j] = 0;
        //}

        //for (int i = 60; i < 65; i++)
        //{
        //    for (int j = 5; j < 11; j++)
        //    {
        //        mapGrid_init[i][j] = 2;
        //    }
        //}

        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 36; j++)
            {
                mapGrid[i][j] = mapGrid_init[i][j]; //依序填入mapGrid
            }
        }
    }

    MapS2::~MapS2()
    {
    }

    void MapS2::LoadBitmap()
    {
        //white.LoadBitmap(IDB_WHITE);
        //blue.LoadBitmap(IDB_BLUE);
        map.LoadBitmap(".\\res\\map02.bmp");
        exitBitmap.LoadBitmap(IDB_EXIT, RGB(0, 0, 0));
        pressEBitmap.LoadBitmap(IDB_PRESSE, RGB(0, 0, 0));
    }

    void MapS2::Initialize()
    {
        setXY(-100, -260);
        setScreenMoving(true);
        setMapName("MapS2");
        setStartPosition(100);
    }

    void MapS2::setPos(int x, int y, int n)
    {
        int gridX = x / 20;
        int gridY = y / 20;
        mapGrid[gridX][gridY] = n;
    }

    bool MapS2::isEmpty(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] != 0)
        {
            return true;
        }
        return false;
    }

    bool MapS2::isPortal(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] == 2)
        {
            return true;
        }
        return false;
    }

    bool MapS2::isBridge(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] == 3)
        {
            return true;
        }
        return false;
    }

    void MapS2::onShow()
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
    }

    void MapS2::setCharacterX(int x)
    {
        characterX = x;
    }
    void MapS2::setCharacterY(int y)
    {
        characterY = y;
    }
    void MapS2::monsterFloorChanging(int x)
    {
        if (x < 1750)
        {
            setMonsterFloor(640);
        }
        else if (x < 2500)
        {
            setMonsterFloor(560);
        }
        else
        {
            setMonsterFloor(460);
        }
    }

    void MapS2::characterFloorChanging()
    {
        if (characterX < 218)
        {
            setFloor(500);
        }
        else if (characterX < 410)
        {
            setFloor(640);
        }
        else if (characterX < 500)
        {
            if (characterY > 382)
                setFloor(640);
            else
                setFloor(460);
        }
        else if (characterX < 1538)
        {
            setFloor(400);
            setCeiling(265);
        }
        else
        {
            if (characterY > 612)
                setFloor(900);
            else if (characterY > 462)
                setFloor(690);
            else
                setFloor(540);

        }
    }

    int MapS2::screenX(int x)
    {
        return x + getSX();
    }
    int MapS2::screenY(int y)
    {
        return y + getSY();
    }
}