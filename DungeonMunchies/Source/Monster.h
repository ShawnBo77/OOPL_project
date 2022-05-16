#ifndef __MONSTER__
#define __MONSTER__

#include "BloodBar.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class是敵人的介面    											   //
	/////////////////////////////////////////////////////////////////////////////
	class Character;
	class Map;
	class BloodBar;
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
		virtual int  GetButtonY() = 0;				// 右下角 y 座標
		//英雄是否和此敵人碰觸
		virtual void intersect();
		void SetIsIntersect(bool flag);
		bool GetIsIntersect();
		double hpProportion();
		/////////////////////////////////////////////////////////////////////////////
		// 設定Monster的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetXY(int x, int y);					// x, y座標
		void SetRelativeMovement(int x);					// x, y座標
		int	GetBorder();
		int GetHorizontalGap();				//之後可能可以刪除
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
		void SetMaxHp(int x);			// 設定最大血量
		int GetMaxHp();                // 取得最大血量
		void SetCurrentHp(int x);      // 設定目前血量
		int GetCurrentHp();            // 取得目前血量
		void lossCurrentHp(int x);

		//攻擊
		void SetIsAttacking(bool flag);		    // 設定是否攻擊
		bool GetIsAttacking();	        // 回傳是否正在攻擊
		void SetIsAttacked(bool flag);	// 設定是否受到攻擊
		bool GetIsAttacked();    // 回傳是否受到攻擊
		void SetAttackDamage(int x);
		int GetAttackDamage();
		//virtual void attack(int attackRange, int attackCD);

	protected:
		bool isAttackSuccessfullyL(int range);
		bool isAttackSuccessfullyR(int range);
		Character* character;
		int _x, _y;
		int init_x, init_y;
		int currentFloor;
		int maxHp;
		int hp;
		BloodBar bloodBar;
		int attackDamage;
		bool isIntersect;

		Action action;
		int STEP_SIZE;              // 移動速度
		int RelativeMovement;              // 移動速度
		int BORDER;				
		int HORIZONTAL_GAP;
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingDown;
		bool isMovingUp;
		bool facingLR;              // 面向 左:0, 右:1
		bool isOnTheFloor;          // 是否位於地面
		bool isAttacking;           // 是否正在攻擊
		bool isAttacked;			// 是否受到攻擊
		bool characterDirectionLR;
		bool characterDirectionTD;
	};
}
#endif
