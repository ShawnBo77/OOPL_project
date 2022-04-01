#ifndef __PROPSTROAGE__
#define __PROPSTROAGE__

#include "Util.h"

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為道具儲存空間
    /////////////////////////////////////////////////////////////////////////////
    class Prop;
    class PropMosquitoJump;

    class PropStorage
    {
    public:
        PropStorage();
        ~PropStorage();
        void Initialize();
        Prop* getProp(int propCase);
    private:
        PropCase propCase;
        PropMosquitoJump* MosquitoJumpP;
        Prop* ShrimpBloodP;
        Prop* GrassFastP;
        Prop* BananaAttackP;
        Prop* ShrimpAttackP;
        Prop* GuavaJuiceBloodP;
    };
}
#endif