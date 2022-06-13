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
        startX = 200;
        finalX = 4350;
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
        for (int i = 0; i < 400; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }
        for (int i = 0; i < 91; i++)
        {
            for (int j = 31; j < 70; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 70; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }
        for (int i = 2; i < 12; i++)
        {
            for (int j = 18; j < 31; j++)
            {
                mapGrid_init[i][j] = 2;
            }
        }
        for (int i = 27; i < 91; i++)
        {
            for (int j = 25; j < 31; j++)
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
        for (int i = 91; i < 400; i++)
        {
            for (int j = 33; j < 70; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }
        for (int i = 152; i < 163; i++)
        {
            for (int j = 0; j < 70; j++)
            {
                mapGrid_init[i][j] = 5;
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
        trashCanClosedBitmap.LoadBitmap(IDB_TRASHCANCLOSED, RGB(0, 0, 0));
        trashCanOpenBitmap.LoadBitmap(IDB_TRASHCANOPEN, RGB(0, 0, 0));
        craftingBitmap.LoadBitmap(IDB_CRAFTING, RGB(0, 0, 0));
        loadMagnifierBitmap();
        loadMessageIconBitmap();
        message01.LoadBitmap(".\\res\\message0201.bmp", RGB(0, 0, 0));
        message02.LoadBitmap(".\\res\\message0202.bmp", RGB(0, 0, 0));
        message03.LoadBitmap(".\\res\\message0203.bmp", RGB(0, 0, 0));
        message04.LoadBitmap(".\\res\\message0204.bmp", RGB(0, 0, 0));
        message05.LoadBitmap(".\\res\\message0205.bmp", RGB(0, 0, 0));
        message06.LoadBitmap(".\\res\\message0206.bmp", RGB(0, 0, 0));
    }

    void MapS3::Initialize()
    {
        setXY(0, -260);
        setInitialXY(0, -260);
        setScreenMoving(true);
        setMapName("MapS3");
        setCeiling(0);
        previousFloor = 0;
        trashCanOpen = false;
        screenUp = screenDown = false;
        messageCode = 0;
        showMaginifierFlag = false;
        showMessageIconFlag = false;
        canShowMessage = false;
        messageCounter = 1;
        messageSize = 6;
        messageEndFlag = false;
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

    bool MapS3::isTrashCan(int x, int y) const
    {
        return (blockProperty(x, y) == 5);
    }

    bool MapS3::isGetHurtPlace(int x, int y) const
    {
        return false;
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

        if (!getTrashCanOpen()) 
        {
            trashCanClosedBitmap.SetTopLeft(3025 + getSX(), getFloor() - 132);
            trashCanClosedBitmap.ShowBitmap();
        }
        else
        {
            trashCanOpenBitmap.SetTopLeft(3025 + getSX(), getFloor() - 180);
            trashCanOpenBitmap.ShowBitmap();
        }

        if (getShowMessageIconFlag())
        {
            showMessageIcon(3410, 705);
            pressEBitmap.SetTopLeft(600, 940 + getSY());
            pressEBitmap.ShowBitmap();
        }

        if (getPortalOpen())
        {
            if (characterX < 500)
                exitBitmap.SetTopLeft(100 + getSX(), 370);
            else
                exitBitmap.SetTopLeft(4345 + getSX(), 400);

            pressEBitmap.SetTopLeft(600, 940 + getSY());
            exitBitmap.ShowBitmap();
            pressEBitmap.ShowBitmap();
        }

        if (getCraftTableOpen())
        {
            craftingBitmap.SetTopLeft(3880 + getSX(), 280);
            craftingBitmap.ShowBitmap();
            pressEBitmap.SetTopLeft(600, 940 + getSY());
            pressEBitmap.ShowBitmap();
        }
    }

    void MapS3::monsterFloorChanging(int x)
    {
        if (x < 502)
        {
            setMonsterFloor(610);
        }
        else if (x < 1840)
        {
            setMonsterFloor(485);
        }
        else
        {
            setMonsterFloor(655);
        }
    }

    void MapS3::characterFloorAndCeiling()
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
    void MapS3::messageOnShow()
    {
        int mX = 136, mY = 201;
        if (messageCounter == 1)
        {
            message01.SetTopLeft(mX, mY);
            message01.ShowBitmap();
        }
        else if (messageCounter == 2)
        {
            message02.SetTopLeft(mX, mY);
            message02.ShowBitmap();
        }
        else if (messageCounter == 3)
        {
            message03.SetTopLeft(mX, mY);
            message03.ShowBitmap();
        }
        else if (messageCounter == 4)
        {
            message04.SetTopLeft(mX, mY);
            message04.ShowBitmap();
        }
        else if (messageCounter == 5)
        {
            message05.SetTopLeft(mX, mY);
            message05.ShowBitmap();
        }
        else if (messageCounter == 6)
        {
            message06.SetTopLeft(mX, mY);
            message06.ShowBitmap();
            messageEndFlag = true;
        }
    }
}