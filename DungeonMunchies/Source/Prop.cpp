#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <vector>
#include "Prop.h"

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
// 這個class為道具
/////////////////////////////////////////////////////////////////////////////

    Prop::Prop() {
    }

    void Prop::Initialize() {
        prop = false;
    }

    void Prop::getProp() {
        prop = true;
    }

    bool Prop::havingProp() {
        return prop;
    }

    void Prop::LoadBitmap(int code) {
        propDetails.LoadBitmap(code);
    }

    void Prop::onShow() {
        propDetails.SetTopLeft(474, 27);
        propDetails.ShowBitmap();
    }
}