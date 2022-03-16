
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include"common.hpp"
#include"menuCommon.hpp"
#include"squad.hpp"
#include<memory>

namespace game {
namespace menu {

namespace actionItem {

enum ActionItem {
    SHOW_FULL_DESCR = actionCommon::__NEXT_ACTION_NUMBER,
    REMOVE,

    __NEXT_ACTION_NUMBER
};

} // namespace actionItem

void menuItem_Inventory(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    std::list<std::unique_ptr<object::Item>>::const_iterator item,
    const Indent indent
);

namespace actionItemWeapon {

enum ActionItemWeapon {
    EQUIP = actionItem::__NEXT_ACTION_NUMBER,
    MODIFY
};

} // namespace actionItemWeapon

int contextSensitiveMenuItem_Inventory(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    std::list<std::unique_ptr<object::Item>>::const_iterator item,
    const Indent indent
);

///************************************************************************************************

void printFullDescription(
    std::istream& is,
    std::ostream& os,
    const std::unique_ptr<object::Item>& item,
    const Indent indent
);

bool removeItem(
    std::istream& is,
    std::ostream& os,
    object::Inventory& inventory,
    std::list<std::unique_ptr<object::Item>>::const_iterator item,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_ITEM_HPP
