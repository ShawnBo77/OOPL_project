#ifndef __PropsBook__
#define __PropsBook__
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為道具書模式
	/////////////////////////////////////////////////////////////////////////////
	class Source;
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
		void setIconList();
		vector<CMovingBitmap> setIconPosition(vector<CMovingBitmap> iconList);
		void setPropList();
		int getMX();
		int getMY();
		void LoadBitmap();
		void onShow();
	private:
		int mx, my;
		int choicex, choicey;
		PropCase propCase;
		Source *MosquitoJumpS;
		Source *ShrimpBloodS;
		Source *GrassFastS;
		Source *BananaAttackS;
		Source *ShrimpAttackS;
		Source *GuavaJuiceBloodS;
		CMovingBitmap propsBook;
		CMovingBitmap propsBookChoice;
		CMovingBitmap propHave;
		CMovingBitmap propsPot1;
		CMovingBitmap MosquitoJumpIcon;
		CMovingBitmap ShrimpBloodIcon;
		CMovingBitmap GrassFastIcon;
		CMovingBitmap BananaAttackIcon;
		CMovingBitmap ShrimpAttackIcon;
		CMovingBitmap GuavaJuiceBloodIcon;
		vector<CMovingBitmap> iconList;
		Prop *MosquitoJumpP;
		Prop *ShrimpBloodP;
		Prop *GrassFastP;
		Prop *BananaAttackP;
		Prop *ShrimpAttackP;
		Prop *GuavaJuiceBloodP;
		vector<Prop*> propList;
	};
}
#endif
