
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
#include<memory>

namespace game {
namespace menu {

namespace actionMain {

enum ActionMain {
    MENU_OPTION = actionCommon::__NEXT_ACTION_NUMBER,
    MENU_SQUAD,
    MENU_INVENTORY,
    MENU_TRADE,
    SAVE_GAME,
    LOAD_GAME,

    __NEXT_ACTION_NUMBER
};

} // namespace actionMain

void menuMain(
    std::istream& is,
    std::ostream& os,
    std::unique_ptr<object::Squad>& _squad,
    std::unique_ptr<object::Inventory>& _shop
);

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

///************************************************************************************************

constexpr auto fileStemRule {  "[A-Za-z0-9-_]+" };
constexpr auto fileStemRuleW{ L"[A-Za-z0-9-_]+" };

void saveGame(
    std::istream& is,
    std::ostream& os,
    std::unique_ptr<object::Squad>& squad,
    std::unique_ptr<object::Inventory>& shop,
    const Indent indent
) noexcept;

void loadGame(
    std::istream& is,
    std::ostream& os,
    std::unique_ptr<object::Squad>& squad,
    std::unique_ptr<object::Inventory>& shop,
    const Indent indent
) noexcept;

} // namespace menu
} // namespace game

#endif // !MENU_MAIN_HPP
