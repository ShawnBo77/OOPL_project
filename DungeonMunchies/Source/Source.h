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
        void Initialize();
        void setNum(int n);
        int getNum();
        void consume();
        void add();
    private:
        int num;
    };
}
#endif