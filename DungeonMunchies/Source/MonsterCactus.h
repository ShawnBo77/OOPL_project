#ifndef __MONSTERGRASS__
#define __MONSTERGRASS__

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Cactus的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	//class Monster;
	class MonsterCactus :public Monster
	{
	public:
		MonsterCactus();
		MonsterCactus(int x, int y, Character* c);
		~MonsterCactus();
		void LoadBitmap();
		void Initialize() override;
		void OnShow(Map* m) override;
		void showData();
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標
		void SetXY(int x, int y);
		void OnMove();
	private:
		CMovingBitmap cactusAlive;
		CMovingBitmap cactusDead;
	};
}
#endif 