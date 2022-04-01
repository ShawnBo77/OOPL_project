#ifndef __PROPBANANAATTACK__
#define __PROPBANANAATTACK__
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為道具BananaAttack
    /////////////////////////////////////////////////////////////////////////////
    class Character;

    class PropBananaAttack : public Prop {
    public:
        PropBananaAttack();
        ~PropBananaAttack();
        void Initialize();
        void effect(Character* character) override;
    private:

    };
}
#endif
