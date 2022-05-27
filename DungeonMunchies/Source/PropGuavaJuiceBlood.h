#ifndef __PROPGUAVAJUICEBLOOD__
#define __PROPGUAVAJUICEBLOOD__
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為道具GuavaJuiceBlood
    /////////////////////////////////////////////////////////////////////////////
    class Character;

    class PropGuavaJuiceBlood : public Prop {
    public:
        PropGuavaJuiceBlood();
        ~PropGuavaJuiceBlood();
        void Initialize();
        void effect(Character* character, bool flag) override;
    private:

    };
}
#endif
