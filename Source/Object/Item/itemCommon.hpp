
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
        using ItemBaseType                  = unsigned short int;
        using ItemModel                     = ItemBaseType;

        enum class ItemType : ItemBaseType {
            WEAPON,
            WEAPONMOD,
            ARMOR,
            ARMORMOD,
            AMMO,
            JUNK
        };

    }
}

#endif // !ITEM_COMMON_HPP
