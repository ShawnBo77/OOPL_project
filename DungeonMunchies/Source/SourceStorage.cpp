#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <vector>
#include "Util.h"
#include "Source.h"
#include "SourceStorage.h"

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
// 這個class為素材儲存空間
/////////////////////////////////////////////////////////////////////////////

    SourceStorage::SourceStorage() {
        MosquitoJumpS = new Source();
        ShrimpBloodS = new Source();
        GrassFastS = new Source();
        BananaAttackS = new Source();
        ShrimpAttackS = new Source();
        GuavaJuiceBloodS = new Source();
    }

    SourceStorage::~SourceStorage()
    {
        delete MosquitoJumpS;
        delete ShrimpBloodS;
        delete GrassFastS;
        delete BananaAttackS;
        delete GuavaJuiceBloodS;
    }

    //void SourceStorage::LoadBitmap(int code)
    //{
    //}

    void SourceStorage::Initialize() {
        MosquitoJumpS->Initialize();
        ShrimpBloodS->Initialize();
        GrassFastS->Initialize();
        BananaAttackS->Initialize();
        ShrimpAttackS->Initialize();
        GuavaJuiceBloodS->Initialize();
    }

    Source* SourceStorage::getSource(int sourceCase) {
        switch (sourceCase)
        {
        case mosquito_jump_s:
            return MosquitoJumpS;
        case shrimp_blood_s:
            return ShrimpBloodS;
        case grass_fast_s:
            return GrassFastS;
        case banana_attack_s:
            return BananaAttackS;
        case shrimp_attack_s:
            return ShrimpAttackS;
        case guava_juice_blood_s:
            return GuavaJuiceBloodS;
        default:
            throw "sourceCase didn't exist!";
        }
    }

    //void SourceStorage::setNum(int sourceCase, int num) {
    //    getSource(sourceCase)->setNum(num);
    //}

    //int SourceStorage::getNum(int sourceCase) {
    //    getSource(sourceCase)->getNum();
    //}

    //void SourceStorage::add(int sourceCase, int num) {
    //    getSource(sourceCase)->add(num);
    //}

    //void SourceStorage::add(int sourceCase) {
    //    getSource(sourceCase)->add();
    //}

    //void SourceStorage::consume(int sourceCase, int num) {
    //    getSource(sourceCase)->consume(num);
    //}

    //void SourceStorage::setXY(int sourceCase, int x, int y) {
    //    getSource(sourceCase)->setXY(x, y);
    //}

    //void SourceStorage::onShow() {
    //}
}