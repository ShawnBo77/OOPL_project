namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class提供地圖構成
    /////////////////////////////////////////////////////////////////////////////
    class Character;

    class PropMosquitoJump : public Prop {
    public:
        PropMosquitoJump();
        ~PropMosquitoJump();
        void Initialize();
        void effect(Character* character) override;
    private:
    
    };
}