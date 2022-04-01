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
        num = _x = _y = 0;
    }

    void Source::LoadBitmap(int code)
    {
        sourceBmp.LoadBitmap(code);
    }

    void Source::Initialize() {
        num = _x = _y = 0;
    }

    void Source::setNum(int n) {
        num = n;
    }

    int Source::getNum() {
        return num;
    }

    void Source::consume(int n) {
        num = num - n;
    }

    void Source::add(int n) {
        num = num + n;
    }

    void Source::add() {
        num++;
    }

    void Source::setXY(int x, int y) {
        _x = x;
        _y = y;
    }

    void Source::onShow() {
        sourceBmp.SetTopLeft(_x, _y);
        sourceBmp.ShowBitmap();
    }
}