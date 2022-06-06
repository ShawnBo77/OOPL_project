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
#include "MonsterMosquito.h"
#include "Util.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Mosquito的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterMosquito::MonsterMosquito()
	{
		_x = 400;
		_y = 400;
		hp = 50;
		attackDamage = 5;
		BORDER = 20;
		HORIZONTAL_GAP = 0;
	}

	MonsterMosquito::MonsterMosquito(int x, int y, Character* c) : Monster(x, y, 50, 5, c)
	{
		BORDER = 20;
		HORIZONTAL_GAP = 0;
	}

	MonsterMosquito::~MonsterMosquito()
	{
	}

	void MonsterMosquito::LoadBitmap()
	{
		bloodBar.LoadBitmap();
		faceLeft.AddBitmap(".\\res\\monster_mosquito01_left.bmp", RGB(0, 0, 0));
		faceLeft.AddBitmap(".\\res\\monster_mosquito02_left.bmp", RGB(0, 0, 0));
		faceRight.AddBitmap(".\\res\\monster_mosquito01_right.bmp", RGB(0, 0, 0));
		faceRight.AddBitmap(".\\res\\monster_mosquito02_right.bmp", RGB(0, 0, 0));
		sourceMosquitoJump.LoadBitmap(".\\res\\source_mosquito_jump.bmp", RGB(0, 0, 0));
		black.LoadBitmap(".\\res\\black.bmp", RGB(0, 0, 0));
	}

	void MonsterMosquito::Initialize()
	{
		_x = init_x;
		_y = init_y;
		currentFloor = 0;
		BORDER = 5;
		HORIZONTAL_GAP = 0;
		hp = 20;
		attackDamage = 5;
		facingLR = 0;
		bloodBar.setFullHP(hp);
		STEP_SIZE = 5;
		velocity = 0;
		lightBulbInside = 20;
		hasGottenLightBulb = false;
		hasGottenSource = false;
	}

	void MonsterMosquito::OnMove(Map* m)
	{
		if (!m == NULL)
		{
			m->monsterFloorChanging((GetLeftX() + GetRightX()) / 2);
		}
		if (isAlive())
		{
			if (GetTopY() < m->getCeiling()) //向上移動
			{
				_y -= STEP_SIZE;
			}
			if (m->isEmpty(GetRightX() + STEP_SIZE, GetTopY()) && m->isEmpty(GetRightX() + STEP_SIZE, GetButtonY())) //向右移動
			{
				_x += STEP_SIZE;
			}
			if (m->isEmpty(GetLeftX() - STEP_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - STEP_SIZE, GetButtonY())) //向左移動
			{
				_x -= STEP_SIZE;
			}
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
				touchSource(m, mosquito_jump_p);
			}
		}
	}

	void MonsterMosquito::OnShow(Map* m)
	{
		if (isAlive())
		{
			if (isAttacked && isSparkleEffectShow)
			{
				isAttackedEffectOnShow(m);
			}
			else
			{
				if (facingLR == 0)
				{
					faceLeft.SetTopLeft(_x, _y);
					faceLeft.OnShow();
				}
				else
				{
					faceRight.SetTopLeft(_x, _y);
					faceRight.OnShow();
				}
			}
			bloodBar.setXY(GetLeftX() + m->getXMovement(), GetTopY() - 16);
			bloodBar.showBloodBar(m, hp);
			if (lossHpShowFlag)
			{
				lossHpShow(m);
			}
			lossHpTimer.CaculateTimeForFalse(&lossHpShowFlag, 0.5);
		}
		else
		{
			if (!hasGottenSource)
			{
				sourceMosquitoJump.SetTopLeft((_x + GetRightX()) / 2 + m->getXMovement(), m->getMonsterFloor() - 64 - m->getYMovement());
				sourceMosquitoJump.ShowBitmap();
			}
		}
		//showData();
	}

	void MonsterMosquito::showData()
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

	int MonsterMosquito::GetLeftX()
	{
		return _x + 18;
	}

	int MonsterMosquito::GetTopY()
	{
		return _y + 28;
	}

	int MonsterMosquito::GetRightX()
	{
		return _x + 80;
	}

	int MonsterMosquito::GetButtonY()
	{
		return _y + 68;
	}
}
