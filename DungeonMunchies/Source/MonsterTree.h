#ifndef __MONSTERTREE__
#define __MONSTERTREE__

#include "Counter.h"
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
		void OnMove();
		void showData();
		void SetFacingLR(bool flag);
		bool GetFacingLR();
		void SetActionNum(int num);
		bool GetActionNum();
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標
		void attack();
	private:
		int actionNum; // 0表示在走路，1為攻擊
		CMovingBitmap sleepLeft;
		CMovingBitmap sleepRight;
		CAnimation walkLeft;
		CAnimation walkRight;
		CAnimation attackLeft;
		CAnimation attackRight;
		CMovingBitmap deadLeft;
		CMovingBitmap deadRight;
		Counter attackCDTime;
		bool attackCD;
	};
}
#endif 