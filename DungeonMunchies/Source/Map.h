namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖構成
	/////////////////////////////////////////////////////////////////////////////
	class Map {
	public:
		Map();
		void LoadBitmap();
		void onShow();
	protected:
		CMovingBitmap map1, map2;
		int map[4][15];
		const int X, Y;
		const int mapW, mapH;
	};
}