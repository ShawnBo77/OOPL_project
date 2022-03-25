#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <vector>
#include "Source.h"

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
// ³o­Óclass¬°¯À§÷
/////////////////////////////////////////////////////////////////////////////

    Source::Source() {
    }

    void Source::Initialize() {
        num = 0;
    }

    void Source::setNum(int n) {
        num = n;
    }

    int Source::getNum() {
        return num;
    }

    void Source::consume() {
        num--;
    }

    void Source::add() {
        num++;
    }
}