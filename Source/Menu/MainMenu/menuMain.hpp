
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

namespace Game {
namespace Menu {

namespace ActionMain {

enum ActionMain {
    MENU_OPTION = ActionCommon::NEXT,
    MENU_SQUAD,
    MENU_INVENTORY,
    MENU_SHOP,
    MENU_TRADE
};

} // namespace ActionMain

void menuMain(Object::Squad& squad, Object::Inventory& shop);

namespace ActionTrade {

enum ActionTrade {
    BUY_ITEM = ActionCommon::NEXT,
    SELL_ITEM
};

} // namespace ActionTrade

void menuTrade(Object::Squad& squad, Object::Inventory& shop, const Indent indent);

namespace ActionShop {

enum ActionShop {
    ALL_ITEMS = ActionCommon::NEXT
};

} // namespace ActionShop

void menuShop(Object::Inventory& shop, const Indent indent);

namespace ActionInventory {

enum ActionInventory {
    MONEY = ActionCommon::NEXT,
    ALL_ITEMS
};

} // namespace ActionInventory

void menuInventory(Object::Squad& squad, const Indent indent);

namespace ActionSquad {

enum ActionSquad {
    SHOW_SQUAD = ActionCommon::NEXT,
    MENU_CHARACTER
};

} // namespace ActionSquad

void menuSquad(Object::Squad& squad, const Indent indent);

namespace ActionCharacter {

enum ActionCharacter {
    SHOW_STATS = ActionCommon::NEXT,
    SHOW_GEAR,
    SHOW_ATTRIBUTES,
    MENU_ATTRIBUTE,
    SHOW_SKILLS,
    MENU_SKILL
};

} // namespace ActionCharacter

void menuCharacter(Object::Character& character, const Indent indent);

///------------------------------------------------------------------------------------------------

Common::Text itemName(const std::unique_ptr<Object::Item>& item);

void showAll(Object::Inventory& inventory, const Indent indent, bool squad = true);

Object::Character* pickCharacter(Object::Squad& squad, const Indent indent);

void showSquad(const Object::Squad& squad, const Indent indent);

void showStats(const Object::Character& character, const Indent indent);

void showGear(const Object::Character& character, const Indent indent);

} // namespace Menu
} // namespace Game

#endif // !MENU_MAIN_HPP
