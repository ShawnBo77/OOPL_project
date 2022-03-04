namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為遊戲的角色人物物件
    /////////////////////////////////////////////////////////////////////////////
    class Character {
    public:
        Character();
        void LoadBitmap();
        void onMove();
        void onShow();
        //protected:
        //    void OnShow();                                    // 顯示這個狀態的遊戲畫面
    private:
        CMovingBitmap character;
        int x, y;
    };
}