
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

void initializeMenu();

///************************************************************************************************

namespace actionMain {

enum ActionMain {
    MENU_OPTION = actionCommon::__NEXT_ACTION_NUMBER,
    MENU_SQUAD,
    MENU_INVENTORY,
    MENU_SHOP,
    MENU_TRADE
};

} // namespace actionMain

void menuMain(std::istream& is, std::ostream& os, object::Squad& squad, object::Inventory& shop);

namespace actionTrade {

enum ActionTrade {
    BUY_ITEM = actionCommon::__NEXT_ACTION_NUMBER,
    SELL_ITEM
};

} // namespace actionTrade

void menuTrade(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    object::Inventory& shop,
    const Indent indent
);

namespace actionShop {

enum ActionShop {
    ALL_ITEMS = actionCommon::__NEXT_ACTION_NUMBER
};

} // namespace actionShop

void menuShop(std::istream& is, std::ostream& os, object::Inventory& shop, const Indent indent);

namespace actionSquad {

enum ActionSquad {
    SHOW_SQUAD = actionCommon::__NEXT_ACTION_NUMBER,
    MENU_CHARACTER
};

} // namespace actionSquad

void menuSquad(std::istream& is, std::ostream& os, object::Squad& squad, const Indent indent);

namespace actionCharacter {

enum ActionCharacter {
    SHOW_STATS = actionCommon::__NEXT_ACTION_NUMBER,
    SHOW_GEAR,
    SHOW_ATTRIBUTES,
    MENU_ATTRIBUTE,
    SHOW_SKILLS,
    MENU_SKILL
};

} // namespace actionCharacter

void menuCharacter(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    const Indent indent
);

///************************************************************************************************

object::Character* pickCharacter(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    const Indent indent
);

void showSquad(
    std::istream& is,
    std::ostream& os,
    const object::Squad& squad,
    const Indent indent
);

void showStats(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent
);

void showGear(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_MAIN_HPP
