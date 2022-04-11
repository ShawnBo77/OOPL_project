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

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//註解請參照BlueGoblin.cpp 												   //
	/////////////////////////////////////////////////////////////////////////////
	MonsterCactus::MonsterCactus() {
		_x = 400;
		_y = 400;
		hp = 1200;
		attackDamage = 20;
	}

	MonsterCactus::MonsterCactus(int x, int y, Character* c) : Monster(x, y, 1200, 20, c) {
	}

	MonsterCactus::~MonsterCactus() {
	}

	void MonsterCactus::LoadBitmap() {
		bloodBar.loadBloodBar();

	}

	void MonsterCactus::OnShow(Map* m) {
		if (isAlive()) {
			bloodBar.setXY(GetLeftX(), GetTopY() - 16);
			bloodBar.showBloodBar(m, hp - 16);
		}
		if (!isAlive()) {

		}
	}

	int MonsterCactus::GetLeftX() {
		return _x;
	}

	int MonsterCactus::GetTopY() {
		return _y;
	}

	int MonsterCactus::GetRightX() {
		return _x + cactus.Width();
	}

	int MonsterCactus::GetButtonY() {
		return _y + cactus.Height();
	}

	void MonsterCactus::Initialize() {
		_x = init_x;
		_y = init_y;
		hp = 1200;
		attackDamage = 20;
		bloodBar.setFullHP(hp);
	}

	bool MonsterCactus::isIntersect() {
		if (isAlive()) {
			if (character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX()
				&& character->GetButtonY() <= GetTopY() && character->GetButtonY() >= GetButtonY()) { //角色右方碰到怪物
				character->SetIsAttackFromRight(true);
				return true;
			}
			if (character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX()
				&& character->GetButtonY() <= GetTopY() && character->GetButtonY() >= GetButtonY()) { //角色左方碰到怪物
				character->SetIsAttackFromLeft(true);
				return true;
			}
			if ((character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX() ||
				character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX())
				&& character->GetButtonY() <= GetTopY() && character->GetButtonY() >= GetButtonY()) { //角色下方碰到怪物
				character->SetIsAttackFromButton(true);
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}


}
