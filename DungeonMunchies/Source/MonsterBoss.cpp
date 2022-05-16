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

	MonsterBoss::MonsterBoss(int x, int y, Character* c) : Monster(x, y, 12, 5, c)
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
		collideRight.AddBitmap(".\\res\\boss_right_collide04.bmp", RGB(0, 0, 0));

		//向左衝撞動畫
		collideLeft.AddBitmap(".\\res\\boss_left_collide01.bmp", RGB(0, 0, 0));
		collideLeft.AddBitmap(".\\res\\boss_left_collide02.bmp", RGB(0, 0, 0));
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
	}

	void MonsterBoss::Initialize()
	{
		_x = init_x;
		_y = init_y;
		hp = 100;
		bloodBar.setFullHP(hp);
		action = walk_a;
		BORDER = 5;
		facingLR = 1;

		hitDamage = 5;
		hitDelayCount = 8;
		hitCD = false;
	}

	void MonsterBoss::OnMove()
	{
		if (isAlive())
		{
			SetCharacterDirection();
			if (action == walk_a)
			{
				facingLR = characterDirectionLR;
			}
			if (distanceToCharacter() < 350 && hitCD == false)
			{
				hitStart();
				intersect();
			}

			walkingLeft.OnMove();
			walkingRight.OnMove();
			if (action == hit_a) {
				hitOnMove();
			}
			hitLeftEffect.OnMove();
			hitRightEffect.OnMove();
			collideLeft.OnMove();
			collideRight.OnMove();
			hitCDTimer.CaculateTimeForFalse(&hitCD, 4);
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
				collideOnShow();
			}

			bloodBar.setXY(_x, _y - 16);
			bloodBar.showBloodBar(m, hp);
		}
		else
		{
		}
		showData();
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
		sprintf(position, "BossLeftX:%d BossRightX:%d BossTopY:%d BossButtonY:%d hitTimer:(%d, %d) distanceToCharacter:%d",
			GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), hitCDTimer.GetStartTime(), hitCDTimer.GetFinishTime(), distanceToCharacter());
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

	void MonsterBoss::hitStart()
	{
		action = hit_a;
		hitCDTimer.Start();
		hitCD = true;
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

	void MonsterBoss::hitOnMove()
	{
		if (facingLR == 0)
		{
			hitLeft.OnMove();
		}
		else if (facingLR == 1)
		{
			hitRight.OnMove();
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

	void MonsterBoss::collideOnShow()
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
			collideLeft.OnShow();
			
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
			collideRight.OnShow();
			
		}
	}
}
