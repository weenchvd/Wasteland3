
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorFullDescr.hpp"
#include"menuAttribute.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuMain.hpp"
#include"menuMainText.hpp"
#include"menuOption.hpp"
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
    MenuInventoryText::initialize();
}

///************************************************************************************************

void menuMain(object::Squad& squad, object::Inventory& shop)
{
    initializeMenu();

    Indent ind1 = Indent{};
    Indent ind2 = ind1 + Indent{};
    const auto& cText{ MenuCommonText::common() };
    const auto& mText{ MenuMainText::common() };

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << mText.menuName() << endl;
        cout << ind1 << cText.actions() << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' " << mText.exit() << endl;
        cout << ind2 << '\'' << actionMain::MENU_OPTION << "\' " << mText.enterOptions() << endl;
        cout << ind2 << '\'' << actionMain::MENU_SQUAD << "\' " << mText.enterSquad() << endl;
        cout << ind2 << '\'' << actionMain::MENU_INVENTORY << "\' " << mText.enterInventory() << endl;
        cout << ind2 << '\'' << actionMain::MENU_SHOP << "\' " << mText.enterShop() << endl;
        cout << ind2 << '\'' << actionMain::MENU_TRADE << "\' " << mText.enterTrade() << endl;

        switch (getAction()) {
        case actionMain::MENU_OPTION:
            menuOption(ind1);
            break;
        case actionMain::MENU_SQUAD:
            menuSquad(squad, ind1);
            break;
        case actionMain::MENU_INVENTORY:
            menuInventory(squad, ind1);
            break;
        case actionMain::MENU_SHOP:
            menuShop(shop, ind1);
            break;
        case actionMain::MENU_TRADE:
            menuTrade(squad, shop, ind1);
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << cText.errorSymbol() << cText.invalidInput() << endl;
            break;
        default:
            cout << cText.errorSymbol() << cText.unknownAction() << endl;
            break;
        }
    }
}

