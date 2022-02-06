
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
    MENU_OPTION = actionCommon::NEXT,
    MENU_SQUAD,
    MENU_INVENTORY,
    MENU_SHOP,
    MENU_TRADE
};

} // namespace actionMain

void menuMain(object::Squad& squad, object::Inventory& shop);

namespace actionTrade {

enum ActionTrade {
    BUY_ITEM = actionCommon::NEXT,
    SELL_ITEM
};

} // namespace actionTrade

void menuTrade(object::Squad& squad, object::Inventory& shop, const Indent indent);

namespace actionShop {

enum ActionShop {
    ALL_ITEMS = actionCommon::NEXT
};

} // namespace actionShop

void menuShop(object::Inventory& shop, const Indent indent);

namespace actionInventory {

enum ActionInventory {
    MONEY = actionCommon::NEXT,
    ALL_ITEMS
};

} // namespace actionInventory

void menuInventory(object::Squad& squad, const Indent indent);

namespace actionSquad {

enum ActionSquad {
    SHOW_SQUAD = actionCommon::NEXT,
    MENU_CHARACTER
};

} // namespace actionSquad

void menuSquad(object::Squad& squad, const Indent indent);

namespace actionCharacter {

enum ActionCharacter {
    SHOW_STATS = actionCommon::NEXT,
    SHOW_GEAR,
    SHOW_ATTRIBUTES,
    MENU_ATTRIBUTE,
    SHOW_SKILLS,
    MENU_SKILL
};

} // namespace actionCharacter

void menuCharacter(object::Character& character, const Indent indent);

///------------------------------------------------------------------------------------------------

common::Text itemName(const std::unique_ptr<object::Item>& item);

void showAll(object::Inventory& inventory, const Indent indent, bool squad = true);

object::Character* pickCharacter(object::Squad& squad, const Indent indent);

void showSquad(const object::Squad& squad, const Indent indent);

void showStats(const object::Character& character, const Indent indent);

void showGear(const object::Character& character, const Indent indent);

} // namespace menu
} // namespace game

#endif // !MENU_MAIN_HPP
