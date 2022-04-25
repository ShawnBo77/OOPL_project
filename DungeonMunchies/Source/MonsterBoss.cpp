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
		hp = 10;
		attackDamage = 5;
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
		walkingRight.AddBitmap(".\\res\\boss_right_stand.bmp", RGB(0, 0, 0));
		walkingRight.AddBitmap(".\\res\\boss_right_walk01.bmp", RGB(0, 0, 0));
		walkingRight.AddBitmap(".\\res\\boss_right_walk02.bmp", RGB(0, 0, 0));
		walkingRight.AddBitmap(".\\res\\boss_right_walk03.bmp", RGB(0, 0, 0));
		walkingRight.AddBitmap(".\\res\\boss_right_walk04.bmp", RGB(0, 0, 0));

		//向左走動畫
		walkingLeft.AddBitmap(".\\res\\boss_left_stand.bmp", RGB(0, 0, 0));
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
		hitRightEffect.AddBitmap(".\\res\\boss_right_hit_effect04.bmp", RGB(0, 0, 0));
		hitRightEffect.AddBitmap(".\\res\\boss_right_hit_effect05.bmp", RGB(0, 0, 0));
		
		//向左捶
		hitLeft.AddBitmap(".\\res\\boss_left_hit01.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit02.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit03.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit04.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit05.bmp", RGB(0, 0, 0));
		hitLeft.AddBitmap(".\\res\\boss_left_hit06.bmp", RGB(0, 0, 0));
		//向左捶效果
		hitLeftEffect.AddBitmap(".\\res\\boss_left_hit_effect04.bmp", RGB(0, 0, 0));
		hitLeftEffect.AddBitmap(".\\res\\boss_left_hit_effect05.bmp", RGB(0, 0, 0));

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
		hp = 10;
		attackDamage = 5;
		bloodBar.setFullHP(hp);
	}

	void MonsterBoss::OnShow(Map* m)
	{
		if (isAlive())
		{
			
		}
		if (!isAlive())
		{
			
		}
		testPosition();
	}

	void MonsterBoss::testPosition()
	{
		//int CharacterLeftX = character->GetLeftX();
		//int CharacterRightX = character->GetRightX();
		//int CharacterTopY = character->GetTopY();
		//int CharacterButtonY = character->GetButtonY();
		//CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		//CFont f, * fp;
		//f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		//fp = pDC->SelectObject(&f);					// 選用 font f
		//pDC->SetBkColor(RGB(230, 220, 200));
		//pDC->SetTextColor(RGB(0, 0, 0));
		//char position[500];								// Demo 數字對字串的轉換
		//sprintf(position, "CharacterLeftX:%d CharacterRightX:%d CharacterTopY:%d CharacterButtonY:%d \r\n\
		//	CactusLeftX:%d CactusRightX:%d CactusTopY:%d CactusButtonY:%d"
		//	, CharacterLeftX, CharacterRightX, CharacterTopY, CharacterButtonY,
		//	GetLeftX(), GetRightX(), GetTopY(), GetButtonY());
		////sprintf(str, "CharacterLeftX : %d", CharacterLeftX);
		//pDC->TextOut(200, 100, position);
		//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	int MonsterBoss::GetLeftX()
	{
		return _x;
	}

	int MonsterBoss::GetTopY()
	{
		return _y;
	}

	int MonsterBoss::GetRightX()
	{
		return _x + walkingLeft.Width();
	}

	int MonsterBoss::GetButtonY()
	{
		return _y + walkingLeft.Height();
	}

	void MonsterBoss::intersect()
	{
		if (isAlive())
		{
			if (character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX()
				&& character->GetButtonY() >= GetTopY() && character->GetButtonY() <= GetButtonY())
			{ //角色右方碰到怪物
				character->SetIsAttackedFromRight(true);
				isIntersect = true;
			}
			if (character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX()
				&& character->GetButtonY() >= GetTopY() && character->GetButtonY() <= GetButtonY())
			{ //角色左方碰到怪物
				character->SetIsAttackedFromLeft(true);
				isIntersect = true;
			}
			if ((character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX() ||
				character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX())
				&& character->GetButtonY() >= GetTopY() && character->GetButtonY() <= GetButtonY())
			{ //角色下方碰到怪物
				character->SetIsAttackedFromButton(true);
				isIntersect = true;
			}
			if (isIntersect && !character->GetIsInvincible())
			{
				character->lossCurrentHp(attackDamage);
			}
		}
		isIntersect = false;
	}

	void MonsterBoss::OnMove()
	{
		if (isAlive())
		{
			intersect();
		}
	}
}
