
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include"weaponPath.hpp"
#include"weaponText.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, WeaponText::language> WeaponText::langObs_;

array<WeaponText::language_bundle, WeaponText::sizeType_>   WeaponText::type_;
WeaponTextPenalties                                         WeaponText::penalties_;
WeaponTextCommon                                            WeaponText::common_;

underlying_type_t<WeaponText::language>     WeaponText::langIndex_  { 0 };
bool                                        WeaponText::initialized_{ false };

///************************************************************************************************

void WeaponText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);
    assert(sizeType_ > 0);
    unique_ptr<char[]> buffer{
        common::getFlatBuffer(WEAPON_TEXT_FB_BIN_FILE__NATIVE_REL_PATH)
    };

    const fbWeapon::FB_WeaponText* table{
        fbWeapon::GetFB_WeaponText(buffer.get())
    };
    assert(table != nullptr);

    initByType(table->type(), type_);
    initPenalties(table->penalties());
    initCommon(table->common());

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponText::initByType(
    const fbWeapon::FB_WeaponTextType* table,
    array<language_bundle, sizeType_>& ar)
{
    assert(table != nullptr);

    common::initLanguageBundle(
        table->ar(),
        ar[common::toUnderlying(Weapon__Type::AR)]
    );
    common::initLanguageBundle(
        table->smg(),
        ar[common::toUnderlying(Weapon__Type::SMG)]
    );
    common::initLanguageBundle(
        table->sa_pistol(),
        ar[common::toUnderlying(Weapon__Type::SEMI_AUTO_PISTOL)]
    );
    common::initLanguageBundle(
        table->revolver(),
        ar[common::toUnderlying(Weapon__Type::REVOLVER)]
    );
    common::initLanguageBundle(
        table->auto_shotgun(),
        ar[common::toUnderlying(Weapon__Type::AUTO_SHOTGUN)]
    );
    common::initLanguageBundle(
        table->pump_shotgun(),
        ar[common::toUnderlying(Weapon__Type::PUMP_SHOTGUN)]
    );
    common::initLanguageBundle(
        table->sr(),
        ar[common::toUnderlying(Weapon__Type::SNIPER)]
    );
    common::initLanguageBundle(
        table->flamethrower(),
        ar[common::toUnderlying(Weapon__Type::FLAMETHROWER)]
    );
    common::initLanguageBundle(
        table->hmg(),
        ar[common::toUnderlying(Weapon__Type::HMG)]
    );
    common::initLanguageBundle(
        table->rocket(),
        ar[common::toUnderlying(Weapon__Type::ROCKET)]
    );
    common::initLanguageBundle(
        table->laser(),
        ar[common::toUnderlying(Weapon__Type::LASER)]
    );
    common::initLanguageBundle(
        table->bladed(),
        ar[common::toUnderlying(Weapon__Type::BLADED)]
    );
    common::initLanguageBundle(
        table->blunt(),
        ar[common::toUnderlying(Weapon__Type::BLUNT)]
    );
    common::initLanguageBundle(
        table->brawling(),
        ar[common::toUnderlying(Weapon__Type::BRAWLING)]
    );
}

void WeaponText::initPenalties(const fbWeapon::FB_WeaponTextPenalties* table)
{
    assert(table != nullptr);

    common::initLanguageBundle(table->crit_damage(), penalties_.critDmg_);
    common::initLanguageBundle(table->hit_chance(), penalties_.hitChance_);
    common::initLanguageBundle(table->crit_chance(), penalties_.critChance_);
    common::initLanguageBundle(table->strike_rate(), penalties_.strikeRate_);
}

void WeaponText::initCommon(const fbWeapon::FB_WeaponTextCommon* table)
{
    assert(table != nullptr);

    common::initLanguageBundle(table->damage(), common_.damage_);
    common::initLanguageBundle(table->level(), common_.level_);
    common::initLanguageBundle(table->ap(), common_.ap_);
    common::initLanguageBundle(table->ap_reload(), common_.apReload_);
    common::initLanguageBundle(table->require(), common_.require_);
    common::initLanguageBundle(table->installed_mods(), common_.mods_);
    common::initLanguageBundle(table->ammo_capacity(), common_.ammoCap_);
    common::initLanguageBundle(table->ammo_type(), common_.ammoType_);
    common::initLanguageBundle(table->range(), common_.range_);
    common::initLanguageBundle(table->failed_req_penalty(), common_.penalty_);
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
