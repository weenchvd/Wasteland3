
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"damagePath.hpp"
#include"damageText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, DamageText::language> DamageText::langObs_;

DamageTextCommon                                DamageText::common_;

underlying_type_t<DamageText::language>         DamageText::langIndex_  { 0 };
bool                                            DamageText::initialized_{ false };

///************************************************************************************************

void DamageText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);
    unique_ptr<char[]> buffer{
        common::getFlatBuffer(DAMAGE_TEXT_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbDamage::FB_DamageText* fb{
        fbDamage::GetFB_DamageText(buffer.get())
    };
    assert(fb != nullptr);

    initCommon(fb->common());

    assert(Locator::isInitialized());
    setLanguage(Locator::getOptions().optLanguage().getLanguage());
    langObs_.getDelegate().bind<&DamageText::setLanguage>();
    Locator::getOptions().optLanguage().languageSubject().addObserver(&langObs_);

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
