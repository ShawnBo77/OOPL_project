#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Map.h"
#include "Source.h"
#include "SourceStorage.h"
#include "Prop.h"
#include "PropStorage.h"
#include "Monster.h"

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的角色人物物件
/////////////////////////////////////////////////////////////////////////////
namespace game_framework
{
	Character::Character()
	{
		//characterX = characterY = 50;
		sourceStorage = new SourceStorage();
		propStorage = new PropStorage();
	}

	Character::~Character()
	{
		delete sourceStorage;
		delete propStorage;
	}

	void Character::LoadBitmap()
	{
		bloodFrame.LoadBitmap(IDB_CHARACTERBLOODFRAME, RGB(0, 0, 0));
		characterBlood[0].LoadBitmap(IDB_CHARACTERBLOOD01, RGB(255, 255, 255));
		characterBlood[1].LoadBitmap(IDB_CHARACTERBLOOD02, RGB(255, 255, 255));
		characterBlood[2].LoadBitmap(IDB_CHARACTERBLOOD03, RGB(255, 255, 255));
		characterBlood[3].LoadBitmap(IDB_CHARACTERBLOOD04, RGB(255, 255, 255));
		characterBlood[4].LoadBitmap(IDB_CHARACTERBLOOD05, RGB(255, 255, 255));
		characterBlood[5].LoadBitmap(IDB_CHARACTERBLOOD06, RGB(255, 255, 255));
		characterBlood[6].LoadBitmap(IDB_CHARACTERBLOOD07, RGB(255, 255, 255));
		characterBlood[7].LoadBitmap(IDB_CHARACTERBLOOD08, RGB(255, 255, 255));
		characterBlood[8].LoadBitmap(IDB_CHARACTERBLOOD09, RGB(255, 255, 255));
		characterBlood[9].LoadBitmap(IDB_CHARACTERBLOOD10, RGB(255, 255, 255));
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
		vector<int> walkingLeftAnimation = { IDB_HEROLEFTWALK1_S, IDB_HEROLEFTWALK2_S, IDB_HEROLEFTWALK3_S };
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingLeft.AddBitmap(walkingLeftAnimation[i], RGB(0, 0, 0));

		//向右走動畫
		vector<int> walkingRightAnimation = { IDB_HERORIGHTWALK1_S, IDB_HERORIGHTWALK2_S, IDB_HERORIGHTWALK3_S };
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

		vector<int> attackingLeftAnimation = { IDB_HEROLEFTATTACK1_S, IDB_HEROLEFTATTACK2_S, IDB_HEROLEFTATTACK3_S, IDB_HEROLEFTATTACK4_S };
		for (int i = 0; i < 4; i++)
			leftAttacking.AddBitmap(attackingLeftAnimation[i], RGB(0, 0, 0));

		vector<int> attackingRightAnimation = { IDB_HERORIGHTATTACK1_S, IDB_HERORIGHTATTACK2_S, IDB_HERORIGHTATTACK3_S, IDB_HERORIGHTATTACK4_S };
		for (int i = 0; i < 4; i++)
			rightAttacking.AddBitmap(attackingRightAnimation[i], RGB(0, 0, 0));

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

		//animation.AddBitmap(IDB_BOSSRIGHTDEAD1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSRIGHTDEAD6, RGB(0, 0, 0));

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
		//animation.AddBitmap(IDB_BOSSLEFTCOLLIDE1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTCOLLIDE2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTCOLLIDE3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTCOLLIDE4, RGB(0, 0, 0));

		//animation.AddBitmap(IDB_BOSSLEFTDEAD1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTDEAD2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTDEAD3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTDEAD4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTDEAD5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTDEAD6, RGB(0, 0, 0));

		//animation.AddBitmap(IDB_BOSSLEFTHIT1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTHIT2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTHIT3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTHIT4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTHIT5, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTHIT6, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTHITEFFECT4, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTHITEFFECT5, RGB(0, 0, 0));

		//animation.AddBitmap(IDB_BOSSLEFTTHORN1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTTHORN2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTTHORN3, RGB(0, 0, 0));

		//animation.AddBitmap(IDB_BOSSLEFTSTAND, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTWALK1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTWALK2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTWALK3, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_BOSSLEFTWALK4, RGB(0, 0, 0));

		//animation.AddBitmap(IDB_THRONGROW1, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_THRONGROW2, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_THRONRED, RGB(0, 0, 0));
		//
		//animation.AddBitmap(IDB_CACTUSALIVE, RGB(0, 0, 0));
		//animation.AddBitmap(IDB_CACTUSDEAD, RGB(0, 0, 0));
		//
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
		STEP_SIZE = 15;
		isMovingLeft = isMovingRight = isMovingUp = isRising = isRolling = false;
		maxHp = 80;
		currentHp = 37;
		rolling_time = 0;
		isAttacking = false;
		attackDamage = 10;
		isAttackedFromRight = false;
		isAttackedFromLeft = false;
		isAttackedFromButton = false;
		isInvincible = false;
		doubleJump = false;
		DJtemp = doubleJump;
		healBlood = false;
		currentMap = NULL;
	}

