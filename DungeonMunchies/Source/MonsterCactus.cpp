#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#include "Character.h"
#include "BloodBar.h"
#include "Monster.h"
#include "MonsterCactus.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Cactus的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterCactus::MonsterCactus()
	{
		_x = 400;
		_y = 400;
		hp = 50;
		attackDamage = 5;
		BORDER = 20;
	}

	MonsterCactus::MonsterCactus(int x, int y, Character* c) : Monster(x, y, 50, 5, c)
	{
		BORDER = 20;
	}

	MonsterCactus::~MonsterCactus()
	{
	}

	void MonsterCactus::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		cactusAlive.LoadBitmap(IDB_MONSTERCACTUSALIVE, RGB(0, 0, 0));
		cactusDead.LoadBitmap(IDB_MONSTERCACTUSDEAD, RGB(0, 0, 0));
		sourceGrassFast.LoadBitmap(IDB_SOURCEGRASSFAST, RGB(0, 0, 0));
		black.LoadBitmap(IDB_BLACK, RGB(0, 0, 0));
	}

	void MonsterCactus::Initialize()
	{
		_x = init_x;
		_y = init_y;
		currentFloor = 0;
		hp = 50;
		attackDamage = 5;
		bloodBar.setFullHP(hp);
		hasGottenSource = false;
		lightBulbInside = 10;
		hasGottenLightBulb = false;
		canStandOn = true;
		isViolent = false;
		haveSetViolent = false;
	}

	void MonsterCactus::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow(m);
			}
			else
			{
				cactusAlive.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
				cactusAlive.ShowBitmap();
			}
			bloodBar.setXY(GetLeftX() + m->getXMovement(), GetTopY() + m->getYMovement() - 16);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		else
		{
			cactusDead.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement() + (cactusAlive.Height() - cactusDead.Height()));
			cactusDead.ShowBitmap();
			if (!hasGottenSource)
			{
				sourceGrassFast.SetTopLeft((GetLeftX() + GetRightX()) / 2 + m->getXMovement(), GetBottomY() - 64 + m->getYMovement());
				sourceGrassFast.ShowBitmap();
			}
		}
	}

	int MonsterCactus::GetLeftX()
	{
		return _x;
	}

	int MonsterCactus::GetTopY()
	{
		return _y;
	}

	int MonsterCactus::GetRightX()
	{
		return _x + cactusAlive.Width();
	}

	int MonsterCactus::GetBottomY()
	{
		return _y + cactusAlive.Height();
	}

	void MonsterCactus::OnMove(Map* m)
	{
		if (isViolent && !haveSetViolent)
		{
			hp = 1000;
			attackDamage = 1;
			haveSetViolent = true;
		}
		if (!m == NULL)
		{
			m->monsterFloorChanging(GetLeftX());
			_y = m->getMonsterFloor() - 120;
			currentFloor = m->getMonsterFloor();
		}
		if (isAlive())
		{
			intersect();
			isAttackedEffectCaculation();
		}
		else
		{
			if (!hasGottenLightBulb)
			{
				character->AddLightBulb(lightBulbInside);
				hasGottenLightBulb = true;
			}
			if (!hasGottenSource)
			{
				touchSource(m, grass_fast_p);
			}
		}
	}
}
