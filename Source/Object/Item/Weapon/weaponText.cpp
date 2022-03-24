
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
    const fbWeapon::FB_WeaponText* fb{
        fbWeapon::GetFB_WeaponText(buffer.get())
    };
    assert(fb != nullptr);

    initByType(fb->type(), type_);
    initPenalties(fb->penalties());
    initCommon(fb->common());

    assert(Locator::isInitialized());
    setLanguage(Locator::getOptions().optLanguage().getLanguage());
    langObs_.getDelegate().bind<&WeaponText::setLanguage>();
    Locator::getOptions().optLanguage().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponText::initByType(
    const fbWeapon::FB_WeaponTextType* fb,
    array<language_bundle, sizeType_>& ar)
{
    assert(fb != nullptr);

    common::initLanguageBundle(
        fb->ar(),
        ar[common::toUnderlying(Weapon__Type::AR)]
    );
    common::initLanguageBundle(
        fb->smg(),
        ar[common::toUnderlying(Weapon__Type::SMG)]
    );
    common::initLanguageBundle(
        fb->sa_pistol(),
        ar[common::toUnderlying(Weapon__Type::SEMI_AUTO_PISTOL)]
    );
    common::initLanguageBundle(
        fb->revolver(),
        ar[common::toUnderlying(Weapon__Type::REVOLVER)]
    );
    common::initLanguageBundle(
        fb->auto_shotgun(),
        ar[common::toUnderlying(Weapon__Type::AUTO_SHOTGUN)]
    );
    common::initLanguageBundle(
        fb->pump_shotgun(),
        ar[common::toUnderlying(Weapon__Type::PUMP_SHOTGUN)]
    );
    common::initLanguageBundle(
        fb->sr(),
        ar[common::toUnderlying(Weapon__Type::SNIPER)]
    );
    common::initLanguageBundle(
        fb->flamethrower(),
        ar[common::toUnderlying(Weapon__Type::FLAMETHROWER)]
    );
    common::initLanguageBundle(
        fb->hmg(),
        ar[common::toUnderlying(Weapon__Type::HMG)]
    );
    common::initLanguageBundle(
        fb->rocket(),
        ar[common::toUnderlying(Weapon__Type::ROCKET)]
    );
    common::initLanguageBundle(
        fb->laser(),
        ar[common::toUnderlying(Weapon__Type::LASER)]
    );
    common::initLanguageBundle(
        fb->bladed(),
        ar[common::toUnderlying(Weapon__Type::BLADED)]
    );
    common::initLanguageBundle(
        fb->blunt(),
        ar[common::toUnderlying(Weapon__Type::BLUNT)]
    );
    common::initLanguageBundle(
        fb->brawling(),
        ar[common::toUnderlying(Weapon__Type::BRAWLING)]
    );
}

void WeaponText::initPenalties(const fbWeapon::FB_WeaponTextPenalties* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->crit_damage(), penalties_.critDmg_);
    common::initLanguageBundle(fb->hit_chance(), penalties_.hitChance_);
    common::initLanguageBundle(fb->crit_chance(), penalties_.critChance_);
    common::initLanguageBundle(fb->strike_rate(), penalties_.strikeRate_);
}

void WeaponText::initCommon(const fbWeapon::FB_WeaponTextCommon* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->item_type(), common_.itemType_);
    common::initLanguageBundle(fb->level(), common_.level_);
    common::initLanguageBundle(fb->damage(), common_.damage_);
    common::initLanguageBundle(fb->ap(), common_.ap_);
    common::initLanguageBundle(fb->ap_reload(), common_.apReload_);
    common::initLanguageBundle(fb->require(), common_.require_);
    common::initLanguageBundle(fb->installed_mods(), common_.mods_);
    common::initLanguageBundle(fb->ammo_capacity(), common_.ammoCap_);
    common::initLanguageBundle(fb->ammo_type(), common_.ammoType_);
    common::initLanguageBundle(fb->range(), common_.range_);
    common::initLanguageBundle(fb->failed_req_penalty(), common_.penalty_);
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
