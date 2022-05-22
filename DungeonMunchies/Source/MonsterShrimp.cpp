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
#include <time.h>

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
		action = walk_a;
		STEP_SIZE = 1;
		attackCD = false;
	}

	MonsterShrimp::MonsterShrimp(int x, int y, Character* c) : Monster(x, y, 12, 50, c)
	{
		hp = 50;
		attackDamage = 5;
		facingLR = 0;
		action = walk_a;
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
		sourceShrimpAttack.LoadBitmap(".\\res\\source_shrimp_attack.bmp", RGB(0, 0, 0));
		sourceShrimpBlood.LoadBitmap(".\\res\\source_shrimp_blood.bmp", RGB(0, 0, 0));
	}

	void MonsterShrimp::Initialize()
	{
		_x = init_x;
		_y = init_y;
		RelativeMovement = 0;
		currentFloor = 0;
		BORDER = 5;
		HORIZONTAL_GAP = 0;
		hp = 50;
		bloodBar.setFullHP(hp);
		attackDamage = 5;
		facingLR = 0;
		action = walk_a;
		STEP_SIZE = 5;
		velocity = 0;
		hasGottenSource = false;
		lightBulbInside = 30;
		hasGottenLightBulb = false;
		srand((unsigned int)time(NULL));
	}

	void MonsterShrimp::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (facingLR == 0)
			{
				if (action == walk_a)
				{
					walkLeft.SetTopLeft(_x - 140 + RelativeMovement, _y); //讓圖片中怪物顯示靠向左
					//walkLeft.SetDelayCount(3);
					walkLeft.OnShow();
				}
				else
				{
					attackLeft.SetTopLeft(_x + RelativeMovement - 110, _y);
					attackLeft.SetDelayCount(3);
					attackLeft.OnShow();
					if (attackLeft.GetCurrentBitmapNumber() == 2)
					{
						attackJudge(100);
					}
					if (attackLeft.IsFinalBitmap())
					{
						action = walk_a;
						attackLeft.Reset();
					}
				}
			}
			else
			{
				if (action == walk_a)
				{
					walkRight.SetTopLeft(_x + RelativeMovement, _y);
					walkRight.OnShow();
				}
				else
				{
					attackRight.SetTopLeft(_x + RelativeMovement, _y);
					attackRight.SetDelayCount(3);
					attackRight.OnShow();
					if (attackRight.GetCurrentBitmapNumber() == 2)
					{
						attackJudge(100);
					}
					if (attackRight.IsFinalBitmap())
					{
						action = walk_a;
						attackRight.Reset();
					}
				}
			}
			bloodBar.setXY(GetLeftX(), GetTopY() - 16);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow();
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
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
			if (!hasGottenSource)
			{
				if (randN == 0)
				{
					sourceShrimpAttack.SetTopLeft((_x + GetRightX()) / 2 + RelativeMovement, m->getMonsterFloor() - 64);
					sourceShrimpAttack.ShowBitmap();
				}
				else
				{
					sourceShrimpBlood.SetTopLeft((_x + GetRightX()) / 2 + RelativeMovement, m->getMonsterFloor() - 64);
					sourceShrimpBlood.ShowBitmap();
				}
			}
		}
		//showData();
	}

	void MonsterShrimp::OnMove(Map* m)
	{
		if (!character->GetMap() == NULL)
		{
			character->GetMap()->monsterFloorChanging(GetLeftX());
			if (character->GetMap()->getMonsterFloor() > currentFloor)
			{
				if (_y < character->GetMap()->getMonsterFloor() - 138)
				{
					_y += velocity * 2;
					if (velocity < 6)
						velocity++;
				}
				else
				{
					currentFloor = character->GetMap()->getMonsterFloor();
					_y = currentFloor - 138;			// 當y座標低於地板，更正為地板上
					velocity = 0;
				}
			}
		}

		if (isAlive())
		{
			SetCharacterDirection();
			if (action == walk_a)
			{
				facingLR = characterDirectionLR;
			}
			if (distanceToCharacter() < 190 && attackCD == false)
			{
				attackStart();
			}
			else if (distanceToCharacter() < 280 && action == walk_a)
			{
				if (characterDirectionLR == 0 && (GetLeftX() - STEP_SIZE + BORDER) >= character->GetRightX() && character->GetMap()->isEmpty(GetLeftX() - STEP_SIZE - BORDER, GetButtonY() - BORDER))
				{
					_x -= STEP_SIZE;
				}
				else if (characterDirectionLR == 1 && (GetRightX() + STEP_SIZE - BORDER) <= character->GetLeftX() && character->GetMap()->isEmpty(GetRightX() + STEP_SIZE + BORDER, GetButtonY() - BORDER))
				{
					_x += STEP_SIZE;
				}
				randN = rand() % 2;
			}
			attackCDTime.CaculateTimeForFalse(&attackCD, 2);
			walkLeft.OnMove();
			walkRight.OnMove();
			if (action == attack_a)
			{
				attackOnMove();
			}

			//intersect();
		}
		else
		{
			if (!hasGottenLightBulb)
			{
				character->AddLightBulb(lightBulbInside);
				hasGottenLightBulb = true;
			}
			if (hasGottenSource == false)
			{

				if (randN == 0)
				{
					touchSource(m, shrimp_attack_p);
				}
				else
				{
					touchSource(m, shrimp_blood_p);
				}
			}
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

	int MonsterShrimp::GetLeftX() //顯示的圖會往左邊靠(onShow調整的)
	{
		return _x;
	}

	int MonsterShrimp::GetTopY() //需調整以對應顯示的圖(_y + (圖片高度-物體高度))
	{
		if (action == walk_a) //walk
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
		if (action == walk_a) //walk 
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
			, GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), GetCurrentHp());
		//sprintf(str, "CharacterLeftX : %d", CharacterLeftX);
		pDC->TextOut(200, 80, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void MonsterShrimp::attackOnMove()
	{
		if (facingLR == 0)
		{
			attackLeft.OnMove();
		}
		else if (facingLR == 1)
		{
			attackRight.OnMove();
		}
	}
}
