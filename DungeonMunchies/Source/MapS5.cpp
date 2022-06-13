#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "MapS5.h"
#include <vector>

namespace game_framework
{
    /////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

    MapS5::MapS5() : Map(0, 0) //地圖設置：0為不能走、1為可以走、2為傳送門(transGate)
    {
        X = 20;
        Y = 20;
        gridW = 20;
        gridH = 20;
        setFloor(517);
        setCeiling(0);
        setMonsterFloor(517);
        int mapGrid_init[400][70];
        for (int i = 2; i < 400; i++)
        {
            for (int j = 0; j < 70; j++)
            {
                mapGrid_init[i][j] = 1;
            }
        }
        //給予地圖左上角座標及每張小圖寬度
        for (int i = 0; i < 400; i++)
        {
            for (int j = 66; j < 70; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 0; i < 400; i++)
        {
            for (int j = 0; j < 43; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 3; i < 28; i++)
        {
            for (int j = 43; j < 66; j++)
            {
                mapGrid_init[i][j] = 2;
            }
        }

        for (int i = 47; i < 92; i++)
        {
            for (int j = 61; j < 70; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 48; i < 59; i++)
        {
            for (int j = 43; j < 61; j++)
            {
                mapGrid_init[i][j] = 5;
            }
        }

        for (int i = 66; i < 89; i++)
        {
            for (int j = 43; j < 52; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 58; i < 90; i++)
        {
            for (int j = 13; j < 32; j++)
            {
                mapGrid_init[i][j] = 1;
            }
        }

        for (int i = 58; i < 74; i++)
        {
            for (int j = 13; j < 32; j++)
            {
                mapGrid_init[i][j] = 2;
            }
        }

        for (int i = 90; i < 99; i++)
        {
            for (int j = 13; j < 43; j++)
            {
                mapGrid_init[i][j] = 1;
            }
        }

        for (int i = 90; i < 97; i++)
        {
            mapGrid_init[i][40] = 3;
            mapGrid_init[i][47] = 3;
        }

        for (int i = 99; i < 400; i++)
        {
            for (int j = 43; j < 48; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 132; i < 400; i++)
        {
            for (int j = 61; j < 70; j++)
            {
                mapGrid_init[i][j] = 0;
            }
        }

        for (int i = 137; i < 148; i++)
        {
            for (int j = 49; j < 61; j++)
            {
                mapGrid_init[i][j] = 4;
            }
        }

        for (int i = 157; i < 179; i++)
        {
            for (int j = 49; j < 61; j++)
            {
                mapGrid_init[i][j] = 2;
            }
        }

        for (int i = 179; i < 400; i++)
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

    MapS5::~MapS5()
    {
    }

    void MapS5::LoadBitmap()
    {
        //white.LoadBitmap(IDB_WHITE);
        //blue.LoadBitmap(IDB_BLUE);
        map.LoadBitmap(".\\res\\map05.bmp");
        exitBitmap.LoadBitmap(IDB_EXIT, RGB(0, 0, 0));
        pressEBitmap.LoadBitmap(IDB_PRESSE, RGB(0, 0, 0));
        craftingBitmap.LoadBitmap(IDB_CRAFTING, RGB(0, 0, 0));
        trashCanClosedBitmap.LoadBitmap(IDB_TRASHCANCLOSED, RGB(0, 0, 0));
        trashCanOpenBitmap.LoadBitmap(IDB_TRASHCANOPEN, RGB(0, 0, 0));
        loadMagnifierBitmap();
        loadMessageIconBitmap();
    }

    void MapS5::Initialize()
    {
        setXY(65, -800);
        setInitialXY(65, 0);
        setScreenMoving(true);
        setMapName("MapS5");
        setCeiling(0);
        setStartPosition(100);
        trashCanOpen = false;
        previousFloor = 0;
        targetSY = 0;
        screenUp = screenDown = false;
        messageCode = 0;
        //isMessageShowing = false;
    }

    void MapS5::setPos(int x, int y, int n)
    {
        int gridX = x / 20;
        int gridY = y / 20;
        mapGrid[gridX][gridY] = n;
    }

    bool MapS5::isEmpty(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] != 0)
        {
            return true;
        }
        return false;
    }

    bool MapS5::isPortal(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] == 2)
        {
            return true;
        }
        return false;
    }

    bool MapS5::isBridge(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] == 3)
        {
            return true;
        }
        return false;
    }