	void Character::OnMove(Map* m)
	{
		//animation.OnMove();
		const int BORDER = 5;													//角色邊框寬度
		if (currentMap == NULL || m->getMapName() != currentMap->getMapName())
		{
			SetMap(m);
			ResetPosition(m);
		}

		if (GetIsRolling())
		{
			if (isMovingLeft)
				Rolling(m, 0);
			else if (isMovingRight)
				Rolling(m, 1);
			else if (facingLR)
				Rolling(m, 1);
			else if (facingLR == 0)
				Rolling(m, 0);
		}
		else
		{
			if (GetIsMovingLeft() && m->isEmpty(GetLeftX() - STEP_SIZE - BORDER, GetTopY()) && m->isEmpty(GetLeftX() - BORDER - STEP_SIZE, GetButtonY() - BORDER))
			{
				if (characterX <= 670 || GetMap()->mapScreenMoving() == false)
				{
					characterX -= STEP_SIZE;
				}
				else
				{
					if (characterX - STEP_SIZE < 670)
					{
						m->addSX(characterX - 670);
						characterX = 670;
					}
					else
					{
						characterX -= STEP_SIZE;
						m->addSX(STEP_SIZE);
					}										//視角移動(王關不用)
				}
			}

			if (GetIsMovingRight() && m->isEmpty(GetRightX() + STEP_SIZE + BORDER, GetTopY()) && m->isEmpty(GetRightX() + BORDER + STEP_SIZE, GetButtonY() - BORDER))
			{
				if (characterX < 670)
				{
					if (characterX + STEP_SIZE > 670 && GetMap()->mapScreenMoving() == true)
					{
						characterX = 670;
					}
					else
					{
						characterX += STEP_SIZE;
					}
				}
				else
				{
					characterX += STEP_SIZE;
					if (GetMap()->mapScreenMoving() == true)
						m->addSX(-STEP_SIZE);
				}
			}

			if (GetIsMovingUp() && GetButtonY() >= m->getFloor() && velocity == 0)
			{
				isRising = true;
				velocity = 12;
			}

			if (GetIsMovingUp() && (velocity < 8 || !GetIsRising()) && velocity > 0 && CanDoubleJump())
			{
				velocity = 10;
				isRising = true;
				SetDoubleJump(false);
			}

			if (GetIsRising())							// 上升狀態	
			{
				if (velocity > 0)
				{
					if (characterY - velocity * 2 < m->getCeiling())
					{
						characterY = m->getCeiling();
						velocity = 0;
					}
					else
					{
						characterY -= velocity * 2;			// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
						velocity--;							// 受重力影響，下次的上升速度降低
					}
				}
				else
				{
					isRising = false;					// 當速度 <= 0，上升終止，下次改為下降
					velocity = 1;						// 下降的初速(velocity)為1
				}
			}
			else										// 下降狀態
			{
				if (GetButtonY() < m->getFloor())				// 當y座標還沒碰到地板
				{
					characterY += velocity * 3;			// y軸下降(移動velocity個點，velocity的單位為 點/次)
					if (velocity < 6)
						velocity++;
				}
				else
				{
					characterY = m->getFloor() - 80;			// 當y座標低於地板，更正為地板上
					velocity = 0;
					SetDoubleJump(DJtemp);
				}
			}

			if (isInvincible)
			{
				invincibleTime.CaculateTime(&isInvincible, 1);
			}

			if (isAttackedFromRight) //還要判定是否能移動
			{
				for (int i = 0; i < 50; i++)
				{
					characterX -= 1;
				}
				isAttackedFromRight = false;
			}

			if (isAttackedFromLeft)
			{
				for (int i = 0; i < 50; i++)
				{
					characterX += 1;
				}
				isAttackedFromLeft = false;
			}

			if (isAttackedFromButton)
			{
				for (int i = 0; i < 50; i++)
				{
					characterY -= 1;
				}
				isAttackedFromButton = false;
			}
		}

		walkingLeft.OnMove();
		walkingRight.OnMove();

		leftRolling.OnMove();
		rightRolling.OnMove();

		leftJump.OnMove();
		rightJump.OnMove();

		leftAttacking.OnMove();
		rightAttacking.OnMove();
	}

