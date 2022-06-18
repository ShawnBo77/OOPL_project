#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <vector>
#include "Prop.h"
#include "PropMosquitoJump.h"
#include "PropShrimpBlood.h"
#include "PropGrassFast.h"
#include "PropBananaAttack.h"
#include "PropShrimpAttack.h"
#include "PropGuavaJuiceBlood.h"
#include "PropStorage.h"

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為道具儲存空間
    /////////////////////////////////////////////////////////////////////////////
    PropStorage::PropStorage() {
        MosquitoJumpP = new PropMosquitoJump();
        ShrimpBloodP = new PropShrimpBlood();
        GrassFastP = new PropGrassFast();
        BananaAttackP = new PropBananaAttack();
        ShrimpAttackP = new PropShrimpAttack();
        GuavaJuiceBloodP = new PropGuavaJuiceBlood();
    }

    PropStorage::~PropStorage()
    {
        delete MosquitoJumpP;
        delete ShrimpBloodP;
        delete GrassFastP;
        delete BananaAttackP;
        delete ShrimpAttackP;
        delete GuavaJuiceBloodP;
    }

    void PropStorage::Initialize() {
        MosquitoJumpP->Initialize();
        ShrimpBloodP->Initialize();
        GrassFastP->Initialize();
        BananaAttackP->Initialize();
        ShrimpAttackP->Initialize();
        GuavaJuiceBloodP->Initialize();
    }

    Prop* PropStorage::getProp(int Case) {
        switch (Case)
        {
        case mosquito_jump_p:
            return MosquitoJumpP;
        case shrimp_blood_p:
            return ShrimpBloodP;
        case grass_fast_p:
            return GrassFastP;
        case banana_attack_p:
            return BananaAttackP;
        case shrimp_attack_p:
            return ShrimpAttackP;
        case guava_juice_blood_p:
            return GuavaJuiceBloodP;
        default:
            throw "Case does not exist!";
        }
    }
}