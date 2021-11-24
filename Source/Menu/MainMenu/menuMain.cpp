
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuAttribute.hpp"
#include"menuMain.hpp"
#include"menuSkill.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace Game
{
    namespace Menu
    {
        using namespace std;


        void menuMain(Object::Squad& squad, Object::Inventory& shop)
        {
            Indent ind = Indent{};
            Indent ind2 = ind + Indent{};

            while (true)
            {
                cout << endl << endl;
                cout << ind << "Main menu" << endl;
                cout << ind << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionMain::MENU_SQUAD << "\' Enter the squad menu" << endl;
                cout << ind2 << '\'' << ActionMain::MENU_INVENTORY << "\' Enter the inventory menu" << endl;

                switch (getAction()) {
                case ActionMain::MENU_SQUAD:
                    menuSquad(squad, ind);
                    break;
                case ActionMain::MENU_INVENTORY:
                    menuInventory(squad, ind);
                    break;
                case ActionCommon::EXIT:
                    return;
                case ActionCommon::INVALID:
                    cout << "!Invalid action" << endl;
                    break;
                default:
                    cout << "!Unknown action" << endl;
                    break;
                }
            }
        }

        void menuInventory(Object::Squad& squad, const Indent indent)
        {
            Indent ind = indent + Indent{};
            Indent ind2 = ind + Indent{};

            while (true)
            {
                cout << endl << endl;
                cout << ind << "Inventory menu" << endl;
                cout << ind << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionInventory::MONEY << "\' Show money" << endl;
                cout << ind2 << '\'' << ActionInventory::ALL_ITEMS << "\' Show all items" << endl;

                switch (getAction()) {
                case ActionInventory::MONEY:
                    cout << ind2 << "Money: $" << squad.money() << endl;
                    break;
                case ActionInventory::ALL_ITEMS:
                    showAll(squad.inventory(), ind);
                    break;
                case ActionCommon::EXIT:
                    return;
                case ActionCommon::INVALID:
                    cout << "!Invalid action" << endl;
                    break;
                default:
                    cout << "!Unknown action" << endl;
                    break;
                }
            }
        }

        void menuSquad(Object::Squad& squad, const Indent indent)
        {
            Indent ind = indent + Indent{};
            Indent ind2 = ind + Indent{};

            while (true)
            {
                cout << endl << endl;
                cout << ind << "Squad menu" << endl;
                cout << ind << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionSquad::SHOW_SQUAD << "\' Show squad members" << endl;
                cout << ind2 << '\'' << ActionSquad::MENU_CHARACTER << "\' Enter the character menu" << endl;

                switch (getAction()) {
                case ActionSquad::SHOW_SQUAD:
                    showSquad(squad, ind);
                    break;
                case ActionSquad::MENU_CHARACTER: {
                    Object::Character* c{ pickCharacter(squad, ind) };
                    if (c != nullptr) {
                        menuCharacter(*c, ind);
                    }
                    else {
                        cout << "!Character not selected" << endl;
                    }
                    break;
                }
                case ActionCommon::EXIT:
                    return;
                case ActionCommon::INVALID:
                    cout << "!Invalid action" << endl;
                    break;
                default:
                    cout << "!Unknown action" << endl;
                    break;
                }
            }
        }

        void menuCharacter(Object::Character& character, const Indent indent)
        {
            Indent ind = indent + Indent{};
            Indent ind2 = ind + Indent{};

            while (true)
            {
                cout << endl << endl;
                cout << ind << "Character menu (" << character.name() << ")" << endl;
                cout << ind << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionCharacter::SHOW_STATS << "\' Show stats" << endl;
                cout << ind2 << '\'' << ActionCharacter::SHOW_GEAR << "\' Show gear" << endl;
                cout << ind2 << '\'' << ActionCharacter::SHOW_ATTRIBUTES << "\' Show attributes" << endl;
                cout << ind2 << '\'' << ActionCharacter::MENU_ATTRIBUTE << "\' Enter the attribute menu" << endl;
                cout << ind2 << '\'' << ActionCharacter::SHOW_SKILLS << "\' Show skills" << endl;
                cout << ind2 << '\'' << ActionCharacter::MENU_SKILL << "\' Enter the skill menu" << endl;

                switch (getAction()) {
                case ActionCharacter::SHOW_STATS:
                    showStats(character, ind);
                    break;
                case ActionCharacter::SHOW_GEAR:
                    showGear(character, ind);
                    break;
                case ActionCharacter::SHOW_ATTRIBUTES:
                    showAllAttributes(character, ind);
                    break;
                case ActionCharacter::MENU_ATTRIBUTE:
                    menuAttribute(character, ind);
                    break;
                case ActionCharacter::SHOW_SKILLS:
                    showAllSkills(character, ind);
                    break;
                case ActionCharacter::MENU_SKILL:
                    menuSkill(character, ind);
                    break;
                case ActionCommon::EXIT:
                    return;
                case ActionCommon::INVALID:
                    cout << "!Invalid action" << endl;
                    break;
                default:
                    cout << "!Unknown action" << endl;
                    break;
                }
            }
        }

        ///------------------------------------------------------------------------------------------------

        Common::Text itemName(const std::unique_ptr<Object::Item>& item)
        {
            Object::TypeItemVisitor vis;
            item->accept(vis);
            if (vis.isWeapon()) {
                auto& r = *static_cast<Object::Weapon*>(item.get());
                return r.name();
            }
            else if (vis.isWeaponMod()) {
                auto& r = *static_cast<Object::WeaponMod*>(item.get());
                return r.name();
            }
            return Common::Text{};
        }

        void showAll(Object::Inventory& inventory, const Indent indent)
        {
            Indent ind = indent + Indent{};
            cout << ind << "Inventory (* - new items):" << endl;
            Indent ind2 = ind + Indent{};
            Object::Inventory::Roster r = inventory.roster();
            int i = 0;
            for (auto iter = r.newItems.beg; iter != r.newItems.end; ++iter) {
                cout << ind2 << "Item " << ++i << ": " << '*' << itemName(*iter) << endl;
            }
            for (auto iter = r.oldItems.beg; iter != r.oldItems.end; ++iter) {
                cout << ind2 << "Item " << ++i << ": " << itemName(*iter) << endl;
            }
        }

        Object::Character* pickCharacter(Object::Squad& squad, const Indent indent)
        {
            Indent ind = indent + Indent{};

            cout << ind << "Select a character:" << endl;
            Object::Character* c{ nullptr };
            int n = getPosNumber() - 1;
            if (n >= 0 && n < squad.members().size()) {
                c = static_cast<Object::Character*>(squad.members()[n].get());
            }
            return c;
        }

        void showSquad(const Object::Squad& squad, const Indent indent)
        {
            Indent ind = indent + Indent{};
            cout << ind << "Squad:" << endl;
            Indent ind2 = ind + Indent{};
            for (int i = 0; i < squad.members().size(); ++i) {
                cout << ind2 << "Member " << i + 1 << ": ";
                if (squad.members()[i] != nullptr) {
                    auto& c = *static_cast<Object::Character*>(squad.members()[i].get());
                    cout << c.name() << ", Level " << integer(c.level()) << " RANGER" << endl;
                }
                else {
                    cout << "(empty)" << endl;
                }
            }
        }

        void showStats(const Object::Character& character, const Indent indent)
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
                                                << percentBonus(character.bonusExplisiveDamage()) << '%' << endl;
            cout << in2 << "Perception: "       << integer(character.perception()) << endl;
            cout << in2 << "Throwing range: "   << multiplier(character.multiplierThrowingRange()) << 'X' << endl;
            cout << in2 << "Initiative: "       << percentInitiative(character.initiative()) << '%' << endl;
            cout << in2 << "Detection time: "   << secondTime(character.timeDetection()) << " seconds" << endl;
            cout << in2 << "Combat speed: "     << multiplier(character.multiplierCombatSpeed()) << 'X' << endl;
            //TODO cout << in2 << "Quick slots: " << character.
            cout << in2 << "Leadership range: " << character.rangeLeadership() << 'M' << endl;
        }

        void showGear(const Object::Character& character, const Indent indent)
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

    }
}
