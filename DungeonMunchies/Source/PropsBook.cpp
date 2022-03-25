#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <vector>
#include "Util.h"
#include "Prop.h"
#include "PropsBook.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
// 這個class為道具書模式
/////////////////////////////////////////////////////////////////////////////

	PropsBook::PropsBook()
	{
		MosquitoJump = new Prop();
		ShrimpBlood = new Prop();
		GrassFast = new Prop();
		BananaAttack = new Prop();
		ShrimpAttack = new Prop();
		GuavaJuiceBlood = new Prop();
		propCase = mosquito_jump;
	}

	PropsBook::~PropsBook()
	{
		delete MosquitoJump;
		delete ShrimpBlood;
		delete GrassFast;
		delete BananaAttack;
		delete GuavaJuiceBlood;
	}

	void PropsBook::Initialize() {
		propCase = mosquito_jump;
		choicex = 125;
		choicey = 90;
	}

	void PropsBook::setXY(CPoint mousePosition) {
		mx = mousePosition.x;
		my = mousePosition.y;
	}

	void PropsBook::setXY(int x, int y) {
		mx = x;
		my = y;
	}

	int PropsBook::getMX() {
		return mx;
	}

	int PropsBook::getMY() {
		return my;
	}

	void PropsBook::setPropCase() {
		if (mx > 125 && my > 90 && mx < 381 && my < 131) {
			int row = (my - 91) / 40;
			int column = (mx - 127) / 43;
			if (row == 0 && column == 0) {
				propCase = mosquito_jump;
			}
			else if (row == 0 && column == 1) {
				propCase = shrimp_blood;
			}
			else if (row == 0 && column == 2) {
				propCase = grass_fast;
			}
			else if (row == 0 && column == 3) {
				propCase = banana_attack;
			}
			else if (row == 0 && column == 4) {
				propCase = shrimp_attack;
			}
			else if (row == 0 && column == 5) {
				propCase = guava_juice_blood;
			}
			choicex = column * 43 + 125;
			choicey = row * 43 + 90;
		}
	}

	void PropsBook::setPropCase(CPoint mousePosition) {
		setXY(mousePosition);
		setPropCase();
	}
	
	void PropsBook::LoadBitmap() {
		propsBook.LoadBitmap(IDB_PROPSBOOK);
		propsBookChoice.LoadBitmap(IDB_PROPSBOOKCHOICE, RGB(0, 0, 0));
		MosquitoJump->LoadBitmap(IDB_PROPMOSQUITOJUMP);
		ShrimpBlood->LoadBitmap(IDB_PROPSHRIMPBLOOD);
		GrassFast->LoadBitmap(IDB_PROPGRASSFAST);
		BananaAttack->LoadBitmap(IDB_PROPBANANAATTACK);
		ShrimpAttack->LoadBitmap(IDB_PROPSHRIMPATTACK);
		GuavaJuiceBlood->LoadBitmap(IDB_PROPGUAVAJUICEBLOOD);
	}

    void PropsBook::onShow() {
		propsBook.SetTopLeft(0, 0);
		propsBook.ShowBitmap();
		propsBookChoice.SetTopLeft(choicex, choicey);
		propsBookChoice.ShowBitmap();
		switch (propCase) {
		case mosquito_jump:
			MosquitoJump->onShow();
			break;
		case shrimp_blood:
			ShrimpBlood->onShow();
			break;
		case grass_fast:
			GrassFast->onShow();
			break;
		case banana_attack:
			BananaAttack->onShow();
			break;
		case shrimp_attack:
			ShrimpAttack->onShow();
			break;
		case guava_juice_blood:
			GuavaJuiceBlood->onShow();
			break;
		default:
			break;
		}
    }
}