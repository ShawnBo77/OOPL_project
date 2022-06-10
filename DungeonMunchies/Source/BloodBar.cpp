#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Map.h"
#include "BloodBar.h"

namespace game_framework
{
	BloodBar::BloodBar()
	{
		_x = 0;
		_y = 0;
		maxHp = 0;
	}

	void BloodBar::setFullHP(int n)
	{
		maxHp = n;
	}

	void BloodBar::setXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	int BloodBar::getFullHP()
	{
		return (int)maxHp;
	}

	void BloodBar::LoadBitmap()
	{
		bloodBar[0].LoadBitmap(IDB_BLOOD1, RGB(0, 0, 0));
		bloodBar[1].LoadBitmap(IDB_BLOOD2, RGB(0, 0, 0));
		bloodBar[2].LoadBitmap(IDB_BLOOD3, RGB(0, 0, 0));
		bloodBar[3].LoadBitmap(IDB_BLOOD4, RGB(0, 0, 0));
		bloodBar[4].LoadBitmap(IDB_BLOOD5, RGB(0, 0, 0));
		bloodBar[5].LoadBitmap(IDB_BLOOD6, RGB(0, 0, 0));
		bloodBar[6].LoadBitmap(IDB_BLOOD7, RGB(0, 0, 0));
		bloodBar[7].LoadBitmap(IDB_BLOOD8, RGB(0, 0, 0));
		bloodBar[8].LoadBitmap(IDB_BLOOD9, RGB(0, 0, 0));
		bloodBar[9].LoadBitmap(IDB_BLOOD10, RGB(0, 0, 0));
	}

	void BloodBar::showBloodBar(Map* m, int hp)
	{ //  現在血量/滿血血量  的比例 決定血條多長 顯示哪個血條bitmap
		if (hp >= maxHp)
		{
			setFullHP(hp);
		}
		double proportion = hp / maxHp;
		if (proportion <= 1.0 / 10)
		{
			bloodBar[0].SetTopLeft(_x, _y - 20);
			bloodBar[0].ShowBitmap();
		}
		else if (proportion <= 2.0 / 10)
		{
			bloodBar[1].SetTopLeft(_x, _y - 20);
			bloodBar[1].ShowBitmap();
		}
		else if (proportion <= 3.0 / 10)
		{
			bloodBar[2].SetTopLeft(_x, _y - 20);
			bloodBar[2].ShowBitmap();
		}
		else if (proportion <= 4.0 / 10)
		{
			bloodBar[3].SetTopLeft(_x, _y - 20);
			bloodBar[3].ShowBitmap();
		}
		else if (proportion <= 5.0 / 10)
		{
			bloodBar[4].SetTopLeft(_x, _y - 20);
			bloodBar[4].ShowBitmap();
		}
		else if (proportion <= 6.0 / 10)
		{
			bloodBar[5].SetTopLeft(_x, _y - 20);
			bloodBar[5].ShowBitmap();
		}
		else if (proportion <= 7.0 / 10)
		{
			bloodBar[6].SetTopLeft(_x, _y - 20);
			bloodBar[6].ShowBitmap();
		}
		else if (proportion <= 8.0 / 10)
		{
			bloodBar[7].SetTopLeft(_x, _y - 20);
			bloodBar[7].ShowBitmap();
		}
		else if (proportion <= 9.0 / 10)
		{
			bloodBar[8].SetTopLeft(_x, _y - 20);
			bloodBar[8].ShowBitmap();
		}
		else
		{
			bloodBar[9].SetTopLeft(_x, _y-20);
			bloodBar[9].ShowBitmap();
		}
	}
}