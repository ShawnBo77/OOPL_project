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
#include "MonsterBanana.h"
#include "Util.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Banana的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterBanana::MonsterBanana()
	{
		_x = 400;
		_y = 400;
		hp = 50;
		attackDamage = 0;
		BORDER = 20;
	}

	MonsterBanana::MonsterBanana(int x, int y, Character* c) : Monster(x, y, 20, 5, c)
	{
		BORDER = 20;
	}

	MonsterBanana::~MonsterBanana()
	{
	}

	void MonsterBanana::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		bananaAlive.LoadBitmap(".\\res\\monster_banana.bmp", RGB(0, 0, 0));
		bananaDead.LoadBitmap(".\\res\\monster_banana_dead.bmp", RGB(0, 0, 0));
		sourceBananaAttack.LoadBitmap(".\\res\\source_banana_attack.bmp", RGB(0, 0, 0));
		black.LoadBitmap(".\\res\\black.bmp", RGB(0, 0, 0));
	}

	void MonsterBanana::Initialize()
	{
		_x = init_x;
		_y = init_y;
		currentFloor = 0;
		hp = 50;
		attackDamage = 5;
		bloodBar.setFullHP(hp);
		hasGottenSource = false;
		lightBulbInside = 60;
		hasGottenLightBulb = false;
		canStandOn = true;
	}

	void MonsterBanana::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow(m);
			}
			else
			{
				bananaAlive.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
				bananaAlive.ShowBitmap();
			}
			bloodBar.setXY(GetLeftX() + m->getXMovement(), GetTopY() - 16 + m->getYMovement());
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		if (!isAlive())
		{
			bananaDead.SetTopLeft(_x + m->getXMovement(), _y + bananaAlive.Height() - bananaDead.Height() + m->getYMovement());
			bananaDead.ShowBitmap();
			if (!hasGottenSource)
			{
				sourceBananaAttack.SetTopLeft((GetLeftX() + GetRightX()) / 2 + m->getXMovement(), GetButtonY() - 64 + m->getYMovement());
				sourceBananaAttack.ShowBitmap();
			}
		}
		showData();
	}

	void MonsterBanana::showData()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		char position[500];								// Demo 數字對字串的轉換
		sprintf(position, "BananaLeftX:%d BananaRightX:%d BananaTopY:%d BananaButtonY:%d BananaHp: %d"
			, GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), GetCurrentHp());
		//sprintf(str, "CharacterLeftX : %d", CharacterLeftX);
		pDC->TextOut(200, 50, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	int MonsterBanana::GetLeftX()
	{
		return _x;
	}

	int MonsterBanana::GetTopY()
	{
		return _y;
	}

	int MonsterBanana::GetRightX()
	{
		return _x + bananaAlive.Width();
	}

	int MonsterBanana::GetButtonY()
	{
		return _y + bananaAlive.Height();
	}

	void MonsterBanana::OnMove(Map* m)
	{
		if (!m == NULL)
		{
			m->monsterFloorChanging(GetLeftX());
			_y = m->getMonsterFloor() - bananaAlive.Height() - 6;
			currentFloor = m->getMonsterFloor();
		}
		if (isAlive())
		{
			//intersect();
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
				touchSource(m, banana_attack_p);
			}
		}
	}
}
