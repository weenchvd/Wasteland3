
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_REFERENCE_HPP
#define WEAPON_REFERENCE_HPP

#include"common.hpp"
#include"item.hpp"
#include"ammo.hpp"
#include"damage.hpp"
#include"weaponMod.hpp"
#include"weaponCommon.hpp"
#include<array>

namespace game {
namespace object {

constexpr unsigned int nWMSlots = 4; // number of weapon mod slots

using Slot_WeaponModTypes = std::array<WeaponMod::Type, nWMSlots>;

struct WeaponReference {
    explicit WeaponReference() noexcept
        :
        model_          { Weapon__Model::INVALID },
        type_           { Weapon__Type::INVALID },
        weaponModTypes_ { WeaponMod::Type::INVALID,
                            WeaponMod::Type::INVALID,
                            WeaponMod::Type::INVALID,
                            WeaponMod::Type::INVALID },
        name_           {},
        descrip_        {},
        dmgMin_         { 0 },
        dmgMax_         { 0 },
        price_          { 0 },
        rangeAttack_    { 0 },
        capAmmo_        { 0 },
        mulCritDmg_     { 0 },
        chaHit_         { 0 },
        chaCritDmg_     { 0 },
        level_          { 0 },
        levSkill_       { 0 },
        armorPen_       { 0 },
        apAttack_       { 0 },
        apReload_       { 0 },
        shoPerAttack_   { 0 },
        tyAmmo_         { Ammo::Type::INVALID },
        tyDmg_          { Damage::Type::INVALID }
    {}

    WeaponReference(const WeaponReference&) = delete;
    WeaponReference& operator=(const WeaponReference&) = delete;
    WeaponReference(WeaponReference&&) = default;
    WeaponReference& operator=(WeaponReference&&) = default;

    void weaponModel(Weapon__Model model) noexcept              { model_ = model; }
    void weaponType(Weapon__Type type) noexcept                 { type_ = type; }
    void slotWeaponModTypes(Slot_WeaponModTypes types) noexcept { weaponModTypes_ = types; }

    void name(common::Text text) noexcept                       { name_ = text; }
    void description(common::Text text) noexcept                { descrip_ = text; }
    void damageMinimum(common::Damage dmg) noexcept             { dmgMin_ = dmg; }
    void damageMaximum(common::Damage dmg) noexcept             { dmgMax_ = dmg; }
    void price(common::Price price) noexcept                    { price_ = price; }
    void rangeAttack(common::Range range) noexcept              { rangeAttack_ = range; }
    void capacityAmmo(common::Capacity capacity) noexcept       { capAmmo_ = capacity; }
    void multiplierCritDamage(common::Multiplier mul) noexcept  { mulCritDmg_ = mul; }
    void chanceHit(common::Chance chance) noexcept              { chaHit_ = chance; }
    void chanceCritDamage(common::Chance chance) noexcept       { chaCritDmg_ = chance; }
    void level(common::Level level) noexcept                    { level_ = level; }
    void levelSkill(common::Level level) noexcept               { levSkill_ = level; }
    void armorPenetration(common::Armor ar) noexcept            { armorPen_ = ar; }
    void actionPointPerAttack(common::ActionPoint ap) noexcept  { apAttack_ = ap; }
    void actionPointPerReload(common::ActionPoint ap) noexcept  { apReload_ = ap; }
    void shotsPerAttack(common::NumberShots num) noexcept       { shoPerAttack_ = num; }
    void ammoType(Ammo::Type type) noexcept                     { tyAmmo_ = type; }
    void damageType(Damage::Type type) noexcept                 { tyDmg_ = type; }

    Weapon__Model           model_;         // weapon model
    Weapon__Type            type_;          // weapon type (kind)
    Slot_WeaponModTypes     weaponModTypes_;// list of slot types

    common::Text            name_;          // weapon name
    common::Text            descrip_;       // description
    common::Damage          dmgMin_;        // min damage per hit
    common::Damage          dmgMax_;        // max damage per hit
    common::Price           price_;         // price
    common::Range           rangeAttack_;   // attack range
    common::Capacity        capAmmo_;       // ammo capacity
    common::Multiplier      mulCritDmg_;    // critical damage multiplier
    common::Chance          chaHit_;        // base hit chance
    common::Chance          chaCritDmg_;    // base critical damage chance
    common::Level           level_;         // weapon level
    common::Level           levSkill_;      // min level of skill
    common::Armor           armorPen_;      // penetration
    common::ActionPoint     apAttack_;      // action points per attack
    common::ActionPoint     apReload_;      // action points per reload
    common::NumberShots     shoPerAttack_;  // number of shots per attack
    Ammo::Type              tyAmmo_;        // ammo type
    Damage::Type            tyDmg_;         // damage type
};

} // namespace object
} // namespace game

#endif // !WEAPON_REFERENCE_HPP
