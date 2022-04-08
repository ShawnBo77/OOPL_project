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
		full_hp = 0;
	}

	void BloodBar::setFullHP(int n)
	{
		full_hp = n;
	}

	void BloodBar::setXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	int BloodBar::getFullHP()
	{
		return (int)full_hp;
	}

	void BloodBar::loadBloodBar()
	{
		blood_bar[0].LoadBitmap(IDB_BLOOD1, RGB(0, 0, 0));
		blood_bar[1].LoadBitmap(IDB_BLOOD2, RGB(0, 0, 0));
		blood_bar[2].LoadBitmap(IDB_BLOOD3, RGB(0, 0, 0));
		blood_bar[3].LoadBitmap(IDB_BLOOD4, RGB(0, 0, 0));
		blood_bar[4].LoadBitmap(IDB_BLOOD5, RGB(0, 0, 0));
		blood_bar[5].LoadBitmap(IDB_BLOOD6, RGB(0, 0, 0));
		blood_bar[6].LoadBitmap(IDB_BLOOD7, RGB(0, 0, 0));
		blood_bar[7].LoadBitmap(IDB_BLOOD8, RGB(0, 0, 0));
		blood_bar[8].LoadBitmap(IDB_BLOOD9, RGB(0, 0, 0));
		blood_bar[9].LoadBitmap(IDB_BLOOD10, RGB(0, 0, 0));
	}

	void BloodBar::showBloodBar(Map* m, int hp)
	{ //  現在血量/滿血血量  的比例 決定血條多長 顯示哪個血條bitmap
		if (hp >= full_hp)
		{
			setFullHP(hp);
		}
		double proportion = hp / full_hp;
		if (proportion < 1.0 / 10)
		{
			blood_bar[0].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[0].ShowBitmap();
		}
		else if (proportion < 2.0 / 10)
		{
			blood_bar[1].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[1].ShowBitmap();
		}
		else if (proportion < 3.0 / 10)
		{
			blood_bar[2].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[2].ShowBitmap();
		}
		else if (proportion < 4.0 / 10)
		{
			blood_bar[3].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[3].ShowBitmap();
		}
		else if (proportion < 5.0 / 10)
		{
			blood_bar[4].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[4].ShowBitmap();
		}
		else if (proportion < 6.0 / 10)
		{
			blood_bar[5].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[5].ShowBitmap();
		}
		else if (proportion < 7.0 / 10)
		{
			blood_bar[6].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[6].ShowBitmap();
		}
		else if (proportion < 8.0 / 10)
		{
			blood_bar[7].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[7].ShowBitmap();
		}
		else if (proportion < 9.0 / 10)
		{
			blood_bar[8].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[8].ShowBitmap();
		}
		else
		{
			blood_bar[9].SetTopLeft(m->screenX(_x), m->screenY(_y - 20));
			blood_bar[9].ShowBitmap();
		}
	}
}