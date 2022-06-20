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
#include "MonsterBoss.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Boss的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterBoss::MonsterBoss()
	{
		_x = 400;
		_y = 400;
		hp = 100;
		hitDamage = 5;
		action = walk_a;
		BORDER = 5;
	}

	MonsterBoss::MonsterBoss(int x, int y, Character* c) : Monster(x, y, 100, 5, c)
	{
	}

	MonsterBoss::~MonsterBoss()
	{
	}

	void MonsterBoss::LoadBitmap()
	{
		bloodBar.LoadBitmap();

		//向右走動畫
		walkingRight.AddBitmap(IDB_BOSSRIGHTWALK1, RGB(0, 0, 0));
		walkingRight.AddBitmap(IDB_BOSSRIGHTWALK2, RGB(0, 0, 0));
		walkingRight.AddBitmap(IDB_BOSSRIGHTWALK3, RGB(0, 0, 0));
		walkingRight.AddBitmap(IDB_BOSSRIGHTWALK4, RGB(0, 0, 0));
		//向左走動畫
		walkingLeft.AddBitmap(IDB_BOSSLEFTWALK1, RGB(0, 0, 0));
		walkingLeft.AddBitmap(IDB_BOSSLEFTWALK2, RGB(0, 0, 0));
		walkingLeft.AddBitmap(IDB_BOSSLEFTWALK3, RGB(0, 0, 0));
		walkingLeft.AddBitmap(IDB_BOSSLEFTWALK4, RGB(0, 0, 0));

		//向右衝撞動畫
		collideRight.AddBitmap(IDB_BOSSRIGHTCOLLIDE1, RGB(0, 0, 0));
		collideRight.AddBitmap(IDB_BOSSRIGHTCOLLIDE2, RGB(0, 0, 0));
		collideRight.AddBitmap(IDB_BOSSRIGHTCOLLIDE3, RGB(0, 0, 0));
		collideRight.AddBitmap(IDB_BOSSRIGHTCOLLIDE3, RGB(0, 0, 0));
		collideRight.AddBitmap(IDB_BOSSRIGHTCOLLIDE4, RGB(0, 0, 0));
		//向左衝撞動畫
		collideLeft.AddBitmap(IDB_BOSSLEFTCOLLIDE1, RGB(0, 0, 0));
		collideLeft.AddBitmap(IDB_BOSSLEFTCOLLIDE2, RGB(0, 0, 0));
		collideLeft.AddBitmap(IDB_BOSSLEFTCOLLIDE3, RGB(0, 0, 0));
		collideLeft.AddBitmap(IDB_BOSSLEFTCOLLIDE3, RGB(0, 0, 0));
		collideLeft.AddBitmap(IDB_BOSSLEFTCOLLIDE4, RGB(0, 0, 0));

		//向右捶
		hitRight.AddBitmap(IDB_BOSSRIGHTHIT1, RGB(0, 0, 0));
		hitRight.AddBitmap(IDB_BOSSRIGHTHIT2, RGB(0, 0, 0));
		hitRight.AddBitmap(IDB_BOSSRIGHTHIT3, RGB(0, 0, 0));
		hitRight.AddBitmap(IDB_BOSSRIGHTHIT4, RGB(0, 0, 0));
		hitRight.AddBitmap(IDB_BOSSRIGHTHIT5, RGB(0, 0, 0));
		hitRight.AddBitmap(IDB_BOSSRIGHTHIT6, RGB(0, 0, 0));
		//向右捶效果
		hitRightEffect.AddBitmap(IDB_BOSSRIGHTHITEFFECT5, RGB(0, 0, 0));
		hitRightEffect.AddBitmap(IDB_BOSSRIGHTHITEFFECT4, RGB(0, 0, 0));
		//向左捶
		hitLeft.AddBitmap(IDB_BOSSLEFTHIT1, RGB(0, 0, 0));
		hitLeft.AddBitmap(IDB_BOSSLEFTHIT2, RGB(0, 0, 0));
		hitLeft.AddBitmap(IDB_BOSSLEFTHIT3, RGB(0, 0, 0));
		hitLeft.AddBitmap(IDB_BOSSLEFTHIT4, RGB(0, 0, 0));
		hitLeft.AddBitmap(IDB_BOSSLEFTHIT5, RGB(0, 0, 0));
		hitLeft.AddBitmap(IDB_BOSSLEFTHIT6, RGB(0, 0, 0));
		//向左捶效果
		hitLeftEffect.AddBitmap(IDB_BOSSLEFTHITEFFECT5, RGB(0, 0, 0));
		hitLeftEffect.AddBitmap(IDB_BOSSLEFTHITEFFECT4, RGB(0, 0, 0));

		//向右刺
		thronRight.AddBitmap(IDB_BOSSRIGHTTHORN1, RGB(0, 0, 0));
		thronRight.AddBitmap(IDB_BOSSRIGHTTHORN2, RGB(0, 0, 0));
		thronRight.AddBitmap(IDB_BOSSRIGHTTHORN3, RGB(0, 0, 0));
		//向左刺
		thronLeft.AddBitmap(IDB_BOSSLEFTTHORN1, RGB(0, 0, 0));
		thronLeft.AddBitmap(IDB_BOSSLEFTTHORN2, RGB(0, 0, 0));
		thronLeft.AddBitmap(IDB_BOSSLEFTTHORN3, RGB(0, 0, 0));
		//刺
		thron.AddBitmap(IDB_THRONGROW1, RGB(0, 0, 0));
		thron.AddBitmap(IDB_THRONGROW2, RGB(0, 0, 0));
		thron.AddBitmap(IDB_THRONRED, RGB(0, 0, 0));

		//死亡動畫
		deadRight.AddBitmap(IDB_BOSSRIGHTDEAD1, RGB(0, 0, 0));
		deadRight.AddBitmap(IDB_BOSSRIGHTDEAD2, RGB(0, 0, 0));
		deadRight.AddBitmap(IDB_BOSSRIGHTDEAD3, RGB(0, 0, 0));
		deadRight.AddBitmap(IDB_BOSSRIGHTDEAD4, RGB(0, 0, 0));
		deadRight.AddBitmap(IDB_BOSSRIGHTDEAD5, RGB(0, 0, 0));
		deadRight.AddBitmap(IDB_BOSSRIGHTDEAD6, RGB(0, 0, 0));
		deadLeft.AddBitmap(IDB_BOSSLEFTDEAD1, RGB(0, 0, 0));
		deadLeft.AddBitmap(IDB_BOSSLEFTDEAD2, RGB(0, 0, 0));
		deadLeft.AddBitmap(IDB_BOSSLEFTDEAD3, RGB(0, 0, 0));
		deadLeft.AddBitmap(IDB_BOSSLEFTDEAD4, RGB(0, 0, 0));
		deadLeft.AddBitmap(IDB_BOSSLEFTDEAD5, RGB(0, 0, 0));
		deadLeft.AddBitmap(IDB_BOSSLEFTDEAD6, RGB(0, 0, 0));

		black.LoadBitmap(IDB_BLACK, RGB(0, 0, 0));
	}

	void MonsterBoss::Initialize()
	{
		_x = init_x;
		_y = init_y;
		hp = 1000;
		bloodBar.setFullHP(hp);
		action = walk_a;
		BORDER = 5;
		facingLR = 1;
		STEP_SIZE = 5;
		attackDamage = 10;

		ResetAtkCounter();
		hitDamage = 5;
		hitDelayCount = 8;
		hitCD = false;
		rushDistance = 10;
		rushStepSize = 3;
		thronDamage = 10;
		thronCount = 0;
		thronDelayCount = 4;
		cMidX = 0;
		floor = 595;
		thronExist = false;
		thronCountFlag = false;
		canStandOn = true;
		bossDead = false;
		isViolent = false;
		haveSetViolent = false;
	}

	void MonsterBoss::OnMove(Map* m)
	{
		if (isAlive())
		{
			if (isViolent && !haveSetViolent)
			{
				hitDamage = 20;
				hitDelayCount = 5;
				attackDamage = 20;
				thronDamage = 30;
				thronDelayCount = 3;
				haveSetViolent = true;
			}
			SetCharacterDirection();
			if (action == walk_a)
			{
				facingLR = characterDirectionLR;
			}
			if (distanceToCharacter() < 300 && hitCD == false && action == walk_a && atkCounter[0] < 3)
			{
				hitStart();
				atkCount(0);
			}
			else if ((distanceToCharacter() > 550 || atkCounter[0] >= 3) && action == walk_a && hpProportion() > 0.5)
			{
				collideStart();
				atkCount(1);
			}
			else if ((distanceToCharacter() > 550 || atkCounter[0] >= 3) && action == walk_a && hpProportion() <= 0.5)
			{
				thronStart();
				atkCount(2);
			}

			if (action == walk_a)
			{
				walk(m);
				walkOnMove();
			}
			else if (action == hit_a)
			{
				hitOnMove();
			}
			else if (action == collide_a)
			{
				collideOnMove();
			}
			else if (action == thron_a)
			{
				thronBossOnMove();
			}
			hitCDTimer.CaculateTimeForFalse(&hitCD, 4);
			isAttackedEffectCaculation();
		}
		else
		{
			if (!bossDead)
			{
				deadOnMove();
			}
		}
	}

	void MonsterBoss::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow(m);
			}
			else
			{
				if (action == walk_a)
				{
					walkOnShow(m);
				}
				else if (action == hit_a)
				{
					hitOnShow(m);
				}
				else if (action == collide_a)
				{
					collideOnShow(m);
				}
				else if (action == thron_a)
				{
					thronBossOnShow(m);
				}
			}
			bloodBar.setXY(_x + m->getXMovement(), _y + m->getYMovement() - 16);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		else
		{
			if (!bossDead)
			{
				deadOnShow(m);
			}
		}
	}

	int MonsterBoss::GetLeftX()
	{
		if (facingLR == 0)
		{
			if (action == walk_a)
			{
				return _x + 90;
			}
			else if (action == hit_a)
			{
				return _x + 130;
			}
			else// if (action == collide_a) //第三張圖 衝撞ing not蓄力
			{
				return _x + 51;
			}
		}
		else
		{
			if (action == walk_a)
			{
				return _x + 72;
			}
			else if (action == hit_a)
			{
				return _x + 90;
			}
			else// if (action == collide_a)
			{
				return _x + 177;
			}
		}
	}

	int MonsterBoss::GetTopY()
	{
		if (action == walk_a || action == hit_a)
		{
			return _y + 90;
		}
		else// if (action == collide_a)
		{
			return _y + 100;
		}
	}

	int MonsterBoss::GetRightX()
	{
		if (facingLR == 0)
		{
			if (action == walk_a)
			{
				return _x + 220;
			}
			else if (action == hit_a)
			{
				return _x + 216;
			}
			else// if (action == collide_a)
			{
				return _x + 117;
			}
		}
		else
		{
			if (action == walk_a)
			{
				return _x + 200;
			}
			else if (action == hit_a)
			{
				return _x + 160;
			}
			else// if (action == collide_a)
			{
				return _x + 237;
			}
		}
	}

	int MonsterBoss::GetBottomY()
	{
		return _y + walkingLeft.Height();
	}

	void MonsterBoss::walk(Map* m)
	{
		if (facingLR == 0)
		{
			if (CanWalkL(m))
			{
				_x -= STEP_SIZE;
			}
		}
		else
		{
			if (CanWalkR(m))
			{
				_x += STEP_SIZE;
			}
		}
	}

	void MonsterBoss::walkOnMove()
	{
		walkingLeft.OnMove();
		walkingRight.OnMove();
	}

	void MonsterBoss::walkOnShow(Map* m)
	{
		if (facingLR == 0)
		{
			walkingLeft.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			walkingLeft.OnShow();
		}
		else
		{
			walkingRight.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			walkingRight.OnShow();
		}
	}

	bool MonsterBoss::CanWalkL(Map* m)
	{
		if (m->isEmpty(_x - STEP_SIZE, GetTopY()) && !character->isIntersect(GetLeftX() - STEP_SIZE, GetRightX() - STEP_SIZE, GetTopY(), GetBottomY()))
		{
			return true;
		}
		return false;
	}

	bool MonsterBoss::CanWalkR(Map* m)
	{
		if (m->isEmpty(_x - STEP_SIZE, GetTopY()) && !character->isIntersect(GetLeftX() + STEP_SIZE, GetRightX() + STEP_SIZE, GetTopY(), GetBottomY()))
		{
			return true;
		}
		return false;
	}

	void MonsterBoss::ResetAtkCounter()
	{
		for (int i = 0; i < 3; i++)
		{
			atkCounter[i] = 0;
		}
	}

	void MonsterBoss::atkCount(int i)
	{
		int temp = atkCounter[i];
		ResetAtkCounter();
		atkCounter[i] = temp + 1;
	}

	void MonsterBoss::hitStart()
	{
		action = hit_a;
		hitCDTimer.Start();
		hitCD = true;
	}

	void MonsterBoss::hitOnMove()
	{
		if (facingLR == 0)
		{
			hitLeft.OnMove();
			hitLeftEffect.OnMove();
		}
		else if (facingLR == 1)
		{
			hitRight.OnMove();
			hitRightEffect.OnMove();
		}
	}

	void MonsterBoss::hitOnShow(Map* m)
	{
		if (facingLR == 0)
		{
			if (hitLeft.GetCurrentBitmapNumber() == 2 || hitLeft.GetCurrentBitmapNumber() == 3 || hitLeft.GetCurrentBitmapNumber() == 4)
			{
				hitLeft.SetTopLeft(_x + m->getXMovement() - 60, _y + m->getYMovement());
			}
			else
			{
				hitLeft.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			}
			hitLeft.SetDelayCount(hitDelayCount);
			hitLeft.OnShow();

			if (hitLeft.GetCurrentBitmapNumber() == 3 || hitLeft.GetCurrentBitmapNumber() == 4)
			{
				hitLeftEffect.SetTopLeft(_x + m->getXMovement() - 60 - 290, _y + m->getYMovement());
				hitLeftEffect.SetDelayCount(hitDelayCount);
				hitLeftEffect.OnShow();
				hitJudge();
			}
			if (hitLeft.GetCurrentBitmapNumber() == 3)
			{
				hitJudge();
			}

			if (hitLeft.IsFinalBitmap())
			{
				action = walk_a;
				hitLeft.Reset();
			}
		}
		else
		{
			if (hitRight.GetCurrentBitmapNumber() == 2 || hitRight.GetCurrentBitmapNumber() == 3 || hitRight.GetCurrentBitmapNumber() == 4)
			{
				hitRight.SetTopLeft(_x + m->getXMovement() + 60, _y + m->getYMovement());
			}
			else
			{
				hitRight.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			}
			hitRight.SetDelayCount(hitDelayCount);
			hitRight.OnShow();

			if (hitRight.GetCurrentBitmapNumber() == 3 || hitRight.GetCurrentBitmapNumber() == 4)
			{
				hitRightEffect.SetTopLeft(_x + m->getXMovement() + 60 - 130, _y + m->getYMovement());
				hitRightEffect.SetDelayCount(hitDelayCount);
				hitRightEffect.OnShow();
				hitJudge();
			}

			if (hitRight.GetCurrentBitmapNumber() == 3)
			{
				hitJudge();
			}

			if (hitRight.IsFinalBitmap())
			{
				action = walk_a;
				hitRight.Reset();
			}
		}
	}

	void MonsterBoss::hitJudge()
	{
		if (!character->GetIsInvincible())
		{
			if (facingLR == 0)
			{
				if (isAttackSuccessfullyL(435))
				{
					character->SetIsAttackedFromRight(true);
					character->SetIsAttackedFromBottom(true);
					character->lossCurrentHp(hitDamage);
				}
				if (isAttackSuccessfullyR(135))
				{
					character->SetIsAttackedFromLeft(true);
					character->SetIsAttackedFromBottom(true);
					character->lossCurrentHp(hitDamage);
				}
			}
			else
			{
				if (isAttackSuccessfullyR(435))
				{
					character->SetIsAttackedFromLeft(true);
					character->SetIsAttackedFromBottom(true);
					character->lossCurrentHp(hitDamage);
				}
				if (isAttackSuccessfullyL(135))
				{
					character->SetIsAttackedFromRight(true);
					character->SetIsAttackedFromBottom(true);
					character->lossCurrentHp(hitDamage);
				}
			}
		}
	}

	void MonsterBoss::collideStart()
	{
		action = collide_a;
	}

	void MonsterBoss::collideOnMove()
	{
		if (facingLR == 0)
		{
			collideLeft.OnMove();
		}
		else if (facingLR == 1)
		{
			collideRight.OnMove();
		}
	}

	void MonsterBoss::collideOnShow(Map* m)
	{
		if (facingLR == 0)
		{
			if (collideLeft.GetCurrentBitmapNumber() == 1)
			{
				collideLeft.SetTopLeft(_x + m->getXMovement() - 20, _y + m->getYMovement());
			}
			else
			{
				collideLeft.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			}

			if (collideLeft.GetCurrentBitmapNumber() == 2 || collideLeft.GetCurrentBitmapNumber() == 3)
			{
				collideJudge();
				rushMove(m);
			}

			collideLeft.OnShow();

			if (collideLeft.IsFinalBitmap())
			{
				action = walk_a;
				collideLeft.Reset();
			}
		}
		else
		{
			if (collideRight.GetCurrentBitmapNumber() == 1)
			{
				collideRight.SetTopLeft(_x + m->getXMovement() + 20, _y + m->getYMovement());
			}
			else
			{
				collideRight.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			}

			if (collideRight.GetCurrentBitmapNumber() == 2 || collideRight.GetCurrentBitmapNumber() == 3)
			{
				collideJudge();
				rushMove(m);
			}

			collideRight.OnShow();

			if (collideRight.IsFinalBitmap())
			{
				action = walk_a;
				collideRight.Reset();
			}
		}
	}

	void MonsterBoss::collideJudge()
	{
		intersect();
	}

	void MonsterBoss::rushMove(Map* m)
	{
		if (facingLR == 0)
		{
			for (int i = 0; i < rushDistance; i++)
			{
				if (m->isEmpty(_x - rushStepSize, GetTopY())/* && m->isEmpty(_x - STEP_SIZE, GetBottomY())*/)
				{
					_x -= rushStepSize;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < rushDistance; i++)
			{
				if (m->isEmpty(_x + rushStepSize, GetTopY())/* && m->isEmpty(_x + STEP_SIZE, GetBottomY())*/)
				{
					_x += rushStepSize;
				}
				else
				{
					break;
				}
			}
		}
	}

	void MonsterBoss::thronStart()
	{
		action = thron_a;
	}

	void MonsterBoss::thronBossOnMove()
	{
		if (facingLR == 0)
		{
			if (thronLeft.GetCurrentBitmapNumber() != 2)
			{
				thronLeft.OnMove();
			}
			else
			{
				thron.OnMove();
			}
		}
		else if (facingLR == 1)
		{
			if (thronRight.GetCurrentBitmapNumber() != 2)
			{
				thronRight.OnMove();
			}
			else
			{
				thron.OnMove();
			}
		}

	}

	void MonsterBoss::thronBossOnShow(Map* m)
	{
		if (facingLR == 0)
		{
			thronLeft.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			//thronLeft.SetDelayCount(thronDelayCount);
			thronLeft.OnShow();
			if (thronLeft.GetCurrentBitmapNumber() == 2)
			{
				thronOnShow(m);
			}
			if (thronLeft.IsFinalBitmap() && thronCount >= 3)
			{
				thronCount = 0;
				action = walk_a;
				thronLeft.Reset();
				thron.Reset();
			}
		}
		else
		{
			thronRight.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			//thronRight.SetDelayCount(thronDelayCount);
			thronRight.OnShow();
			if (thronRight.GetCurrentBitmapNumber() == 2)
			{
				thronOnShow(m);
			}
			if (thronRight.IsFinalBitmap() && thronCount >= 3)
			{
				thronCount = 0;
				action = walk_a;
				thronRight.Reset();
				thron.Reset();
			}
		}
	}

	void MonsterBoss::thronOnShow(Map* m)
	{
		thron.SetDelayCount(thronDelayCount);
		if (thron.GetCurrentBitmapNumber() == 0)
		{
			thronCountFlag = false;
			if (!thronExist)
			{
				SetCMidX();
				thronExist = true;
			}
			thron.SetTopLeft(cMidX + m->getXMovement() - 7, floor + m->getYMovement() - 50);
		}
		else
		{
			thron.SetTopLeft(cMidX + m->getXMovement() - 18, floor + m->getYMovement() - 199);
		}
		if (thron.GetCurrentBitmapNumber() == 2)
		{
			thronJudge();
			if (!thronCountFlag)
			{
				thronCount += 1;
				thronCountFlag = true;
			}
			thronExist = false;
		}
		thron.OnShow();
	}

	void MonsterBoss::thronJudge()
	{
		if (((character->GetRightX() >= cMidX - 18 && character->GetRightX() <= cMidX + 20) || //角色右邊碰到刺
			(character->GetLeftX() <= cMidX + 20 && character->GetLeftX() >= cMidX - 18) || //角色左邊碰到刺
			(character->GetLeftX() <= cMidX - 18 && character->GetRightX() >= cMidX + 20)) && //角色左右橫跨刺
			((character->GetBottomY() >= floor - 200 && character->GetBottomY() <= floor) ||
				(character->GetTopY() >= floor - 200 && character->GetTopY() <= floor)))
		{
			if (!character->GetIsInvincible())
			{
				character->SetIsAttackedFromBottom(true);
				character->lossCurrentHp(thronDamage);
			}
		}
	}

	void MonsterBoss::SetCMidX()
	{
		cMidX = (character->GetLeftX() + character->GetRightX()) / 2;
	}

	void MonsterBoss::deadOnMove()
	{
		if (facingLR == 0)
		{
			deadLeft.OnMove();
		}
		else if (facingLR == 1)
		{
			deadRight.OnMove();
		}
	}

	void MonsterBoss::deadOnShow(Map* m)
	{
		if (facingLR == 0)
		{
			deadLeft.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			deadLeft.OnShow();

			if (deadLeft.IsFinalBitmap())
			{
				bossDead = true;
				deadLeft.Reset();
			}
		}
		else
		{
			deadRight.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
			deadRight.OnShow();

			if (deadRight.IsFinalBitmap())
			{
				bossDead = true;
				deadRight.Reset();
			}
		}
	}
}
