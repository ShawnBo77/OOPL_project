#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Util.h"
#include "Monster.h"
#include "Character.h"
#include "SourceStorage.h"
#include "Map.h"

namespace game_framework
{
	Monster::Monster()
	{
		_x = 400;
		_y = 400;
		hp = 1200;
		attackDamage = 0;
		isAttacking = false;
		isIntersect = false;
	}

	Monster::Monster(int x, int y, int enemyHp, int ATK, Character* c)
	{
		_x = x;
		_y = y;
		init_x = x;
		init_y = y;
		hp = enemyHp;
		bloodBar.setFullHP(hp);
		attackDamage = ATK;
		isAttacking = false;
		isIntersect = false;
		character = c;
		characterDirectionLR = 0;
		characterDirectionTD = 0;
		bossDead = false;
		hasGottenSource = false;
		lossHp = 0;
		lossHpShowFlag = 0;
		lightBulbInside = 0;
		hasGottenLightBulb = false;
		isAttacked = false;
		isSparkleEffectTimerStart = false;
		isSparkleEffectShow = false;
	}

	Monster::~Monster()
	{
	}

	void Monster::intersect()
	{
		if (isAlive())
		{
			if (character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX()
				&& character->GetBottomY() >= GetTopY() && character->GetBottomY() <= GetBottomY())
			{ //角色右方碰到怪物
				isIntersect = true;
				if (!character->GetIsInvincible())
				{
					character->SetIsAttackedFromRight(true);
				}
			}
			if (character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX()
				&& character->GetBottomY() >= GetTopY() && character->GetBottomY() <= GetBottomY())
			{ //角色左方碰到怪物
				isIntersect = true;
				if (!character->GetIsInvincible())
				{
					character->SetIsAttackedFromLeft(true);
				}
			}
			if ((character->GetRightX() >= GetLeftX() && character->GetRightX() <= GetRightX() ||
				character->GetLeftX() <= GetRightX() && character->GetLeftX() >= GetLeftX() ||
				character->GetLeftX() <= GetLeftX() && character->GetRightX() >= GetRightX() || //角色比怪物寬
				character->GetRightX() <= GetRightX() && character->GetLeftX() >= GetLeftX()) && //怪物比角色寬
				((character->GetBottomY() >= GetTopY() && character->GetBottomY() <= GetBottomY()) || //角色下方碰到怪物
					(character->GetTopY() >= GetTopY() && character->GetTopY() <= GetBottomY())))
			{
				isIntersect = true;
				if (!character->GetIsInvincible())
				{
					character->SetIsAttackedFromBottom(true);
				}
			}
			if (isIntersect && !character->GetIsInvincible())
			{
				character->lossCurrentHp(attackDamage);
			}
		}
		isIntersect = false;
	}

	void Monster::SetIsIntersect(bool flag)
	{
		isIntersect = flag;
	}

	bool Monster::GetIsIntersect()
	{
		return isIntersect;
	}

	int Monster::distanceToCharacter() //與角色的距離 若太遠則不用動作
	{
		int x_distance = (GetLeftX() + GetRightX()) / 2 - (character->GetLeftX() + character->GetRightX()) / 2;
		int y_distance = _y - character->GetTopY();
		return (int)(sqrt(pow(x_distance, 2) + pow(y_distance, 2)));
	}

	void Monster::SetCharacterDirection()
	{
		int cX, cY, mX, mY;
		cX = (character->GetLeftX() + character->GetRightX()) / 2;
		cY = (character->GetBottomY() + character->GetTopY()) / 2;
		mX = (_x + GetRightX()) / 2;
		mY = (_y + GetBottomY()) / 2;
		if (cX < mX)
		{
			characterDirectionLR = 0; //角色在怪物左邊
		}
		else
		{
			characterDirectionLR = 1;
		}
		if (cY < mY)
		{
			characterDirectionTD = 0;
		}
		else
		{
			characterDirectionTD = 1;
		}
	}

	bool Monster::GetCharacterDirectionLR()
	{
		return characterDirectionLR;
	}

	bool Monster::GetCharacterDirectionTD()
	{
		return characterDirectionTD;
	}

	double Monster::hpProportion()
	{
		return (double)(hp) / bloodBar.getFullHP();
	}

	void Monster::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	int Monster::GetBorder()
	{
		return BORDER;
	}

	bool Monster::GetCanStandOn()
	{
		return canStandOn;
	}

	void Monster::SetMovingDown(bool b)
	{
		isMovingDown = b;
	}

	bool Monster::GetIsMovingDown()
	{
		return isMovingDown;
	}

	void Monster::SetMovingUp(bool b)
	{
		isMovingUp = b;
	}

	bool Monster::GetIsMovingUp()
	{
		return isMovingUp;
	}

	void Monster::SetMovingLeft(bool b)
	{
		isMovingLeft = b;
	}

	bool Monster::GetIsMovingLeft()
	{
		return isMovingLeft;
	}

	void Monster::SetMovingRight(bool b)
	{
		isMovingRight = b;
	}

	bool Monster::GetIsMovingRight()
	{
		return isMovingRight;
	}

