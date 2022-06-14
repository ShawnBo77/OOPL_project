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
		black.LoadBitmap(".\\res\\black.bmp", RGB(0, 0, 0));
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

		standLeft[0].LoadBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));		//向左站
		standRight[0].LoadBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));		//向右站

		//向左走動畫
		vector<int> walkingLeftAnimation_S = { IDB_HEROLEFTWALK1_S, IDB_HEROLEFTWALK2_S, IDB_HEROLEFTWALK3_S };
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingLeft[0].AddBitmap(walkingLeftAnimation_S[i], RGB(0, 0, 0));

		//向右走動畫
		vector<int> walkingRightAnimation_S = { IDB_HERORIGHTWALK1_S, IDB_HERORIGHTWALK2_S, IDB_HERORIGHTWALK3_S };
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingRight[0].AddBitmap(walkingRightAnimation_S[i], RGB(0, 0, 0));


		leftJump[0].AddBitmap(IDB_HEROLEFTJUMP_S, RGB(0, 0, 0));
		for (int i = 0; i < 3; i++)
			leftJump[0].AddBitmap(IDB_HEROLEFTSTAND_S, RGB(0, 0, 0));

		rightJump[0].AddBitmap(IDB_HERORIGHTJUMP_S, RGB(0, 0, 0));
		for (int i = 0; i < 3; i++)
			rightJump[0].AddBitmap(IDB_HERORIGHTSTAND_S, RGB(0, 0, 0));

		vector<int> rollingLeftAnimation = { IDB_HEROLEFTROLL1, IDB_HEROLEFTROLL2, IDB_HEROLEFTROLL3, IDB_HEROLEFTROLL4, IDB_HEROLEFTROLL5, IDB_HEROLEFTROLL6, IDB_HEROLEFTROLL7, IDB_HEROLEFTROLL8 };
		for (int i = 0; i < 8; i++)
			leftRolling.AddBitmap(rollingLeftAnimation[i], RGB(0, 0, 0));

		vector<int> rollingRightAnimation = { IDB_HERORIGHTROLL1, IDB_HERORIGHTROLL2, IDB_HERORIGHTROLL3, IDB_HERORIGHTROLL4, IDB_HERORIGHTROLL5, IDB_HERORIGHTROLL6, IDB_HERORIGHTROLL7, IDB_HERORIGHTROLL8 };
		for (int i = 0; i < 8; i++)
			rightRolling.AddBitmap(rollingRightAnimation[i], RGB(0, 0, 0));

		vector<int> attackingLeftAnimation_S = { IDB_HEROLEFTATTACK1_S, IDB_HEROLEFTATTACK2_S, IDB_HEROLEFTATTACK3_S, IDB_HEROLEFTATTACK4_S };
		for (int i = 0; i < 4; i++)
			leftAttacking[0].AddBitmap(attackingLeftAnimation_S[i], RGB(0, 0, 0));

		vector<int> attackingRightAnimation_S = { IDB_HERORIGHTATTACK1_S, IDB_HERORIGHTATTACK2_S, IDB_HERORIGHTATTACK3_S, IDB_HERORIGHTATTACK4_S };
		for (int i = 0; i < 4; i++)
			rightAttacking[0].AddBitmap(attackingRightAnimation_S[i], RGB(0, 0, 0));

		//has sword

		standLeft[1].LoadBitmap(IDB_HEROLEFTSTAND_G, RGB(0, 0, 0));		//向左站
		standRight[1].LoadBitmap(IDB_HERORIGHTSTAND_G, RGB(0, 0, 0));		//向右站

		//向左走動畫
		vector<int> walkingLeftAnimation_G = { IDB_HEROLEFTWALK1_G, IDB_HEROLEFTWALK2_G, IDB_HEROLEFTWALK3_G };
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingLeft[1].AddBitmap(walkingLeftAnimation_G[i], RGB(0, 0, 0));

		//向右走動畫
		vector<int> walkingRightAnimation_G = { IDB_HERORIGHTWALK1_G, IDB_HERORIGHTWALK2_G, IDB_HERORIGHTWALK3_G };
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingRight[1].AddBitmap(walkingRightAnimation_G[i], RGB(0, 0, 0));


		leftJump[1].AddBitmap(IDB_HEROLEFTJUMP_G, RGB(0, 0, 0));
		for (int i = 0; i < 3; i++)
			leftJump[1].AddBitmap(IDB_HEROLEFTSTAND_G, RGB(0, 0, 0));

		rightJump[1].AddBitmap(IDB_HERORIGHTJUMP_G, RGB(0, 0, 0));
		for (int i = 0; i < 3; i++)
			rightJump[1].AddBitmap(IDB_HERORIGHTSTAND_G, RGB(0, 0, 0));

		leftAttacking[1].AddBitmap(".\\res\\g_attack01_left.bmp", RGB(0, 0, 0));
		leftAttacking[1].AddBitmap(".\\res\\g_attack02_left.bmp", RGB(0, 0, 0));
		leftAttacking[1].AddBitmap(".\\res\\g_attack03_left.bmp", RGB(0, 0, 0));
		leftAttacking[1].AddBitmap(".\\res\\g_attack04_left.bmp", RGB(0, 0, 0));
		leftAttacking[1].AddBitmap(".\\res\\g_attack05_left.bmp", RGB(0, 0, 0));
		leftAttacking[1].AddBitmap(".\\res\\g_attack06_left.bmp", RGB(0, 0, 0));

		rightAttacking[1].AddBitmap(".\\res\\g_attack01_right.bmp", RGB(0, 0, 0));
		rightAttacking[1].AddBitmap(".\\res\\g_attack02_right.bmp", RGB(0, 0, 0));
		rightAttacking[1].AddBitmap(".\\res\\g_attack03_right.bmp", RGB(0, 0, 0));
		rightAttacking[1].AddBitmap(".\\res\\g_attack04_right.bmp", RGB(0, 0, 0));
		rightAttacking[1].AddBitmap(".\\res\\g_attack05_right.bmp", RGB(0, 0, 0));
		rightAttacking[1].AddBitmap(".\\res\\g_attack06_right.bmp", RGB(0, 0, 0));
	}

	void Character::Initialize()
	{
		characterH = 120;
		characterW = 80;
		const int X_POS = 335;													//角色起始X軸
		const int Y_POS = 80;													//角色起始Y軸
		characterX = X_POS;
		characterY = Y_POS;
		characterStage = 0;
		facingLR = 1;
		STEP_SIZE = 10;
		BORDER = 5;
		isMovingLeft = isMovingRight = isMovingUp = isRising = isRolling = false;
		canGoToNextMap = canCraft = false;
		maxHp = 80;
		currentHp = 80;
		rolling_time = 0;
		isAttacking = false;
		attackDamage = 10;
		attackRange = 60;
		isAttackedFromRight = false;
		isAttackedFromLeft = false;
		isAttackedFromBottom = false;
		isAttacked = false;
		isSparkleEffectTimerStart = false;
		isSparkleEffectShow = false;

		isInvincible = false;
		doubleJump = false;
		DJtemp = doubleJump;
		healBlood = false;
		isShrimpAttack = false;
		isMosquitoJump = isGrassFast = isShrimpBlood = isGuavaJuiceBlood = isBananaAttack = false;
		shrimpAttack = false;
		currentMap = NULL;
		action = walk_a;
		lightBulbNum = 0;
	}

	void Character::OnMove(Map* m, vector<Monster*>* monsters)
	{
		int monsterBorder;
		bool isOnMonster = false;

		if (currentMap == NULL || m->getMapName() != currentMap->getMapName())
		{
			SetMap(m);
			velocity = 30;
		}

		shouldShowMagnifier(m);
		shouldShowMessageIconFlag(m);
		SetMapCanShowMessage(m);
		SetMapAutoShowMessage(m);

		if (m->getMapName() != "MapS1" && m->getMapName() != "MapForBoss")
		{
			m->setCharacterX((GetLeftX() + GetRightX()) / 2);
			m->setCharacterY(characterY);
			m->characterFloorAndCeiling();
		}

		if (m->isPortal(GetLeftX() - BORDER, GetTopY()))
		{
			if (!canGoToNextMap)
			{
				m->setPortalOpen(true);
				SetCanGoToNextMap(true);

			}
		}
		else
		{
			m->setPortalOpen(false);
			SetCanGoToNextMap(false);
		}

		if (m->isCraftTable(GetLeftX() - BORDER, GetTopY()))
		{
			if (!canCraft)
			{
				CAudio::Instance()->Play(AUDIO_POT, false);
				m->setCraftTableOpen(true);
				SetCanCraft(true);
			}
		}
		else
		{
			m->setCraftTableOpen(false);
			SetCanCraft(false);
		}

		if (m->isTrashCan(GetLeftX() - BORDER, GetTopY()) && !m->getTrashCanOpen())
		{
			if (!m->getTrashCanOpen())
			{
				CAudio::Instance()->Play(AUDIO_RECYCLE_CAN, false);
				m->setTrashCanOpen(true);
				currentHp = maxHp;
			}
		}

		if (m->isGetHurtPlace(GetLeftX() - BORDER, GetBottomY()))
		{
			if (!isInvincible)
			{
				lossCurrentHp(5);
				if (rand() % 2)
				{
					isAttackedFromLeft = true;
					isAttackedFromBottom = true;
				}
				else
				{
					isAttackedFromRight = true;
					isAttackedFromBottom = true;
				}
			}
		}

		if (GetIsRolling())
		{
			if (isMovingLeft)
				Rolling(m, 0, monsters);
			else if (isMovingRight)
				Rolling(m, 1, monsters);
			else if (facingLR)
				Rolling(m, 1, monsters);
			else if (facingLR == 0)
				Rolling(m, 0, monsters);
		}
		else
		{
			if (CanMovingLeft(m, monsters))
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

			if (CanMovingRight(m, monsters))
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
					{
						m->addSX(-STEP_SIZE);
					}
				}
			}

			if (GetIsMovingUp() && ((GetBottomY() >= m->getFloor() && velocity == 0) || GetBottomY() == monsterTop))
			{
				isRising = true;
				velocity = 13;
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
						characterY -= velocity * 2;			// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次
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
				if (GetBottomY() < m->getFloor())				// 當y座標還沒碰到地板
				{
					if (characterY + velocity * 3 < m->getFloor() - 120)
					{
						for (unsigned int i = 0; i < monsters->size(); i++)
						{
							monsterBorder = monsters->at(i)->GetBorder();

							if (GetRightX() > monsters->at(i)->GetLeftX() + monsterBorder && GetLeftX() < monsters->at(i)->GetRightX() - monsterBorder && GetBottomY() + velocity * 3 >= monsters->at(i)->GetTopY() + monsterBorder && monsters->at(i)->isAlive())
							{
								if (characterY <= monsters->at(i)->GetTopY() + monsterBorder - 100 && monsters->at(i)->GetCanStandOn())
								{
									characterY = monsters->at(i)->GetTopY() + monsterBorder - 120;
									monsterTop = monsters->at(i)->GetTopY() + monsterBorder;
									isOnMonster = true;
								}
								break;
							}
						}
						if (!isOnMonster)
							characterY += velocity * 3;
					}

					else
						characterY = m->getFloor() - 119;
					if (velocity < 6)
						velocity++;
				}
				else
				{
					monsterTop = 0;
					characterY = m->getFloor() - 120;			// 當y座標低於地板，更正為地板上
					velocity = 0;
					SetDoubleJump(DJtemp);
				}
			}

			if (isAttackedFromRight) //還要判定是否能移動
			{
				for (int i = 0; i < 50; i++)
				{
					if (m->isEmpty(GetLeftX() - 1 - BORDER, GetTopY()) && m->isEmpty(GetLeftX() - 1 - BORDER, GetBottomY() - BORDER))
					{
						if (characterX > 670 && m->mapScreenMoving())
						{
							m->addSX(1);
						}
						characterX -= 1;
					}
				}
				isAttackedFromRight = false;
			}

			if (isAttackedFromLeft)
			{
				for (int i = 0; i < 50; i++)
				{
					if (m->isEmpty(GetRightX() + 1 + BORDER, GetTopY()) && m->isEmpty(GetRightX() + 1 + BORDER, GetBottomY() - BORDER))
					{
						if (characterX > 670 && m->mapScreenMoving())
						{
							m->addSX(-1);
						}

						characterX += 1;
					}
				}
				isAttackedFromLeft = false;
			}

			if (isAttackedFromBottom)
			{
				for (int i = 0; i < 50; i++)
				{
					characterY -= 1;
				}
				isAttackedFromBottom = false;
			}
		}

		if (isInvincible)
		{
			invincibleTimer.CaculateTimeForFalse(&isInvincible, 0.5);
		}

		if (isShrimpAttack && !shrimpAttack)
		{
			ShrimpAttackTimer.CaculateTimeForTrue(&shrimpAttack, 3);
		}

		if (healBlood)
		{
			healBloodEveryTenSeconds();
		}

		isAttackedEffectCaculation();

		for (int i = 0; i < 2; i++)
		{
			walkingLeft[i].OnMove();
			walkingRight[i].OnMove();
			leftJump[i].OnMove();
			rightJump[i].OnMove();
		}

		leftRolling.OnMove();
		rightRolling.OnMove();


		if (isAttacking)
		{
			attackOnMove();
		}
	}

	void Character::OnShow(Map* m)
	{
		BloodShow();
		ScreenCXY(m);

		if (isAttacked && isSparkleEffectShow)
		{
			isAttackedEffectOnShow();
		}
		else
		{
			if (facingLR == 0)
			{
				if (isRolling)//action == roll_a)
				{
					leftRolling.SetTopLeft(screenCX - 5, characterY + 10 + m->getYMovement());
					leftRolling.OnShow();
					leftRolling.SetDelayCount(1);
					if (leftRolling.IsFinalBitmap())
					{
						//isRolling = false;
						action = walk_a;
					}
				}
				else if (isAttacking)//action == attack_a) //attack
				{
					leftAttacking[characterStage].SetTopLeft(screenCX - 30, screenCY + m->getYMovement());
					leftAttacking[characterStage].SetDelayCount(1);
					leftAttacking[characterStage].OnShow();
					if (leftAttacking[characterStage].IsFinalBitmap())
					{
						isAttacking = false;
						action = walk_a;
						leftAttacking[characterStage].Reset();
					}
				}
				else if (GetIsRising() == true)
				{
					leftJump[characterStage].SetTopLeft(screenCX, characterY + m->getYMovement());
					leftJump[characterStage].OnShow();
					leftJump[characterStage].SetDelayCount(3);
				}
				else if ((GetIsMovingLeft() == true || GetIsMovingRight() == true) && GetIsOnTheFloor() == true)
				{
					walkingLeft[characterStage].SetTopLeft(screenCX, characterY + m->getYMovement());
					walkingLeft[characterStage].OnShow();
				}
				else
				{
					standLeft[characterStage].SetTopLeft(screenCX, characterY + m->getYMovement());
					standLeft[characterStage].ShowBitmap();
				}
			}
			else
			{
				if (isRolling)//action == roll_a)
				{
					rightRolling.SetTopLeft(screenCX - 5, characterY + 10 + m->getYMovement());
					rightRolling.OnShow();
					rightRolling.SetDelayCount(1);
					if (rightRolling.IsFinalBitmap())
					{
						//isRolling = false;
						action = walk_a;
					}
				}
				else if (isAttacking)//action == attack_a)
				{
					rightAttacking[characterStage].SetTopLeft(screenCX + 30, screenCY + m->getYMovement());
					rightAttacking[characterStage].SetDelayCount(1);
					rightAttacking[characterStage].OnShow();
					if (rightAttacking[characterStage].IsFinalBitmap())
					{
						isAttacking = false;
						action = walk_a;
						rightAttacking[characterStage].Reset();
					}
				}
				else if (GetIsRising() == true)
				{
					rightJump[characterStage].SetTopLeft(screenCX, characterY + m->getYMovement());
					rightJump[characterStage].OnShow();
					rightJump[characterStage].SetDelayCount(3);
				}
				else if ((GetIsMovingLeft() == true || GetIsMovingRight() == true) && GetIsOnTheFloor() == true)
				{
					walkingRight[characterStage].SetTopLeft(screenCX, characterY + m->getYMovement());
					walkingRight[characterStage].OnShow();
				}
				else
				{
					standRight[characterStage].SetTopLeft(screenCX, characterY + m->getYMovement());
					standRight[characterStage].ShowBitmap();
				}
			}
		}

		showData();
	}

	void Character::shouldShowMagnifier(Map* m)
	{
		if (m->getMapName() == "MapS1" && characterX > 1135 && characterX < 1300)
		{
			m->setShowMaginifierFlag(true);
		}
		else if (m->getMapName() == "MapS5" && characterX > 1450 && characterX < 1620 && GetBottomY() <= 640)
		{
			m->setShowMaginifierFlag(true);
		}
		else
		{
			m->setShowMaginifierFlag(false);
		}
	}

	void Character::shouldShowMessageIconFlag(Map* m)
	{
		if (m->getMapName() == "MapS3" && characterX > 3280 && characterX < 3500)
		{
			m->setShowMessageIconFlag(true);
		}
		else
		{
			m->setShowMessageIconFlag(false);
		}
	}

	void Character::SetMapCanShowMessage(Map* m)
	{
		if (m->getMapName() == "MapS1" && characterX > 1135 && characterX < 1300)
		{
			m->setCanShowMessage(true, 0);
		}
		else if (m->getMapName() == "MapS3" && characterX > 3280 && characterX < 3500)
		{
			m->setCanShowMessage(true, 0);
		}
		else if (m->getMapName() == "MapS5" && characterX > 1450 && characterX < 1620 && GetBottomY() <= 640)
		{
			m->setCanShowMessage(true, 0);
		}
		else
		{
			m->setCanShowMessage(false, 0);
		}
	}

	void Character::SetMapAutoShowMessage(Map* m)
	{
		if (m->getMapName() == "MapS6" && !m->getHavePlayedAutoMessage() && characterX > 3500 && characterX < 3600)
		{
			m->setAutoShowMessage(true, 0);
		}
		else
		{
			m->setAutoShowMessage(false, 0);
		}
	}

	/*Getter*/
	int Character::GetLeftX()
	{
		//if (characterStage == 1)
		//{
		//	if (facingLR)
		//		return characterX;
		//	else
		//		return characterX + 40;//+武器距離
		//}
		//else
		return characterX;
	}

	int Character::GetTopY()
	{
		return characterY;
	}

	int Character::GetRightX()
	{
		//if (characterStage == 1)
		//{
		//	if (facingLR)
		//		return characterX + characterW;
		//	else
		//		return characterX + 120;//+bitmap寬度
		//}
		//else
		return characterX + characterW;
	}

	int Character::GetBottomY()
	{
		return characterY + characterH; // + animation.Height();
	}

	int Character::GetCharacterStage()
	{
		return characterStage;
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

	bool Character::GetIsAttackedFromRight()
	{
		return isAttackedFromRight;
	}

	bool Character::GetIsAttackedFromLeft()
	{
		return isAttackedFromLeft;
	}

	bool Character::GetIsAttackedFromBottom()
	{
		return isAttackedFromBottom;
	}

	void Character::isAttackedEffectCaculation()
	{
		if (isAttacked)
		{
			isAttackedTimer.CaculateTimeForFalse(&isAttacked, 0.5);
		}
		if (isSparkleEffectShow)
		{
			sparkleEffectTimer.CaculateTimeForFalse(&isSparkleEffectShow, 0.1);
			if (!isSparkleEffectShow)
			{
				isSparkleEffectTimerStart = false;
			}
		}
		else
		{
			if (!isSparkleEffectTimerStart)
			{
				sparkleEffectTimer.Start();
				isSparkleEffectTimerStart = true;
			}
			sparkleEffectTimer.CaculateTimeForTrue(&isSparkleEffectShow, 0.15);
		}
	}

	void Character::isAttackedEffectOnShow()
	{
		black.SetTopLeft(screenCX, characterY - GetMap()->getYMovement());
		black.ShowBitmap();
	}

	bool Character::GetIsOnTheFloor()
	{
		if (GetBottomY() == GetMap()->getFloor())
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

	bool Character::GetCanGoToNextMap()
	{
		return canGoToNextMap;
	}

	bool Character::GetCanCraft()
	{
		return canCraft;
	}

	/*Setter*/
	void Character::SetMap(Map* m)
	{
		currentMap = m;
	}

	void Character::SetMovingDown()
	{
		if (GetMap()->isBridge(characterX - BORDER, GetBottomY()))
			characterY += 10;
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

	void Character::SetIsAttackedFromRight(bool flag)
	{
		isAttackedFromRight = flag;
	}

	void Character::SetIsAttackedFromLeft(bool flag)
	{
		isAttackedFromLeft = flag;
	}

	void Character::SetIsAttackedFromBottom(bool flag)
	{
		isAttackedFromBottom = flag;
	}

	void Character::SetCurrentHp(int x)
	{
		currentHp = x;
	}

	void Character::SetIsInvincible(bool flag)
	{
		isInvincible = flag;
	}

	/*翻滾*/

	bool Character::CanMovingLeft(Map* m, vector<Monster*>* monsters)
	{
		int monsterBorder;
		if (GetIsMovingLeft())
		{
			if (m->isEmpty(GetLeftX() - STEP_SIZE - BORDER, GetTopY()) && m->isEmpty(GetLeftX() - STEP_SIZE - BORDER, GetBottomY() - BORDER))
			{
				if (monsters == NULL)
				{
					return true;
				}
				else
				{
					for (unsigned int i = 0; i < monsters->size(); i++)
					{
						monsterBorder = monsters->at(i)->GetBorder();

						if (GetLeftX() - STEP_SIZE - BORDER <= monsters->at(i)->GetLeftX() + monsterBorder || GetLeftX() - STEP_SIZE - BORDER >= monsters->at(i)->GetRightX() - monsterBorder)
						{
						}
						else if (GetBottomY() - BORDER < monsters->at(i)->GetTopY() + monsterBorder || GetTopY() + BORDER > monsters->at(i)->GetBottomY() - monsterBorder)
						{
						}
						else
						{
							if (monsters->at(i)->isAlive())
								return false;
						}
					}
					return true;
				}
			}
		}
		return false;
	}

	bool Character::CanMovingRight(Map* m, vector<Monster*>* monsters)
	{
		int monsterBorder;
		if (GetIsMovingRight())
		{
			if (m->isEmpty(GetRightX() + STEP_SIZE + BORDER, GetTopY()) && m->isEmpty(GetRightX() + STEP_SIZE + BORDER, GetBottomY() - BORDER))
			{
				if (monsters == NULL)
				{
					return true;
				}
				else
				{
					for (unsigned int i = 0; i < monsters->size(); i++)
					{
						monsterBorder = monsters->at(i)->GetBorder();

						if (GetRightX() + STEP_SIZE + BORDER >= monsters->at(i)->GetRightX() - monsterBorder || GetRightX() + STEP_SIZE + BORDER <= monsters->at(i)->GetLeftX() + monsterBorder)
						{
						}
						else if (GetBottomY() - BORDER < monsters->at(i)->GetTopY() + monsterBorder || GetTopY() + BORDER > monsters->at(i)->GetBottomY() - monsterBorder)
						{
						}
						else
						{
							if (monsters->at(i)->isAlive())
								return false;
						}
					}
					return true;
				}
			}
		}
		return false;
	}

	void Character::SetSpeed(int x)
	{
		STEP_SIZE = x;
	}

	int Character::GetSpeed()
	{
		return STEP_SIZE;
	}

	void Character::SetRolling(bool flag)
	{
		if (GetIsOnTheFloor() && rolling_time <= 0)
		{
			rolling_time = 5;
			isRolling = true;
		}
		else
		{
			isRolling = false;
		}
	}

	bool Character::GetIsRolling()
	{
		return isRolling;
	}

	void Character::Rolling(Map* m, bool flag, vector<Monster*>* monsters)								//左:0 右:1
	{
		action = roll_a;
		isInvincible = true;
		invincibleTimer.Start();
		const int ROLLING_SIZE = 4;											//角色翻滾距離
		const int BORDER = 5;
		if (flag)
		{
			if (rolling_time >= 0)
			{
				if (characterX <= 670)
				{
					for (int i = 0; i < 10; i++)
					{
						if (m->isEmpty(GetRightX() + ROLLING_SIZE, GetTopY()) && m->isEmpty(GetRightX() + ROLLING_SIZE, GetBottomY() - BORDER))
						{
							if (characterX + ROLLING_SIZE > 670 && characterX + ROLLING_SIZE < 670 + ROLLING_SIZE && GetMap()->mapScreenMoving() == true)
							{
								characterX = 670;
							}
							else if (characterX >= 670)
							{
								characterX += ROLLING_SIZE;
								if (GetMap()->mapScreenMoving() == true)
								{
									m->addSX(-ROLLING_SIZE);
								}
							}
							else
							{
								characterX += ROLLING_SIZE;
							}
						}
						else
							break;
					}
				}
				else
				{
					for (int i = 0; i < 10; i++)
					{
						if (m->isEmpty(GetRightX() + ROLLING_SIZE, GetTopY()) && m->isEmpty(GetRightX() + ROLLING_SIZE, GetBottomY() - BORDER))
						{
							characterX += ROLLING_SIZE;
							if (GetMap()->mapScreenMoving() == true)
							{
								m->addSX(-ROLLING_SIZE);
							}
						}
						else
							break;
					}
				}
				rolling_time--;
			}
			else
			{
				rolling_time = 0;
				isRolling = false;
			}
		}
		else
		{
			if (rolling_time >= 0)
			{
				if (characterX <= 670 || GetMap()->mapScreenMoving() == false)
				{
					for (int i = 0; i < 10; i++)
					{
						if (m->isEmpty(GetLeftX() - ROLLING_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - ROLLING_SIZE, GetBottomY() - BORDER))
							characterX -= ROLLING_SIZE;
						else
							break;
					}
				}
				else
				{
					for (int i = 0; i < 10; i++)
					{
						if (m->isEmpty(GetLeftX() - ROLLING_SIZE, GetTopY()) && m->isEmpty(GetLeftX() - ROLLING_SIZE, GetBottomY() - BORDER))
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
						else
							break;
					}
				}
				rolling_time--;
			}
			else
			{
				rolling_time = 0;
				isRolling = false;
			}
		}
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

	void Character::SetAttackRange(int x)
	{
		attackRange = x;
	}

	int Character::GetAttackRange()
	{
		return attackRange;
	}

	void Character::attack(vector<Monster*>* monsters)
	{
		CAudio::Instance()->Play(AUDIO_ATTACK_HU, false);
		action = attack_a;
		isAttacking = true;

		for (unsigned int i = 0; i < monsters->size(); i++)
		{
			if (facingLR == 0)
			{
				if (isAttackSuccessfullyL(attackRange, monsters->at(i)))
				{
					if (monsters->at(i)->isAlive())
					{
						//monsters[i].SetIsAttackedFromRight(true);
						if (shrimpAttack)
						{
							monsters->at(i)->lossCurrentHp(attackDamage + 15);
							shrimpAttack = false;
							ShrimpAttackTimer.Start();
						}
						else
						{
							monsters->at(i)->lossCurrentHp(attackDamage);
						}
					}
				}
			}
			else
			{
				if (isAttackSuccessfullyR(attackRange, monsters->at(i)))
				{
					if (monsters->at(i)->isAlive())
					{
						//monsters[i].SetIsAttackedFromLeft(true);
						if (shrimpAttack)
						{
							monsters->at(i)->lossCurrentHp(attackDamage + 15);
							shrimpAttack = false;
							ShrimpAttackTimer.Start();
						}
						else
						{
							monsters->at(i)->lossCurrentHp(attackDamage);
						}
					}
				}
			}
		}
	}

	void Character::attackOnMove()
	{
		if (facingLR == 0)
		{
			leftAttacking[0].OnMove();
			leftAttacking[1].OnMove();
		}
		else
		{
			rightAttacking[0].OnMove();
			rightAttacking[1].OnMove();
		}
	}

	bool Character::isAttackSuccessfullyL(int range, Monster* monster)
	{
		if (((monster->GetRightX() >= GetLeftX() - range && monster->GetRightX() <= GetLeftX()) ||
			(monster->GetLeftX() >= GetLeftX() - range && monster->GetLeftX() <= GetLeftX()) ||
			(monster->GetLeftX() <= GetLeftX() - range && monster->GetRightX() >= GetLeftX()))
			&& ((monster->GetBottomY() >= GetTopY() && monster->GetBottomY() <= GetBottomY()) ||
				(monster->GetTopY() >= GetTopY() && monster->GetTopY() <= GetBottomY()) ||
				(monster->GetTopY() <= GetTopY() && monster->GetBottomY() >= GetBottomY())))
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
			&& ((monster->GetBottomY() >= GetTopY() && monster->GetBottomY() <= GetBottomY()) ||
				(monster->GetTopY() >= GetTopY() && monster->GetTopY() <= GetBottomY()) ||
				(monster->GetBottomY() >= GetBottomY() && monster->GetTopY() <= GetTopY())))
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
		return sourceStorage;
	}

	PropStorage* Character::GetPropStorage()
	{
		return propStorage;
	}

	void Character::EatMosquitoJump(bool flag)
	{
		isMosquitoJump = flag;
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
		isGrassFast = flag;
		if (flag)
		{
			ChangeSpeed(1.4);
		}
		else
		{
			ChangeSpeed(0.72);
		}
	}

	void Character::ChangeSpeed(double m)
	{
		STEP_SIZE = int(STEP_SIZE * m);
	}

	void Character::EatShrimpBlood(bool flag)
	{
		isShrimpBlood = flag;
		if (flag)
		{
			maxHp += 20;
		}
		else
		{
			maxHp -= 20;
		}
	}

	void Character::addMaxHp(int blood)
	{
		maxHp += blood;
	}

	void Character::EatGuavaJuiceBlood(bool flag)
	{
		isGuavaJuiceBlood = flag;
		healBlood = flag;
	}

	void Character::healBloodEveryTenSeconds()
	{
		if (healBloodTimer.GetTime() == 0)
		{
			healBloodTimer.Start();
		}
		else
		{
			healBloodTimer.Finish();
			if (healBloodTimer.GetTime() / CLOCKS_PER_SEC > 10)
			{
				restoreCurrentHp(3);
				healBloodTimer.Start();
			}
		}
	}

	void Character::EatBananaAttack(bool flag)
	{
		isBananaAttack = flag;
		if (flag)
		{
			attackDamage += 3;
		}
		else
		{
			attackDamage -= 3;
		}
	}

	void Character::EatShrimpAttack(bool flag)
	{
		if (flag)
		{
			isShrimpAttack = true;
			ShrimpAttackTimer.Start();
		}
		else
		{
			isShrimpAttack = false;
		}
	}

	void Character::SetIsMosquitoJump(bool flag)
	{
		isMosquitoJump = flag;
	}

	bool Character::GetIsMosquitoJump()
	{
		return isMosquitoJump;
	}

	void Character::SetIsGrassFast(bool flag)
	{
		isGrassFast = flag;
	}

	bool Character::GetIsGrassFast()
	{
		return isGrassFast;
	}

	void Character::SetIsShrimpBlood(bool flag)
	{
		isShrimpBlood = flag;
	}

	bool Character::GetIsShrimpBlood()
	{
		return isShrimpBlood;
	}

	void Character::SetIsGuavaJuiceBlood(bool flag)
	{
		isGuavaJuiceBlood = flag;
	}

	bool Character::GetIsGuavaJuiceBlood()
	{
		return isGuavaJuiceBlood;
	}

	void Character::SetIsBananaAttack(bool flag)
	{
		isBananaAttack = flag;
	}

	bool Character::GetIsBananaAttack()
	{
		return isBananaAttack;
	}

	void Character::SetIsShrimpAttack(bool flag)
	{
		isShrimpAttack = flag;
	}

	bool Character::GetIsShrimpAttack()
	{
		return isShrimpAttack;
	}

	void Character::SetLightBulbNum(int num)
	{
		lightBulbNum = num;
	}

	int Character::GetLightBulbNum()
	{
		return lightBulbNum;
	}

	void Character::AddLightBulb(int num)
	{
		lightBulbNum += num;
	}

	void Character::ConsumeLightBulb(int num)
	{
		lightBulbNum -= num;
	}

	void Character::SetAllSourceNumToHundred()
	{
		sourceStorage->getSource(0)->setNum(100);
		sourceStorage->getSource(1)->setNum(100);
		sourceStorage->getSource(2)->setNum(100);
		sourceStorage->getSource(3)->setNum(100);
		sourceStorage->getSource(4)->setNum(100);
		sourceStorage->getSource(5)->setNum(100);
	}

	void Character::restoreCurrentHp(int n)
	{
		(GetCurrentHp() + n) >= GetMaxHp() ? SetCurrentHp(GetMaxHp()) : currentHp += n;
	}

	void Character::lossCurrentHp(int n)
	{
		currentHp -= n;
		isInvincible = true;
		invincibleTimer.Start();
		isAttacked = true;
		isAttackedTimer.Start();
		isSparkleEffectShow = true;
		sparkleEffectTimer.Start();
		isSparkleEffectTimerStart = true;
	}

	bool Character::isIntersect(int lX, int rX, int tY, int bY)
	{
		if ((GetRightX() >= lX && GetRightX() <= rX ||
			GetLeftX() <= rX && GetLeftX() >= lX ||
			GetLeftX() <= lX && GetRightX() >= rX || //角色比東西寬
			GetRightX() <= rX && GetLeftX() >= lX) && //東西比角色寬
			((GetBottomY() >= tY && GetBottomY() <= bY) ||
				(GetTopY() >= tY && GetTopY() <= bY) ||
				(GetTopY() >= tY && GetBottomY() <= bY) ||
				(GetTopY() <= tY && GetBottomY() >= bY)))
		{
			return true;
		}
		return false;
	}

	void Character::characterHasSword(bool flag)
	{
		if (flag)
		{
			attackDamage = 25;
			attackRange = 170;
			characterStage = 1;
		}
		else
		{
			attackDamage = 10;
			attackRange = 60;
			characterStage = 0;
		}

	}

	void Character::SetXY(int x, int y)
	{
		characterX = x;
		characterY = y;
	}

	void Character::SetCanGoToNextMap(bool flag)
	{
		canGoToNextMap = flag;
	}

	void Character::SetCanCraft(bool flag)
	{
		canCraft = flag;
	}

	void Character::showData()
	{
		//CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		//CFont f, * fp;
		//f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		//fp = pDC->SelectObject(&f);					// 選用 font f
		//pDC->SetBkColor(RGB(230, 220, 200));
		//pDC->SetTextColor(RGB(0, 0, 0));
		//char str[100];								// Demo 數字對字串的轉換
		//sprintf(str, "CharacterBlood:%d invincibleTimer(start:%d, finish:%d)", currentHp, (int)invincibleTimer.GetStartTime(), (int)invincibleTimer.GetFinishTime());
		//pDC->TextOut(200, 120, str);
		//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

		CDC* pDC2 = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f2, * f2p;
		f2.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		f2p = pDC2->SelectObject(&f2);					// 選用 font f
		pDC2->SetBkColor(RGB(230, 220, 200));
		pDC2->SetTextColor(RGB(0, 0, 0));
		char position[500];								// Demo 數字對字串的轉換
		sprintf(position, "CharacterLeftX:%d CharacterRightX:%d CharacterTopY:%d CharacterBottomY:%d CharacterAttack:%d ScreenX: %d ScreenY: %d"
			, GetLeftX(), GetRightX(), GetTopY(), GetBottomY(), attackDamage, (currentMap == NULL) ? 0 : currentMap->getSX(), (currentMap == NULL) ? 0 : currentMap->getSY());
		pDC2->TextOut(200, 120, position);
		pDC2->SelectObject(f2p);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void Character::BloodShow()
	{
		int frameNum;
		int fullHeartNum;
		int chagingHeart;

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
	void Character::ScreenCXY(Map* m)
	{
		int bmpBorderX = 0;
		int bmpBorderY = 0;

		if (characterStage == 1)
		{
			if (facingLR)
			{
				if (isAttacking)
				{
					bmpBorderX = 105;
					bmpBorderY = 105;
				}
				else
					bmpBorderX = 25;
			}
			else
			{
				if (isAttacking)
				{
					bmpBorderX = 155;
					bmpBorderY = 105;
				}
				else
					bmpBorderX = 35;
			}
		}

		screenCY = characterY - bmpBorderY;
		if (characterX < 670 || m == NULL || m->mapScreenMoving() == false)
		{
			screenCX = characterX - bmpBorderX;
		}
		else
		{
			screenCX = 670 - bmpBorderX;
		}
	}
}