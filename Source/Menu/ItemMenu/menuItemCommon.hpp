
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ITEM_COMMON_HPP
#define MENU_ITEM_COMMON_HPP

#include"attack.hpp"
#include"common.hpp"
#include"damage.hpp"
#include"inventory.hpp"
#include"menuCommon.hpp"
#include"squad.hpp"
#include<iostream>

namespace game {
namespace menu {

namespace itemCounter {

constexpr auto countFrom{ 1 };

} // namespace itemCounter

common::Text getDamageDescription(
    const Indent indent,
    const object::Damage::Type type
);

void printAttackDescription(
    std::ostream& os,
    const Indent indent,
    const object::Attack& attack,
    const bool printAttackType = true
);

void printFullDescription(
    std::istream& is,
    std::ostream& os,
    const object::InventoryIterator& iterItem,
    const Indent indent
);

void printFullDescription(
    std::istream& is,
    std::ostream& os,
    const object::Item& item,
    const Indent indent
);

bool removeItem(
    std::istream& is,
    std::ostream& os,
    object::Inventory& inventory,
    object::InventoryIterator& iterItem,
    const Indent indent
);

void showSlotsAndMods(
    std::istream& is,
    std::ostream& os,
    const object::Item& item,
    const Indent indent
);

std::pair<int, bool> pickSlotNumber(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    const object::Item& item,
    const Indent indent
);

void showModsWithTypes(
    std::istream& is,
    std::ostream& os,
    const object::Roster& roster,
    const common::Text& title,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_ITEM_COMMON_HPP
