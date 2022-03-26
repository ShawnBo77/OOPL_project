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
		setPropList();
		setIconList();
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
		if (mx > 127 && my > 91 && mx < 381 && my < 131) {
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

	void PropsBook::setIconList() {
		iconList.push_back(MosquitoJumpIcon);
		iconList.push_back(ShrimpBloodIcon);
		iconList.push_back(GrassFastIcon);
		iconList.push_back(BananaAttackIcon);
		iconList.push_back(ShrimpAttackIcon);
		iconList.push_back(GuavaJuiceBloodIcon);
		iconList = setIconPosition(propList, iconList);
	}
	
	vector<CMovingBitmap> PropsBook::setIconPosition(vector<Prop*> propList, vector<CMovingBitmap> iconList) {
		int iconx, icony;
		int counter = 0;
		for (int row = 0; row < 7; row++) {
			icony = row * 40 + 91;
			for (int column = 0; column < 7; column++) {
				iconx = column * 43 + 125;
				iconList[counter].SetTopLeft(iconx, icony);
				if (counter == (iconList).size()-1) {
					return iconList;
				}
				counter++;
			}
		}
		return iconList;
	}

	void PropsBook::setPropList() {
		propList.push_back(MosquitoJump);
		propList.push_back(ShrimpBlood);
		propList.push_back(GrassFast);
		propList.push_back(BananaAttack);
		propList.push_back(ShrimpAttack);
		propList.push_back(GuavaJuiceBlood);
		//MosquitoJump->setPropFlag(true);
		//ShrimpBlood->setPropFlag(true);
		//GrassFast->setPropFlag(true);
		//BananaAttack->setPropFlag(true);
		//ShrimpAttack->setPropFlag(true);
		//GuavaJuiceBlood->setPropFlag(true);
	}

	void PropsBook::LoadBitmap() {
		propsBook.LoadBitmap(IDB_PROPSBOOK);
		propsBookChoice.LoadBitmap(IDB_PROPSBOOKCHOICE, RGB(0, 0, 0));
		propHave.LoadBitmap(IDB_PROPHAVE);
		propsPot1.LoadBitmap(IDB_PROPSPOT1);
		MosquitoJumpIcon.LoadBitmap(IDB_PROPMOSQUITOJUMPICON);
		ShrimpBloodIcon.LoadBitmap(IDB_PROPSHRIMPBLOODICON);
		GrassFastIcon.LoadBitmap(IDB_PROPGRASSFASTICON);
		BananaAttackIcon.LoadBitmap(IDB_PROPBANANAATTACKICON);
		ShrimpAttackIcon.LoadBitmap(IDB_PROPSHRIMPATTACKICON);
		GuavaJuiceBloodIcon.LoadBitmap(IDB_PROPGUAVAJUICEBLOODICON);
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
		propHave.SetTopLeft(475, 247);
		propsPot1.SetTopLeft(568,373);

		for (unsigned int i = 0; i < iconList.size(); i++) {
			if (propList[i]->getPropFlag()) {
				iconList[i].ShowBitmap();
			}
		}

		switch (propCase) {
		case mosquito_jump:
			MosquitoJump->onShow();
			if (MosquitoJump->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_blood:
			ShrimpBlood->onShow();
			if (ShrimpBlood->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case grass_fast:
			GrassFast->onShow();
			if (GrassFast->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case banana_attack:
			BananaAttack->onShow();
			if (BananaAttack->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_attack:
			ShrimpAttack->onShow();
			if (ShrimpAttack->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case guava_juice_blood:
			GuavaJuiceBlood->onShow();
			if (GuavaJuiceBlood->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		default:
			break;
		}
		propsBookChoice.SetTopLeft(choicex, choicey);
		propsBookChoice.ShowBitmap();
    }
}