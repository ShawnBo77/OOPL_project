#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "MapS3.h"
#include <vector>

namespace game_framework
{
    /////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

    MapS3::MapS3() : Map(0, 0) //地圖設置：0為不能走、1為可以走、2為傳送門(transGate)
    {
        X = 20;
        Y = 20;
        gridW = 20;
        gridH = 20;
        setFloor(610);
        setCeiling(0);
        setMonsterFloor(610);
        int mapGrid_init[400][70];
        for (int i = 0; i < 400; i++)
        {
            for (int j = 0; j < 70; j++)
            {
                mapGrid_init[i][j] = 1;
            }
        }
        //給予地圖左上角座標及每張小圖寬度
        for (int i = 0; i < 19; i++)
        {
            for (int j = 0; j < 18; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }
        for (int i = 27; i < 92; i++)
        {
            for (int j = 25; j < 70; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }
        for (int i = 63; i < 400; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }
        for (int i = 190; i < 203; i++)
        {
            for (int j = 0; j < 70; j++)
            {
                mapGrid_init[i][j] = 4;
            }
        }
        for (int i = 210; i < 230; i++)
        {
            for (int j = 0; j < 70; j++)
            {
                mapGrid_init[i][j] = 2;
            }
        }
        for (int i = 230; i < 400; i++)
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

    MapS3::~MapS3()
    {
    }

    void MapS3::LoadBitmap()
    {
        //white.LoadBitmap(IDB_WHITE);
        //blue.LoadBitmap(IDB_BLUE);
        map.LoadBitmap(".\\res\\map03.bmp");
        exitBitmap.LoadBitmap(IDB_EXIT, RGB(0, 0, 0));
        pressEBitmap.LoadBitmap(IDB_PRESSE, RGB(0, 0, 0));
    }

    void MapS3::Initialize()
    {
        setXY(0, -260);
        setScreenMoving(true);
        setMapName("MapS3");
        setCeiling(0);
        setStartPosition(100);
        setCharacterYRelativeMovement(0);
        previousFloor = 0;
        targetSY = 0;
        screenUp = screenDown = false;
    }

    void MapS3::setPos(int x, int y, int n)
    {
        int gridX = x / 20;
        int gridY = y / 20;
        mapGrid[gridX][gridY] = n;
    }

    bool MapS3::isEmpty(int x, int y) const
    {
        
        return (blockProperty(x, y) != 0);
    }

    bool MapS3::isPortal(int x, int y) const
    {
        return (blockProperty(x, y) == 2);
    }

    bool MapS3::isBridge(int x, int y) const
    {
         return (blockProperty(x, y) == 3);
    }

    bool MapS3::isCraftTable(int x, int y) const
    {
        return (blockProperty(x, y) == 4);
    }

    int MapS3::blockProperty(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        return mapGrid[gridX][gridY];
    }

    void MapS3::onShow()
    {
        map.SetTopLeft(getSX(), getSY());
        map.ShowBitmap();
        syMoving(targetSY);

        if (getPortalOpen())
        {
            exitBitmap.SetTopLeft(4345 + getSX(), 400);
            exitBitmap.ShowBitmap();
            pressEBitmap.SetTopLeft(600, 680);
            pressEBitmap.ShowBitmap();
        }
        if (getCraftTableOpen())
        {
            pressEBitmap.SetTopLeft(600, 680);
            pressEBitmap.ShowBitmap();
        }
    }

    void MapS3::syMoving(int y)
    {
        if (screenUp)
        {
            if (getSY() - 20 > y)
            {
                addCharacterYRelativeMovement(20);
                addSY(-20);
            }
            else
            {
                screenUp = false;
                addCharacterYRelativeMovement(y - getSY());
                addSY(getSY() - y);
            }
        }

        if (screenUp)
        {
            if (getSY() - 20 > y)
            {
                addCharacterYRelativeMovement(20);
                addSY(-20);
            }
            else
            {
                screenUp = false;
                addCharacterYRelativeMovement(getSY() - y);
                addSY(y - getSY());
            }
        }
        else if (screenDown)
        {
            if (getSY() + 20 < y)
            {
                addCharacterYRelativeMovement(-20);
                addSY(20);
            }
            else
            {
                screenDown = false;
                addCharacterYRelativeMovement(getSY() - y);
                addSY(y - getSY());
            }
        }
    }

    void MapS3::setCharacterX(int x)
    {
        characterX = x;
    }
    void MapS3::setCharacterY(int y)
    {
        characterY = y;
    }
    void MapS3::monsterFloorChanging(int x)
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
            setMonsterFloor(880);
        }
    }

    void MapS3::characterFloorChanging()
    {
        if (characterX < 502)
        {
            setFloor(610);
        }
        else if (characterX < 1838)
        {
            setFloor(485);
        }
        else
        {
            setFloor(655);
        }

        if (characterX < 370)
        {
            setCeiling(360);
        }
        else if (characterX < 1220)
        {
            setCeiling(60);
        }
        else if (characterX < 1930)
        {
            setCeiling(230);
        }
        else
        {
            setCeiling(255);
        }
    }

    int MapS3::screenX(int x)
    {
        return x + getSX();
    }
    int MapS3::screenY(int y)
    {
        return y + getSY();
    }
}