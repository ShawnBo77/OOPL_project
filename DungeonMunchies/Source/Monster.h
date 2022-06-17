#ifndef __MONSTER__
#define __MONSTER__
#include "BloodBar.h"
#include "Timer.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class是敵人的介面    											   //
	/////////////////////////////////////////////////////////////////////////////
	class Character;
	class Map;
	class BloodBar;
	class SourceStorage;
	class Monster
	{
	public:
		Monster();
		Monster::Monster(int x, int y, int enemyHp, int attackDamage, Character* c);
		virtual ~Monster();
		virtual void LoadBitmap() = 0;				//加載敵人Bitmap
		virtual void Initialize() = 0;				//初始化
		virtual void OnShow(Map* m) = 0;			//顯示敵人於畫面上
		virtual void OnMove(Map* m) = 0;					//敵人移動
		virtual int  GetLeftX() = 0;				// 左上角 x 座標
		virtual int  GetTopY() = 0;					// 左上角 y 座標
		virtual int  GetRightX() = 0;				// 右下角 x 座標
		virtual int  GetBottomY() = 0;				// 右下角 y 座標
		//英雄是否和此敵人碰觸
		virtual void intersect();
		void SetIsIntersect(bool flag);
		bool GetIsIntersect();
		double hpProportion();
		/////////////////////////////////////////////////////////////////////////////
		// 設定Monster的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetXY(int x, int y);					// x, y座標
		int	GetBorder();
		bool GetCanStandOn();
		void SetMovingDown(bool b);					//下
		bool GetIsMovingDown();           // 回傳是否正在往上移動
		void SetMovingUp(bool b);					//上
		bool GetIsMovingUp();           // 回傳是否正在往上移動
		void SetMovingLeft(bool b);					//左
		bool GetIsMovingLeft();	        // 回傳是否正在往左移動
		void SetMovingRight(bool b);				//右
		bool GetIsMovingRight();        // 回傳是否正在往右移動
		void SetFacingLR(bool b);				//右
		bool GetFacingLR();        // 回傳是否正在往右移動

		int distanceToCharacter();
		void SetCharacterDirection();	// 設定角色相對怪物的位置(0:角色在怪物左邊或下面)
		bool GetCharacterDirectionLR();	// 回傳角色相對怪物的位置
		bool GetCharacterDirectionTD();	// 回傳角色相對怪物的位置

		bool isAlive();
		bool isAttack();
		void knockBack();

		void SetIsOnTheFloor(bool b);
		bool GetIsOnTheFloor();         // 回傳是否正在地面

		//血量
		void SetCurrentHp(int x);      // 設定目前血量
		int GetCurrentHp();            // 取得目前血量
		void lossCurrentHp(int x);
		void lossHpShow(Map* m);

		//攻擊
		void SetIsAttacking(bool flag);		    // 設定是否攻擊
		bool GetIsAttacking();	        // 回傳是否正在攻擊
		void SetAttackDamage(int x);
		int GetAttackDamage();
		virtual void attackStart();
		virtual void attackJudge(int attackRange);
		void SetIsAttacked(bool flag);	// 設定是否受到攻擊
		bool GetIsAttacked();    // 回傳是否受到攻擊
		void isAttackedEffectCaculation();
		void isAttackedEffectOnShow(Map* m);

		//狂暴化
		void SetIsViolent(bool flag);	// 設定是否受到攻擊
		bool GetIsViolent();    // 回傳是否受到攻擊

		//結束
		void SetBossDead(bool flag);
		bool GetBossDead();

	protected:
		bool isAttackSuccessfullyL(int range);
		bool isAttackSuccessfullyR(int range);
		void touchSource(Map* m, int sourceCase);
		Character* character;
		int _x, _y;
		int init_x, init_y;
		int currentFloor;
		int hp;
		BloodBar bloodBar;
		int attackDamage;
		bool isIntersect;
		bool hasGottenSource; //看素材是否已被取得
		int lightBulbInside;
		bool hasGottenLightBulb;
		bool canStandOn;

		Action action;
		int STEP_SIZE;              // 移動速度
		int walkLength;
		int BORDER;
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingDown;
		bool isMovingUp;
		bool facingLR;              // 面向 左:0, 右:1
		bool isOnTheFloor;          // 是否位於地面
		bool isAttacking;           // 是否正在攻擊
		Timer attackCDTime;
		bool attackCD;
		int attackDelayCount;

		Timer isAttackedTimer;
		bool isAttacked;			// 是否受到攻擊
		Timer sparkleEffectTimer;
		bool isSparkleEffectTimerStart;
		bool isSparkleEffectShow;
		CMovingBitmap black;

		int lossHp;
		bool lossHpShowFlag;
		Timer lossHpTimer;
		bool characterDirectionLR;
		bool characterDirectionTD;

		bool isViolent;
		bool haveSetViolent;
		bool bossDead;
	};
}
#endif
