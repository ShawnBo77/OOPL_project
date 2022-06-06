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
		hp = 50;
		attackDamage = 5;
		BORDER = 20;
		HORIZONTAL_GAP = 0;
	}

	MonsterCactus::MonsterCactus(int x, int y, Character* c) : Monster(x, y, 50, 5, c)
	{
		BORDER = 20;
		HORIZONTAL_GAP = 0;
	}

	MonsterCactus::~MonsterCactus()
	{
	}

	void MonsterCactus::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		cactusAlive.LoadBitmap(IDB_MONSTERCACTUSALIVE, RGB(0, 0, 0));
		cactusDead.LoadBitmap(IDB_MONSTERCACTUSDEAD, RGB(0, 0, 0));
		sourceGrassFast.LoadBitmap(".\\res\\source_grass_fast.bmp", RGB(0, 0, 0));
		black.LoadBitmap(".\\res\\black.bmp", RGB(0, 0, 0));
	}

	void MonsterCactus::Initialize()
	{
		_x = init_x;
		_y = init_y;
		RelativeMovement = 0;
		hp = 50;
		attackDamage = 5;
		bloodBar.setFullHP(hp);
		hasGottenSource = false;
		lightBulbInside = 10;
		hasGottenLightBulb = false;
	}

	void MonsterCactus::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow();
			}
			else
			{
				cactusAlive.SetTopLeft(_x + RelativeMovement, _y);
				cactusAlive.ShowBitmap();
			}
			bloodBar.setXY(GetLeftX() + RelativeMovement, GetTopY() - 16);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		else
		{
			cactusDead.SetTopLeft(_x + RelativeMovement, _y + (cactusAlive.Height() - cactusDead.Height()));
			cactusDead.ShowBitmap();
			if (!hasGottenSource)
			{
				sourceGrassFast.SetTopLeft((_x + GetRightX()) / 2 + RelativeMovement, m->getMonsterFloor() - 64);
				sourceGrassFast.ShowBitmap();
			}
		}
		//showData();
	}

	void MonsterCactus::showData()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		char position[600];								// Demo 數字對字串的轉換
		sprintf(position, "CactusLeftX:%d CactusRightX:%d CactusTopY:%d CactusButtonY:%d CactusHp: %d sparkleEffectTimer(%f, %f, %f)"
			, GetLeftX(), GetRightX(), GetTopY(), GetButtonY(), GetCurrentHp(), (double)sparkleEffectTimer.GetStartTime(), (double)sparkleEffectTimer.GetFinishTime(), (double)sparkleEffectTimer.GetTime());
		//sprintf(str, "CharacterLeftX : %d", CharacterLeftX);
		pDC->TextOut(200, 50, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
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

	void MonsterCactus::OnMove(Map* m)
	{
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
				touchSource(m, grass_fast_p);
			}
		}
		if (!m == NULL)
		{
			m->monsterFloorChanging(GetLeftX());
			_y = m->getMonsterFloor() - 120;
		}
	}
}
