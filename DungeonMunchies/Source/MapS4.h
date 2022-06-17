#ifndef __MapS4__
#define __MAPS4__
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖構成
	/////////////////////////////////////////////////////////////////////////////
	class MapS4 : public Map
	{
	public:
		MapS4();
		~MapS4();
		void LoadBitmap();
		void Initialize();
		void setPos(int x, int y, int n);			//將地圖座標的陣列設為傳入的數字
		bool isEmpty(int x, int y) const;
		bool isPortal(int x, int y) const;
		bool isBridge(int x, int y) const;
		bool isCraftTable(int x, int y) const;
		bool isTrashCan(int x, int y) const;
		bool isGetHurtPlace(int x, int y) const;
		int blockProperty(int x, int y) const;
		void onShow();
		void syMoving(int y);
		void monsterFloorChanging(int x) override;
		void characterFloorAndCeiling() override;
		int screenX(int x) override;
		int screenY(int y) override;
		void messageOnShow() override;
	protected:
		CMovingBitmap map;
		int X, Y;
		int mapGrid[400][70];
		CMovingBitmap white, blue;
		int gridW, gridH;
		int previousFloor;
		int targetSY;
		bool screenUp;
		bool screenDown;
		CMovingBitmap message01;
		CMovingBitmap message02;
		CMovingBitmap message03;
		CMovingBitmap message04;
		CMovingBitmap message05;
		CMovingBitmap message06;
	};
}
#endif
