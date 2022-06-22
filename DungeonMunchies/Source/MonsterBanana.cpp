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
#include "MonsterBanana.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Banana的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterBanana::MonsterBanana()
	{
		_x = 400;
		_y = 400;
		hp = 50;
		attackDamage = 0;
		BORDER = 20;
	}

	MonsterBanana::MonsterBanana(int x, int y, Character* c) : Monster(x, y, 20, 5, c)
	{
		BORDER = 20;
	}

	MonsterBanana::~MonsterBanana()
	{
	}

	void MonsterBanana::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		bananaAlive.LoadBitmap(IDB_MONSTERBANANA, RGB(0, 0, 0));
		bananaDead.LoadBitmap(IDB_MONSTERBANANADEAD, RGB(0, 0, 0));
		sourceBananaAttack.LoadBitmap(IDB_SOURCEBANANAATTACK, RGB(0, 0, 0));
		black.LoadBitmap(IDB_BLACK, RGB(0, 0, 0));
	}

	void MonsterBanana::Initialize()
	{
		_x = init_x;
		_y = init_y;
		currentFloor = 0;
		hp = 1;
		attackDamage = 5;
		bloodBar.setFullHP(hp);
		hasGottenSource = false;
		lightBulbInside = 60;
		hasGottenLightBulb = false;
		canStandOn = true;
		isViolent = false;
		haveSetViolent = false;
	}

	void MonsterBanana::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow(m);
			}
			else
			{
				bananaAlive.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
				bananaAlive.ShowBitmap();
			}
			bloodBar.setXY(GetLeftX() + m->getXMovement(), GetTopY() - 16 + m->getYMovement());
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		if (!isAlive())
		{
			bananaDead.SetTopLeft(_x + m->getXMovement(), _y + bananaAlive.Height() - bananaDead.Height() + m->getYMovement());
			bananaDead.ShowBitmap();
			if (!hasGottenSource)
			{
				sourceBananaAttack.SetTopLeft((GetLeftX() + GetRightX()) / 2 + m->getXMovement(), GetBottomY() - 64 + m->getYMovement());
				sourceBananaAttack.ShowBitmap();
			}
		}
	}

	int MonsterBanana::GetLeftX()
	{
		return _x;
	}

	int MonsterBanana::GetTopY()
	{
		return _y;
	}

	int MonsterBanana::GetRightX()
	{
		return _x + bananaAlive.Width();
	}

	int MonsterBanana::GetBottomY()
	{
		return _y + bananaAlive.Height();
	}

	void MonsterBanana::OnMove(Map* m)
	{
		if (!m == NULL)
		{
			m->monsterFloorChanging(GetLeftX());
			_y = m->getMonsterFloor() - bananaAlive.Height() - 6;
			currentFloor = m->getMonsterFloor();
		}
		if (isAlive())
		{
			//intersect();
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
				touchSource(m, banana_attack_p);
			}
		}
	}
}
