
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_MAIN_HPP
#define MENU_MAIN_HPP

#include"character.hpp"
#include"common.hpp"
#include"inventory.hpp"
#include"menuCommon.hpp"
#include"squad.hpp"
#include<iostream>

namespace game {
namespace menu {

namespace actionMain {

enum ActionMain {
    MENU_OPTION = actionCommon::__NEXT_ACTION_NUMBER,
    MENU_SQUAD,
    MENU_INVENTORY,
    MENU_TRADE,

    __NEXT_ACTION_NUMBER
};

} // namespace actionMain

void menuMain(std::istream& is, std::ostream& os, object::Squad& squad, object::Inventory& shop);

namespace actionTrade {

enum ActionTrade {
    SHOW_ALL_ITEMS = actionCommon::__NEXT_ACTION_NUMBER,
    BUY_ITEM,
    SELL_ITEM,

    __NEXT_ACTION_NUMBER
};

} // namespace actionTrade

void menuTrade(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    object::Inventory& shop,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_MAIN_HPP
