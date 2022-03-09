
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_INVENTORY_HPP
#define MENU_INVENTORY_HPP

#include"common.hpp"
#include"inventory.hpp"
#include"menuCommon.hpp"
#include"squad.hpp"
#include<utility>

namespace game {
namespace menu {

namespace itemNumber {

constexpr auto countFrom{ 1 };

} // namespace itemNumber

namespace actionInventory {

enum ActionInventory {
    MONEY = actionCommon::NEXT,
    SHOW_ITEMS,
    MENU_ITEM
};

} // namespace actionInventory

void menuInventory(object::Squad& squad, const Indent indent);

namespace actionShowItems {

enum ActionShowItems {
    SHOW_ALL_ITEMS = actionCommon::NEXT,
    SHOW_ITEMS_OF_TYPE,
};

} // namespace actionShowItems

std::pair<object::Roster, bool> subMenuShowItems(object::Inventory& inventory, const Indent indent);

///************************************************************************************************

void showItems(object::Roster& roster, const common::Text& title, const Indent indent);

void showRoster(object::Roster& roster, const Indent indent);

object::Item::Type pickItemType(const Indent indent);

std::pair<std::list<std::unique_ptr<object::Item>>::const_iterator, bool> pickItem(
    object::Roster& roster,
    const Indent indent
);

const common::Text& getItemTypeName(const object::Item::Type type);

} // namespace menu
} // namespace game

#endif // !MENU_INVENTORY_HPP
