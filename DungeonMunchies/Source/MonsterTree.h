#ifndef __MONSTERTREE__
#define __MONSTERTREE__

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Tree的物件											   //
	/////////////////////////////////////////////////////////////////////////////
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
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetBottomY();				// 右下角 y 座標
		Action actionController();
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