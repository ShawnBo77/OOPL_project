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
#include "Source.h"
#include "SourceStorage.h"

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

	void PropsBook::Initialize(Character* character) {
		propCase = mosquito_jump_p;
		choicex = 125;
		choicey = 90;
		setIconList();
		propStorage = character->GetPropStorage();
		sourceStorage = character->GetSourceStorage();
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

	void PropsBook::sourceNumShow(int sourceCase) {
		int sourceNum = sourceStorage->getSource(sourceCase)->getNum();
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(70, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		CString cstr(to_string(sourceNum).c_str());
		pDC->TextOut(627, 278, cstr);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

    void PropsBook::onShow() {
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
			sourceNumShow(mosquito_jump_p);
			if (propStorage->getProp(mosquito_jump_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_blood_p:
			ShrimpBloodDetails.ShowBitmap();
			sourceNumShow(shrimp_blood_p);
			if (propStorage->getProp(shrimp_blood_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case grass_fast_p:
			GrassFastDetails.ShowBitmap();
			sourceNumShow(grass_fast_p);
			if (propStorage->getProp(grass_fast_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case banana_attack_p:
			BananaAttackDetails.ShowBitmap();
			sourceNumShow(banana_attack_p);
			if (propStorage->getProp(banana_attack_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_attack_p:
			ShrimpAttackDetails.ShowBitmap();
			sourceNumShow(shrimp_attack_p);
			if (propStorage->getProp(shrimp_attack_p)->getPropFlag()) {
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case guava_juice_blood_p:
			GuavaJuiceBloodDetails.ShowBitmap();
			sourceNumShow(guava_juice_blood_p);
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