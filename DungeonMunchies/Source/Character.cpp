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
		characterH = 60;
		characterW = 60;
		const int X_POS = 60;
		const int Y_POS = 60;
		characterX = X_POS;
		characterY = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Character::LoadBitmap()
	{
		//animation.AddBitmap(IDB_GRAY);
		animation.AddBitmap(IDB_MAINCHARACTERSTAND, RGB(255, 51, 255));
		animation.AddBitmap(IDB_MAINCHARACTERWALK1, RGB(255, 51, 255));
		animation.AddBitmap(IDB_MAINCHARACTERWALK2, RGB(255, 51, 255));
		animation.AddBitmap(IDB_MAINCHARACTERWALK3, RGB(255, 51, 255));
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