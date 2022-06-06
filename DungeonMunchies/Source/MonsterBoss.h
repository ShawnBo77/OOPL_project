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
		void OnMove(Map* m) override;
		void OnShow(Map* m) override;
		void showData();
		int  GetLeftX();				// 左上角 x 座標
		int  GetTopY();					// 左上角 y 座標
		int  GetRightX();				// 右下角 x 座標
		int  GetButtonY();				// 右下角 y 座標
		
	private:
		/*行為*/
		/*走路*/
		void walk(Map* m);
		void walkOnMove();
		void walkOnShow(Map* m);
		bool CanWalkL(Map* m);
		bool CanWalkR(Map* m);
		/*攻擊*/
		void ResetAtkCounter();
		void atkCount(int i);
		//hit
		void hitStart();
		void hitOnMove();
		void hitOnShow(Map* m);
		void hitJudge();
		//collide
		void collideStart();
		void collideOnMove();
		void collideOnShow(Map* m);
		void collideJudge();
		void rushMove(Map* m);
		//thron
		void thronStart();
		void thronBossOnMove();
		void thronBossOnShow(Map* m);
		void thronOnShow(Map* m);
		void thronJudge();
		void SetCMidX();
		//dead
		void deadOnMove();
		void deadOnShow(Map* m);
		
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
		CAnimation deadRight;
		CAnimation deadLeft;

		/*攻擊*/
		int atkCounter[3]; //計算攻擊已連續使用幾次 (0:hit ; 1:collide ; 2:thronBoss)
		//hit
		int hitDamage;
		int hitDelayCount;
		bool hitCD;
		Timer hitCDTimer;
		//collide
		int rushDistance;
		int rushStepSize;
		//thron
		int thronDamage;
		int thronCount;
		int cMidX, floor;
		bool thronExist;
	};
}
#endif
