namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為遊戲的角色人物物件
    /////////////////////////////////////////////////////////////////////////////
    class Character {
    public:
        Character();
        int  GetX1();					// 左上角 x 座標
        int  GetY1();					// 左上角 y 座標
        int  GetX2();					// 右下角 x 座標
        int  GetY2();					// 右下角 y 座標
        void Initialize();				// 設定初始值
        void LoadBitmap();				// 載入圖形
        void OnMove();					// 移動
        void OnShow();					// 將圖形貼到畫面
        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
        void SetXY(int nx, int ny);		// 設定左上角座標
    protected:
        CAnimation animation;
        int x, y;
        bool isMovingDown;			// 是否正在往下移動
        bool isMovingLeft;			// 是否正在往左移動
        bool isMovingRight;			// 是否正在往右移動
        bool isMovingUp;			// 是否正在往上移動
    };
}