#ifndef __BLOODBAR__
#define __BLOODBAR__

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供血條													   //
	/////////////////////////////////////////////////////////////////////////////
	class Map;
	class BloodBar
	{
	public:
		BloodBar();
		void loadBloodBar();
		void showBloodBar(Map* m, int hp);
		void setFullHP(int n);					//設定滿血的血量
		void setXY(int x, int y);				//設定血條的x y 座標
		int getFullHP();						//回傳滿血的血量
	private:
		CMovingBitmap bloodBar[10];			//不同長度的血條
		double fullHp;
		int _x, _y;
	};
}
#endif#pragma once
