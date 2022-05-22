#ifndef __MONSTERTREE__
#define __MONSTERTREE__

#include "Timer.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Shrimp的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	//class Monster;
	class MonsterTree :public Monster
	{
	public:
		MonsterTree();
		MonsterTree(int x, int y, Character* c);
		~MonsterTree();
		void LoadBitmap();
		void Initialize() override;
		void OnShow(Map* m) override;
		void OnMove(Map* m) override;
		void SetFacingLR(bool flag);
		bool GetFacingLR();
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標
		Action actionController();
		void showData();
	private:
		void walkOnMove();
		void attackOnMove();
		int velocity;
		CMovingBitmap sleepLeft;
		CMovingBitmap sleepRight;
		CAnimation walkLeft;
		CAnimation walkRight;
		CAnimation attackLeft;
		CAnimation attackRight;
		CMovingBitmap deadLeft;
		CMovingBitmap deadRight;
		CMovingBitmap sourceGuavaJuiceBlood;
	};
}
#endif 