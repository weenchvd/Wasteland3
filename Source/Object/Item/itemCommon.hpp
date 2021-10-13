
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

        enum class ItemType : CommonItemBase {
            Weapon, // TODO UPPERCASE
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
