#ifndef __MONSTERMOSQUITO__
#define __MONSTERMOSQUITO__

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Mosquito的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	//class Monster;

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
		void showData();
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標
	private:
		int velocity;
		CAnimation faceLeft;
		CAnimation faceRight;
		CMovingBitmap sourceMosquitoJump;
	};
}
#endif 