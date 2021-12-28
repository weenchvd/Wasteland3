
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
        using ItemBaseType                  = short int;
        using Item__Model                   = ItemBaseType;

        enum class Item__Type : ItemBaseType {
            INVALID = -1,                   /// invalid, must be the first

            WEAPON,
            WEAPONMOD,
            ARMOR,
            ARMORMOD,
            AMMO,
            JUNK,

            NUMBER_OF                       /// must be the last
        };

    }
}

#endif // !ITEM_COMMON_HPP