	void Monster::SetFacingLR(bool b)
	{
		facingLR = b;
	}

	bool Monster::GetFacingLR()
	{
		return facingLR;
	}
	bool Monster::isAlive()
	{
		if (hp <= 0)
		{
			return false;
		}
		return true;
	}

	bool Monster::isAttack()
	{
		return isAttacking;
	}

	void Monster::knockBack()
	{
		if (facingLR == 0)
		{
			_x += 1;
		}
		if (facingLR == 1)
		{
			_x -= 1;
		}
	}

	void Monster::SetIsOnTheFloor(bool b)
	{
		isOnTheFloor = b;
	}

	bool Monster::GetIsOnTheFloor()
	{
		return isOnTheFloor;
	}

	void Monster::SetCurrentHp(int x)
	{
		hp = x;
	}

	int Monster::GetCurrentHp()
	{
		return hp;
	}

	void Monster::lossCurrentHp(int x)
	{
		hp -= x;
		lossHp = x;
		lossHpShowFlag = true;
		lossHpTimer.Start();
		isAttacked = true;
		isAttackedTimer.Start();
		isSparkleEffectShow = true;
		sparkleEffectTimer.Start();
		isSparkleEffectTimerStart = true;
	}

	void Monster::lossHpShow(Map* m)
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		/*pDC->SetBkColor(RGB(230, 220, 200));*/
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 0, 0));
		char position[500];								// Demo 數字對字串的轉換
		sprintf(position, "%d", lossHp);
		pDC->TextOut(GetRightX() + m->getXMovement() + 10, GetTopY() + m->getYMovement() + 10, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void Monster::SetIsAttacking(bool flag)
	{
		isAttacking = flag;
	}

	bool Monster::GetIsAttacking()
	{
		return isAttacking;
	}

	void Monster::SetAttackDamage(int x)
	{
		attackDamage = x;
	}

	int Monster::GetAttackDamage()
	{
		return attackDamage;
	}

	void Monster::attackStart()
	{
		action = attack_a;
		attackCDTime.Start();
		attackCD = true;
	}

	void Monster::attackJudge(int attackRange)
	{
		if (!character->GetIsInvincible())
		{
			if (facingLR == 0)
			{
				if (isAttackSuccessfullyL(attackRange))
				{
					character->SetIsAttackedFromRight(true);
					character->lossCurrentHp(attackDamage);
				}
			}
			else
			{
				if (isAttackSuccessfullyR(attackRange))
				{
					character->SetIsAttackedFromLeft(true);
					character->lossCurrentHp(attackDamage);
				}
			}
		}
	}

	void Monster::SetIsAttacked(bool flag)
	{
		isAttacked = flag;
	}

	bool Monster::GetIsAttacked()
	{
		return isAttacked;
	}

	void Monster::isAttackedEffectCaculation()
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

	void Monster::isAttackedEffectOnShow(Map* m)
	{
		black.SetTopLeft(_x + m->getXMovement(), _y + m->getYMovement());
		black.ShowBitmap();
	}

	void Monster::SetIsViolent(bool flag)
	{
		isViolent = flag;
	}

	bool Monster::GetIsViolent()
	{
		return isViolent;
	}

	void Monster::SetBossDead(bool flag)
	{
		bossDead = flag;
	}

	bool Monster::GetBossDead()
	{
		return bossDead;
	}

	bool Monster::isAttackSuccessfullyL(int range)
	{
		if (((character->GetRightX() >= GetLeftX() - range && character->GetRightX() <= GetLeftX()) ||
			(character->GetLeftX() >= GetLeftX() - range && character->GetLeftX() <= GetLeftX()) ||
			(character->GetLeftX() <= GetLeftX() - range && character->GetRightX() >= GetRightX()))
			&& ((character->GetBottomY() >= GetTopY() && character->GetBottomY() <= GetBottomY()) ||
				(character->GetTopY() >= GetTopY() && character->GetTopY() <= GetBottomY()) ||
				(character->GetTopY() <= GetTopY() && character->GetBottomY() >= GetBottomY())))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Monster::isAttackSuccessfullyR(int range)
	{
		if (((character->GetLeftX() <= GetRightX() + range && character->GetLeftX() >= GetRightX()) ||
			(character->GetRightX() <= GetRightX() + range && character->GetRightX() >= GetRightX()) ||
			(character->GetLeftX() <= GetRightX() && character->GetRightX() >= GetRightX() + range))
			&& ((character->GetBottomY() >= GetTopY() && character->GetBottomY() <= GetBottomY()) ||
				(character->GetTopY() >= GetTopY() && character->GetTopY() <= GetBottomY()) ||
				(character->GetBottomY() >= GetBottomY() && character->GetTopY() <= GetTopY())))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Monster::touchSource(Map* m, int sourceCase)
	{
		if (character->isIntersect((GetLeftX() + GetRightX()) / 2, (GetLeftX() + GetRightX()) / 2 + 64, currentFloor - 64, currentFloor))
		{
			hasGottenSource = true;
			if (sourceCase == green_sword_s)
			{
				character->characterHasSword(true);
			}
			else
			{
				character->GetSourceStorage()->add(sourceCase);
			}
		}
	}
}
