#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <vector>
#include "Util.h"
#include "SourceStorage.h"
#include "Prop.h"
#include "PropMosquitoJump.h"
#include "PropShrimpBlood.h"
#include "PropGrassFast.h"
#include "PropBananaAttack.h"
#include "PropShrimpAttack.h"
#include "PropGuavaJuiceBlood.h"
#include "PropsBook.h"
#include "PropStorage.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為道具書模式
	/////////////////////////////////////////////////////////////////////////////

	PropsBook::PropsBook()
	{
		propCase = mosquito_jump_p;
	}

	PropsBook::~PropsBook()
	{
	}

	void PropsBook::Initialize(Character* character) {
		propCase = mosquito_jump_p;
		choicex = 125;
		choicey = 90;
		setPropList();
		setIconList();
		propStorage = character->GetPropStorage();
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
				propCase = mosquito_jump_p;
			}
			else if (row == 0 && column == 1) {
				propCase = shrimp_blood_p;
			}
			else if (row == 0 && column == 2) {
				propCase = grass_fast_p;
			}
			else if (row == 0 && column == 3) {
				propCase = banana_attack_p;
			}
			else if (row == 0 && column == 4) {
				propCase = shrimp_attack_p;
			}
			else if (row == 0 && column == 5) {
				propCase = guava_juice_blood_p;
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
		iconList = setIconPosition(iconList);
	}
	
	vector<CMovingBitmap> PropsBook::setIconPosition(vector<CMovingBitmap> iconList) {
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
		//propList.push_back(MosquitoJumpP);
		//propList.push_back(ShrimpBloodP);
		//propList.push_back(GrassFastP);
		//propList.push_back(BananaAttackP);
		//propList.push_back(ShrimpAttackP);
		//propList.push_back(GuavaJuiceBloodP);
		//MosquitoJumpP->setPropFlag(true);
		//ShrimpBloodP->setPropFlag(true);
		//GrassFastP->setPropFlag(true);
		//BananaAttackP->setPropFlag(true);
		//ShrimpAttackP->setPropFlag(true);
		//GuavaJuiceBloodP->setPropFlag(true);
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

		MosquitoJumpDetails.LoadBitmap(IDB_PROPMOSQUITOJUMP);
		ShrimpBloodDetails.LoadBitmap(IDB_PROPSHRIMPBLOOD);
		GrassFastDetails.LoadBitmap(IDB_PROPGRASSFAST);
		BananaAttackDetails.LoadBitmap(IDB_PROPBANANAATTACK);
		ShrimpAttackDetails.LoadBitmap(IDB_PROPSHRIMPATTACK);
		GuavaJuiceBloodDetails.LoadBitmap(IDB_PROPGUAVAJUICEBLOOD);
	}

    void PropsBook::onShow(Character* character) {
		propsBook.SetTopLeft(0, 0);
		propsBook.ShowBitmap();
		propHave.SetTopLeft(475, 247);
		propsPot1.SetTopLeft(568,373);
		MosquitoJumpDetails.SetTopLeft(474, 27);
		ShrimpBloodDetails.SetTopLeft(474, 27);
		GrassFastDetails.SetTopLeft(474, 27);
		BananaAttackDetails.SetTopLeft(474, 27);
		ShrimpAttackDetails.SetTopLeft(474, 27);
		GuavaJuiceBloodDetails.SetTopLeft(474, 27);

		for (unsigned int i = 0; i < iconList.size(); i++) {
			if (propStorage->getProp(i)->getPropFlag()) {
				iconList[i].ShowBitmap();
			}
		}

		switch (propCase) {
		case mosquito_jump_p:
			MosquitoJumpDetails.ShowBitmap();
			if (propStorage->getProp(mosquito_jump_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_blood_p:
			ShrimpBloodDetails.ShowBitmap();
			if (propStorage->getProp(shrimp_blood_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case grass_fast_p:
			GrassFastDetails.ShowBitmap();
			if (propStorage->getProp(grass_fast_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case banana_attack_p:
			BananaAttackDetails.ShowBitmap();
			if (propStorage->getProp(banana_attack_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_attack_p:
			ShrimpAttackDetails.ShowBitmap();
			if (propStorage->getProp(shrimp_attack_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case guava_juice_blood_p:
			GuavaJuiceBloodDetails.ShowBitmap();
			if (propStorage->getProp(guava_juice_blood_p)->getPropFlag()) {
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