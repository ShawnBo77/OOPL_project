#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Monster.h"
#include "Character.h"
#include "Map.h"

namespace game_framework
{
	Monster::Monster()
	{
		_x = 400;
		_y = 400;
		hp = 1200;
		attackDamage = 0;
		isAttacking = false;
		isIntersect = false;
	}

	Monster::Monster(int x, int y, int enemyHp, int ATK, Character* c)
	{
		_x = x;
		_y = y;
		init_x = x;
		init_y = y;
		hp = enemyHp;
		maxHp = enemyHp;
		attackDamage = ATK;
		isAttacking = false;
		isIntersect = false;
		character = c;
		characterDirectionLR = 0;
		characterDirectionTD = 0;
	}

	Monster::~Monster()
	{
	}

	void Monster::SetIsIntersect(bool flag)
	{
		isIntersect = flag;
	}

	bool Monster::GetIsIntersect()
	{
		return isIntersect;
	}

	int Monster::distanceToCharacter() //與角色的距離 若太遠則不用動作
	{
		int x_distance = _x - character->GetLeftX();
		int y_distance = _y - character->GetTopY();
		return (int)(sqrt(pow(x_distance, 2) + pow(y_distance, 2)));
	}

	void Monster::SetCharacterDirection()
	{
		int cX, cY, mX, mY;
		cX = (character->GetLeftX() + character->GetRightX()) / 2;
		cY = (character->GetButtonY() + character->GetTopY()) / 2;
		mX = (_x + GetRightX()) / 2;
		mY = (_y + GetButtonY()) / 2;
		if (cX < mX)
		{
			characterDirectionLR = 0; //角色在怪物左邊
		}
		else
		{
			characterDirectionLR = 1;
		}
		if (cY < mY)
		{
			characterDirectionTD = 0;
		}
		else
		{
			characterDirectionTD = 1;
		}
	}

	bool Monster::GetCharacterDirectionLR()
	{
		return characterDirectionLR;
	}

	bool Monster::GetCharacterDirectionTD()
	{
		return characterDirectionTD;
	}

	double Monster::hpProportion()
	{
		return (double)(hp) / maxHp;
	}

	void Monster::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void Monster::SetMovingDown(bool b)
	{
		isMovingDown = b;
	}

	bool Monster::GetIsMovingDown()
	{
		return isMovingDown;
	}

	void Monster::SetMovingUp(bool b)
	{
		isMovingUp = b;
	}

	bool Monster::GetIsMovingUp()
	{
		return isMovingUp;
	}

	void Monster::SetMovingLeft(bool b)
	{
		isMovingLeft = b;
	}

	bool Monster::GetIsMovingLeft()
	{
		return isMovingLeft;
	}

	void Monster::SetMovingRight(bool b)
	{
		isMovingRight = b;
	}

	bool Monster::GetIsMovingRight()
	{
		return isMovingRight;
	}

	void Monster::SetFacingLR(bool b)
	{
		facingLR = b;
	}

	bool Monster::GetFacingLR()
	{
		return facingLR;
	}

	bool Monster::isAlive()
	{
		if (hp <= 0)
		{
			return false;
		}
		return true;
	}

	bool Monster::isAttack()
	{
		return isAttacking;
	}

	void Monster::knockBack()
	{
		if (facingLR == 0)
		{
			_x += 1;
		}
		if (facingLR == 1)
		{
			_x -= 1;
		}
	}
	void Monster::SetIsOnTheFloor(bool b)
	{
		isOnTheFloor = b;
	}
	bool Monster::GetIsOnTheFloor()
	{
		return isOnTheFloor;
	}
	void Monster::SetMaxHp(int x)
	{
		maxHp = x;
	}
	int Monster::GetMaxHp()
	{
		return maxHp;
	}
	void Monster::SetCurrentHp(int x)
	{
		hp = x;
	}
	int Monster::GetCurrentHp()
	{
		return hp;
	}
	void Monster::SetIsAttacking(bool flag)
	{
		isAttacking = flag;
	}
	bool Monster::GetIsAttacking()
	{
		return isAttacking;
	}
	void Monster::SetIsAttacked(bool flag)
	{
		isAttacked = flag;
	}
	bool Monster::GetIsAttacked()
	{
		return isAttacked;
	}
	void Monster::SetAttackDamage(int x)
	{
		attackDamage = x;
	}
	int Monster::GetAttackDamage()
	{
		return attackDamage;
	}
}
