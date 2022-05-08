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
#include "MonsterShrimp.h"
#include "Util.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Shrimp的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterShrimp::MonsterShrimp()
	{
		_x = 400;
		_y = 400;
		hp = 10;
		attackDamage = 5;
		facingLR = 0;
		actionNum = 0;
		STEP_SIZE = 1;
		attackCD = false;
	}

	MonsterShrimp::MonsterShrimp(int x, int y, Character* c) : Monster(x, y, 12, 5, c)
	{
		hp = 50;
		attackDamage = 5;
		facingLR = 0;
		actionNum = 0;
		STEP_SIZE = 1;
		attackCD = false;
	}

	MonsterShrimp::~MonsterShrimp()
	{
	}

	void MonsterShrimp::LoadBitmap()
	{
		bloodBar.LoadBitmap();

		walkLeft.AddBitmap(".\\res\\monster_shrimp_walk01_left.bmp", RGB(0, 0, 0));
		walkLeft.AddBitmap(".\\res\\monster_shrimp_walk02_left.bmp", RGB(0, 0, 0));
		walkRight.AddBitmap(".\\res\\monster_shrimp_walk01_right.bmp", RGB(0, 0, 0));
		walkRight.AddBitmap(".\\res\\monster_shrimp_walk02_right.bmp", RGB(0, 0, 0));

		attackLeft.AddBitmap(".\\res\\monster_shrimp_attack01_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_shrimp_attack02_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_shrimp_attack03_left.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_shrimp_attack01_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_shrimp_attack02_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_shrimp_attack03_right.bmp", RGB(0, 0, 0));

		deadLeft.LoadBitmap(".\\res\\monster_shrimp_dead_left.bmp", RGB(0, 0, 0));
		deadRight.LoadBitmap(".\\res\\monster_shrimp_dead_right.bmp", RGB(0, 0, 0));
	}

	void MonsterShrimp::Initialize()
	{
		_x = init_x;
		_y = init_y;
		hp = 50;
		attackDamage = 5;
		facingLR = 0;
		actionNum = 0;
		bloodBar.setFullHP(hp);
		STEP_SIZE = 5;
	}

	void MonsterShrimp::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (facingLR == 0)
			{
				if (actionNum == 0)
				{
					walkLeft.SetTopLeft(_x - 140, _y); //讓圖片中怪物顯示靠向左
					//walkLeft.SetDelayCount(3);
					walkLeft.OnShow();
				}
				else
				{
					attackLeft.SetTopLeft(_x - 110, _y);
					attackLeft.SetDelayCount(4);
					attackLeft.OnShow();
					if (attackLeft.IsFinalBitmap())
					{
						actionNum = 0;
					}
				}
			}
			else
			{
				if (actionNum == 0)
				{
					walkRight.SetTopLeft(_x, _y);
					walkRight.OnShow();
				}
				else
				{
					attackRight.SetTopLeft(_x, _y);
					attackRight.SetDelayCount(4);
					attackRight.OnShow();
					if (attackRight.IsFinalBitmap())
					{
						actionNum = 0;
					}
				}
			}
			bloodBar.setXY(GetLeftX(), GetTopY() - 16);
			bloodBar.showBloodBar(m, hp);
		}
		else
		{
			if (facingLR == 0)
			{
				deadLeft.SetTopLeft(_x, _y);
				deadLeft.ShowBitmap();
			}
			else
			{
				deadRight.SetTopLeft(_x, _y);
				deadRight.ShowBitmap();
			}
		}
		showData();
	}

	void MonsterShrimp::OnMove()
	{
		if (isAlive())
		{
			SetCharacterDirection();
			if (actionNum == 0)
			{
				facingLR = characterDirectionLR;
			}
			if (distanceToCharacter() < 190 && attackCD == false)
			{
				attack();
			}
			else if (distanceToCharacter() < 280 && actionNum == 0)
			{
				if (characterDirectionLR == 0)
				{
					_x -= STEP_SIZE;
				}
				else
				{
					_x += STEP_SIZE;
				}
			}
			attackCDTime.CaculateTime(&attackCD, 2);
			walkLeft.OnMove();
			walkRight.OnMove();

			attackLeft.OnMove();
			attackRight.OnMove();

			//intersect();
		}
	}

	void MonsterShrimp::SetFacingLR(bool flag)
	{
		facingLR = flag;
	}

	bool MonsterShrimp::GetFacingLR()
	{
		return facingLR;
	}

	void MonsterShrimp::SetActionNum(int num)
	{
		actionNum = num;
	}

	bool MonsterShrimp::GetActionNum()
	{
		return actionNum;
	}

	int MonsterShrimp::GetLeftX() //顯示的圖會往左邊靠(onShow調整的)
	{
		return _x;
	}

	int MonsterShrimp::GetTopY() //需調整以對應顯示的圖(_y + (圖片高度-物體高度))
	{
		if (actionNum == 0) //walk
		{
			return _y + 68;
		}
		else// if (actionNum == 1) //attack ?????????????????
		{
			return _y + 75;
		}
	}

	int MonsterShrimp::GetRightX() //加上物體本身的長度
	{
		if (actionNum == 0) //walk 
		{
			return _x + 125;
		}
		else // if (actionNum == 1) //attack 
		{
			return _x + 140;
		}
	}

	int MonsterShrimp::GetButtonY()
	{
		return _y + walkLeft.Height();
	}

	void MonsterShrimp::attack()
	{
		if (attackCD == false) //保險起見多加的
		{
			actionNum = 1;
			attackCDTime.Start();
			attackCD = true;
			if (!character->GetIsInvincible())
			{
				if (facingLR == 0)
				{
					if (isAttackSuccessfullyL(100))
					{
						character->SetIsAttackedFromRight(true);
						character->lossCurrentHp(attackDamage);
					}
				}
				else
				{
					if (isAttackSuccessfullyR(100))
					{
						character->SetIsAttackedFromLeft(true);
						character->lossCurrentHp(attackDamage);
					}
				}
			}
		}
	}

	void MonsterShrimp::showData()
	{
		int CharacterLeftX = character->GetLeftX();
		int CharacterRightX = character->GetRightX();
		int CharacterTopY = character->GetTopY();
		int CharacterButtonY = character->GetButtonY();
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		char position[500];								// Demo 數字對字串的轉換
		sprintf(position, "ShrimpLeftX:%d ShrimpRightX:%d ShrimpTopY:%d ShrimpButtonY:%d ShrimpHp:%d"
			,GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), GetCurrentHp());
		//sprintf(str, "CharacterLeftX : %d", CharacterLeftX);
		pDC->TextOut(200, 80, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}
