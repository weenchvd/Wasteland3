
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_COMMON_HPP
#define ITEM_COMMON_HPP

namespace game {
namespace object {

using ItemBaseType                  = short int;
using Item__Model                   = ItemBaseType;

enum class Item__Type : ItemBaseType {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    WEAPON,
    ///ARMOR,
    WEAPON_MOD,
    ///ARMOR_MOD,
    AMMO,
    ///JUNK,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

} // namespace object
} // namespace game

#endif // !ITEM_COMMON_HPP
