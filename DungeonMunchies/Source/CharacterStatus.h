#ifndef __CHARACTERSTATUS__
#define __CHARACTERSTATUS__
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為道具書模式
	/////////////////////////////////////////////////////////////////////////////
	class Character;

	class CharacterStatus
	{
	public:
		CharacterStatus();
		~CharacterStatus();
		void LoadBitmap();
		void Initialize(Character* character);
		void onShow();
		void showhp();
		void showAttackDamage();
		void showAttackRange();
		void showSpeed();
		void showEffect();
		void effectCheck();
		void showData(int x, int y, int data);
		void showData(int x, int y, char* data);
		void showData(int x, int y, int data1, int data2);
		void setStage(Stage stage);
		Stage getStage();
		void showStage();
	private:
		CMovingBitmap characterStatus;
		Character* _character;
		Stage _stage;
		char* cstage;
		int row;
		int col[3];
		bool haveFirstLine;
		int x, y;
		int mjLen, gfLen, sbLen;
	};
}
#endif

