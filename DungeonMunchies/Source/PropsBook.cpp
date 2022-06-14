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

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為道具書模式
	/////////////////////////////////////////////////////////////////////////////

	PropsBook::PropsBook()
	{
		Case = mosquito_jump_p;
	}

	PropsBook::~PropsBook()
	{
	}

	void PropsBook::LoadBitmap()
	{
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

		MosquitoJumpIconS.LoadBitmap(".\\res\\prop_mosquito_jump_icon_s.bmp");
		ShrimpBloodIconS.LoadBitmap(".\\res\\prop_shrimp_blood_icon_s.bmp");
		GrassFastIconS.LoadBitmap(".\\res\\prop_grass_fast_icon_s.bmp");
		BananaAttackIconS.LoadBitmap(".\\res\\prop_banana_attack_icon_s.bmp");
		ShrimpAttackIconS.LoadBitmap(".\\res\\prop_shrimp_attack_icon_s.bmp");
		GuavaJuiceBloodIconS.LoadBitmap(".\\res\\prop_guava_juice_blood_icon_s.bmp");

		MosquitoJumpDetails.LoadBitmap(IDB_PROPMOSQUITOJUMP);
		ShrimpBloodDetails.LoadBitmap(IDB_PROPSHRIMPBLOOD);
		GrassFastDetails.LoadBitmap(IDB_PROPGRASSFAST);
		BananaAttackDetails.LoadBitmap(IDB_PROPBANANAATTACK);
		ShrimpAttackDetails.LoadBitmap(IDB_PROPSHRIMPATTACK);
		GuavaJuiceBloodDetails.LoadBitmap(IDB_PROPGUAVAJUICEBLOOD);
	}

	void PropsBook::Initialize(Character* character)
	{
		Case = mosquito_jump_p;
		choicex = 177;
		choicey = 127;
		setIconList();
		propStorage = character->GetPropStorage();
		sourceStorage = character->GetSourceStorage();
		_character = character;
		px = 219;
	}

	void PropsBook::setXY(CPoint mousePosition)
	{
		mx = mousePosition.x;
		my = mousePosition.y;
	}

	void PropsBook::setXY(int x, int y)
	{
		mx = x;
		my = y;
	}

	int PropsBook::getMX()
	{
		return mx;
	}

	int PropsBook::getMY()
	{
		return my;
	}

	void PropsBook::setCase()
	{
		int column = (mx - 177) / 62;
		int row = (my - 127) / 62;
		if (row == 0 && column == 0)
		{
			Case = mosquito_jump_p;
		}
		else if (row == 0 && column == 1)
		{
			Case = shrimp_blood_p;
		}
		else if (row == 0 && column == 2)
		{
			Case = grass_fast_p;
		}
		else if (row == 0 && column == 3)
		{
			Case = banana_attack_p;
		}
		else if (row == 0 && column == 4)
		{
			Case = shrimp_attack_p;
		}
		else if (row == 0 && column == 5)
		{
			Case = guava_juice_blood_p;
		}
		choicex = column * 62 + 177;
		choicey = row * 62 + 128;
	}

	void PropsBook::setCase(CPoint mousePosition)
	{
		setXY(mousePosition);
		if (mx > 177 && my > 127 && mx < 543 && my < 185)
		{
			setCase();
		}
		else if (mx > 900 && my > 580 && mx < 1023 && my < 623)
		{
			cook();
		}
		else if (mx > 219 && my > 612 && mx < 541 && my < 657)
		{
			propCancellation();
		}
	}

	void PropsBook::setIconList()
	{
		iconList.push_back(MosquitoJumpIcon);
		iconList.push_back(ShrimpBloodIcon);
		iconList.push_back(GrassFastIcon);
		iconList.push_back(BananaAttackIcon);
		iconList.push_back(ShrimpAttackIcon);
		iconList.push_back(GuavaJuiceBloodIcon);
		iconList = setIconPosition(iconList);
	}

	vector<CMovingBitmap> PropsBook::setIconPosition(vector<CMovingBitmap> iconList)
	{
		int iconx, icony;
		int counter = 0;
		for (int row = 0; row < 7; row++)
		{
			icony = row * 62 + 127;
			for (int column = 0; column < 7; column++)
			{
				iconx = column * 62 + 177;
				iconList[counter].SetTopLeft(iconx, icony);
				if (counter == (iconList).size() - 1)
				{
					return iconList;
				}
				counter++;
			}
		}
		return iconList;
	}

	void PropsBook::cook()
	{ //用過不能再用
		switch (Case)
		{
		case mosquito_jump_p:
			if (!(propStorage->getProp(mosquito_jump_p)->getPropFlag()) && sourceStorage->getSource(mosquito_jump_s)->getNum() >= 5 && _character->GetLightBulbNum() >= 0)
			{
				CAudio::Instance()->Play(AUDIO_COOK, false);
				sourceStorage->getSource(mosquito_jump_s)->consume(5);
				propStorage->getProp(mosquito_jump_p)->setPropFlag(true);
				propStorage->getProp(mosquito_jump_p)->effect(_character, true);
				propList.push_back(mosquito_jump_p);
			}
			break;
		case shrimp_blood_p:
			if (!(propStorage->getProp(shrimp_blood_p)->getPropFlag()) && sourceStorage->getSource(shrimp_blood_s)->getNum() >= 1 && _character->GetLightBulbNum() >= 50)
			{
				CAudio::Instance()->Play(AUDIO_COOK, false);
				sourceStorage->getSource(shrimp_blood_s)->consume(1);
				propStorage->getProp(shrimp_blood_p)->setPropFlag(true);
				propStorage->getProp(shrimp_blood_p)->effect(_character, true);
				_character->ConsumeLightBulb(50);
				propList.push_back(shrimp_blood_p);
			}
			break;
		case grass_fast_p:
			if (!(propStorage->getProp(grass_fast_p)->getPropFlag()) && sourceStorage->getSource(grass_fast_s)->getNum() >= 5 && _character->GetLightBulbNum() >= 40)
			{
				CAudio::Instance()->Play(AUDIO_COOK, false);
				sourceStorage->getSource(grass_fast_s)->consume(5);
				propStorage->getProp(grass_fast_p)->setPropFlag(true);
				propStorage->getProp(grass_fast_p)->effect(_character, true);
				_character->ConsumeLightBulb(40);
				propList.push_back(grass_fast_p);
			}
			break;
		case banana_attack_p:
			if (!(propStorage->getProp(banana_attack_p)->getPropFlag()) && sourceStorage->getSource(banana_attack_s)->getNum() >= 1 && _character->GetLightBulbNum() >= 60)
			{
				CAudio::Instance()->Play(AUDIO_COOK, false);
				sourceStorage->getSource(banana_attack_s)->consume(1);
				propStorage->getProp(banana_attack_p)->setPropFlag(true);
				propStorage->getProp(banana_attack_p)->effect(_character, true);
				_character->ConsumeLightBulb(60);
				propList.push_back(banana_attack_p);
			}
			break;
		case shrimp_attack_p:
			if (!(propStorage->getProp(shrimp_attack_p)->getPropFlag()) && sourceStorage->getSource(guava_juice_blood_s)->getNum() >= 1 && _character->GetLightBulbNum() >= 60)
			{
				CAudio::Instance()->Play(AUDIO_COOK, false);
				sourceStorage->getSource(shrimp_attack_s)->consume(1);
				propStorage->getProp(shrimp_attack_p)->setPropFlag(true);
				propStorage->getProp(shrimp_attack_p)->effect(_character, true);
				_character->ConsumeLightBulb(60);
				propList.push_back(shrimp_attack_p);
			}
			break;
		case guava_juice_blood_p:
			if (!(propStorage->getProp(guava_juice_blood_p)->getPropFlag()) && sourceStorage->getSource(guava_juice_blood_s)->getNum() >= 1 && _character->GetLightBulbNum() >= 50)
			{
				CAudio::Instance()->Play(AUDIO_COOK, false);
				sourceStorage->getSource(guava_juice_blood_s)->consume(1);
				propStorage->getProp(guava_juice_blood_p)->setPropFlag(true);
				propStorage->getProp(guava_juice_blood_p)->effect(_character, true);
				_character->ConsumeLightBulb(50);
				propList.push_back(guava_juice_blood_p);
			}
			break;
		default:
			break;
		}
	}

	void PropsBook::propListOnShow()
	{
		px = 219;
		for (int i = 0; (unsigned)i < propList.size(); i++)
		{
			propBitmap(propList.at(i))->SetTopLeft(px, 612);
			propBitmap(propList.at(i))->ShowBitmap();
			px += 46;
		}
	}

	void PropsBook::LightBulbOnShow()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(235, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(145, 137, 125));
		char position[100];								// Demo 數字對字串的轉換
		sprintf(position, "%d", _character->GetLightBulbNum());
		pDC->TextOut(228, 73, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void PropsBook::getAllProps()
	{
		propStorage->getProp(mosquito_jump_p)->setPropFlag(true);
		propStorage->getProp(mosquito_jump_p)->effect(_character, true);
		propList.push_back(mosquito_jump_p);

		propStorage->getProp(shrimp_blood_p)->setPropFlag(true);
		propStorage->getProp(shrimp_blood_p)->effect(_character, true);
		propList.push_back(shrimp_blood_p);

		propStorage->getProp(grass_fast_p)->setPropFlag(true);
		propStorage->getProp(grass_fast_p)->effect(_character, true);
		propList.push_back(grass_fast_p);

		propStorage->getProp(banana_attack_p)->setPropFlag(true);
		propStorage->getProp(banana_attack_p)->effect(_character, true);
		propList.push_back(banana_attack_p);

		propStorage->getProp(shrimp_attack_p)->setPropFlag(true);
		propStorage->getProp(shrimp_attack_p)->effect(_character, true);
		propList.push_back(shrimp_attack_p);

		propStorage->getProp(guava_juice_blood_p)->setPropFlag(true);
		propStorage->getProp(guava_juice_blood_p)->effect(_character, true);
		propList.push_back(guava_juice_blood_p);
	}

	void PropsBook::loseAllProps()
	{
		propStorage->getProp(mosquito_jump_p)->setPropFlag(false);
		propStorage->getProp(mosquito_jump_p)->effect(_character, false);

		propStorage->getProp(shrimp_blood_p)->setPropFlag(false);
		propStorage->getProp(shrimp_blood_p)->effect(_character, false);

		propStorage->getProp(grass_fast_p)->setPropFlag(false);
		propStorage->getProp(grass_fast_p)->effect(_character, false);

		propStorage->getProp(banana_attack_p)->setPropFlag(false);
		propStorage->getProp(banana_attack_p)->effect(_character, false);

		propStorage->getProp(shrimp_attack_p)->setPropFlag(false);
		propStorage->getProp(shrimp_attack_p)->effect(_character, false);

		propStorage->getProp(guava_juice_blood_p)->setPropFlag(false);
		propStorage->getProp(guava_juice_blood_p)->effect(_character, false);

		propList.erase(propList.begin(), propList.end());
	}

	CMovingBitmap* PropsBook::propBitmap(PropCase pc)
	{
		switch (pc)
		{
		case mosquito_jump_p:
			return &MosquitoJumpIconS;
		case shrimp_blood_p:
			return &ShrimpBloodIconS;
		case grass_fast_p:
			return &GrassFastIconS;
		case banana_attack_p:
			return &BananaAttackIconS;
		case shrimp_attack_p:
			return &ShrimpAttackIconS;
		case guava_juice_blood_p:
			return &GuavaJuiceBloodIconS;
		}
		throw;
	}

	void PropsBook::propCancellation()
	{
		int cancellationCase = (mx - 219) / 46;
		vector <PropCase>::iterator it;
		it = propList.begin();
		advance(it, cancellationCase);
		switch (propList.at(cancellationCase))
		{
		case mosquito_jump_p:
			propStorage->getProp(mosquito_jump_p)->setPropFlag(false);
			sourceStorage->getSource(mosquito_jump_s)->add(5);
			propStorage->getProp(mosquito_jump_p)->effect(_character, false);
			propList.erase(it);
			break;
		case shrimp_blood_p:
			propStorage->getProp(shrimp_blood_p)->setPropFlag(false);
			sourceStorage->getSource(shrimp_blood_s)->add(1);
			_character->AddLightBulb(50);
			propStorage->getProp(shrimp_blood_p)->effect(_character, false);
			propList.erase(it);
			break;
		case grass_fast_p:
			propStorage->getProp(grass_fast_p)->setPropFlag(false);
			sourceStorage->getSource(grass_fast_p)->add(5);
			_character->AddLightBulb(40);
			propStorage->getProp(grass_fast_p)->effect(_character, false);
			propList.erase(it);
			break;
		case banana_attack_p:
			propStorage->getProp(banana_attack_p)->setPropFlag(false);
			sourceStorage->getSource(banana_attack_p)->add(1);
			_character->AddLightBulb(60);
			propStorage->getProp(banana_attack_p)->effect(_character, false);
			propList.erase(it);
			break;
		case shrimp_attack_p:
			propStorage->getProp(shrimp_attack_p)->setPropFlag(false);
			sourceStorage->getSource(shrimp_attack_p)->add(1);
			_character->AddLightBulb(60);
			propStorage->getProp(shrimp_attack_p)->effect(_character, false);
			propList.erase(it);
			break;
		case guava_juice_blood_p:
			propStorage->getProp(guava_juice_blood_p)->setPropFlag(false);
			sourceStorage->getSource(guava_juice_blood_p)->add(1);
			_character->AddLightBulb(50);
			propStorage->getProp(guava_juice_blood_p)->effect(_character, false);
			propList.erase(it);
			break;
		}

	}

	void PropsBook::sourceNumShow(int sourceCase)
	{
		int sourceNum = sourceStorage->getSource(sourceCase)->getNum();
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(100, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		CString cstr(to_string(sourceNum).c_str());
		pDC->TextOut(890, 395, cstr);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void PropsBook::onShow()
	{
		propsBook.SetTopLeft(0, 0);
		propsBook.ShowBitmap();
		propHave.SetTopLeft(675, 350);
		propsPot1.SetTopLeft(806, 530);
		MosquitoJumpDetails.SetTopLeft(673, 38);
		ShrimpBloodDetails.SetTopLeft(673, 38);
		GrassFastDetails.SetTopLeft(673, 38);
		BananaAttackDetails.SetTopLeft(673, 38);
		ShrimpAttackDetails.SetTopLeft(673, 38);
		GuavaJuiceBloodDetails.SetTopLeft(673, 38);
		propListOnShow();

		for (unsigned int i = 0; i < iconList.size(); i++)
		{
			if (propStorage->getProp(i)->getPropFlag())
			{
				iconList[i].ShowBitmap();
			}
		}

		switch (Case)
		{
		case mosquito_jump_p:
			MosquitoJumpDetails.ShowBitmap();
			sourceNumShow(mosquito_jump_p);
			if (propStorage->getProp(mosquito_jump_p)->getPropFlag())
			{
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_blood_p:
			ShrimpBloodDetails.ShowBitmap();
			sourceNumShow(shrimp_blood_p);
			if (propStorage->getProp(shrimp_blood_p)->getPropFlag())
			{
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case grass_fast_p:
			GrassFastDetails.ShowBitmap();
			sourceNumShow(grass_fast_p);
			if (propStorage->getProp(grass_fast_p)->getPropFlag())
			{
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case banana_attack_p:
			BananaAttackDetails.ShowBitmap();
			sourceNumShow(banana_attack_p);
			if (propStorage->getProp(banana_attack_p)->getPropFlag())
			{
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case shrimp_attack_p:
			ShrimpAttackDetails.ShowBitmap();
			sourceNumShow(shrimp_attack_p);
			if (propStorage->getProp(shrimp_attack_p)->getPropFlag())
			{
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		case guava_juice_blood_p:
			GuavaJuiceBloodDetails.ShowBitmap();
			sourceNumShow(guava_juice_blood_p);
			if (propStorage->getProp(guava_juice_blood_p)->getPropFlag())
			{
				propHave.ShowBitmap();
				propsPot1.ShowBitmap();
			}
			break;
		default:
			break;
		}
		propsBookChoice.SetTopLeft(choicex, choicey);
		propsBookChoice.ShowBitmap();
		LightBulbOnShow();
	}
}