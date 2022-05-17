
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"damagePath.hpp"
#include"damageText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include<assert.h>
#include<memory>
#include<stdlib.h>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase                       DamageText::base_;
DamageTextCommon                            DamageText::common_;
bool                                        DamageText::initialized_{ false };

///************************************************************************************************

void DamageText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(DAMAGE_TEXT_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              DAMAGE_TEXT_FB_BIN_FILE__HASH);
    const fbDamage::FB_DamageText* fb{
        fbDamage::GetFB_DamageText(buffer.get())
    };

    assert(fb != nullptr);
    initCommon(fb->common());

    initialized_ = true;
}

void DamageText::initCommon(const fbDamage::FB_DamageTextCommon* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->damage_vs_robots(), common_.dmgRobots_);
    common::initLanguageBundle(fb->damage_vs_vehicles(), common_.dmgVehicles_);
    common::initLanguageBundle(fb->damage_vs_humans(), common_.dmgHumans_);
    common::initLanguageBundle(fb->damage_vs_animals(), common_.dmgAnimals_);
    common::initLanguageBundle(fb->damage_vs_mutants(), common_.dmgMutants_);
}

} // namespace object
} // namespace game
