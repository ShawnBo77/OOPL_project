#ifndef __MONSTERBOSS__
#define __MONSTERBOSS__

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	//這個class是怪物Boss的物件											   //
	/////////////////////////////////////////////////////////////////////////////
	//class Monster;
	class MonsterBoss :public Monster
	{
	public:
		MonsterBoss();
		MonsterBoss(int x, int y, Character* c);
		~MonsterBoss();
		void LoadBitmap();
		void Initialize() override;
		void OnShow(Map* m) override;
		void showData();
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標
		void intersect() override;
		void SetXY(int x, int y);
		void OnMove();
	private:
		CAnimation walkingRight;        // 向右行走動畫
		CAnimation walkingLeft;         // 向左行走動畫
		CAnimation collideRight;        // 向右衝撞動畫
		CAnimation collideLeft;        // 向左衝撞動畫
		CAnimation hitRight;        // 向右捶動畫
		CAnimation hitLeft;        // 向左捶動畫
		CAnimation hitRightEffect;        // 向右捶動畫
		CAnimation hitLeftEffect;        // 向左捶動畫
		CAnimation thronRight;        // 向右刺動畫
		CAnimation thronLeft;        // 向左刺動畫
		CAnimation thron;        // 刺動畫

	};
}
#endif
