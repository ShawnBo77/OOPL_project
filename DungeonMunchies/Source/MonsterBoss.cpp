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
#include "Util.h"

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
		walkingRight.AddBitmap(".\\res\\boss_right_walk01.bmp", RGB(0, 0, 0));
		walkingRight.AddBitmap(".\\res\\boss_right_walk02.bmp", RGB(0, 0, 0));
		walkingRight.AddBitmap(".\\res\\boss_right_walk03.bmp", RGB(0, 0, 0));
		walkingRight.AddBitmap(".\\res\\boss_right_walk04.bmp", RGB(0, 0, 0));
		//向左走動畫
		walkingLeft.AddBitmap(".\\res\\boss_left_walk01.bmp", RGB(0, 0, 0));
		walkingLeft.AddBitmap(".\\res\\boss_left_walk02.bmp", RGB(0, 0, 0));
		walkingLeft.AddBitmap(".\\res\\boss_left_walk03.bmp", RGB(0, 0, 0));
		walkingLeft.AddBitmap(".\\res\\boss_left_walk04.bmp", RGB(0, 0, 0));

		//向右衝撞動畫
		collideRight.AddBitmap(".\\res\\boss_right_collide01.bmp", RGB(0, 0, 0));
		collideRight.AddBitmap(".\\res\\boss_right_collide02.bmp", RGB(0, 0, 0));
		collideRight.AddBitmap(".\\res\\boss_right_collide03.bmp", RGB(0, 0, 0));
		collideRight.AddBitmap(".\\res\\boss_right_collide03.bmp", RGB(0, 0, 0));
		collideRight.AddBitmap(".\\res\\boss_right_collide04.bmp", RGB(0, 0, 0));
		//向左衝撞動畫
		collideLeft.AddBitmap(".\\res\\boss_left_collide01.bmp", RGB(0, 0, 0));
		collideLeft.AddBitmap(".\\res\\boss_left_collide02.bmp", RGB(0, 0, 0));
		collideLeft.AddBitmap(".\\res\\boss_left_collide03.bmp", RGB(0, 0, 0));
		collideLeft.AddBitmap(".\\res\\boss_left_collide03.bmp", RGB(0, 0, 0));
		collideLeft.AddBitmap(".\\res\\boss_left_collide04.bmp", RGB(0, 0, 0));

		//向右捶
		hitRight.AddBitmap(".\\res\\boss_right_hit01.bmp", RGB(0, 0, 0));
		hitRight.AddBitmap(".\\res\\boss_right_hit02.bmp", RGB(0, 0, 0));
		hitRight.AddBitmap(".\\res\\boss_right_hit03.bmp", RGB(0, 0, 0));
		hitRight.AddBitmap(".\\res\\boss_right_hit04.bmp", RGB(0, 0, 0));
		hitRight.AddBitmap(".\\res\\boss_right_hit05.bmp", RGB(0, 0, 0));
		hitRight.AddBitmap(".\\res\\boss_right_hit06.bmp", RGB(0, 0, 0));
		//向右捶效果
		hitRightEffect.AddBitmap(".\\res\\boss_right_hit_effect05.bmp", RGB(0, 0, 0));
		hitRightEffect.AddBitmap(".\\res\\boss_right_hit_effect04.bmp", RGB(0, 0, 0));
		//向左捶
		hitLeft.AddBitmap(".\\res\\boss_left_hit01.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit02.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit03.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit04.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit05.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit06.bmp", RGB(0, 0, 0));
		//向左捶效果
		hitLeftEffect.AddBitmap(".\\res\\boss_left_hit_effect05.bmp", RGB(0, 0, 0));
		hitLeftEffect.AddBitmap(".\\res\\boss_left_hit_effect04.bmp", RGB(0, 0, 0));

		//向右刺
		thronRight.AddBitmap(".\\res\\boss_right_thorn01.bmp", RGB(0, 0, 0));
		thronRight.AddBitmap(".\\res\\boss_right_thorn02.bmp", RGB(0, 0, 0));
		thronRight.AddBitmap(".\\res\\boss_right_thorn03.bmp", RGB(0, 0, 0));
		//向左刺
		thronLeft.AddBitmap(".\\res\\boss_left_thorn01.bmp", RGB(0, 0, 0));
		thronLeft.AddBitmap(".\\res\\boss_left_thorn02.bmp", RGB(0, 0, 0));
		thronLeft.AddBitmap(".\\res\\boss_left_thorn03.bmp", RGB(0, 0, 0));
		//刺
		thron.AddBitmap(".\\res\\thron_grow01.bmp", RGB(0, 0, 0));
		thron.AddBitmap(".\\res\\thron_grow02.bmp", RGB(0, 0, 0));
		thron.AddBitmap(".\\res\\thron_red.bmp", RGB(0, 0, 0));

		//死亡動畫
		deadRight.AddBitmap(".\\res\\boss_right_dead01.bmp", RGB(0, 0, 0));
		deadRight.AddBitmap(".\\res\\boss_right_dead02.bmp", RGB(0, 0, 0));
		deadRight.AddBitmap(".\\res\\boss_right_dead03.bmp", RGB(0, 0, 0));
		deadRight.AddBitmap(".\\res\\boss_right_dead04.bmp", RGB(0, 0, 0));
		deadRight.AddBitmap(".\\res\\boss_right_dead05.bmp", RGB(0, 0, 0));
		deadRight.AddBitmap(".\\res\\boss_right_dead06.bmp", RGB(0, 0, 0));
		deadLeft.AddBitmap(".\\res\\boss_left_dead01.bmp", RGB(0, 0, 0));
		deadLeft.AddBitmap(".\\res\\boss_left_dead02.bmp", RGB(0, 0, 0));
		deadLeft.AddBitmap(".\\res\\boss_left_dead03.bmp", RGB(0, 0, 0));
		deadLeft.AddBitmap(".\\res\\boss_left_dead04.bmp", RGB(0, 0, 0));
		deadLeft.AddBitmap(".\\res\\boss_left_dead05.bmp", RGB(0, 0, 0));
		deadLeft.AddBitmap(".\\res\\boss_left_dead06.bmp", RGB(0, 0, 0));
	}

	void MonsterBoss::Initialize()
	{
		_x = init_x;
		_y = init_y;
		//hp = 100;
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
		cMidX = 0;
		floor = 595;
		thronExist = false;

		bossDead = false;
	}

	void MonsterBoss::OnMove(Map* m)
	{
		if (isAlive())
		{
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
		}
		else
		{
			deadOnMove();
		}
	}

	void MonsterBoss::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (action == walk_a)
			{
				walkOnShow();
			}
			else if (action == hit_a)
			{
				hitOnShow();
			}
			else if (action == collide_a)
			{
				collideOnShow(m);
			}
			else if (action == thron_a)
			{
				thronBossOnShow();
			}
			bloodBar.setXY(_x, _y - 16);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow();
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		else
		{
			deadOnShow();
		}
		//showData();
	}

	void MonsterBoss::showData()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		char position[500];								// Demo 數字對字串的轉換
		sprintf(position, "BossLeftX:%d BossRightX:%d BossTopY:%d BossButtonY:%d hitTimer:(%d, %d) distanceToCharacter:%d hpProportion:%f",
			GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), hitCDTimer.GetStartTime(), hitCDTimer.GetFinishTime(), distanceToCharacter(), hpProportion());
		pDC->TextOut(200, 100, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
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

	int MonsterBoss::GetButtonY()
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

	void MonsterBoss::walkOnShow()
	{
		if (facingLR == 0)
		{
			walkingLeft.SetTopLeft(_x, _y);
			walkingLeft.OnShow();
		}
		else
		{
			walkingRight.SetTopLeft(_x, _y);
			walkingRight.OnShow();
		}
	}

	bool MonsterBoss::CanWalkL(Map* m)
	{
		if (m->isEmpty(_x - STEP_SIZE, GetTopY()) && !character->isIntersect(GetLeftX() - STEP_SIZE, GetRightX() - STEP_SIZE, GetTopY(), GetButtonY()))
		{
			return true;
		}
		return false;
	}

	bool MonsterBoss::CanWalkR(Map* m)
	{
		if (m->isEmpty(_x - STEP_SIZE, GetTopY()) && !character->isIntersect(GetLeftX() + STEP_SIZE, GetRightX() + STEP_SIZE, GetTopY(), GetButtonY()))
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

	void MonsterBoss::hitOnShow()
	{
		if (facingLR == 0)
		{
			if (hitLeft.GetCurrentBitmapNumber() == 2 || hitLeft.GetCurrentBitmapNumber() == 3 || hitLeft.GetCurrentBitmapNumber() == 4)
			{
				hitLeft.SetTopLeft(_x - 60, _y);
			}
			else
			{
				hitLeft.SetTopLeft(_x, _y);
			}
			hitLeft.SetDelayCount(hitDelayCount);
			hitLeft.OnShow();

			if (hitLeft.GetCurrentBitmapNumber() == 3 || hitLeft.GetCurrentBitmapNumber() == 4)
			{
				hitLeftEffect.SetTopLeft(_x - 60 - 290, _y);
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
				hitRight.SetTopLeft(_x + 60, _y);
			}
			else
			{
				hitRight.SetTopLeft(_x, _y);
			}
			hitRight.SetDelayCount(hitDelayCount);
			hitRight.OnShow();

			if (hitRight.GetCurrentBitmapNumber() == 3 || hitRight.GetCurrentBitmapNumber() == 4)
			{
				hitRightEffect.SetTopLeft(_x + 60 - 130, _y);
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
					character->SetIsAttackedFromButton(true);
					character->lossCurrentHp(hitDamage);
				}
			}
			else
			{
				if (isAttackSuccessfullyR(435))
				{
					character->SetIsAttackedFromLeft(true);
					character->SetIsAttackedFromButton(true);
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
				collideLeft.SetTopLeft(_x - 20, _y);
			}
			else
			{
				collideLeft.SetTopLeft(_x, _y);
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
				collideRight.SetTopLeft(_x + 20, _y);
			}
			else
			{
				collideRight.SetTopLeft(_x, _y);
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
				if (m->isEmpty(_x - rushStepSize, GetTopY())/* && m->isEmpty(_x - STEP_SIZE, GetButtonY())*/)
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
				if (m->isEmpty(_x + rushStepSize, GetTopY())/* && m->isEmpty(_x + STEP_SIZE, GetButtonY())*/)
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

	void MonsterBoss::thronBossOnShow()
	{
		if (facingLR == 0)
		{
			thronLeft.SetTopLeft(_x, _y);
			thronLeft.OnShow();
			if (thronLeft.GetCurrentBitmapNumber() == 2)
			{
				thronOnShow();
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
			thronRight.SetTopLeft(_x, _y);
			thronRight.OnShow();
			if (thronRight.GetCurrentBitmapNumber() == 2)
			{
				thronOnShow();
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

	void MonsterBoss::thronOnShow()
	{
		if (thron.GetCurrentBitmapNumber() == 0)
		{
			if (!thronExist)
			{
				SetCMidX();
				thronExist = true;
			}
			thron.SetTopLeft(cMidX - 7, floor - 50);
		}
		else
		{
			thron.SetTopLeft(cMidX - 18, floor - 199);
		}
		if (thron.GetCurrentBitmapNumber() == 2)
		{
			thronJudge();
			thronCount += 1;
			thronExist = false;
		}
		thron.OnShow();
	}

	void MonsterBoss::thronJudge()
	{
		if (((character->GetRightX() >= cMidX - 18 && character->GetRightX() <= cMidX + 20) || //角色右邊碰到刺
			(character->GetLeftX() <= cMidX + 20 && character->GetLeftX() >= cMidX - 18) || //角色左邊碰到刺
			(character->GetLeftX() <= cMidX - 18 && character->GetRightX() >= cMidX + 20)) && //角色左右橫跨刺
			(character->GetButtonY() >= floor - 200 && character->GetButtonY() <= floor))
		{
			if (!character->GetIsInvincible())
			{
				character->SetIsAttackedFromButton(true);
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

	void MonsterBoss::deadOnShow()
	{
		if (facingLR == 0)
		{
			deadLeft.SetTopLeft(_x, _y);

			deadLeft.OnShow();

			if (deadLeft.IsFinalBitmap())
			{
				bossDead = true;
			}
		}
		else
		{
			deadRight.SetTopLeft(_x, _y);

			deadRight.OnShow();

			if (deadRight.IsFinalBitmap())
			{
				bossDead = true;
			}
		}
	}
}
