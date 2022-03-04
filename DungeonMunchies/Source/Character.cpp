#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的角色人物物件
/////////////////////////////////////////////////////////////////////////////
namespace game_framework {
    Character::Character() {
		Initialize();
        x = y = 50;
    }

	int Character::GetX1()
	{
		return x;
	}

	int Character::GetY1()
	{
		return y;
	}

	int Character::GetX2()
	{
		return x + animation.Width();
	}

	int Character::GetY2()
	{
		return y + animation.Height();
	}

	void Character::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Character::LoadBitmap()
	{
		animation.AddBitmap(IDB_MONSTER, RGB(255, 0, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_MONSTER, RGB(255, 0, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
	}

	void Character::OnMove()
	{
		const int STEP_SIZE = 2;
		animation.OnMove();
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
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

	void Character::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Character::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}