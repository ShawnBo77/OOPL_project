#ifndef CHARACTER_H
#define CHARACTER_H

#include "Map.h"
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為遊戲的角色人物物件
    /////////////////////////////////////////////////////////////////////////////
    class Character {
    public:
        Character();
        void Initialize();				// 設定初始值
        void LoadBitmap();				// 載入圖形
        void OnMove(Map *m);		    // 移動
        void OnShow();					// 將圖形貼到畫面
        int  GetLeftX();				// 左上角 x 座標
        int  GetTopY();					// 左上角 y 座標
        int  GetRightX();				// 右下角 x 座標
        int  GetButtonY();				// 右下角 y 座標
        void GetMovingDown(bool flag);	// 回傳是否正在往下移動
        bool GetIsMovingLeft();	        // 回傳是否正在往左移動
        bool GetIsMovingRight();        // 回傳是否正在往右移動
        bool GetIsMovingUp();           // 回傳是否正在往上移動
        bool GetIsRolling();            // 回傳是否正在翻滾
        bool GetIsOnTheFloor();         // 回傳是否正在地面
        bool GetIsRising();	            // 回傳是否正在上升

        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
        void SetRolling(bool flag);	    // 設定是否翻滾
        void SetXY(int x, int y);		// 設定左上角座標

    protected:
        CMovingBitmap standLeft;	   // 站立面向左
        CMovingBitmap standRight;	   // 站立面向右
        CAnimation walkingLeft;
        CAnimation walkingRight;
        CAnimation leftJump;
        CAnimation rightJump;
        CAnimation leftRolling;
        CAnimation rightRolling;

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
        int  velocity;
        int  floor;
    };
}

#endif