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
		~PropsBook();
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
		int choicex, choicey;
		PropCase propCase;
		CMovingBitmap propsBook;
		CMovingBitmap propsBookChoice;
		Prop *MosquitoJump;
		Prop *ShrimpBlood;
		Prop *GrassFast;
		Prop *BananaAttack;
		Prop *ShrimpAttack;
		Prop *GuavaJuiceBlood;
	};
}
#endif
