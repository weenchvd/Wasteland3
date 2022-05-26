
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ITEM_MODIFY_HPP
#define MENU_ITEM_MODIFY_HPP

#include"common.hpp"
#include"menuCommon.hpp"
#include"squad.hpp"
#include<memory>

namespace game {
namespace menu {

namespace actionItemModify {

enum ActionItemModify {
    SHOW_FULL_DESCR = actionCommon::__NEXT_ACTION_NUMBER,
    INSTALL_MOD,
    REMOVE_MOD,

    __NEXT_ACTION_NUMBER
};

} // namespace actionItemModify

void menuItemModify(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    object::InventoryIterator& iterItem,
    const Indent indent
);

int contextSensitiveMenuItemModify(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    object::Item& item,
    int nextActionNumber,
    const Indent indent
);

void contextSensitiveMenuItemModify_Install(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    object::InventoryIterator& iterItem,
    const Indent indent
);

void contextSensitiveMenuItemModify_Remove(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    object::InventoryIterator& iterItem,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_ITEM_MODIFY_HPP
