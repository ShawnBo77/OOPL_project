#ifndef __CHARACTER__
#define __CHARACTER__

#include "Map.h"
#include "Timer.h"
#include "Util.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的角色人物物件
	/////////////////////////////////////////////////////////////////////////////
	class Source;
	class SourceStorage;
	class Prop;
	class PropStorage;
	class Monster;

	class Character
	{
	public:
		Character();
		~Character();
		Map* GetMap();				    // 地圖
		void Initialize();				// 設定初始值
		void LoadBitmap();				// 載入圖形
		void OnMove(Map* m, vector<Monster*>* monsters);		    // 移動
		void OnShow();			        // 將圖形貼到畫面
		void ResetPosition(Map* m);			// 地圖切換時，重置位置
		void showData();
		void BloodShow();

		/*map*/
		//MapS1
		void shouldShowMagnifier(Map* m);

		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標

		void GetMovingDown();	        // 回傳是否正在往下移動
		bool GetIsMovingLeft();	        // 回傳是否正在往左移動
		bool GetIsMovingRight();        // 回傳是否正在往右移動
		bool GetIsMovingUp();           // 回傳是否正在往上移動
		bool GetIsOnTheFloor();         // 回傳是否正在地面
		bool GetIsRising();	            // 回傳是否正在上升
		bool GetCanGoToNextMap();		// 回傳是否可以前往下一關

		int GetMaxHp();                // 取得最大血量
		int GetCurrentHp();            // 取得目前血量
		bool GetIsInvincible();         //回傳是否為無敵狀態

		void SetMap(Map* m);
		void SetMovingDown();					// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	        // 設定是否正在往左移動
		void SetMovingRight(bool flag);         // 設定是否正在往右移動
		void SetFacingDirection(int mouseX);    // 設定面對方向
		void SetMovingUp(bool flag);	        // 設定是否正在往上移動
		void SetXY(int x, int y);		        // 設定左上角座標
		void SetCanGoToNextMap(bool flag);		// 設定左上角座標


		void SetCurrentHp(int x);               // 設定目前血量
		void SetIsInvincible(bool flag);         //設定是否為無敵狀態

		void restoreCurrentHp(int n);           // 恢復目前血量
		void lossCurrentHp(int n);              // 損血

		bool isIntersect(int lX, int rX, int tY, int bY); //看物體是否和角色重疊

		/*行為*/
		//判定是否可以左右移動
		bool CanMovingLeft(Map* m, vector<Monster*>* monsters);
		bool CanMovingRight(Map* m, vector<Monster*>* monsters);

		void monsterRelativeMove(vector<Monster*>* monsters, int x);
		//速度
		void SetSpeed(int x);
		int GetSpeed();
		//翻滾
		void SetRolling(bool flag);	            // 設定是否翻滾
		bool GetIsRolling();            // 回傳是否正在翻滾
		void Rolling(Map* m, bool flag, vector<Monster*>* monsters);        // 翻滾動作
		//攻擊
		void SetAttacking(bool flag);		    // 設定是否攻擊
		bool GetIsAttacking();	        // 回傳是否正在攻擊
		void SetAttackDamage(int x);                     // 設定攻擊力
		int GetAttackDamage();                  // 取得攻擊力
		void addAttackDamage(int x);                   // 提升攻擊力
		void SetAttackRange(int x);
		int GetAttackRange();
		void attack(vector<Monster*>* monsters);
		void attackOnMove();
		//受到攻擊
		void SetIsAttackedFromRight(bool flag);	// 設定攻擊是否來自右方
		bool GetIsAttackedFromRight();    // 回傳攻擊是否來自右方
		void SetIsAttackedFromLeft(bool flag);	// 設定攻擊是否來自左方
		bool GetIsAttackedFromLeft();	    // 回傳攻擊是否來自左方
		void SetIsAttackedFromButton(bool flag);	// 設定攻擊是否來自下方
		bool GetIsAttackedFromButton();	// 回傳攻擊是否來自下方
		void isAttackedEffectCaculation();
		void isAttackedEffectOnShow();


		/*餐點能力*/
		SourceStorage* GetSourceStorage();	        // 回傳素材儲存空間
		PropStorage* GetPropStorage();	            // 回傳道具儲存空間
		void EatMosquitoJump(bool flag);        // 吃下二段跳能力
		bool CanDoubleJump();                   // 回傳是否可以二段跳
		void SetDoubleJump(bool flag);          // 設定是否可以二段跳
		void EatGrassFast(bool flag);           // 吃下移動速度提升能力
		void ChangeSpeed(double m);           // 提升移動速度(倍率)
		void EatShrimpBlood(bool flag);         // 吃下血量提升能力
		void addMaxHp(int blood);               // 提升血量上限
		void EatGuavaJuiceBlood(bool flag);     // 吃下每十秒回三滴血能力
		void healBloodEveryTenSeconds();        // 每十秒回三滴血
		void EatBananaAttack(bool flag);
		void EatShrimpAttack(bool flag);

		void SetIsMosquitoJump(bool flag);
		bool GetIsMosquitoJump();
		void SetIsGrassFast(bool flag);
		bool GetIsGrassFast();
		void SetIsShrimpBlood(bool flag);
		bool GetIsShrimpBlood();
		void SetIsGuavaJuiceBlood(bool flag);
		bool GetIsGuavaJuiceBlood();
		void SetIsBananaAttack(bool flag);
		bool GetIsBananaAttack();
		void SetIsShrimpAttack(bool flag);
		bool GetIsShrimpAttack();
		void SetLightBulbNum(int num);
		int GetLightBulbNum();
		void AddLightBulb(int num);
		void ConsumeLightBulb(int num);

	protected:
		bool isAttackSuccessfullyL(int range, Monster* monster);
		bool isAttackSuccessfullyR(int range, Monster* monster);
		CMovingBitmap standLeft;	    // 站立面向左
		CMovingBitmap standRight;	    // 站立面向右
		CMovingBitmap bloodFrame;	    // 角色血量框
		CMovingBitmap characterBlood[10];   // 角色血量
		CAnimation walkingLeft;         // 向左行走動畫
		CAnimation walkingRight;        // 向右行走動畫
		CAnimation leftJump;            // 左跳動畫
		CAnimation rightJump;           // 右跳動畫
		CAnimation leftRolling;         // 左滾動畫
		CAnimation rightRolling;        // 右滾動畫
		CAnimation leftAttacking;       // 向左攻擊動畫
		CAnimation rightAttacking;      // 向右攻擊動畫
		//CAnimation animation;           // for test
		Map* currentMap;

		int characterX, characterY;
		int screenCX, screenCY;
		int yRelativeMovement;
		int characterW, characterH;
		bool mapScreenCanMoving;
		bool canGoToNextMap;
		int STEP_SIZE;              // 移動速度
		int BORDER;
		bool isMovingDown;		    // 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isRolling;             // 是否正在翻滾
		bool facingLR;              // 面向 左:0, 右:1
		bool isOnTheFloor;          // 是否位於地面
		bool isRising;              // 是否正在上升
		bool isAttacking;           // 是否正在攻擊
		int attackRange;
		bool isAttackedFromRight;
		bool isAttackedFromLeft;
		bool isAttackedFromButton;
		Timer isAttackedTimer;
		bool isAttacked;			// 是否受到攻擊
		Timer sparkleEffectTimer;
		bool isSparkleEffectTimerStart;
		bool isSparkleEffectShow;
		CMovingBitmap black;

		int  velocity;
		int  rolling_time;
		Action action;

		Timer healBloodTimer;
		bool healBlood;

		Timer invincibleTimer;
		bool isInvincible;

		int currentHp;
		int maxHp;
		int attackDamage;
		bool doubleJump;
		bool DJtemp;

		/*餐點*/
		bool isMosquitoJump;
		bool isGrassFast;
		bool isShrimpBlood;
		bool isGuavaJuiceBlood;
		bool isBananaAttack;
		Timer ShrimpAttackTimer;
		bool shrimpAttack;
		bool isShrimpAttack;

		int lightBulbNum;

		SourceStorage* sourceStorage;
		PropStorage* propStorage;
	};
}

#endif