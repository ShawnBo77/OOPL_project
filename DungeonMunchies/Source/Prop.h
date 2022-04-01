#ifndef __Prop__
#define __Prop__
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為道具
    /////////////////////////////////////////////////////////////////////////////
    class Character;

    class Prop
    {
    public:
        Prop();
        void LoadBitmap(int code);
        void Initialize();
        void setPropFlag(bool flag);
        bool getPropFlag();
        virtual void effect(Character* character);
        void onShow();
    private:
        bool propFlag;
        CMovingBitmap propDetails;
    };
}
#endif