#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Prop.h"
#include "PropShrimpAttack.h"
#include <vector>

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
// 這個class為道具ShrimpAttack
/////////////////////////////////////////////////////////////////////////////

    PropShrimpAttack::PropShrimpAttack() : Prop()
    {
    }

    PropShrimpAttack::~PropShrimpAttack()
    {
    }

    void PropShrimpAttack::Initialize()
    {
    }

    void PropShrimpAttack::effect(Character* character)
    {
    }
}