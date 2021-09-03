
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_COMMON_HPP
#define ITEM_COMMON_HPP

namespace Game
{
    namespace Object
    {
        using CommonItemBase                = unsigned short int;
        using ItemModel                     = CommonItemBase;

        using CritMultiplier                = double;
        using MinDamage                     = short int;
        using MaxDamage                     = short int;
        using HitChance                     = short int;
        using CritChance                    = short int;
        using Penetration                   = char;
        using AttackRange                   = char;
        using AttackNumber                  = char;
        using ActionPoints                  = char;
        using ActionPointsReload            = char;
        using SkillLevel                    = char;
        using AmmoCapacity                  = char;

        enum class ItemType : CommonItemBase {
            Weapon,
            WeaponMod,
            Armor,
            ArmorMod,
            Ammo,
            Junk
        };

        enum class DamageType : unsigned char {
            INVALID,                        /// invalid type, must be the first

            NORMAL,
            FIRE,
            COLD,
            ENERGY,
            EXPLOSIVE
        };

    }
}

#endif // !ITEM_COMMON_HPP
