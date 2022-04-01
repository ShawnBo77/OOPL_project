#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Prop.h"
#include "PropGrassFast.h"
#include <vector>

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
// 這個class為道具GrassFast
/////////////////////////////////////////////////////////////////////////////

    PropGrassFast::PropGrassFast() : Prop()
    {
    }

    PropGrassFast::~PropGrassFast()
    {
    }

    void PropGrassFast::Initialize()
    {
    }

    void PropGrassFast::effect(Character* character)
    {
    }
}