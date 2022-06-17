#ifndef __MONSTERMOSQUITO__
#define __MONSTERMOSQUITO__

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Mosquito的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	class MonsterMosquito :public Monster
	{
	public:
		MonsterMosquito();
		MonsterMosquito(int x, int y, Character* c);
		~MonsterMosquito();
		void LoadBitmap();
		void Initialize() override;
		void OnMove(Map* m) override;
		void OnShow(Map* m) override;
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetBottomY();				// 右下角 y 座標
	private:
		void moveUp(Map* m);
		void moveDown(Map* m);
		void moveLeft(Map* m);
		void moveRight(Map* m);
		void flyCaseChanger();
		int velocity;
		int flyCase;
		bool shouldFlyCaseChange;
		Timer flyTimer;
		CAnimation faceLeft;
		CAnimation faceRight;
		CMovingBitmap sourceMosquitoJump;
	};
}
#endif 