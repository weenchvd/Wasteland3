
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include"weaponModPath.hpp"
#include"weaponModText.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, WeaponModText::language> WeaponModText::langObs_;

array<WeaponModText::language_bundle, WeaponModText::sizeType_> WeaponModText::type_;
WeaponModTextCommon                                             WeaponModText::common_;

underlying_type_t<WeaponModText::language>  WeaponModText::langIndex_   { 0 };
bool                                        WeaponModText::initialized_ { false };

///************************************************************************************************

void WeaponModText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);
    assert(sizeType_ > 0);
    unique_ptr<char[]> buffer{
        common::getFlatBuffer(WEAPON_MOD_TEXT_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbWeaponMod::FB_WeaponModText* fb{
        fbWeaponMod::GetFB_WeaponModText(buffer.get())
    };
    assert(fb != nullptr);

    initByType(fb->type(), type_);
    initCommon(fb->common());

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponModText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponModText::initByType(
    const fbWeaponMod::FB_WeaponModTextType* fb,
    array<language_bundle, sizeType_>& ar)
{
    assert(fb != nullptr);

    common::initLanguageBundle(
        fb->choke(),
        ar[common::toUnderlying(WeaponMod__Type::CHOKE)]
    );
    common::initLanguageBundle(
        fb->barrel(),
        ar[common::toUnderlying(WeaponMod__Type::BARREL)]
    );
    common::initLanguageBundle(
        fb->underbarrel(),
        ar[common::toUnderlying(WeaponMod__Type::UNDERBARREL)]
    );
    common::initLanguageBundle(
        fb->scope(),
        ar[common::toUnderlying(WeaponMod__Type::SCOPE)]
    );
    common::initLanguageBundle(
        fb->magazine(),
        ar[common::toUnderlying(WeaponMod__Type::MAGAZINE)]
    );
    common::initLanguageBundle(
        fb->weight(),
        ar[common::toUnderlying(WeaponMod__Type::WEIGHT)]
    );
    common::initLanguageBundle(
        fb->handle(),
        ar[common::toUnderlying(WeaponMod__Type::HANDLE)]
    );
}

void WeaponModText::initCommon(const fbWeaponMod::FB_WeaponModTextCommon* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->item_type(), common_.itemType_);
    common::initLanguageBundle(fb->min_damage(), common_.minDamage_);
    common::initLanguageBundle(fb->max_damage(), common_.maxDamage_);
    common::initLanguageBundle(fb->shots(), common_.shoPerAttack_);
    common::initLanguageBundle(fb->damage_type(), common_.tyDmg_);
    common::initLanguageBundle(fb->ap(), common_.ap_);
    common::initLanguageBundle(fb->ap_reload(), common_.apReload_);
    common::initLanguageBundle(fb->require(), common_.require_);
    common::initLanguageBundle(fb->ammo_capacity(), common_.ammoCap_);
    common::initLanguageBundle(fb->ammo_type(), common_.ammoType_);
    common::initLanguageBundle(fb->range(), common_.range_);
    common::initLanguageBundle(fb->base_hit_chance(), common_.hitChance_);
    common::initLanguageBundle(fb->crit_damage(), common_.critDamage_);
    common::initLanguageBundle(fb->crit_chance(), common_.critChance_);
    common::initLanguageBundle(fb->penetration(), common_.penet_);
    common::initLanguageBundle(fb->damage_vs_robots(), common_.dmgRobots_);
    common::initLanguageBundle(fb->damage_vs_synths(), common_.dmgSynths_);
    common::initLanguageBundle(fb->damage_vs_vehicles(), common_.dmgVehicles_);
    common::initLanguageBundle(fb->damage_vs_humans(), common_.dmgHumans_);
    common::initLanguageBundle(fb->damage_vs_animals(), common_.dmgAnimals_);
    common::initLanguageBundle(fb->damage_vs_mutants(), common_.dmgMutants_);
}

} // namespace object
} // namespace game
