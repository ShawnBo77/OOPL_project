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
#include "MonsterCactusMutation.h"
#include "Util.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Cactus的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterCactusMutation::MonsterCactusMutation()
	{
		_x = 400;
		_y = 400;
		hp = 50;
		attackDamage = 5;
		BORDER = 20;
	}

	MonsterCactusMutation::MonsterCactusMutation(int x, int y, Character* c) : Monster(x, y, 50, 5, c)
	{
		BORDER = 20;
	}

	MonsterCactusMutation::~MonsterCactusMutation()
	{
	}

	void MonsterCactusMutation::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		cactusAlive.LoadBitmap(".\\res\\cactus_g_alive.bmp", RGB(0, 0, 0));
		cactusDead.LoadBitmap(".\\res\\cactus_g_dead.bmp", RGB(0, 0, 0));
		sourceGreenSword.LoadBitmap(".\\res\\source_green_sword.bmp", RGB(0, 0, 0));
		black.LoadBitmap(".\\res\\black.bmp", RGB(0, 0, 0));
	}

	void MonsterCactusMutation::Initialize()
	{
		_x = init_x;
		_y = init_y;
		currentFloor = 0;
		hp = 100;
		attackDamage = 5;
		bloodBar.setFullHP(hp);
		hasGottenSource = false;
		lightBulbInside = 10;
		hasGottenLightBulb = false;
	}

	void MonsterCactusMutation::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow(m);
			}
			else
			{
				cactusAlive.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
				cactusAlive.ShowBitmap();
			}
			bloodBar.setXY(GetLeftX() + m->getXMovement(), GetTopY() + m->getYMovement() - 16);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		else
		{
			cactusDead.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement() + (cactusAlive.Height() - cactusDead.Height()));
			cactusDead.ShowBitmap();
			if (!hasGottenSource)
			{
				sourceGreenSword.SetTopLeft((GetLeftX() + GetRightX()) / 2 + m->getXMovement(), GetButtonY() - 64 + m->getYMovement());
				sourceGreenSword.ShowBitmap();
			}
		}
		showData();
	}

	void MonsterCactusMutation::showData()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		char position[600];								// Demo 數字對字串的轉換
		sprintf(position, "CactusLeftX:%d CactusRightX:%d CactusTopY:%d CactusButtonY:%d CactusHp: %d CactusFullHp: %d"
			, GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), GetCurrentHp(), bloodBar.getFullHP());
		//sprintf(str, "CharacterLeftX : %d", CharacterLeftX);
		pDC->TextOut(200, 50, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	int MonsterCactusMutation::GetLeftX()
	{
		return _x;
	}

	int MonsterCactusMutation::GetTopY()
	{
		return _y;
	}

	int MonsterCactusMutation::GetRightX()
	{
		return _x + cactusAlive.Width();
	}

	int MonsterCactusMutation::GetButtonY()
	{
		return _y + cactusAlive.Height();
	}

	void MonsterCactusMutation::OnMove(Map* m)
	{
		if (!m == NULL)
		{
			m->monsterFloorChanging(GetLeftX());
			_y = m->getMonsterFloor() - 120;
			currentFloor = m->getMonsterFloor();
		}
		if (isAlive())
		{
			intersect();
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
				touchSource(m, green_sword_s);
			}
		}
	}
}
