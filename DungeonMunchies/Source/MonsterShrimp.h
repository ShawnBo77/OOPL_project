#ifndef __MONSTERSHRIMP__
#define __MONSTERSHRIMP__

#include "Counter.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Cactus的物件											   //
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
		void SetXY(int x, int y);
		void attack();
	private:
		int actionNum; // 0表示在走路，1為攻擊
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