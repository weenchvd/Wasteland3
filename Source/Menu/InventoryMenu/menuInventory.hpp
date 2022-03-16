
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

namespace actionInventory {

enum ActionInventory {
    MONEY = actionCommon::__NEXT_ACTION_NUMBER,
    SHOW_ITEMS,
    MENU_ITEM
};

} // namespace actionInventory

void menuInventory(std::istream& is, std::ostream& os, object::Squad& squad, const Indent indent);

namespace actionShowItems {

enum ActionShowItems {
    SHOW_ALL_ITEMS = actionCommon::__NEXT_ACTION_NUMBER,
    SHOW_ITEMS_OF_TYPE,
};

} // namespace actionShowItems

std::pair<object::Roster, bool> subMenuShowItems(
    std::istream& is,
    std::ostream& os,
    object::Inventory& inventory,
    const Indent indent
);

///************************************************************************************************

namespace itemNumber {

constexpr auto countFrom{ 1 };

} // namespace itemNumber

void showItems(
    std::istream& is,
    std::ostream& os,
    object::Roster& roster,
    const common::Text& title,
    const Indent indent
);

void showRoster(std::istream& is, std::ostream& os, object::Roster& roster, const Indent indent);

object::Item::Type pickItemType(std::istream& is, std::ostream& os, const Indent indent);

std::pair<std::list<std::unique_ptr<object::Item>>::const_iterator, bool> pickItem(
    std::istream& is,
    std::ostream& os,
    object::Roster& roster,
    const Indent indent
);

const common::Text& getItemTypeName(const object::Item::Type type);

} // namespace menu
} // namespace game

#endif // !MENU_INVENTORY_HPP