    bool MapS5::isCraftTable(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] == 4)
        {
            return true;
        }
        return false;
    }

    bool MapS5::isTrashCan(int x, int y) const
    {
        int gridX = x / 20;
        int gridY = y / 20;
        if (mapGrid[gridX][gridY] == 5)
        {
            return true;
        }
        return false;
    }

    bool MapS5::isGetHurtPlace(int x, int y) const
    {
        return false;
    }

    void MapS5::onShow()
    {
        map.SetTopLeft(getSX(), getSY());
        map.ShowBitmap();
        syMoving(targetSY);

        if (getPortalOpen())
        {
            if (characterX > 1580) 
            {
                exitBitmap.SetTopLeft(3170 + getSX(), 120);
                exitBitmap.ShowBitmap();
            }
            else if (characterX > 1000)
            {
                exitBitmap.SetTopLeft(1155 + getSX(), 250);
                exitBitmap.ShowBitmap();
            }
            else
            {
                exitBitmap.SetTopLeft(230, 250);
                exitBitmap.ShowBitmap();
            }
            pressEBitmap.SetTopLeft(600, 585);
            pressEBitmap.ShowBitmap();
        }

        if (getCraftTableOpen())
        {
            craftingBitmap.SetTopLeft(2760 + getSX(), 175);
            craftingBitmap.ShowBitmap();
            pressEBitmap.SetTopLeft(600, 585);
            pressEBitmap.ShowBitmap();
        }

        if (!getTrashCanOpen())
        {
            trashCanClosedBitmap.SetTopLeft(860 + getSX(), 1217 - 132 + getSY());
            trashCanClosedBitmap.ShowBitmap();
        }
        else
        {
            trashCanOpenBitmap.SetTopLeft(860 + getSX(), 1217 - 180 + getSY());
            trashCanOpenBitmap.ShowBitmap();
        }
    }

    void MapS5::syMoving(int y)
    {
        if (screenUp)
        {
            if (getSY() - 20 > y)
            {
                addSY(-20);
            }
            else
            {
                screenUp = false;
                addSY(getSY() - y);
            }
        }

        if (screenUp)
        {
            if (getSY() - 20 > y)
            {
                addSY(-20);
            }
            else
            {
                screenUp = false;
                addSY(y - getSY());
            }
        }
        else if (screenDown)
        {
            if (getSY() + 20 < y)
            {
                addSY(20);
            }
            else
            {
                screenDown = false;
                addSY(y - getSY());
            }
        }
    }

    void MapS5::monsterFloorChanging(int x)
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

    void MapS5::characterFloorAndCeiling()
    {
        //floor
        if (characterX > 1000 && characterX < 1840 && characterY + 120 < 649)
            setFloor(640);
        else if (characterX < 920)
            setFloor(1317);
        else if (characterX < 1875)
        {
            if (characterX > 1810 && characterY + 120 < 822)
            {
                setFloor(813);
                if (getSY() != -100)
                {
                    screenDown = true;
                    targetSY = -100;
                }
                previousFloor = 813;
            }
            else if (characterX > 1810 && characterY + 120 < 954)
            {
                setFloor(945);
                if (getSY() != -450)
                {
                    if (previousFloor == 1217)
                        screenDown = true;
                    else
                        screenUp = true;
                    targetSY = -450;
                }
            }
            else
            {
                setFloor(1217);
                if (getSY() != -800)
                {
                    screenUp = true;
                    targetSY = -800;
                }
                previousFloor = 1217;
            }  
        }
        else if (characterX < 2625)
        {
            if (characterX < 1910 && characterY + 120 < 822)
            {
                setFloor(813);
                if (getSY() != -100)
                {
                    screenDown = true;
                    targetSY = -100;
                }
                previousFloor = 945;
            }
            else
            {
                setFloor(1287);
                if (getSY() != -800)
                {
                    screenUp = true;
                    targetSY = -800;
                }
            }
        }
        else
            setFloor(1217);

        //ceiling
        if (characterX < 1290 && characterY > 700)
            setCeiling(875);
        else if (characterX < 1820 && characterY > 700)
            setCeiling(1040);
        else if (characterX < 1980)
            setCeiling(260);
        else
            setCeiling(975);
    }

    int MapS5::screenX(int x)
    {
        return x + getSX();
    }
    int MapS5::screenY(int y)
    {
        return y + getSY();
    }
}