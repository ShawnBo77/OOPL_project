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
#include "Util.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Cactus的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterCactus::MonsterCactus()
	{
		_x = 400;
		_y = 400;
		hp = 10;
		attackDamage = 5;
	}

	MonsterCactus::MonsterCactus(int x, int y, Character* c) : Monster(x, y, 12, 5, c)
	{
	}

	MonsterCactus::~MonsterCactus()
	{
	}

	void MonsterCactus::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		cactusAlive.LoadBitmap(IDB_MONSTERCACTUSALIVE, RGB(0, 0, 0));
		cactusDead.LoadBitmap(IDB_MONSTERCACTUSDEAD, RGB(0, 0, 0));
	}

	void MonsterCactus::Initialize()
	{
		_x = init_x;
		_y = init_y;
		hp = 10;
		attackDamage = 5;
		bloodBar.setFullHP(hp);
	}

	void MonsterCactus::OnShow(Map* m)
	{
		if (isAlive())
		{
			cactusAlive.SetTopLeft(_x, _y);
			cactusAlive.ShowBitmap();
			bloodBar.setXY(GetLeftX(), GetTopY() - 16);
			bloodBar.showBloodBar(m, hp);
		}
		if (!isAlive())
		{
			cactusDead.SetTopLeft(_x, _y + (cactusAlive.Height() - cactusDead.Height()));
			cactusDead.ShowBitmap();
		}
		showData();
	}

	void MonsterCactus::showData()
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

	int MonsterCactus::GetButtonY()
	{
		return _y + cactusAlive.Height();
	}

	void MonsterCactus::intersect()
	{
		if (isAlive())
		{
			if (character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX()
				&& character->GetButtonY() >= GetTopY() - 20 && character->GetButtonY() <= GetButtonY())
			{ //角色右方碰到怪物
				character->SetIsAttackedFromRight(true);
				isIntersect = true;
			}
			if (character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX()
				&& character->GetButtonY() >= GetTopY() - 20 && character->GetButtonY() <= GetButtonY())
			{ //角色左方碰到怪物
				character->SetIsAttackedFromLeft(true);
				isIntersect = true;
			}
			if ((character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX() ||
				character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX())
				&& character->GetButtonY() >= GetTopY() - 20 && character->GetButtonY() <= GetButtonY())
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

	void MonsterCactus::OnMove()
	{
		if (isAlive())
		{
			intersect();
		}
	}
}
