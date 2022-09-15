
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

enum class Item__Type : char {
    __INVALID = -1,                 /// invalid, must be the first
    // vvv TYPES vvv
    WEAPON,
    ///ARMOR,
    WEAPON_MOD,
    ///ARMOR_MOD,
    AMMO,
    ///JUNK,
    // ^^^ TYPES ^^^
    __NUMBER_OF,
    __END                           /// must be the last
};

///************************************************************************************************

// @brief Check if the types are compatible.
// @param "id1" - must be a type;
// @param "id2" - must be a type;
bool isCompatible(Item__Type id1, Item__Type id2);

} // namespace object
} // namespace game

#endif // !ITEM_COMMON_HPP
