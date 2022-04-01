#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Prop.h"
#include "PropShrimpBlood.h"
#include <vector>

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
// 這個class道具ShrimpBlood
/////////////////////////////////////////////////////////////////////////////

    PropShrimpBlood::PropShrimpBlood() : Prop()
    {
    }

    PropShrimpBlood::~PropShrimpBlood()
    {
    }

    void PropShrimpBlood::Initialize()
    {
    }

    void PropShrimpBlood::effect(Character* character)
    {
    }
}