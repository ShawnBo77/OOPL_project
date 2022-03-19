#ifndef __PropsBook__
#define __PropsBook__
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為道具書模式
	/////////////////////////////////////////////////////////////////////////////
	class Prop;
	class PropsBook
	{
	public:
		PropsBook();
		//~PropsBook();
		void Initialize();
		void setXY(int x, int y);
		void setXY(CPoint mousePosition);
		void setPropCase();
		void setPropCase(CPoint mousePosition);
		int getMX();
		int getMY();
		void LoadBitmap();
		void onShow();
	private:
		int mx, my;
		PropCase propCase;
		CMovingBitmap propsBook;
		Prop *MosquitoJump = new Prop();
		Prop *ShrimpBlood = new Prop();
		Prop *GrassFast = new Prop();
		Prop *BananaAttack = new Prop();
		Prop *ShrimpAttack = new Prop();
		Prop *GuavaJuiceBlood = new Prop();
	};
}
#endif