	void Character::OnShow()
	{
		//animation.SetTopLeft(500, 350);
		//animation.OnShow();
		BloodShow();
		if (characterX < 670 || GetMap() == NULL || GetMap()->mapScreenMoving() == false)
		{
			if (facingLR == 0)
			{
				if (GetIsRolling())
				{
					leftRolling.SetTopLeft(characterX - 5, characterY + 10);
					leftRolling.OnShow();
					leftRolling.SetDelayCount(1);

					/*leftRolling.SetTopLeft(characterX, characterY+15);
					leftRolling.OnShow();
					leftRolling.SetDelayCount(1);*/
				}
				else if (GetIsAttacking())
				{
					leftAttacking.SetTopLeft(characterX, characterY);
					leftAttacking.SetDelayCount(3);
					leftAttacking.OnShow();
					if (leftAttacking.IsFinalBitmap())
					{
						isAttacking = false;
						actionNum = 0;
					}
				}
				else if (GetIsRising() == true)
				{
					leftJump.SetTopLeft(characterX, characterY);
					leftJump.OnShow();
					leftJump.SetDelayCount(3);
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
					rightRolling.SetTopLeft(characterX - 5, characterY + 10);
					rightRolling.OnShow();
					rightRolling.SetDelayCount(1);
				}
				else if (GetIsAttacking())
				{
					rightAttacking.SetTopLeft(characterX, characterY);
					rightAttacking.SetDelayCount(3);
					rightAttacking.OnShow();
					if (rightAttacking.IsFinalBitmap())
					{
						isAttacking = false;
						actionNum = 0;
					}
				}
				else if (GetIsRising() == true)
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
		else
		{
			if (facingLR == 0)
			{
				if (GetIsRolling())
				{
					leftRolling.SetTopLeft(670 - 5, characterY + 10);
					leftRolling.OnShow();
					leftRolling.SetDelayCount(1);

					/*leftRolling.SetTopLeft(characterX, characterY+15);
					leftRolling.OnShow();
					leftRolling.SetDelayCount(1);*/
				}
				else if (GetIsAttacking())
				{
					leftAttacking.SetTopLeft(670, characterY);
					leftAttacking.SetDelayCount(3);
					leftAttacking.OnShow();
					if (leftAttacking.IsFinalBitmap())
					{
						isAttacking = false;
						actionNum = 0;
					}
				}
				else if (GetIsRising() == true)
				{
					leftJump.SetTopLeft(670, characterY);
					leftJump.OnShow();
					leftJump.SetDelayCount(3);
				}
				else if ((GetIsMovingLeft() == true || GetIsMovingRight() == true) && GetIsOnTheFloor() == true)
				{
					walkingLeft.SetTopLeft(670, characterY);
					walkingLeft.OnShow();
				}
				else
				{
					standLeft.SetTopLeft(670, characterY);
					standLeft.ShowBitmap();
				}
			}
			else
			{
				if (GetIsRolling())
				{
					rightRolling.SetTopLeft(670 - 5, characterY + 10);
					rightRolling.OnShow();
					rightRolling.SetDelayCount(1);
				}
				else if (GetIsAttacking())
				{
					rightAttacking.SetTopLeft(670, characterY);
					rightAttacking.SetDelayCount(3);
					rightAttacking.OnShow();
					if (rightAttacking.IsFinalBitmap())
					{
						isAttacking = false;
						actionNum = 0;
					}
				}
				else if (GetIsRising() == true)
				{
					rightJump.SetTopLeft(670, characterY);
					rightJump.OnShow();
					rightJump.SetDelayCount(3);
				}
				else if ((GetIsMovingLeft() == true || GetIsMovingRight() == true) && GetIsOnTheFloor() == true)
				{
					walkingRight.SetTopLeft(670, characterY);
					walkingRight.OnShow();
				}
				else
				{
					standRight.SetTopLeft(670, characterY);
					standRight.ShowBitmap();
				}
			}
		}

		showData();
	}

	void Character::ResetPosition(Map* m)
	{
		characterX = m->getStartPosition();
		characterY = 100;
		velocity = 30;
	}

	/*Getter*/
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

	Map* Character::GetMap()
	{
		return currentMap;
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

	int Character::GetCurrentHp()
	{
		return currentHp;
	}

	bool Character::GetIsInvincible()
	{
		return isInvincible;
	}

	int Character::GetMaxHp()
	{
		return maxHp;
	}

	bool Character::GetIsRolling()
	{
		return isRolling;
	}

	bool Character::GetIsAttackedFromRight()
	{
		return isAttackedFromRight;
	}

	bool Character::GetIsAttackedFromLeft()
	{
		return isAttackedFromLeft;
	}

	bool Character::GetIsAttackedFromButton()
	{
		return isAttackedFromButton;
	}

	bool Character::GetIsOnTheFloor()
	{
		if (GetButtonY() == GetMap()->getFloor())
		{
			isOnTheFloor = true;
		}
		else
		{
			isOnTheFloor = false;
		}

		return isOnTheFloor;
	}

	bool Character::GetIsRising()
	{
		return isRising;
	}

	/*Setter*/
	void Character::SetMap(Map* m)
	{
		currentMap = m;
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

	void Character::SetFacingDirection(int mouseX)
	{
		if (characterX < 670 || GetMap()->mapScreenMoving() == false)
		{
			if (mouseX < characterX)
				facingLR = 0;
			else if (mouseX > GetRightX())
				facingLR = 1;
		}
		else
		{
			if (mouseX > 670)
				facingLR = 1;
			else if (mouseX < 670)
				facingLR = 0;
		}
	}

	void Character::SetRolling(bool flag)
	{
		if (GetIsOnTheFloor() && rolling_time <= 0)
		{
			rolling_time = 5;
			isRolling = flag;
		}
		else
		{
			isRolling = false;
		}
	}

	void Character::SetIsAttackedFromRight(bool flag)
	{
		isAttackedFromRight = flag;
	}

	void Character::SetIsAttackedFromLeft(bool flag)
	{
		isAttackedFromLeft = flag;
	}

	void Character::SetIsAttackedFromButton(bool flag)
	{
		isAttackedFromButton = flag;
	}

	void Character::SetCurrentHp(int x)
	{
		currentHp = x;
	}

	void Character::SetIsInvincible(bool flag)
	{
		isInvincible = flag;
	}

	/*攻擊*/
	void Character::SetAttacking(bool flag)
	{
		isAttacking = flag;
	}

	bool Character::GetIsAttacking()
	{
		return isAttacking;
	}

	void Character::SetAttackDamage(int x)
	{
		attackDamage = x;
	}

	int Character::GetAttackDamage()
	{
		return attackDamage;
	}

	void Character::addAttackDamage(int x)
	{
		attackDamage += x;
	}

	void Character::attack(vector<Monster*>* monsters)
	{
		actionNum = 3;
		isAttacking = true;

		for (unsigned int i = 0; i < monsters->size(); i++)
		{
			if (facingLR == 0)
			{
				if (isAttackSuccessfullyL(50, monsters->at(i)))
				{
					//monsters[i].SetIsAttackedFromRight(true);
					monsters->at(i)->lossCurrentHp(attackDamage);
				}
			}
			else
			{
				if (isAttackSuccessfullyR(50, monsters->at(i)))
				{
					//monsters[i].SetIsAttackedFromLeft(true);
					monsters->at(i)->lossCurrentHp(attackDamage);
				}
			}
		}
	}

	bool Character::isAttackSuccessfullyL(int range, Monster* monster)
	{
		if (((monster->GetRightX() >= GetLeftX() - range && monster->GetRightX() <= GetLeftX()) ||
			(monster->GetLeftX() >= GetLeftX() - range && monster->GetLeftX() <= GetLeftX()) ||
			(monster->GetLeftX() <= GetLeftX() - range && monster->GetRightX() >= GetRightX()))
			&& ((monster->GetButtonY() >= GetTopY() && monster->GetButtonY() <= GetButtonY()) ||
				(monster->GetTopY() >= GetTopY() && monster->GetTopY() <= GetButtonY()) ||
				(monster->GetTopY() <= GetTopY() && monster->GetButtonY() >= GetButtonY())))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Character::isAttackSuccessfullyR(int range, Monster* monster)
	{
		if (((monster->GetLeftX() <= GetRightX() + range && monster->GetLeftX() >= GetRightX()) ||
			(monster->GetRightX() <= GetRightX() + range && monster->GetRightX() >= GetRightX()) ||
			(monster->GetLeftX() <= GetRightX() && monster->GetRightX() >= GetRightX() + range))
			&& ((monster->GetButtonY() >= GetTopY() && monster->GetButtonY() <= GetButtonY()) ||
				(monster->GetTopY() >= GetTopY() && monster->GetTopY() <= GetButtonY()) ||
				(monster->GetButtonY() >= GetButtonY() && monster->GetTopY() <= GetTopY())))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*餐點能力*/
	SourceStorage* Character::GetSourceStorage()
	{
		sourceStorage->getSource(0)->setNum(5);
		sourceStorage->getSource(1)->setNum(5);
		sourceStorage->getSource(2)->setNum(5);
		sourceStorage->getSource(3)->setNum(5);
		sourceStorage->getSource(4)->setNum(15);
		sourceStorage->getSource(5)->setNum(15);
		return sourceStorage;
	}

	PropStorage* Character::GetPropStorage()
	{
		return propStorage;
	}

	void Character::EatMosquitoJump(bool flag)
	{
		SetDoubleJump(flag);
		DJtemp = flag;
	}

	bool Character::CanDoubleJump()
	{
		return doubleJump;
	}

	void Character::SetDoubleJump(bool flag)
	{
		doubleJump = flag;
	}

	void Character::EatGrassFast(bool flag)
	{
		if (flag)
		{
			IncreaseSpeed(1.4);
		}
	}

	void Character::IncreaseSpeed(double m)
	{
		STEP_SIZE = int(STEP_SIZE * m);
	}

	void Character::EatShrimpBlood(bool flag)
	{
		if (flag)
		{
			addMaxHp(20);
		}
	}

	void Character::addMaxHp(int blood)
	{
		maxHp += blood;
	}

	void Character::EatGuavaJuiceBlood(bool flag)
	{
		healBlood = flag;
	}

	void Character::healBloodEveryTenSeconds()
	{
		if (healBloodTime.GetTime() == 0)
		{
			healBloodTime.Start();
		}
		else
		{
			healBloodTime.Finish();
			if (healBloodTime.GetTime() / CLOCKS_PER_SEC > 10)
			{
				restoreCurrentHp(3);
				healBloodTime.Start();
			}
		}
	}

	void Character::Rolling(Map* m, bool flag)								//左:0 右:1
	{
		const int ROLLING_SIZE = 4;											//角色翻滾距離
		const int BORDER = 5;
		if (flag)
		{
			if (m->isEmpty(GetRightX() + ROLLING_SIZE * 3, GetTopY()) && m->isEmpty(GetRightX() + ROLLING_SIZE * 3, GetButtonY() - BORDER) && rolling_time >= 0)
			{
				if (characterX <= 670)
				{
					for (int i = 0; i < 10; i++)
					{
						if (characterX + ROLLING_SIZE > 670 && GetMap()->mapScreenMoving() == true)
						{
							characterX = 670;
						}
						else
						{
							characterX += ROLLING_SIZE;
						}
					}
				}
				else
				{
					for (int i = 0; i < 10; i++)
					{
						characterX += ROLLING_SIZE;
						if (GetMap()->mapScreenMoving() == true)
							m->addSX(-ROLLING_SIZE);
					}
				}
				rolling_time--;

				//m->addSX(-STEP_SIZE);
			}
			else
			{
				rolling_time = 0;
				isRolling = false;
			}
		}
		else
		{
			if (m->isEmpty(GetLeftX() - ROLLING_SIZE * 3, GetTopY()) && m->isEmpty(GetLeftX() - ROLLING_SIZE * 3, GetButtonY() - BORDER) && rolling_time >= 0)
			{
				if (characterX <= 670 || GetMap()->mapScreenMoving() == false)
				{
					for (int i = 0; i < 10; i++)
					{
						characterX -= ROLLING_SIZE;
					}
				}
				else
				{
					for (int i = 0; i < 10; i++)
					{
						if (characterX - ROLLING_SIZE < 670)
						{
							m->addSX(characterX - 670);
							characterX = 670;
							break;
						}
						else
						{
							characterX -= ROLLING_SIZE;
							m->addSX(ROLLING_SIZE);
						}
					}
				}
				rolling_time--;
				//m->addSX(STEP_SIZE);												//視角移動(王關不用)
			}
			else
			{
				rolling_time = 0;
				isRolling = false;
			}
		}
	}

	void Character::restoreCurrentHp(int n)
	{
		(GetCurrentHp() + n) >= GetMaxHp() ? SetCurrentHp(GetMaxHp()) : currentHp += n;
	}

	void Character::lossCurrentHp(int n)
	{
		currentHp -= n;
		isInvincible = true;
		invincibleTime.Start();
	}

	void Character::SetXY(int x, int y)
	{
		characterX = x;
		characterY = y;
	}

	void Character::showData()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[100];								// Demo 數字對字串的轉換
		sprintf(str, "CharacterBlood:%d invincibleTime(start:%d, finish:%d)", currentHp, (int)invincibleTime.GetStartTime(), (int)invincibleTime.GetFinishTime());
		pDC->TextOut(200, 120, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

		CDC* pDC2 = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f2, * f2p;
		f2.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		f2p = pDC2->SelectObject(&f2);					// 選用 font f
		pDC2->SetBkColor(RGB(230, 220, 200));
		pDC2->SetTextColor(RGB(0, 0, 0));
		char position[500];								// Demo 數字對字串的轉換
		sprintf(position, "CharacterLeftX:%d CharacterRightX:%d CharacterTopY:%d CharacterButtonY:%d"
			, GetLeftX(), GetRightX(), GetTopY(), GetButtonY());
		pDC2->TextOut(200, 100, position);
		pDC2->SelectObject(f2p);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void Character::BloodShow()
	{
		int frameNum;
		int fullHeartNum;
		int chagingHeart;

		if (healBlood)
		{
			healBloodEveryTenSeconds();
		}

		frameNum = GetMaxHp() / 20;
		fullHeartNum = GetCurrentHp() / 20;
		chagingHeart = GetCurrentHp() - fullHeartNum * 20;

		for (int i = 0; i < frameNum; i++)
		{
			bloodFrame.SetTopLeft(i * 70, 0);
			bloodFrame.ShowBitmap();
		}

		for (int i = 0; i < fullHeartNum; i++)
		{
			characterBlood[0].SetTopLeft(i * 70, 0);
			characterBlood[0].ShowBitmap();
		}

		if (GetCurrentHp() <= 0)
		{
			//show Game Over
		}
		else if (chagingHeart == 0)
		{
		}
		else if (chagingHeart <= 2)
		{
			characterBlood[9].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[9].ShowBitmap();
		}
		else if (chagingHeart <= 4)
		{
			characterBlood[8].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[8].ShowBitmap();
		}
		else if (chagingHeart <= 6)
		{
			characterBlood[7].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[7].ShowBitmap();
		}
		else if (chagingHeart <= 8)
		{
			characterBlood[6].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[6].ShowBitmap();
		}
		else if (chagingHeart <= 10)
		{
			characterBlood[5].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[5].ShowBitmap();
		}
		else if (chagingHeart <= 12)
		{
			characterBlood[4].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[4].ShowBitmap();
		}
		else if (chagingHeart <= 14)
		{
			characterBlood[3].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[3].ShowBitmap();
		}
		else if (chagingHeart <= 16)
		{
			characterBlood[2].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[2].ShowBitmap();
		}
		else if (chagingHeart <= 18)
		{
			characterBlood[1].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[1].ShowBitmap();
		}
		else if (chagingHeart <= 20)
		{
			characterBlood[0].SetTopLeft(fullHeartNum * 70, 0);
			characterBlood[0].ShowBitmap();
		}
	}
}