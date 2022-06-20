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
#include "MonsterMosquito.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Mosquito的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterMosquito::MonsterMosquito()
	{
		_x = 400;
		_y = 400;
		hp = 50;
		attackDamage = 5;
		BORDER = 20;
	}

	MonsterMosquito::MonsterMosquito(int x, int y, Character* c) : Monster(x, y, 50, 5, c)
	{
		BORDER = 20;
	}

	MonsterMosquito::~MonsterMosquito()
	{
	}

	void MonsterMosquito::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		faceLeft.AddBitmap(IDB_MONSTERMOSQUITOL01, RGB(0, 0, 0));
		faceLeft.AddBitmap(IDB_MONSTERMOSQUITOL02, RGB(0, 0, 0));
		faceRight.AddBitmap(IDB_MONSTERMOSQUITOR01, RGB(0, 0, 0));
		faceRight.AddBitmap(IDB_MONSTERMOSQUITOR02, RGB(0, 0, 0));
		sourceMosquitoJump.LoadBitmap(IDB_SOURCEMOSQUITOJUMP, RGB(0, 0, 0));
		black.LoadBitmap(IDB_BLACK, RGB(0, 0, 0));
	}

	void MonsterMosquito::Initialize()
	{
		_x = init_x;
		_y = init_y;
		currentFloor = 0;
		BORDER = 5;
		hp = 20;
		attackDamage = 3;
		facingLR = 0;
		bloodBar.setFullHP(hp);
		STEP_SIZE = 5;
		velocity = 0;
		lightBulbInside = 2;
		hasGottenLightBulb = false;
		hasGottenSource = false;
		flyCase = 2;
		shouldFlyCaseChange = false;
		canStandOn = false;
		isViolent = false;
		haveSetViolent = false;
	}

	void MonsterMosquito::OnMove(Map* m)
	{
		if (isViolent && !haveSetViolent)
		{
			hp = 200;
			attackDamage = 5;
			haveSetViolent = true;
		}
		if (!m == NULL)
		{
			m->monsterFloorChanging((GetLeftX() + GetRightX()) / 2);
			currentFloor = m->getMonsterFloor();
		}
		if (isAlive())
		{
			if (shouldFlyCaseChange)
			{
				flyTimer.Start();
				flyCaseChanger();
				shouldFlyCaseChange = false;
			}
			if (flyCase == 1) // 左上
			{
				moveUp(m);
				moveLeft(m);
			}
			else if (flyCase == 2) // 左下
			{
				moveDown(m);
				moveLeft(m);
			}
			else if (flyCase == 3) // 右下
			{
				moveDown(m);
				moveRight(m);
			}
			else if (flyCase == 4) // 右上
			{
				moveUp(m);
				moveRight(m);
			}
			flyTimer.CaculateTimeForTrue(&shouldFlyCaseChange, (rand() % 200) / 100);
			intersect();
			isAttackedEffectCaculation();
			faceLeft.OnMove();
			faceRight.OnMove();
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
				touchSource(m, mosquito_jump_p);
			}
		}
	}

	void MonsterMosquito::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow(m);
			}
			else
			{
				if (facingLR == 0)
				{
					faceLeft.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
					faceLeft.SetDelayCount(1);
					faceLeft.OnShow();
				}
				else
				{
					faceRight.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
					faceRight.SetDelayCount(1);
					faceRight.OnShow();
				}
			}
			bloodBar.setXY(GetLeftX() + m->getXMovement(), GetTopY() + m->getYMovement() - 25);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		else
		{
			if (!hasGottenSource)
			{
				sourceMosquitoJump.SetTopLeft((GetLeftX() + GetRightX()) / 2 + m->getXMovement(), currentFloor - 64 + m->getYMovement());
				sourceMosquitoJump.ShowBitmap();
			}
		}
	}

	int MonsterMosquito::GetLeftX()
	{
		return _x + 18;
	}

	int MonsterMosquito::GetTopY()
	{
		return _y + 28;
	}

	int MonsterMosquito::GetRightX()
	{
		return _x + 80;
	}

	int MonsterMosquito::GetBottomY()
	{
		return _y + 68;
	}
	void MonsterMosquito::moveUp(Map* m)
	{
		if (m->isEmpty(GetLeftX(), GetTopY() - STEP_SIZE) && m->isEmpty(GetRightX(), GetTopY() - STEP_SIZE)) //向上移動
		{
			_y -= STEP_SIZE;
		}
	}
	void MonsterMosquito::moveDown(Map* m)
	{
		if (m->isEmpty(GetLeftX(), GetBottomY() + STEP_SIZE)) //向下移動
		{
			_y += STEP_SIZE;
		}
	}
	void MonsterMosquito::moveLeft(Map* m)
	{
		if (m->isEmpty(GetLeftX() - STEP_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - STEP_SIZE, GetBottomY())) //向左移動
		{
			_x -= STEP_SIZE;
		}
	}
	void MonsterMosquito::moveRight(Map* m)
	{
		if (m->isEmpty(GetRightX() + STEP_SIZE, GetTopY()) && m->isEmpty(GetRightX() + STEP_SIZE, GetBottomY())) //向右移動
		{
			_x += STEP_SIZE;
		}
	}
	void MonsterMosquito::flyCaseChanger()
	{
		if (flyCase < 4)
		{
			flyCase++;
		}
		else
		{
			flyCase = 1;
		}
	}
}
