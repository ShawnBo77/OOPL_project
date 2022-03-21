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

	bool Character::GetIsMovingLeft()
	{
		return isMovingLeft;
	}

	bool Character::GetIsMovingRight()
	{
		return isMovingRight;
	}

	bool Character::GetIsMovingUp()
	{
		return isMovingUp;
	}

	bool Character::GetIsRolling()
	{
		return isRolling;
	}

	bool Character::GetIsOnTheFloor()
	{
		if (GetButtonY() == floor) {
			isOnTheFloor = true;
		}
		else {
			isOnTheFloor = false;
		}

		return isOnTheFloor;
	}

	bool Character::GetIsRising()
	{
		return isRising;
	}

	void Character::Initialize()
	{
		characterH = 80;
		characterW = 80;
		const int X_POS = 80;													//角色起始X軸
		const int Y_POS = 100;													//角色起始Y軸
		characterX = X_POS;
		characterY = Y_POS;
		facingLR = 1;
		isMovingLeft = isMovingRight = isMovingUp = isRising = isRolling = false;
		floor = 400;
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
		standLeft.LoadBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));		//向左站
		standRight.LoadBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));		//向右站

		//向左走動畫
		vector<int> walkingLeftAnimation = {IDB_HEROLEFTWALK1_S, IDB_HEROLEFTWALK2_S, IDB_HEROLEFTWALK3_S};
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingLeft.AddBitmap(walkingLeftAnimation[i], RGB(0, 0, 0));

		//向右走動畫
		vector<int> walkingRightAnimation = {IDB_HERORIGHTWALK1_S, IDB_HERORIGHTWALK2_S, IDB_HERORIGHTWALK3_S};
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingRight.AddBitmap(walkingRightAnimation[i], RGB(0, 0, 0));

		leftJump.AddBitmap(IDB_HEROLEFTJUMP_S, RGB(0, 0, 0));
		for (int i = 0; i < 3; i++)
			leftJump.AddBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));
		rightJump.AddBitmap(IDB_HERORIGHTJUMP_S, RGB(0, 0, 0));
		for (int i = 0; i < 3; i++)
			rightJump.AddBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));

		vector<int> rollingLeftAnimation = { IDB_HEROLEFTROLL1, IDB_HEROLEFTROLL2, IDB_HEROLEFTROLL3, IDB_HEROLEFTROLL4, IDB_HEROLEFTROLL5, IDB_HEROLEFTROLL6, IDB_HEROLEFTROLL7, IDB_HEROLEFTROLL8 };
		for (int i = 0; i < 8; i++)
			leftRolling.AddBitmap(rollingLeftAnimation[i], RGB(0, 0, 0));

		vector<int> rollingRightAnimation = { IDB_HERORIGHTROLL1, IDB_HERORIGHTROLL2, IDB_HERORIGHTROLL3, IDB_HERORIGHTROLL4, IDB_HERORIGHTROLL5, IDB_HERORIGHTROLL6, IDB_HERORIGHTROLL7, IDB_HERORIGHTROLL8 };
		for (int i = 0; i < 8; i++)
			rightRolling.AddBitmap(rollingRightAnimation[i], RGB(0, 0, 0));


		/*animation.AddBitmap(IDB_HERORIGHTROLL1, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTROLL2, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTROLL3, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTROLL4, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTROLL5, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTROLL6, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTROLL7, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HERORIGHTROLL8, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL1, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL2, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL3, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL4, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL5, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL6, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL7, RGB(0, 0, 0));
		animation.AddBitmap(IDB_HEROLEFTROLL8, RGB(0, 0, 0));*/
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
		/*animation.AddBitmap(IDB_BOSSLEFTCOLLIDE1, RGB(0, 0, 0));
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
		animation.AddBitmap(IDB_BOSSLEFTWALK4, RGB(0, 0, 0));*/

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
		facingLR = 0;
	}

	void Character::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		facingLR = 1;
	}

	void Character::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Character::SetRolling(bool flag)
	{
		if (GetIsOnTheFloor())
			isRolling = flag;
		else
			isRolling = false;
	}

	void Character::OnMove(Map* m)
	{
		const int BORDER = 5;													//角色邊框寬度
		const int STEP_SIZE = 10;												//角色移動速度
		const int ROLLING_SIZE = 1;											//角色翻滾距離

		if (GetIsRolling())							//翻滾
		{
			if (facingLR == 0 && m->isEmpty(GetLeftX() - ROLLING_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - ROLLING_SIZE, GetButtonY() - BORDER))
			{
				for (int i = 0; i < 20; i++)
				{
					characterX -= ROLLING_SIZE;
				}

				//m->addSX(STEP_SIZE);												//視角移動(王關不用)
			}
			else if (facingLR == 1 && m->isEmpty(GetRightX() + ROLLING_SIZE - 5, GetTopY()) && m->isEmpty(GetRightX() - BORDER + ROLLING_SIZE, GetButtonY() - BORDER))
			{
				if (m->getSX() > -230)
				{
					for (int i = 0; i < 20; i++)
					{
						characterX += ROLLING_SIZE;
					}
				}

				//m->addSX(-STEP_SIZE);
			}
		}
		else 
		{
			if (GetIsMovingLeft() && m->isEmpty(GetLeftX() - STEP_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - STEP_SIZE, GetButtonY() - BORDER))
			{
				if (m->getSX() > -230)
				{
					characterX -= STEP_SIZE;
				}

				//m->addSX(STEP_SIZE);												//視角移動(王關不用)
			}
			if (GetIsMovingRight() && m->isEmpty(GetRightX() + STEP_SIZE - 5, GetTopY()) && m->isEmpty(GetRightX() - BORDER + STEP_SIZE, GetButtonY() - BORDER))
			{
				if (m->getSX() > -230)
				{
					characterX += STEP_SIZE;
				}

				//m->addSX(-STEP_SIZE);                             	
			}
			if (GetIsMovingUp() && GetButtonY() >= floor && velocity == 0) {
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
				if (GetButtonY() < floor)				// 當y座標還沒碰到地板
				{
					characterY += velocity * 2;		// y軸下降(移動velocity個點，velocity的單位為 點/次)
					if (velocity < 5)
						velocity++;
				}
				else
				{
					characterY = floor - 80;				// 當y座標低於地板，更正為地板上
					velocity = 0;
				}
			}
		}
		

		walkingLeft.OnMove();
		walkingRight.OnMove();

		leftRolling.OnMove();
		rightRolling.OnMove();

		leftJump.OnMove();
		rightJump.OnMove();

	}

	void Character::SetXY(int x, int y)
	{
		characterX = x;
		characterY = y;
	}

	void Character::OnShow()
	{
		if (facingLR == 0) {
			if (GetIsRolling()) 
			{
				leftRolling.SetTopLeft(characterX, characterY+15);
				leftRolling.OnShow();
				leftRolling.SetDelayCount(1);
			}
			else if (GetIsMovingUp() == true) 
			{
				leftJump.SetTopLeft(characterX, characterY);
				leftJump.OnShow();
				leftJump.SetDelayCount(10);
			}
			else if ((GetIsMovingLeft() == true || GetIsMovingRight() == true) && GetIsOnTheFloor() == true)
			{
				walkingLeft.SetTopLeft(characterX, characterY);
				walkingLeft.OnShow();
			}
			else 
			{
				standLeft.SetTopLeft(characterX, characterY);
				standLeft.ShowBitmap();
			}
		} 
		else
		{
			if (GetIsRolling())
			{
				rightRolling.SetTopLeft(characterX, characterY);
				rightRolling.OnShow();
			}
			else if (GetIsMovingUp() == true)
			{
				rightJump.SetTopLeft(characterX, characterY);
				rightJump.OnShow();
				rightJump.SetDelayCount(3);
			}
			else if ((GetIsMovingLeft() == true || GetIsMovingRight() == true) && GetIsOnTheFloor() == true)
			{
				walkingRight.SetTopLeft(characterX, characterY);
				walkingRight.OnShow();
			} 
			else
			{
				standRight.SetTopLeft(characterX, characterY);
				standRight.ShowBitmap();
			}
		}
	}
}