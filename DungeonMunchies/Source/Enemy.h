#ifndef __ENEMY__
#define __ENEMY__

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class是敵人的共同介面    											   //
	/////////////////////////////////////////////////////////////////////////////
	class Character;
	class Map;
	class Enemy
	{
	public:
		Enemy();
		Enemy::Enemy(int x, int y, int enemyHp, string name, Character* c);
		virtual ~Enemy();
		virtual void LoadBitmap() = 0;				//加載敵人Bitmap
		virtual void OnShow(Map* m) = 0;			//顯示敵人於畫面上
		virtual void OnMove(Map* m) = 0;			//敵人移動
		virtual int  GetLeftX() = 0;				// 左上角 x 座標
		virtual int  GetTopY() = 0;					// 左上角 y 座標
		virtual int  GetRightX() = 0;				// 右下角 x 座標
		virtual int  GetButtonY() = 0;				// 右下角 y 座標
		virtual void Initialize() = 0;				//初始化
		//英雄是否和此敵人所在同一位置，前身是cannotPass
		virtual bool intersect(int x1, int x2, int y1, int y2) = 0;
		int distanceToHero();
		double hpProportion();
		/////////////////////////////////////////////////////////////////////////////
		// 設定Enemy的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);					//下
		void SetMovingUp(bool b);					//上
		void SetMovingLeft(bool b);					//左
		void SetMovingRight(bool b);				//右
		void SetXY(int x, int y);					//x, y座標
		bool isAlive();
		bool isAttack();
		void knockBack();
	protected:
		Character* character;
		int _x, _y;
		int init_x, init_y;
		int hp;
		int full_hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		int _direction;
	};
}
#endif