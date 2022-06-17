#ifndef __MONSTERSHRIMP__
#define __MONSTERSHRIMP__

#include "Timer.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Shrimp的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	//class Monster;
	class MonsterShrimp :public Monster
	{
	public:
		MonsterShrimp();
		MonsterShrimp(int x, int y, Character* c);
		~MonsterShrimp();
		void LoadBitmap();
		void Initialize() override;
		void OnShow(Map* m) override;
		void OnMove(Map* m) override;
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetBottomY();				// 右下角 y 座標
		void showData();
	private:
		void attackOnMove();
		int velocity;
		CAnimation walkLeft;
		CAnimation walkRight;
		CAnimation attackLeft;
		CAnimation attackRight;
		CMovingBitmap deadLeft;
		CMovingBitmap deadRight;
		CMovingBitmap sourceShrimpAttack;
		CMovingBitmap sourceShrimpBlood;
		int randN;		
	};
}
#endif 