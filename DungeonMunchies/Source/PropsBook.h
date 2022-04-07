#ifndef __PropsBook__
#define __PropsBook__
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為道具書模式
	/////////////////////////////////////////////////////////////////////////////

	class Prop;
	class PropMosquitoJump;
	class PropShrimpBlood;
	class PropGrassFast;
	class PropBananaAttack;
	class PropShrimpAttack;
	class PropGuavaJuiceBlood;
	class PropStorage;
	class Character;
	class Source;
	class SourceStorage;

	class PropsBook
	{
	public:
		PropsBook();
		~PropsBook();
		void Initialize(Character* character);
		void setXY(int x, int y);
		void setXY(CPoint mousePosition);
		void setPropCase();
		void setPropCase(CPoint mousePosition);
		void setIconList();
		vector<CMovingBitmap> setIconPosition(vector<CMovingBitmap> iconList);
		int getMX();
		int getMY();
		void LoadBitmap();
		void sourceNumShow(int sourceCase);
		void onShow();
	private:
		int mx, my;
		int choicex, choicey;
		PropCase propCase;

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

		CMovingBitmap MosquitoJumpDetails;
		CMovingBitmap ShrimpBloodDetails;
		CMovingBitmap GrassFastDetails;
		CMovingBitmap BananaAttackDetails;
		CMovingBitmap ShrimpAttackDetails;
		CMovingBitmap GuavaJuiceBloodDetails;

		PropStorage* propStorage;
		SourceStorage* sourceStorage;
	};
}
#endif
