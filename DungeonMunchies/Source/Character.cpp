#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Map.h"

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的角色人物物件
/////////////////////////////////////////////////////////////////////////////
namespace game_framework {
    Character::Character() {
		Initialize();
		//characterX = characterY = 50;
    }

	int Character::GetLeftX()
	{
		return characterX;
	}

	int Character::GetTopY()
	{
		return characterY;
	}

	int Character::GetRightX()
	{
		return characterX + characterW; // + animation.Width();
	}

	int Character::GetButtonY()
	{
		return characterY + characterH; // + animation.Height();
	}

	void Character::Initialize()
	{
		characterH = 80;
		characterW = 80;
		const int X_POS = 100;
		const int Y_POS = 100;
		characterX = X_POS;
		characterY = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Character::LoadBitmap()
	{
		//animation.AddBitmap(IDB_GRAY);
		//animation.AddBitmap(IDB_BOSSRIGHTSTAND, RGB(0, 0, 0));

		/*animation.AddBitmap(IDB_HERORIGHTSTAND_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTJUMP_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTWALK1_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTWALK2_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTWALK3_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTSTAND_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTJUMP_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTWALK1_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTWALK2_G, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTWALK3_G, RGB(0, 0, 0));*/

		//animation.AddBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTJUMP_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK3_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTJUMP_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK3_S, RGB(0, 0, 0));

		//animation.AddBitmap(IDB_HERORIGHTATTACK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTATTACK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTATTACK3_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTATTACK4_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK3_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK4_S, RGB(0, 0, 0));

		//animation.AddBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL6, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL7, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL8, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL6, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL7, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL8, RGB(0, 0, 0));
	}

	void Character::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Character::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Character::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Character::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Character::OnMove(Map *m)
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		if (isMovingLeft && m->isEmpty(GetLeftX() - STEP_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - STEP_SIZE, GetButtonY() - 5)) {
			characterX -= STEP_SIZE;
			m->addSX(STEP_SIZE);
		}
		if (isMovingRight && m->isEmpty(GetRightX() + STEP_SIZE - 5, GetTopY()) && m->isEmpty(GetRightX() - 5 + STEP_SIZE, GetButtonY() - 5)) {
			characterX += STEP_SIZE;
			m->addSX(-STEP_SIZE);
		}
		if (isMovingUp && m->isEmpty(GetLeftX(), GetTopY() - STEP_SIZE) && m->isEmpty(GetRightX() - 5, GetTopY() - STEP_SIZE)) {
			characterY -= STEP_SIZE;
			m->addSY(STEP_SIZE);
		}
		if (isMovingDown && m->isEmpty(GetLeftX(), GetButtonY() + STEP_SIZE - 5) && m->isEmpty(GetRightX() - 5, GetButtonY() + STEP_SIZE - 5)) {
			characterY += STEP_SIZE;
			m->addSY(-STEP_SIZE);
		}
	}

	void Character::SetXY(int x, int y)
	{
		characterX = x;
		characterY = y;
	}

	void Character::OnShow()
	{
		animation.SetTopLeft(characterX, characterY);
		animation.OnShow();
	}
}