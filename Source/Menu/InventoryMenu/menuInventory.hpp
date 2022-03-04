
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_INVENTORY_HPP
#define MENU_INVENTORY_HPP

#include"common.hpp"
#include"inventory.hpp"
#include"menuCommon.hpp"
#include"squad.hpp"

namespace game {
namespace menu {

namespace actionInventory {

enum ActionInventory {
    MONEY = actionCommon::NEXT,
    ALL_ITEMS,
    TYPE_ITEMS
};

} // namespace actionInventory

void menuInventory(object::Squad& squad, const Indent indent);

///************************************************************************************************

void printFullDescription(const std::unique_ptr<object::Item>& item, const Indent indent);

void showItems(
    object::Inventory& inventory,
    const object::Item::Type type,
    const Indent indent,
    const bool squad
);

void showAllItems(object::Inventory& inventory, const Indent indent, const bool squad = true);

void showItemsOfType(
    object::Inventory& inventory,
    const object::Item::Type type,
    const Indent indent,
    const bool squad = true
);

object::Item::Type pickItemType(const Indent indent);

const common::Text& getItemTypeName(const object::Item::Type type);

} // namespace menu
} // namespace game

#endif // !MENU_INVENTORY_HPP
