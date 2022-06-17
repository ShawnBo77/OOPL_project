#ifndef __MonsterCactusMUTATION__
#define __MonsterCactusMUTATION__

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物CactusMutation的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	class MonsterCactusMutation :public Monster
	{
	public:
		MonsterCactusMutation();
		MonsterCactusMutation(int x, int y, Character* c);
		~MonsterCactusMutation();
		void LoadBitmap();
		void Initialize() override;
		void OnShow(Map* m) override;
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetBottomY();				// 右下角 y 座標
		void OnMove(Map* m) override;
	private:
		CMovingBitmap cactusAlive;
		CMovingBitmap cactusDead;
		CMovingBitmap sourceGreenSword;
	};
}
#endif 