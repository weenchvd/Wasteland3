
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorFullDescr.hpp"
#include"menuAttribute.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuItemText.hpp"
#include"menuMain.hpp"
#include"menuMainText.hpp"
#include"menuOptions.hpp"
#include"menuOptionsText.hpp"
#include"menuSkill.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace game {
namespace menu {

using namespace std;

void initializeMenu()
{
    MenuCommonText::initialize();
    MenuMainText::initialize();
    MenuOptionsText::initialize();
    MenuInventoryText::initialize();
    MenuItemText::initialize();
}

///************************************************************************************************

void menuMain(istream& is, ostream& os, object::Squad& squad, object::Inventory& shop)
{
    initializeMenu();

    Indent ind0{ Indent{} };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, text.exit()) << endl;
        printNumBar(os, ind1, actionMain::MENU_OPTION, text.enterOptions()) << endl;
        printNumBar(os, ind1, actionMain::MENU_SQUAD, text.enterSquad()) << endl;
        printNumBar(os, ind1, actionMain::MENU_INVENTORY, text.enterInventory()) << endl;
        printNumBar(os, ind1, actionMain::MENU_SHOP, text.enterShop()) << endl;
        printNumBar(os, ind1, actionMain::MENU_TRADE, text.enterTrade()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionMain::MENU_OPTION:
            menuOptions(is, os, ind1);
            break;
        case actionMain::MENU_SQUAD:
            menuSquad(is, os, squad, ind1);
            break;
        case actionMain::MENU_INVENTORY:
            menuInventory(is, os, squad, ind1);
            break;
        case actionMain::MENU_SHOP:
            menuShop(is, os, shop, ind1);
            break;
        case actionMain::MENU_TRADE:
            menuTrade(is, os, squad, shop, ind1);
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void menuTrade(
    istream& is,
    ostream& os,
    object::Squad& squad,
    object::Inventory& shop,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Trade menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionTrade::BUY_ITEM, "Buy items") << endl;
        printNumBar(os, ind1, actionTrade::SELL_ITEM, "Sell items") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionTrade::BUY_ITEM:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionTrade::SELL_ITEM:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void menuShop(istream& is, ostream& os, object::Inventory& shop, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Shop menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionShop::ALL_ITEMS, "Show all items") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionShop::ALL_ITEMS:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void menuSquad(istream& is, ostream& os, object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Squad menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionSquad::SHOW_SQUAD, "Show squad members") << endl;
        printNumBar(os, ind1, actionSquad::MENU_CHARACTER, "Enter the character menu") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionSquad::SHOW_SQUAD:
            showSquad(is, os, squad, ind1);
            break;
        case actionSquad::MENU_CHARACTER: {
            object::Character* c{ pickCharacter(is, os, squad, ind1) };
            if (c != nullptr) {
                menuCharacter(is, os, *c, ind1);
            }
            else {
                os << "!Character not selected" << endl;
            }
            break;
        }
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void menuCharacter(istream& is, ostream& os, object::Character& character, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Character menu (" << character.name() << ")" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_STATS, "Show stats") << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_GEAR, "Show gear") << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_ATTRIBUTES, "Show attributes") << endl;
        printNumBar(os, ind1, actionCharacter::MENU_ATTRIBUTE, "Enter the attribute menu") << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_SKILLS, "Show skills") << endl;
        printNumBar(os, ind1, actionCharacter::MENU_SKILL, "Enter the skill menu") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionCharacter::SHOW_STATS:
            showStats(is, os, character, ind1);
            break;
        case actionCharacter::SHOW_GEAR:
            showGear(is, os, character, ind1);
            break;
        case actionCharacter::SHOW_ATTRIBUTES:
            showAllAttributes(is, os, character, ind1);
            break;
        case actionCharacter::MENU_ATTRIBUTE:
            menuAttribute(is, os, character, ind1);
            break;
        case actionCharacter::SHOW_SKILLS:
            showAllSkills(is, os, character, ind1);
            break;
        case actionCharacter::MENU_SKILL:
            menuSkill(is, os, character, ind1);
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

///************************************************************************************************

object::Character* pickCharacter(istream& is, ostream& os, object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    const auto& comT{ MenuCommonText::common() };

    os << ind0 << "Select a character:" << endl;
    object::Character* c{ nullptr };

    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        pair.first -= 1;
        if (pair.first >= 0 && pair.first < squad.members().size()) {
            c = static_cast<object::Character*>(squad.members()[pair.first].get());
        }
        else {
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return c;
}

void showSquad(istream& is, ostream& os, const object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };

    os << ind0 << "Squad:" << endl;
    for (int i = 0; i < squad.members().size(); ++i) {
        os << ind1 << "Member " << i + 1 << ": ";
        if (squad.members()[i] != nullptr) {
            auto& c{ *static_cast<object::Character*>(squad.members()[i].get()) };
            os << c.name() << ", Level " << integer(c.level()) << " RANGER" << endl;
        }
        else {
            os << "(empty)" << endl;
        }
    }
}

void showStats(istream& is, ostream& os, const object::Character& character, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };

    os << ind0                         << character.name() << endl;
    os << ind0 << "Level "             << integer(character.level()) << " RANGER" << endl;
    os << ind0 << "Stats:" << endl;
    os << ind1 << "CON "               << character.constitutionCurrent() << '\\'
                                        << character.constitutionMaximum() << endl;
    os << ind1 << "XP "                << character.experience() << endl;
    os << ind1 << "CON per level: "    << character.constitutionPerLevel() << endl;
    os << ind1 << "Healing bonus: "    << percentBonus(character.bonusHealing()) << '%' << endl;
    os << ind1 << "Action points: "    << integer(character.actionPointMaximum()) << endl;
    os << ind1 << "Hit chance: "       << percentChance(character.chanceHit()) << '%' << endl;
    os << ind1 << "Critical chance: "  << percentChance(character.chanceCritDamage()) << '%' << endl;
    os << ind1 << "Critical damage: "  << multiplier(character.multiplierCritDamage()) << 'X' << endl;
    os << ind1 << "Penetration: "      << integer(character.armorPenetration()) << endl;
    os << ind1 << "Sneak attack damage: "
                                        << percentBonus(character.bonusSneakAttackDamage()) << '%' << endl;
    os << ind1 << "Strike rate: "      << percentStrike(character.strikeRate()) << '%' << endl;
    os << ind1 << "Armor: "            << integer(character.armor()) << endl;
    os << ind1 << "Evasion: "          << percentEvasion(character.evasion()) << '%' << endl;
    os << ind1 << "Crit resistance: "  << percentResistance(character.resistanceCritDamage()) << '%' << endl;
    os << ind1 << "Fire resistance: "  << percentResistance(character.resistanceFireDamage()) << '%' << endl;
    os << ind1 << "Cold resistance: "  << percentResistance(character.resistanceColdDamage()) << '%' << endl;
    os << ind1 << "Energy resistance: "
                                        << percentResistance(character.resistanceEnergyDamage()) << '%' << endl;
    os << ind1 << "Explosive resistance: "
                                        << percentResistance(character.resistanceExplosiveDamage()) << '%' << endl;
    os << ind1 << "Status effect resistance: "
                                        << percentResistance(character.resistanceStatusEffect()) << '%' << endl;
    os << ind1 << "Radiation resistance: Level "
                                        << integer(character.radiationResistance()) << endl;
    os << ind1 << "Downed time: "      << integer(character.downedTime()) << endl;
    os << ind1 << "Melee damage bonus: "
                                        << percentBonus(character.bonusMeleeDamage()) << '%' << endl;
    os << ind1 << "Ranged damage bonus: "
                                        << percentBonus(character.bonusRangedDamage()) << '%' << endl;
    os << ind1 << "Normal damage bonus: "
                                        << percentBonus(character.bonusNormalDamage()) << '%' << endl;
    os << ind1 << "Fire damage bonus: "
                                        << percentBonus(character.bonusFireDamage()) << '%' << endl;
    os << ind1 << "Cold damage bonus: "
                                        << percentBonus(character.bonusColdDamage()) << '%' << endl;
    os << ind1 << "Energy damage bonus: "
                                        << percentBonus(character.bonusEnergyDamage()) << '%' << endl;
    os << ind1 << "Explosive damage bonus: "
                                        << percentBonus(character.bonusExplosiveDamage()) << '%' << endl;
    os << ind1 << "Perception: "       << integer(character.perception()) << endl;
    os << ind1 << "Throwing range: "   << multiplier(character.multiplierThrowingRange()) << 'X' << endl;
    os << ind1 << "Initiative: "       << percentInitiative(character.initiative()) << '%' << endl;
    os << ind1 << "Detection time: "   << secondTime(character.timeDetection()) << " seconds" << endl;
    os << ind1 << "Combat speed: "     << multiplier(character.multiplierCombatSpeed()) << 'X' << endl;
    //TODO os << ind1 << "Quick slots: " << character.
    os << ind1 << "Leadership range: " << character.rangeLeadership() << 'M' << endl;
}

void showGear(istream& is, ostream& os, const object::Character& character, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };

    os << ind0 << "Gear:" << endl;
    const auto& weapons{ character.slotWeapon() };
    for (int i = 0; i < weapons.size(); ++i) {
        os << ind1 << "Weapon " << i + 1 << ": ";
        if (weapons[i] != nullptr) {
            os << weapons[i]->name();
        }
        else {
            os << "(empty)";
        }
        os << endl;
    }
    // TODO armor
    // TODO ...
}

} // namespace menu
} // namespace game
