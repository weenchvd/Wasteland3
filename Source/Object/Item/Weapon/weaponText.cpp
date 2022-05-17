
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"weaponPath.hpp"
#include"weaponText.hpp"
#include<assert.h>
#include<memory>
#include<stdlib.h>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase                       WeaponText::base_;
array<WeaponText::language_bundle_t, WeaponText::sizeType_>
                                            WeaponText::type_;
WeaponTextPenalties                         WeaponText::penalties_;
WeaponTextCommon                            WeaponText::common_;
bool                                        WeaponText::initialized_{ false };

///************************************************************************************************

void WeaponText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(WEAPON_TEXT_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              WEAPON_TEXT_FB_BIN_FILE__HASH);
    const fbWeapon::FB_WeaponText* fb{
        fbWeapon::GetFB_WeaponText(buffer.get())
    };

    assert(fb != nullptr);
    initByType(fb->type(), type_);
    initPenalties(fb->penalties());
    initCommon(fb->common());

    initialized_ = true;
}

void WeaponText::initByType(
    const fbWeapon::FB_WeaponTextType* fb,
    array<language_bundle_t, sizeType_>& ar)
{
    assert(sizeType_ > 0);
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
    common::initLanguageBundle(fb->failed_req_penalty(), common_.penalty_);
    common::initLanguageBundle(fb->base_hit_chance(), common_.hitChance_);
    common::initLanguageBundle(fb->crit_damage(), common_.critDamage_);
    common::initLanguageBundle(fb->crit_chance(), common_.critChance_);
    common::initLanguageBundle(fb->bonus_sneak_damage(), common_.bonSneakDmg_);
    common::initLanguageBundle(fb->bonus_norm_damage(), common_.bonNormDmg_);
    common::initLanguageBundle(fb->bonus_melee_damage(), common_.bonMeleeDmg_);
    common::initLanguageBundle(fb->bonus_range_damage(), common_.bonRangeDmg_);
    common::initLanguageBundle(fb->penetration(), common_.penet_);
}

} // namespace object
} // namespace game
