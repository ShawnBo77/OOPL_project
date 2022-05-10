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
		void CharacterStatus::showhp();
		void CharacterStatus::showAttackDamage();
		void CharacterStatus::showAttackRange();
		void CharacterStatus::showSpeed();
		void CharacterStatus::showEffect();
		void CharacterStatus::effectCheck();
		void CharacterStatus::showData(int x, int y, int data);
		void CharacterStatus::showData(int x, int y, char* data);
		void CharacterStatus::showData(int x, int y, int data1, int data2);
	private:
		CMovingBitmap characterStatus;
		Character* _character;
		int row;
		int col[3];
		bool haveFirstLine;
		int x, y;
		int mjLen, gfLen, sbLen;
	};
}
#endif

