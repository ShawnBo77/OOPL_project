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
		fullHp = enemyHp;
		attackDamage = ATK;
		isAttacking = false;
		isIntersect = false;
		character = c;
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

	int Monster::distanceToHero() //與角色的距離 若太遠則不用動作
	{
		int x_distance = _x - character->GetLeftX();
		int y_distance = _y - character->GetTopY();
		return (int)(sqrt(pow(x_distance, 2) + pow(y_distance, 2)));
	}

	double Monster::hpProportion()
	{
		return (double)(hp) / fullHp;
	}

	void Monster::SetMovingDown(bool b)
	{
		isMovingDown = b;
	}

	void Monster::SetMovingUp(bool b)
	{
		isMovingUp = b;
	}

	void Monster::SetMovingLeft(bool b)
	{
		isMovingLeft = b;
	}

	void Monster::SetMovingRight(bool b)
	{
		isMovingRight = b;
	}

	void Monster::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
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
		if (_direction == 0)
		{
			_x += 1;
		}
		if (_direction == 1)
		{
			_x -= 1;
		}
	}
}
