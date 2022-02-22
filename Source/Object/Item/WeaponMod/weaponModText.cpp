
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

    const fbWeaponMod::FB_WeaponModText* table{
        fbWeaponMod::GetFB_WeaponModText(buffer.get())
    };

    initByType(table->type(), type_);
    initCommon(table->common());

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponModText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponModText::initByType(
    const fbWeaponMod::FB_WeaponModTextType* table,
    array<language_bundle, sizeType_>& ar)
{
    assert(table != nullptr);

    common::initLanguageBundle(
        table->choke(),
        ar[common::toUnderlying(WeaponMod__Type::CHOKE)]
    );
    common::initLanguageBundle(
        table->barrel(),
        ar[common::toUnderlying(WeaponMod__Type::BARREL)]
    );
    common::initLanguageBundle(
        table->underbarrel(),
        ar[common::toUnderlying(WeaponMod__Type::UNDERBARREL)]
    );
    common::initLanguageBundle(
        table->scope(),
        ar[common::toUnderlying(WeaponMod__Type::SCOPE)]
    );
    common::initLanguageBundle(
        table->magazine(),
        ar[common::toUnderlying(WeaponMod__Type::MAGAZINE)]
    );
    common::initLanguageBundle(
        table->weight(),
        ar[common::toUnderlying(WeaponMod__Type::WEIGHT)]
    );
    common::initLanguageBundle(
        table->handle(),
        ar[common::toUnderlying(WeaponMod__Type::HANDLE)]
    );
}

void WeaponModText::initCommon(const fbWeaponMod::FB_WeaponModTextCommon* table)
{
    assert(table != nullptr);

    common::initLanguageBundle(table->item_type(), common_.itemType_);
    common::initLanguageBundle(table->min_damage(), common_.minDamage_);
    common::initLanguageBundle(table->max_damage(), common_.maxDamage_);
    common::initLanguageBundle(table->shots(), common_.shoPerAttack_);
    common::initLanguageBundle(table->damage_type(), common_.tyDmg_);
    common::initLanguageBundle(table->ap(), common_.ap_);
    common::initLanguageBundle(table->ap_reload(), common_.apReload_);
    common::initLanguageBundle(table->require(), common_.require_);
    common::initLanguageBundle(table->ammo_capacity(), common_.ammoCap_);
    common::initLanguageBundle(table->ammo_type(), common_.ammoType_);
    common::initLanguageBundle(table->range(), common_.range_);
    common::initLanguageBundle(table->base_hit_chance(), common_.hitChance_);
    common::initLanguageBundle(table->crit_damage(), common_.critDamage_);
    common::initLanguageBundle(table->crit_chance(), common_.critChance_);
    common::initLanguageBundle(table->penetration(), common_.penet_);
    common::initLanguageBundle(table->damage_vs_robots(), common_.dmgRobots_);
    common::initLanguageBundle(table->damage_vs_synths(), common_.dmgSynths_);
    common::initLanguageBundle(table->damage_vs_vehicles(), common_.dmgVehicles_);
    common::initLanguageBundle(table->damage_vs_humans(), common_.dmgHumans_);
    common::initLanguageBundle(table->damage_vs_animals(), common_.dmgAnimals_);
    common::initLanguageBundle(table->damage_vs_mutants(), common_.dmgMutants_);
}

} // namespace object
} // namespace game
