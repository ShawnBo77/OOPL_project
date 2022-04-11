#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Character.h"
#include "Map.h"

namespace game_framework
{
	Enemy::Enemy()
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack = 0;
	}
	Enemy::Enemy(int x, int y, int enemyHp, string name, Character* c)
	{
		_x = x;
		_y = y;
		init_x = x;
		init_y = y;
		hp = enemyHp;
		full_hp = enemyHp;
		attack = 0;
		isAttacking = false;
		character = c;
	}
	Enemy::~Enemy()
	{
	}
	int Enemy::distanceToHero() //與角色的距離 若太遠則不用動作
	{
		int x_distance = _x - character->GetLeftX();
		int y_distance = _y - character->GetTopY();
		return (int)(sqrt(pow(x_distance, 2) + pow(y_distance, 2)));
	}
	double Enemy::hpProportion()
	{
		return (double)(hp) / full_hp;
	}
	void Enemy::SetMovingDown(bool b)
	{
		isMovingDown = b;
	}
	void Enemy::SetMovingUp(bool b)
	{
		isMovingUp = b;
	}
	void Enemy::SetMovingLeft(bool b)
	{
		isMovingLeft = b;
	}
	void Enemy::SetMovingRight(bool b)
	{
		isMovingRight = b;
	}
	void Enemy::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}
	bool Enemy::isAlive()
	{
		if (hp <= 0)
		{
			return false;
		}
		return true;
	}
	bool Enemy::isAttack()
	{
		return isAttacking;
	}
	void Enemy::knockBack()
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