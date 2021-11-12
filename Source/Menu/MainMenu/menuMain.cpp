
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuMain.hpp"
#include"attribute.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace Game
{
    namespace Menu
    {
        using namespace std;


        Indent operator+(const Indent& left, const Indent& right) {
            return Indent{ left.get() + right.get() };
        }

        ostream& operator<<(ostream& os, const Indent& indent) {
            for (unsigned int i = 0; i < indent.get(); ++i) {
                os.put(' ');
            }
            return os;
        }

        inline double secondTime(Common::Time time) {
            return static_cast<double>(time) / 1000;
        }

        inline double multiplier(Common::Multiplier mult) {
            return static_cast<double>(mult) / 100;
        }

        inline double percentChance(Common::Chance chance) {
            return static_cast<double>(chance) / 10;
        }

        inline double percentBonus(Common::Bonus bonus) {
            return static_cast<double>(bonus) / 10;
        }

        inline double percentEvasion(Common::Evasion evasion) {
            return static_cast<double>(evasion) / 10;
        }

        inline double percentResistance(Common::Resistance res) {
            return static_cast<double>(res) / 10;
        }

        inline double percentInitiative(Common::Initiative init) {
            return static_cast<double>(init) / 10;
        }

        inline double percentStrike(Common::Strike strike) {
            return static_cast<double>(strike) / 10;
        }

        inline int integer(char ch)
        {
            return static_cast<int>(ch);
        }

        int getAction()
        {
            cout << "> Enter an action: ";
            string input;
            getline(cin, input);
            try {
                return stoi(input);
            }
            catch (...) {
                return ActionCommon::INVALID;
            }
        }

        int getPosNumber()
        {
            cout << "> Enter a number: ";
            string input;
            getline(cin, input);
            int n;
            try {
                n = stoi(input);
            }
            catch (...) {
                return -1;
            }
            if (n < 0) {
                return -1;
            }
            return n;
        }

        YesNo getYesNo()
        {
            cout << "> 'Y' Yes | 'N' No: ";
            string input;
            getline(cin, input);
            if (input.size() != sizeof('Y')) {
                return YesNo::INVALID;
            }
            char ch = toupper(input[0]);
            if (ch == 'Y') {
                return YesNo::YES;
            }
            else if (ch == 'N') {
                return YesNo::NO;
            }
            else {
                return YesNo::INVALID;
            }
        }

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
                cout << ind2 << '\'' << ActionMain::MENUSQUAD << "\' Enter the squad menu" << endl;
                cout << ind2 << '\'' << ActionMain::MENUINVENTORY << "\' Enter the inventory menu" << endl;

                switch (getAction()) {
                case ActionMain::MENUSQUAD:
                    menuSquad(squad, ind);
                    break;
                case ActionMain::MENUINVENTORY:
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
                cout << ind2 << '\'' << ActionInventory::ALLITEMS << "\' Show all items" << endl;

                switch (getAction()) {
                case ActionInventory::MONEY:
                    cout << ind2 << "Money: $" << squad.money() << endl;
                    break;
                case ActionInventory::ALLITEMS:
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
                cout << ind2 << '\'' << ActionSquad::SHOWSQUAD << "\' Show squad members" << endl;
                cout << ind2 << '\'' << ActionSquad::MENUCHARACTER << "\' Enter the character menu" << endl;

                switch (getAction()) {
                case ActionSquad::SHOWSQUAD:
                    showSquad(squad, ind);
                    break;
                case ActionSquad::MENUCHARACTER: {
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
                cout << ind2 << '\'' << ActionCharacter::SHOWSTATS << "\' Show stats" << endl;
                cout << ind2 << '\'' << ActionCharacter::SHOWGEAR << "\' Show gear" << endl;
                cout << ind2 << '\'' << ActionCharacter::SHOWATTRIBUTES << "\' Show attributes" << endl;
                cout << ind2 << '\'' << ActionCharacter::MENUATTRIBUTE << "\' Enter the attribute menu" << endl;

                switch (getAction()) {
                case ActionCharacter::SHOWSTATS:
                    showStats(character, ind);
                    break;
                case ActionCharacter::SHOWGEAR:
                    showGear(character, ind);
                    break;
                case ActionCharacter::SHOWATTRIBUTES:
                    showAllAttributes(character, ind);
                    break;
                case ActionCharacter::MENUATTRIBUTE:
                    menuAttribute(character, ind);
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

        void menuAttribute(Object::Character& character, const Indent indent)
        {
            Indent ind1 = indent + Indent{};
            Indent ind2 = ind1 + Indent{};

            while (true)
            {
                cout << endl << endl;
                cout << ind1 << "Attribute menu (" << character.name() << ")" << endl;
                cout << ind1 << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionAttribute::SHOWALL << "\' Show attributes" << endl;
                cout << ind2 << '\'' << ActionAttribute::SHOWALLACC << "\' Show attributes (accepted)" << endl;
                cout << ind2 << '\'' << ActionAttribute::MODIFY << "\' Modify attribute" << endl;

                switch (getAction()) {
                case ActionAttribute::SHOWALL:
                    showAllAttributes(character, ind1);
                    break;
                case ActionAttribute::SHOWALLACC:
                    showAllAttributes(character, ind1, true);
                    break;
                case ActionAttribute::MODIFY: {
                    Object::Attribute::Type type{ pickAttribute(ind1) };
                    if (type != Object::Attribute::Type::INVALID) {
                        menuModifyAttribute(character, type, ind1);
                    }
                    else {
                        cout << "!Invalid type" << endl;
                    }
                    break;
                }
                case ActionCommon::EXIT:
                    if (character.attribute().isModified()) {
                        switch (getYesNo()) {
                        case YesNo::YES:
                            character.attribute().accept();
                            return;
                        case YesNo::NO:
                            character.attribute().reject();
                            return;
                        default:
                            cout << "!Invalid input" << endl;
                            break;
                        }
                    }
                    else {
                        return;
                    }
                    break;
                case ActionCommon::INVALID:
                    cout << "!Invalid action" << endl;
                    break;
                default:
                    cout << "!Unknown action" << endl;
                    break;
                }
            }
        }

        void menuModifyAttribute(Object::Character& character, Object::Attribute::Type type, const Indent indent)
        {
            Indent ind1 = indent + Indent{};
            Indent ind2 = ind1 + Indent{};

            while (true)
            {
                cout << endl << endl;
                showAttPoints(character, ind1);
                showAttribute(character, type, ind1);
                cout << ind1 << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionModifyAttribute::SHOWACC << "\' Show the accepted level" << endl;
                cout << ind2 << '\'' << ActionModifyAttribute::INCREASELEVEL << "\' Increase level" << endl;
                cout << ind2 << '\'' << ActionModifyAttribute::DECREASELEVEL << "\' Decrease level" << endl;

                switch (getAction()) {
                case ActionModifyAttribute::SHOWACC:
                    showAttribute(character, type, ind2, true);
                    break;
                case ActionModifyAttribute::INCREASELEVEL: {
                    int n = getPosNumber();
                    if (n >= 0 && n <= numeric_limits<Common::LevelStat>::max()) {
                        character.attribute().addLevel(type, n);
                    }
                    break;
                }
                case ActionModifyAttribute::DECREASELEVEL: {
                    int n = getPosNumber();
                    if (n >= 0 && n <= numeric_limits<Common::LevelStat>::max()) {
                        character.attribute().addLevel(type, -n);
                    }
                    break;
                }
                //case ActionAttribute::MODIFY: {
                //    Object::Attribute::Type type{ pickAttribute(ind1) };
                //    if (type != Object::Attribute::Type::INVALID) {
                //        menuModifyAttribute(character, type, ind1);
                //    }
                //    else {
                //        cout << "!Invalid type" << endl;
                //    }
                //    break;
                //}
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
            //cout << in2 << "Quick slots: " << character.
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

        Common::Text attLevel(const Common::SpecStorage<Common::LevelStat>& level, bool accepted)
        {
            Common::Text s;
            if (accepted) {
                for (Common::LevelStat i = level.getMinPossible() + 1; i <= level.getMaxPossible(); ++i) {
                    if (i <= level.getAccepted()) {
                        s += '+';
                    }
                    else {
                        s += '-';
                    }
                }
            }
            else {
                for (Common::LevelStat i = level.getMinPossible() + 1; i <= level.getMaxPossible(); ++i) {
                    if (i <= level.get()) {
                        s += '+';
                    }
                    else {
                        s += '-';
                    }
                }
            }
            return s;
        }

        void showAllAttributes(const Object::Character& character, const Indent indent, bool accepted)
        {
            Indent ind1 = indent + Indent{};
            showAttPoints(character, ind1, accepted);
            cout << ind1 << "Attributes";
            if (accepted) {
                cout << " (accepted)";
            }
            cout <<":" << endl;
            Indent ind2 = ind1 + Indent{};

            cout << ind2 << "COORDINATION   "
                << attLevel(character.attribute().level(Object::Attribute::Type::COORDINATION), accepted) << endl;
            cout << ind2 << "LUCK           "
                << attLevel(character.attribute().level(Object::Attribute::Type::LUCK), accepted) << endl;
            cout << ind2 << "AWARENESS      "
                << attLevel(character.attribute().level(Object::Attribute::Type::AWARENESS), accepted) << endl;
            cout << ind2 << "STRENGTH       "
                << attLevel(character.attribute().level(Object::Attribute::Type::STRENGTH), accepted) << endl;
            cout << ind2 << "SPEED          "
                << attLevel(character.attribute().level(Object::Attribute::Type::SPEED), accepted) << endl;
            cout << ind2 << "INTELLIGENCE   "
                << attLevel(character.attribute().level(Object::Attribute::Type::INTELLIGENCE), accepted) << endl;
            cout << ind2 << "CHARISMA       "
                << attLevel(character.attribute().level(Object::Attribute::Type::CHARISMA), accepted) << endl;
        }

        void showAttribute(Object::Character& character, Object::Attribute::Type type,
            const Indent indent, bool accepted)
        {
            cout << indent << "Attribute";
            if (accepted) {
                cout << " (accepted)";
            }
            cout << " \'";
            switch (type) {
            case Object::Attribute::Type::COORDINATION:
                cout << "COORDINATION\': "
                    << attLevel(character.attribute().level(Object::Attribute::Type::COORDINATION), accepted) << endl;
                break;
            case Object::Attribute::Type::LUCK:
                cout << "LUCK\': "
                    << attLevel(character.attribute().level(Object::Attribute::Type::LUCK), accepted) << endl;
                break;
            case Object::Attribute::Type::AWARENESS:
                cout << "AWARENESS\': "
                    << attLevel(character.attribute().level(Object::Attribute::Type::AWARENESS), accepted) << endl;
                break;
            case Object::Attribute::Type::STRENGTH:
                cout << "STRENGTH\': "
                    << attLevel(character.attribute().level(Object::Attribute::Type::STRENGTH), accepted) << endl;
                break;
            case Object::Attribute::Type::SPEED:
                cout << "SPEED\': "
                    << attLevel(character.attribute().level(Object::Attribute::Type::SPEED), accepted) << endl;
                break;
            case Object::Attribute::Type::INTELLIGENCE:
                cout << "INTELLIGENCE\': "
                    << attLevel(character.attribute().level(Object::Attribute::Type::INTELLIGENCE), accepted) << endl;
                break;
            case Object::Attribute::Type::CHARISMA:
                cout << "CHARISMA\': "
                    << attLevel(character.attribute().level(Object::Attribute::Type::CHARISMA), accepted) << endl;
                break;
            default:
                cout << "UNKNOWN\'" << endl;
                return;
            }
        }

        void showAttPoints(const Object::Character& character, const Indent indent, bool accepted)
        {
            cout << indent << "Attribute points";
            if (accepted) {
                cout << " (accepted): " << static_cast<int>(character.attribute().storage().getAccepted()) << endl;
            }
            else {
                cout << ": " << static_cast<int>(character.attribute().storage().get()) << endl;
            }
        }

        Object::Attribute::Type pickAttribute(const Indent indent)
        {
            Indent ind1 = indent + Indent{};
            cout << ind1 << "Attributes:" << endl;
            Indent ind2 = ind1 + Indent{};
            cout << ind2 << '\'' << static_cast<int>(Object::Attribute::Type::COORDINATION) << "\' COORDINATION" << endl;
            cout << ind2 << '\'' << static_cast<int>(Object::Attribute::Type::LUCK)         << "\' LUCK" << endl;
            cout << ind2 << '\'' << static_cast<int>(Object::Attribute::Type::AWARENESS)    << "\' AWARENESS" << endl;
            cout << ind2 << '\'' << static_cast<int>(Object::Attribute::Type::STRENGTH)     << "\' STRENGTH" << endl;
            cout << ind2 << '\'' << static_cast<int>(Object::Attribute::Type::SPEED)        << "\' SPEED" << endl;
            cout << ind2 << '\'' << static_cast<int>(Object::Attribute::Type::INTELLIGENCE) << "\' INTELLIGENCE" << endl;
            cout << ind2 << '\'' << static_cast<int>(Object::Attribute::Type::CHARISMA)     << "\' CHARISMA" << endl;

            cout << ind1 << "Select an attribute:" << endl;
            Object::Attribute::Type t{ Object::Attribute::Type::INVALID };
            int n = getPosNumber();
            if (n > static_cast<int>(Object::Attribute::Type::INVALID) &&
                n < static_cast<int>(Object::Attribute::Type::NUMBER_OF)) {
                t = static_cast<Object::Attribute::Type>(n);
            }
            return t;
        }




    }
}
