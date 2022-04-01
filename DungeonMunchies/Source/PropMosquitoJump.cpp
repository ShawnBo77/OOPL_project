#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Prop.h"
#include "PropMosquitoJump.h"
#include <vector>

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
// 這個class提供地圖構成
/////////////////////////////////////////////////////////////////////////////

    PropMosquitoJump::PropMosquitoJump() : Prop() 
    {

    }

    PropMosquitoJump::~PropMosquitoJump()
    {
    }

    void PropMosquitoJump::Initialize()
    {
    }

    void PropMosquitoJump::effect(Character* character)
    {
        character->GetButtonY();
    }
}