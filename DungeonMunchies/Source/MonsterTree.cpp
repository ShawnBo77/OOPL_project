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
#include "MonsterTree.h"
#include "Util.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物tree的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterTree::MonsterTree()
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

	MonsterTree::MonsterTree(int x, int y, Character* c) : Monster(x, y, 12, 5, c)
	{
		hp = 50;
		attackDamage = 5;
		facingLR = 0;
		actionNum = 0;
		STEP_SIZE = 1;
		attackCD = false;
	}

	MonsterTree::~MonsterTree()
	{
	}

	void MonsterTree::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		sleepLeft.LoadBitmap(".\\res\\monster_tree_sleep_left.bmp", RGB(0, 0, 0));
		sleepRight.LoadBitmap(".\\res\\monster_tree_sleep_right.bmp", RGB(0, 0, 0));

		walkLeft.AddBitmap(".\\res\\monster_tree_walk01_left.bmp", RGB(0, 0, 0));
		walkLeft.AddBitmap(".\\res\\monster_tree_walk02_left.bmp", RGB(0, 0, 0));
		walkLeft.AddBitmap(".\\res\\monster_tree_walk03_left.bmp", RGB(0, 0, 0));
		walkLeft.AddBitmap(".\\res\\monster_tree_walk04_left.bmp", RGB(0, 0, 0));
		walkRight.AddBitmap(".\\res\\monster_tree_walk01_right.bmp", RGB(0, 0, 0));
		walkRight.AddBitmap(".\\res\\monster_tree_walk02_right.bmp", RGB(0, 0, 0));
		walkRight.AddBitmap(".\\res\\monster_tree_walk03_right.bmp", RGB(0, 0, 0));
		walkRight.AddBitmap(".\\res\\monster_tree_walk04_right.bmp", RGB(0, 0, 0));

		attackLeft.AddBitmap(".\\res\\monster_tree_attack01_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_tree_attack02_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_tree_attack03_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_tree_attack04_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_tree_attack05_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_tree_attack06_left.bmp", RGB(0, 0, 0));
		attackLeft.AddBitmap(".\\res\\monster_tree_attack07_left.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_tree_attack01_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_tree_attack02_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_tree_attack03_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_tree_attack04_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_tree_attack05_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_tree_attack06_right.bmp", RGB(0, 0, 0));
		attackRight.AddBitmap(".\\res\\monster_tree_attack07_right.bmp", RGB(0, 0, 0));

		deadLeft.LoadBitmap(".\\res\\monster_tree_dead_left.bmp", RGB(0, 0, 0));
		deadRight.LoadBitmap(".\\res\\monster_tree_dead_right.bmp", RGB(0, 0, 0));
	}

	void MonsterTree::Initialize()
	{
		_x = init_x;
		_y = init_y;
		RelativeMovement = 0;
		BORDER = 5;
		HORIZONTAL_GAP = 0;
		hp = 50;
		attackDamage = 5;
		facingLR = 0;
		actionNum = 0;
		bloodBar.setFullHP(hp);
		STEP_SIZE = 5;
	}

	void MonsterTree::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (facingLR == 0)
			{
				if (actionNum == 0)
				{
					walkLeft.SetTopLeft(_x + RelativeMovement, _y); //讓圖片中怪物顯示靠向左
					//walkLeft.SetDelayCount(3);
					walkLeft.OnShow();
				}
				else
				{
					attackLeft.SetTopLeft(_x + RelativeMovement, _y);
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
					walkRight.SetTopLeft(_x + RelativeMovement, _y);
					walkRight.OnShow();
				}
				else
				{
					attackRight.SetTopLeft(_x + RelativeMovement, _y);
					attackRight.SetDelayCount(4);
					attackRight.OnShow();
					if (attackRight.IsFinalBitmap())
					{
						actionNum = 0;
					}
				}
			}
			bloodBar.setXY(_x + RelativeMovement, _y - 16);
			bloodBar.showBloodBar(m, hp);
		}
		else
		{
			if (facingLR == 0)
			{
				deadLeft.SetTopLeft(_x + RelativeMovement, _y);
				deadLeft.ShowBitmap();
			}
			else
			{
				deadRight.SetTopLeft(_x + RelativeMovement, _y);
				deadRight.ShowBitmap();
			}
		}
		showData();
	}

	void MonsterTree::OnMove()
	{
		if (!character->GetMap() == NULL)
		{
			character->GetMap()->monsterFloorChanging(GetLeftX());
			_y = character->GetMap()->getMonsterFloor() -170;
		}
		if (isAlive())
		{
			SetCharacterDirection();
			if (actionNum == 0)
			{
				facingLR = characterDirectionLR;
			}
			if (distanceToCharacter() < 130 && attackCD == false)
			{
				attack();
				intersect();
			}
			else if (distanceToCharacter() < 280 && actionNum == 0)
			{
				if (characterDirectionLR == 0 && (GetLeftX() - STEP_SIZE + BORDER) >= character->GetRightX())
				{
					_x -= STEP_SIZE;
				}
				else if (characterDirectionLR == 1 && (GetRightX() + STEP_SIZE - BORDER - 5) <= character->GetLeftX())
				{
					_x += STEP_SIZE;
				}
			}
			attackCDTime.CaculateTimeForFalse(&attackCD, 2);
			walkLeft.OnMove();
			walkRight.OnMove();

			attackLeft.OnMove();
			attackRight.OnMove();

			//intersect();
		}
	}

	void MonsterTree::SetFacingLR(bool flag)
	{
		facingLR = flag;
	}

	bool MonsterTree::GetFacingLR()
	{
		return facingLR;
	}

	void MonsterTree::SetActionNum(int num)
	{
		actionNum = num;
	}

	bool MonsterTree::GetActionNum()
	{
		return actionNum;
	}

	int MonsterTree::GetLeftX() //以物件本體為主(攻擊範圍不要算在裡面)
	{
		if (facingLR == 0) //left
		{
			return _x + 87;
		}
		else
		{
			return _x + 60;
		}
	}

	int MonsterTree::GetTopY() //需調整以對應顯示的圖(_y + (圖片高度-物體高度))
	{
		if (actionNum == 0) //left
		{
			return _y + 72;
		}
		else
		{
			return _y;
		}
	}

	int MonsterTree::GetRightX() //加上物體本身的長度
	{
		if (facingLR == 0) //left
		{
			return _x + 175;
		}
		else
		{
			return _x + 145;
		}
	}

	int MonsterTree::GetButtonY()
	{
		return _y + walkLeft.Height();
	}

	void MonsterTree::attack()
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
					if (isAttackSuccessfullyL(90))
					{
						character->SetIsAttackedFromRight(true);
						character->lossCurrentHp(attackDamage);
					}
				}
				else
				{
					if (isAttackSuccessfullyR(90))
					{
						character->SetIsAttackedFromLeft(true);
						character->lossCurrentHp(attackDamage);
					}
				}
			}
		}
	}

	void MonsterTree::showData()
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
		sprintf(position, "TreeLeftX:%d TreeRightX:%d TreeTopY:%d TreeButtonY:%d TreeHp:%d"
			,GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), GetCurrentHp());
		//sprintf(str, "CharacterLeftX : %d", CharacterLeftX);
		pDC->TextOut(200, 100, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}
