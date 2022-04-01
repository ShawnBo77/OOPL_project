#ifndef __SOURCESTROAGE__
#define __SOURCESTROAGE__
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為素材儲存空間
    /////////////////////////////////////////////////////////////////////////////
    class Source;
    
    class SourceStorage
    {
    public:
        SourceStorage();
        ~SourceStorage();
        //void LoadBitmap(int code);
        void Initialize();
        Source* getSource(int sourceCase);
        //void setNum(int sourceCase, int num);
        //int getNum(int sourceCase);
        //void add(int sourceCase, int num);
        //void add(int sourceCase);
        //void consume(int sourceCase, int num);
        //void setXY(int sourceCase, int x, int y);
        //void onShow();
    private:
        //Source* getSource(int sourceCase);
        SourceCase sourceCase;
        Source* MosquitoJumpS;
        Source* ShrimpBloodS;
        Source* GrassFastS;
        Source* BananaAttackS;
        Source* ShrimpAttackS;
        Source* GuavaJuiceBloodS;
    };
}
#endif