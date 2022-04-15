#ifndef __CHARACTER__
#define __CHARACTER__

#include "Map.h"
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為遊戲的角色人物物件
    /////////////////////////////////////////////////////////////////////////////
    class Source;
    class SourceStorage;
    class Prop;
    class PropStorage;
    
    class Character {
    public:
        Character();
        ~Character();
        Map* GetMap();				    // 地圖
        void Initialize();				// 設定初始值
        void LoadBitmap();				// 載入圖形
        void OnMove(Map *m);		    // 移動
        void OnShow();			// 將圖形貼到畫面

        int  GetLeftX();				// 左上角 x 座標
        int  GetTopY();					// 左上角 y 座標
        int  GetRightX();				// 右下角 x 座標
        int  GetButtonY();				// 右下角 y 座標
        void GetMovingDown();	        // 回傳是否正在往下移動
        bool GetIsMovingLeft();	        // 回傳是否正在往左移動
        bool GetIsMovingRight();        // 回傳是否正在往右移動
        bool GetIsMovingUp();           // 回傳是否正在往上移動
        bool GetIsRolling();            // 回傳是否正在翻滾
        bool GetIsOnTheFloor();         // 回傳是否正在地面
        bool GetIsRising();	            // 回傳是否正在上升
        bool GetIsAttacking();	        // 回傳是否正在攻擊
        bool GetIsAttackFromRight();	        // 回傳攻擊是否來自右方
        bool GetIsAttackFromLeft();	        // 回傳攻擊是否來自左方
        bool GetIsAttackFromButton();	        // 回傳攻擊是否來自下方
        bool CanDoubleJump();           // 回傳是否可以二段跳

        void SetMap(Map *m);
        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetFacingDirection(int mouseX); // 設定面對方向
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
        void SetRolling(bool flag);	    // 設定是否翻滾
        void SetXY(int x, int y);		// 設定左上角座標
        void SetAttacking(bool flag);		// 設定是否攻擊
        void SetIsAttackFromRight(bool flag);	        // 回傳攻擊是否來自右方
        void SetIsAttackFromLeft(bool flag);	        // 回傳攻擊是否來自左方
        void SetIsAttackFromButton(bool flag);	        // 回傳攻擊是否來自下方
        void SetDoubleJump(bool flag);      // 設定是否可以二段跳

        void Rolling(Map *m, bool flag);    // 翻滾動作
        void addATK(int ATK);
        void Attack(bool flag);

        /*餐點能力*/
        SourceStorage* GetSourceStorage();	        // 回傳素材儲存空間
        PropStorage* GetPropStorage();	            // 回傳道具儲存空間
        void EatMosquitoJump(bool flag);  
        
        

    protected:
        CMovingBitmap standLeft;	    // 站立面向左
        CMovingBitmap standRight;	    // 站立面向右
        CMovingBitmap bloodFrame;	    // 角色血量框
        CAnimation walkingLeft;         // 向左行走動畫
        CAnimation walkingRight;        // 向右行走動畫
        CAnimation leftJump;            // 左跳動畫
        CAnimation rightJump;           // 右跳動畫
        CAnimation leftRolling;         // 左滾動畫
        CAnimation rightRolling;        // 右滾動畫
        CAnimation leftAttacking;        // 向左攻擊動畫
        CAnimation rightAttacking;       // 向右攻擊動畫
        Map* currentMap;

		int characterX, characterY;
		int characterW, characterH;
		bool isMovingDown;		    // 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isRolling;             // 是否正在翻滾
		bool facingLR;              // 面向 左:0, 右:1
		bool isOnTheFloor;          // 是否位於地面
		bool isRising;              // 是否正在上升
		bool isAttacking;           // 是否正在攻擊
		bool isAttackFromRight;
		bool isAttackFromLeft;
		bool isAttackFromButton;
		int  velocity;
		int  rolling_time;

		bool doubleJump;
		bool DJtemp;

		SourceStorage* sourceStorage;
		PropStorage* propStorage;
	};
}

#endif