#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <vector>
#include "Character.h"
#include "Prop.h"

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class為道具
    /////////////////////////////////////////////////////////////////////////////

    Prop::Prop() {
        propFlag = false;
    }

    void Prop::LoadBitmap(int code) {
        propDetails.LoadBitmap(code);
    }

    void Prop::Initialize() {
        propFlag = false;
    }

    void Prop::setPropFlag(bool flag) {
        propFlag = flag;
    }

    bool Prop::getPropFlag() {
        return propFlag;
    }

    void Prop::effect(Character* character) {
    }

    void Prop::onShow() {
        propDetails.SetTopLeft(474, 27);
        propDetails.ShowBitmap();
    }
}