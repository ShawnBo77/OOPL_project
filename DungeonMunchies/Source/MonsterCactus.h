#ifndef __MONSTERGRASS__
#define __MONSTERGRASS__

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//註解請參照BlueGoblin.h 												   //
	/////////////////////////////////////////////////////////////////////////////
	//class Monster;
	class MonsterCactus :public Monster {
	public:
		MonsterCactus();
		MonsterCactus(int x, int y, Character* c);
		~MonsterCactus();
		void LoadBitmap();
		void OnShow(Map* m) override;
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標
		void Initialize()override;
		bool isIntersect() override;
		void SetXY(int x, int y);
	private:
		CMovingBitmap cactus;
	};
}
#endif 