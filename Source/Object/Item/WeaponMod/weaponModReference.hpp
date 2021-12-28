
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_REFERENCE_HPP
#define WEAPON_MOD_REFERENCE_HPP

#include"common.hpp"
#include"item.hpp"
#include"ammo.hpp"
#include"damage.hpp"
#include"weaponModCommon.hpp"

namespace Game
{
    namespace Object
    {
        struct WeaponModReference {
            explicit WeaponModReference() noexcept
                :
                model_          { WeaponMod__Model::INVALID },
                type_           { WeaponMod__Type::INVALID },
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

            WeaponModReference(const WeaponModReference&) = delete;
            WeaponModReference& operator=(const WeaponModReference&) = delete;
            WeaponModReference(WeaponModReference&&) = default;
            WeaponModReference& operator=(WeaponModReference&&) = default;
            
            void weaponModModel(WeaponMod__Model model) noexcept        { model_ = model; }
            void weaponModType(WeaponMod__Type type) noexcept           { type_ = type; }

            void name(Common::Text text) noexcept                       { name_ = text; }
            void description(Common::Text text) noexcept                { descrip_ = text; }
            void damageMinimum(Common::Damage dmg) noexcept             { dmgMin_ = dmg; }
            void damageMaximum(Common::Damage dmg) noexcept             { dmgMax_ = dmg; }
            void price(Common::Price price) noexcept                    { price_ = price; }
            void rangeAttack(Common::Range range) noexcept              { rangeAttack_ = range; }
            void capacityAmmo(Common::Capacity capacity) noexcept       { capAmmo_ = capacity; }
            void multiplierCritDamage(Common::Multiplier mul) noexcept  { mulCritDmg_ = mul; }
            void chanceHit(Common::Chance chance) noexcept              { chaHit_ = chance; }
            void chanceCritDamage(Common::Chance chance) noexcept       { chaCritDmg_ = chance; }
            void level(Common::Level level) noexcept                    { level_ = level; }
            void levelSkill(Common::Level level) noexcept               { levSkill_ = level; }
            void armorPenetration(Common::Armor ar) noexcept            { armorPen_ = ar; }
            void actionPointPerAttack(Common::ActionPoint ap) noexcept  { apAttack_ = ap; }
            void actionPointPerReload(Common::ActionPoint ap) noexcept  { apReload_ = ap; }
            void shotsPerAttack(Common::NumberShots num) noexcept       { shoPerAttack_ = num; }
            void ammoType(Ammo::Type type) noexcept                     { tyAmmo_ = type; }
            void damageType(Damage::Type type) noexcept                 { tyDmg_ = type; }

            WeaponMod__Model        model_;         // weapon mod model
            WeaponMod__Type         type_;          // weapon mod type (kind)

            Common::Text            name_;          // weapon mod name
            Common::Text            descrip_;       // description
            Common::Damage          dmgMin_;        // min damage per hit
            Common::Damage          dmgMax_;        // max damage per hit
            Common::Price           price_;         // price
            Common::Range           rangeAttack_;   // attack range
            Common::Capacity        capAmmo_;       // ammo capacity
            Common::Multiplier      mulCritDmg_;    // critical damage multiplier
            Common::Chance          chaHit_;        // base hit chance
            Common::Chance          chaCritDmg_;    // base critical damage chance
            Common::Level           level_;         // weapon mod level
            Common::Level           levSkill_;      // min level of skill
            Common::Armor           armorPen_;      // penetration
            Common::ActionPoint     apAttack_;      // action points per attack
            Common::ActionPoint     apReload_;      // action points per reload
            Common::NumberShots     shoPerAttack_;  // number of shots per attack
            Ammo::Type              tyAmmo_;        // ammo type
            Damage::Type            tyDmg_;         // damage type
        };

    }
}

#endif // !WEAPON_MOD_REFERENCE_HPP
