#ifndef __SOURCE__
#define __SOURCE__
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // ³o­Óclass¬°¯À§÷
    /////////////////////////////////////////////////////////////////////////////
    class Source
    {
    public:
        Source();
        void LoadBitmap(int code);
        void Initialize();
        void setNum(int n);
        int getNum();
        void consume(int n);
        void add(int n);
        void add();
        void setXY(int x, int y);
        void onShow();
    private:
        int num;
        int _x, _y;
        CMovingBitmap sourceBmp;
    };
}
#endif