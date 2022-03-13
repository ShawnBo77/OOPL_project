#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Map.h"

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的角色人物物件
/////////////////////////////////////////////////////////////////////////////
namespace game_framework {
    Character::Character() {
		Initialize();
		//characterX = characterY = 50;
    }

	int Character::GetLeftX()
	{
		return characterX;
	}

	int Character::GetTopY()
	{
		return characterY;
	}

	int Character::GetRightX()
	{
		return characterX + characterW; // + animation.Width();
	}

	int Character::GetButtonY()
	{
		return characterY + characterH; // + animation.Height();
	}

	void Character::Initialize()
	{
		characterH = 80;
		characterW = 80;
		const int X_POS = 80;													//角色起始X軸
		const int Y_POS = 100;													//角色起始Y軸
		characterX = X_POS;
		characterY = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

		isRising = false;
		floor = 320;
	}

	void Character::LoadBitmap()
	{
		//animation.AddBitmap(IDB_GRAY);
		//animation.AddBitmap(IDB_BOSSRIGHTSTAND, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_HERORIGHTSTAND_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTJUMP_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK1_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK2_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK3_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTSTAND_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTJUMP_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK1_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK2_G, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK3_G, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTJUMP_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTWALK3_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTJUMP_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTWALK3_S, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_HERORIGHTATTACK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTATTACK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTATTACK3_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTATTACK4_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK1_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK2_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK3_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTATTACK4_S, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL6, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL7, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HERORIGHTROLL8, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL6, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL7, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_HEROLEFTROLL8, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_BOSSRIGHTCOLLIDE1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTCOLLIDE2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTCOLLIDE3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTCOLLIDE4, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD6, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_BOSSRIGHTHIT1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTHIT2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTHIT3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTHIT4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTHIT5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTHIT6, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTHITEFFECT4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTHITEFFECT5, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_BOSSRIGHTTHORN1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTTHORN2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTTHORN3, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_BOSSRIGHTWALK1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTWALK2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTWALK3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTWALK4, RGB(0, 0, 0));
		//
		animation.AddBitmap(IDB_BOSSLEFTCOLLIDE1, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTCOLLIDE2, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTCOLLIDE3, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTCOLLIDE4, RGB(0, 0, 0));
		
		animation.AddBitmap(IDB_BOSSLEFTDEAD1, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTDEAD2, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTDEAD3, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTDEAD4, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTDEAD5, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTDEAD6, RGB(0, 0, 0));
		
		animation.AddBitmap(IDB_BOSSLEFTHIT1, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTHIT2, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTHIT3, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTHIT4, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTHIT5, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTHIT6, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTHITEFFECT4, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTHITEFFECT5, RGB(0, 0, 0));
		
		animation.AddBitmap(IDB_BOSSLEFTTHORN1, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTTHORN2, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTTHORN3, RGB(0, 0, 0));
		
		animation.AddBitmap(IDB_BOSSLEFTWALK1, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTWALK2, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTWALK3, RGB(0, 0, 0));
		animation.AddBitmap(IDB_BOSSLEFTWALK4, RGB(0, 0, 0));
		
		//animation.AddBitmap(IDB_THRONGROW1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_THRONGROW2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_THRONRED, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_CACTUSALIVE, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_CACTUSDEAD, RGB(0, 0, 0));
		//

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

	void Character::OnMove(Map *m)
	{

		const int BORDER = 5;													//角色邊框寬度
		const int STEP_SIZE = 5;												//腳色移動速度
		animation.OnMove();
		if (isMovingLeft && m->isEmpty(GetLeftX() - STEP_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - STEP_SIZE, GetButtonY() - BORDER))
		{
			if (m->getSX() > -230) 
			{
				characterX -= STEP_SIZE;
			}

			//m->addSX(STEP_SIZE);												//視角移動(王關不用)
		}
		if (isMovingRight && m->isEmpty(GetRightX() + STEP_SIZE - 5, GetTopY()) && m->isEmpty(GetRightX() - BORDER + STEP_SIZE, GetButtonY() - BORDER)) 
		{
			if (m->getSX() > -230) 
			{
				characterX += STEP_SIZE;
			}

			//m->addSX(-STEP_SIZE);                             	
		}
		if (isMovingUp && GetButtonY() >= floor && velocity == 0) {
			isRising = true;
			velocity = 10;
		}
		/*if (isMovingDown && !m->isEmpty(GetLeftX(), GetButtonY() + STEP_SIZE - 5) && !m->isEmpty(GetRightX() - 5, GetButtonY() + STEP_SIZE - 5)) {
			characterY += STEP_SIZE;
			m->addSY(-STEP_SIZE);
		}*/

		if (isRising)							// 上升狀態	
		{						
			if (velocity > 0)
			{
				characterY -= velocity * 2;		// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;						// 受重力影響，下次的上升速度降低
			}
			else
			{
				isRising = false;				// 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;					// 下降的初速(velocity)為1
			}
		}
		else									// 下降狀態
		{		
			if (characterY < floor)				// 當y座標還沒碰到地板
			{									
				characterY += velocity * 2;		// y軸下降(移動velocity個點，velocity的單位為 點/次)
				if (velocity < 5)
					velocity++;
			}
			else
			{
				characterY = floor;				// 當y座標低於地板，更正為地板上
				velocity = 0;
			}
		}
		
	}

	void Character::SetXY(int x, int y)
	{
		characterX = x;
		characterY = y;
	}

	void Character::OnShow()
	{
		animation.SetTopLeft(characterX, characterY);
		animation.OnShow();
	}
}