void menuTrade(object::Squad& squad, object::Inventory& shop, const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Trade menu" << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionTrade::BUY_ITEM << "\' Buy items" << endl;
        cout << ind2 << '\'' << actionTrade::SELL_ITEM << "\' Sell items" << endl;

        switch (getAction()) {
        case actionTrade::BUY_ITEM:
            showAllItems(shop, ind1, false);

            break;
        case actionTrade::SELL_ITEM:
            showAllItems(squad.inventory(), ind1);

            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

void menuShop(object::Inventory& shop, const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Shop menu" << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionShop::ALL_ITEMS << "\' Show all items" << endl;

        switch (getAction()) {
        case actionShop::ALL_ITEMS:
            showAllItems(shop, ind1, false);
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

void menuSquad(object::Squad& squad, const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Squad menu" << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionSquad::SHOW_SQUAD << "\' Show squad members" << endl;
        cout << ind2 << '\'' << actionSquad::MENU_CHARACTER << "\' Enter the character menu" << endl;

        switch (getAction()) {
        case actionSquad::SHOW_SQUAD:
            showSquad(squad, ind1);
            break;
        case actionSquad::MENU_CHARACTER: {
            object::Character* c{ pickCharacter(squad, ind1) };
            if (c != nullptr) {
                menuCharacter(*c, ind1);
            }
            else {
                cout << "!Character not selected" << endl;
            }
            break;
        }
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

void menuCharacter(object::Character& character, const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Character menu (" << character.name() << ")" << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionCharacter::SHOW_STATS << "\' Show stats" << endl;
        cout << ind2 << '\'' << actionCharacter::SHOW_GEAR << "\' Show gear" << endl;
        cout << ind2 << '\'' << actionCharacter::SHOW_ATTRIBUTES << "\' Show attributes" << endl;
        cout << ind2 << '\'' << actionCharacter::MENU_ATTRIBUTE << "\' Enter the attribute menu" << endl;
        cout << ind2 << '\'' << actionCharacter::SHOW_SKILLS << "\' Show skills" << endl;
        cout << ind2 << '\'' << actionCharacter::MENU_SKILL << "\' Enter the skill menu" << endl;

        switch (getAction()) {
        case actionCharacter::SHOW_STATS:
            showStats(character, ind1);
            break;
        case actionCharacter::SHOW_GEAR:
            showGear(character, ind1);
            break;
        case actionCharacter::SHOW_ATTRIBUTES:
            showAllAttributes(character, ind1);
            break;
        case actionCharacter::MENU_ATTRIBUTE:
            menuAttribute(character, ind1);
            break;
        case actionCharacter::SHOW_SKILLS:
            showAllSkills(character, ind1);
            break;
        case actionCharacter::MENU_SKILL:
            menuSkill(character, ind1);
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

///************************************************************************************************

object::Character* pickCharacter(object::Squad& squad, const Indent indent)
{
    Indent ind = indent + Indent{};

    cout << ind << "Select a character:" << endl;
    object::Character* c{ nullptr };
    int n = getPosNumber() - 1;
    if (n >= 0 && n < squad.members().size()) {
        c = static_cast<object::Character*>(squad.members()[n].get());
    }
    return c;
}

void showSquad(const object::Squad& squad, const Indent indent)
{
    Indent ind = indent + Indent{};
    cout << ind << "Squad:" << endl;
    Indent ind2 = ind + Indent{};
    for (int i = 0; i < squad.members().size(); ++i) {
        cout << ind2 << "Member " << i + 1 << ": ";
        if (squad.members()[i] != nullptr) {
            auto& c = *static_cast<object::Character*>(squad.members()[i].get());
            cout << c.name() << ", Level " << integer(c.level()) << " RANGER" << endl;
        }
        else {
            cout << "(empty)" << endl;
        }
    }
}

void showStats(const object::Character& character, const Indent indent)
{
    Indent ind = indent + Indent{};
    Indent in2 = ind + Indent{};
    cout << ind                         << character.name() << endl;
    cout << ind << "Level "             << integer(character.level()) << " RANGER" << endl;
    cout << ind << "Stats:" << endl;
    cout << in2 << "CON "               << character.constitutionCurrent() << '\\'
                                        << character.constitutionMaximum() << endl;
    cout << in2 << "XP "                << character.experience() << endl;
    cout << in2 << "CON per level: "    << character.constitutionPerLevel() << endl;
    cout << in2 << "Healing bonus: "    << percentBonus(character.bonusHealing()) << '%' << endl;
    cout << in2 << "Action points: "    << integer(character.actionPointMaximum()) << endl;
    cout << in2 << "Hit chance: "       << percentChance(character.chanceHit()) << '%' << endl;
    cout << in2 << "Critical chance: "  << percentChance(character.chanceCritDamage()) << '%' << endl;
    cout << in2 << "Critical damage: "  << multiplier(character.multiplierCritDamage()) << 'X' << endl;
    cout << in2 << "Penetration: "      << integer(character.armorPenetration()) << endl;
    cout << in2 << "Sneak attack damage: "
                                        << percentBonus(character.bonusSneakAttackDamage()) << '%' << endl;
    cout << in2 << "Strike rate: "      << percentStrike(character.strikeRate()) << '%' << endl;
    cout << in2 << "Armor: "            << integer(character.armor()) << endl;
    cout << in2 << "Evasion: "          << percentEvasion(character.evasion()) << '%' << endl;
    cout << in2 << "Crit resistance: "  << percentResistance(character.resistanceCritDamage()) << '%' << endl;
    cout << in2 << "Fire resistance: "  << percentResistance(character.resistanceFireDamage()) << '%' << endl;
    cout << in2 << "Cold resistance: "  << percentResistance(character.resistanceColdDamage()) << '%' << endl;
    cout << in2 << "Energy resistance: "
                                        << percentResistance(character.resistanceEnergyDamage()) << '%' << endl;
    cout << in2 << "Explosive resistance: "
                                        << percentResistance(character.resistanceExplosiveDamage()) << '%' << endl;
    cout << in2 << "Status effect resistance: "
                                        << percentResistance(character.resistanceStatusEffect()) << '%' << endl;
    cout << in2 << "Radiation resistance: Level "
                                        << integer(character.radiationResistance()) << endl;
    cout << in2 << "Downed time: "      << integer(character.downedTime()) << endl;
    cout << in2 << "Melee damage bonus: "
                                        << percentBonus(character.bonusMeleeDamage()) << '%' << endl;
    cout << in2 << "Ranged damage bonus: "
                                        << percentBonus(character.bonusRangedDamage()) << '%' << endl;
    cout << in2 << "Normal damage bonus: "
                                        << percentBonus(character.bonusNormalDamage()) << '%' << endl;
    cout << in2 << "Fire damage bonus: "
                                        << percentBonus(character.bonusFireDamage()) << '%' << endl;
    cout << in2 << "Cold damage bonus: "
                                        << percentBonus(character.bonusColdDamage()) << '%' << endl;
    cout << in2 << "Energy damage bonus: "
                                        << percentBonus(character.bonusEnergyDamage()) << '%' << endl;
    cout << in2 << "Explosive damage bonus: "
                                        << percentBonus(character.bonusExplosiveDamage()) << '%' << endl;
    cout << in2 << "Perception: "       << integer(character.perception()) << endl;
    cout << in2 << "Throwing range: "   << multiplier(character.multiplierThrowingRange()) << 'X' << endl;
    cout << in2 << "Initiative: "       << percentInitiative(character.initiative()) << '%' << endl;
    cout << in2 << "Detection time: "   << secondTime(character.timeDetection()) << " seconds" << endl;
    cout << in2 << "Combat speed: "     << multiplier(character.multiplierCombatSpeed()) << 'X' << endl;
    //TODO cout << in2 << "Quick slots: " << character.
    cout << in2 << "Leadership range: " << character.rangeLeadership() << 'M' << endl;
}

void showGear(const object::Character& character, const Indent indent)
{
    Indent ind1 = indent + Indent{};
    cout << ind1 << "Gear:" << endl;
    Indent ind2 = ind1 + Indent{};

    const auto& weapons = character.slotWeapon();
    for (int i = 0; i < weapons.size(); ++i) {
        cout << ind2 << "Weapon " << i + 1 << ": ";
        if (weapons[i] != nullptr) {
            cout << weapons[i]->name();
        }
        else {
            cout << "(empty)";
        }
        cout << endl;
    }
    // TODO armor
    // TODO ...
}

} // namespace menu
} // namespace game
