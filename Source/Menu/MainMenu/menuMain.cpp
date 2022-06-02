
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorFullDescr.hpp"
#include"menuAttribute.hpp"
#include"menuAttributeText.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuItemText.hpp"
#include"menuMain.hpp"
#include"menuMainText.hpp"
#include"menuOptions.hpp"
#include"menuOptionsText.hpp"
#include"menuSkill.hpp"
#include"menuSkillText.hpp"
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
    MenuAttributeText::initialize();
    MenuSkillText::initialize();
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
            os << c.name() << ", Level " << c.level() << " RANGER" << endl;
        }
        else {
            os << "(empty)" << endl;
        }
    }
}

void showStats(istream& is, ostream& os, const object::Character& character, const Indent indent)
{
    constexpr unsigned char statWidth{ 40 };
    constexpr auto sp{ sign::space };
    constexpr auto ph{ sign::dot };
    constexpr auto pc{ sign::percent };
    constexpr auto x { sign::x };
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& tCom{ character.characterText().common() };
    const auto& tSta{ character.characterText().stats() };
    ostringstream oss;

    os << ind0 << character.name() << endl;
    os << ind0 << tCom.level() << sp << character.level() << sp
        << character.characterText().type(character.type()) << endl;
    os << ind0 << tCom.stats() << endl;
    clearStream(oss) << character.constitutionCurrent() << '/' << character.constitutionMaximum();
    os << ind1 << fitInWidth(tSta.con(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.experience();
    os << ind1 << fitInWidth(tCom.xp(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.constitutionPerLevel();
    os << ind1 << fitInWidth(tSta.conPerLevel(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusHealing() << pc;
    os << ind1 << fitInWidth(tSta.healingBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.actionPointMaximum();
    os << ind1 << fitInWidth(tSta.actionPoints(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.chanceHit() << pc;
    os << ind1 << fitInWidth(tSta.hitChance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.chanceCritDamage() << pc;
    os << ind1 << fitInWidth(tSta.critChance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.multiplierCritDamage() << x;
    os << ind1 << fitInWidth(tSta.critDmg(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.armorPenetration();
    os << ind1 << fitInWidth(tSta.penetration(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusSneakAttackDamage() << pc;
    os << ind1 << fitInWidth(tSta.sneakAttackDmg(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.strikeRate() << pc;
    os << ind1 << fitInWidth(tSta.strikeRate(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.armor();
    os << ind1 << fitInWidth(tSta.armor(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.evasion() << pc;
    os << ind1 << fitInWidth(tSta.evasion(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceCritDamage() << pc;
    os << ind1 << fitInWidth(tSta.critResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceFireDamage() << pc;
    os << ind1 << fitInWidth(tSta.fireResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceColdDamage() << pc;
    os << ind1 << fitInWidth(tSta.coldResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceEnergyDamage() << pc;
    os << ind1 << fitInWidth(tSta.energyResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceExplosiveDamage() << pc;
    os << ind1 << fitInWidth(tSta.explosiveResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceStatusEffect() << pc;
    os << ind1 << fitInWidth(tSta.statusEffectResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << tCom.level() << sp << character.radiationResistance();
    os << ind1 << fitInWidth(tSta.radiationResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.downedTime();
    os << ind1 << fitInWidth(tSta.downedTime(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusMeleeDamage() << pc;
    os << ind1 << fitInWidth(tSta.meleeDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusRangedDamage() << pc;
    os << ind1 << fitInWidth(tSta.rangedDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusNormalDamage() << pc;
    os << ind1 << fitInWidth(tSta.normalDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusFireDamage() << pc;
    os << ind1 << fitInWidth(tSta.fireDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusColdDamage() << pc;
    os << ind1 << fitInWidth(tSta.coldDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusEnergyDamage() << pc;
    os << ind1 << fitInWidth(tSta.energyDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusExplosiveDamage() << pc;
    os << ind1 << fitInWidth(tSta.explosiveDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.perception();
    os << ind1 << fitInWidth(tSta.perception(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.multiplierThrowingRange() << x;
    os << ind1 << fitInWidth(tSta.throwingRange(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.initiative() << pc;
    os << ind1 << fitInWidth(tSta.initiative(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.timeDetection() << sp << tCom.sec();
    os << ind1 << fitInWidth(tSta.detectionTime(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.multiplierCombatSpeed() << x;
    os << ind1 << fitInWidth(tSta.combatSpeed(), oss.str(), statWidth, ph) << endl;
    //clearStream(oss) << character.();
    //os << ind1 << fitInWidth(tSta.quickSlots(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.rangeLeadership() << sp << tCom.m_meter();
    os << ind1 << fitInWidth(tSta.leadershipRange(), oss.str(), statWidth, ph) << endl;
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
