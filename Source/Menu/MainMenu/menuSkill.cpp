
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuSkill.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace Game
{
    namespace Menu
    {
        using namespace std;


        void menuSkill(Object::Character& character, const Indent indent)
        {
            Indent ind1 = indent + Indent{};
            Indent ind2 = ind1 + Indent{};

            while (true)
            {
                cout << endl << endl;
                cout << ind1 << "Skill menu (" << character.name() << ")" << endl;
                cout << ind1 << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionSkill::SHOW_ALL << "\' Show skills" << endl;
                cout << ind2 << '\'' << ActionSkill::SHOW_ALL_ACCEPTED << "\' Show skills (accepted)" << endl;
                cout << ind2 << '\'' << ActionSkill::MODIFY << "\' Modify skill" << endl;

                switch (getAction()) {
                case ActionSkill::SHOW_ALL:
                    showAllSkills(character, ind1);
                    break;
                case ActionSkill::SHOW_ALL_ACCEPTED:
                    showAllSkills(character, ind1, true);
                    break;
                case ActionSkill::MODIFY: {
                    Object::Skill::Type type{ pickSkill(ind1) };
                    if (type != Object::Skill::Type::INVALID) {
                        menuModifySkill(character, type, ind1);
                    }
                    else {
                        cout << "!Invalid type" << endl;
                    }
                    break;
                }
                case ActionCommon::EXIT:
                    if (character.skill().isModified()) {
                        switch (getYesNo()) {
                        case YesNo::YES:
                            character.skill().accept();
                            return;
                        case YesNo::NO:
                            character.skill().reject();
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

        void menuModifySkill(Object::Character& character, Object::Skill::Type type, const Indent indent)
        {
            Indent ind1 = indent + Indent{};
            Indent ind2 = ind1 + Indent{};

            while (true)
            {
                cout << endl << endl;
                showSkillPoints(character, ind1);
                showSkill(character, type, ind1);
                cout << ind1 << "Actions:" << endl;
                cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
                cout << ind2 << '\'' << ActionModifySkill::SHOW_ACCEPTED << "\' Show the accepted level" << endl;
                cout << ind2 << '\'' << ActionModifySkill::INCREASE_LEVEL << "\' Increase level" << endl;
                cout << ind2 << '\'' << ActionModifySkill::DECREASE_LEVEL << "\' Decrease level" << endl;

                switch (getAction()) {
                case ActionModifySkill::SHOW_ACCEPTED:
                    showSkill(character, type, ind2, true);
                    break;
                case ActionModifySkill::INCREASE_LEVEL: {
                    int n = getPosNumber();
                    if (n >= 0 && n <= numeric_limits<Common::LevelStat>::max()) {
                        character.skill().addLevel(type, n);
                    }
                    break;
                }
                case ActionModifySkill::DECREASE_LEVEL: {
                    int n = getPosNumber();
                    if (n >= 0 && n <= numeric_limits<Common::LevelStat>::max()) {
                        character.skill().addLevel(type, -n);
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

        ///------------------------------------------------------------------------------------------------

        void showAllSkills(const Object::Character& character, const Indent indent, bool accepted)
        {
            Indent ind1 = indent + Indent{};
            showSkillPoints(character, ind1, accepted);
            cout << ind1 << "Skills";
            if (accepted) {
                cout << " (accepted)";
            }
            cout << ":" << endl;
            Indent ind2 = ind1 + Indent{};
            Indent ind3 = ind2 + Indent{};
            cout << ind2 << "COMBAT SKILLS" << endl;
            cout << ind3 << "AUTOMATIC WEAPONS  "
                << statLevel(character.skill().level(Object::Skill::Type::AUTOMATIC_WEAPONS), accepted) << endl;
            cout << ind3 << "BIG GUNS           "
                << statLevel(character.skill().level(Object::Skill::Type::BIG_GUNS), accepted) << endl;
            cout << ind3 << "BRAWLING           "
                << statLevel(character.skill().level(Object::Skill::Type::BRAWLING), accepted) << endl;
            cout << ind3 << "MELEE COMBAT       "
                << statLevel(character.skill().level(Object::Skill::Type::MELEE_COMBAT), accepted) << endl;
            cout << ind3 << "SMALL ARMS         "
                << statLevel(character.skill().level(Object::Skill::Type::SMALL_ARMS), accepted) << endl;
            cout << ind3 << "SNIPER RIFLES      "
                << statLevel(character.skill().level(Object::Skill::Type::SNIPER_RIFLES), accepted) << endl;

            cout << ind2 << "GENERAL SKILLS" << endl;
            cout << ind3 << "ANIMAL WHISPERER   "
                << statLevel(character.skill().level(Object::Skill::Type::ANIMAL_WHISPERER), accepted) << endl;
            cout << ind3 << "EXPLOSIVES         "
                << statLevel(character.skill().level(Object::Skill::Type::EXPLOSIVES), accepted) << endl;
            cout << ind3 << "FIRST AID          "
                << statLevel(character.skill().level(Object::Skill::Type::FIRST_AID), accepted) << endl;
            cout << ind3 << "SNEAKY SHIT        "
                << statLevel(character.skill().level(Object::Skill::Type::SNEAKY_SHIT), accepted) << endl;
            cout << ind3 << "WEIRD SCIENCE      "
                << statLevel(character.skill().level(Object::Skill::Type::WEIRD_SCIENCE), accepted) << endl;


            cout << ind2 << "EXPLORATION SKILLS" << endl;
            cout << ind3 << "ARMOR MODDING      "
                << statLevel(character.skill().level(Object::Skill::Type::ARMOR_MODDING), accepted) << endl;
            cout << ind3 << "LOCKPICKING        "
                << statLevel(character.skill().level(Object::Skill::Type::LOCKPICKING), accepted) << endl;
            cout << ind3 << "NERD STUFF         "
                << statLevel(character.skill().level(Object::Skill::Type::NERD_STUFF), accepted) << endl;
            cout << ind3 << "MECHANICS          "
                << statLevel(character.skill().level(Object::Skill::Type::MECHANICS), accepted) << endl;
            cout << ind3 << "SURVIVAL           "
                << statLevel(character.skill().level(Object::Skill::Type::SURVIVAL), accepted) << endl;
            cout << ind3 << "TOASTER REPAIR     "
                << statLevel(character.skill().level(Object::Skill::Type::TOASTER_REPAIR), accepted) << endl;
            cout << ind3 << "WEAPON MODDING     "
                << statLevel(character.skill().level(Object::Skill::Type::WEAPON_MODDING), accepted) << endl;


            cout << ind2 << "SOCIAL SKILLS" << endl;
            cout << ind3 << "BARTER             "
                << statLevel(character.skill().level(Object::Skill::Type::BARTER), accepted) << endl;
            cout << ind3 << "HARD ASS           "
                << statLevel(character.skill().level(Object::Skill::Type::HARD_ASS), accepted) << endl;
            cout << ind3 << "KISS ASS           "
                << statLevel(character.skill().level(Object::Skill::Type::KISS_ASS), accepted) << endl;
            cout << ind3 << "LEADERSHIP         "
                << statLevel(character.skill().level(Object::Skill::Type::LEADERSHIP), accepted) << endl;
        }

        void showSkill(Object::Character& character, Object::Skill::Type type,
            const Indent indent, bool accepted)
        {
            cout << indent << "Skill";
            if (accepted) {
                cout << " (accepted)";
            }
            cout << " \'";
            switch (type) {
            case Object::Skill::Type::AUTOMATIC_WEAPONS:
                cout << "AUTOMATIC WEAPONS\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::BIG_GUNS:
                cout << "BIG GUNS\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::BRAWLING:
                cout << "BRAWLING\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::MELEE_COMBAT:
                cout << "MELEE COMBAT\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::SMALL_ARMS:
                cout << "SMALL ARMS\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::SNIPER_RIFLES:
                cout << "SNIPER RIFLES\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::ANIMAL_WHISPERER:
                cout << "ANIMAL WHISPERER\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::EXPLOSIVES:
                cout << "EXPLOSIVES\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::FIRST_AID:
                cout << "FIRST AID\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::SNEAKY_SHIT:
                cout << "SNEAKY SHIT\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::WEIRD_SCIENCE:
                cout << "WEIRD SCIENCE\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::ARMOR_MODDING:
                cout << "ARMOR MODDING\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::LOCKPICKING:
                cout << "LOCKPICKING\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::NERD_STUFF:
                cout << "NERD STUFF\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::MECHANICS:
                cout << "MECHANICS\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::SURVIVAL:
                cout << "SURVIVAL\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::TOASTER_REPAIR:
                cout << "TOASTER REPAIR\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::WEAPON_MODDING:
                cout << "WEAPON MODDING\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::BARTER:
                cout << "BARTER\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::HARD_ASS:
                cout << "HARD ASS\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::KISS_ASS:
                cout << "KISS ASS\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            case Object::Skill::Type::LEADERSHIP:
                cout << "LEADERSHIP\': "
                    << statLevel(character.skill().level(type), accepted) << endl;
                break;
            default:
                cout << "UNKNOWN\'" << endl;
                return;
            }
        }

        void showSkillPoints(const Object::Character& character, const Indent indent, bool accepted)
        {
            cout << indent << "Skill points";
            if (accepted) {
                cout << " (accepted): " << static_cast<int>(character.skill().storage().getAccepted()) << endl;
            }
            else {
                cout << ": " << static_cast<int>(character.skill().storage().get()) << endl;
            }
        }

        Object::Skill::Type pickSkill(const Indent indent)
        {
            Indent ind1 = indent + Indent{};
            cout << ind1 << "Skills:" << endl;
            Indent ind2 = ind1 + Indent{};
            Indent ind3 = ind2 + Indent{};
            cout << ind2 << "COMBAT SKILLS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::AUTOMATIC_WEAPONS)
                << "\' AUTOMATIC WEAPONS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::BIG_GUNS)
                << "\' BIG GUNS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::BRAWLING)
                << "\' BRAWLING" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::MELEE_COMBAT)
                << "\' MELEE COMBAT" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::SMALL_ARMS)
                << "\' SMALL ARMS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::SNIPER_RIFLES)
                << "\' SNIPER RIFLES" << endl;

            cout << ind2 << "GENERAL SKILLS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::ANIMAL_WHISPERER)
                << "\' ANIMAL WHISPERER" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::EXPLOSIVES)
                << "\' EXPLOSIVES" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::FIRST_AID)
                << "\' FIRST AID" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::SNEAKY_SHIT)
                << "\' SNEAKY SHIT" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::WEIRD_SCIENCE)
                << "\' WEIRD SCIENCE" << endl;

            cout << ind2 << "EXPLORATION SKILLS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::ARMOR_MODDING)
                << "\' ARMOR MODDING" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::LOCKPICKING)
                << "\' LOCKPICKING" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::NERD_STUFF)
                << "\' NERD STUFF" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::MECHANICS)
                << "\' MECHANICS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::SURVIVAL)
                << "\' SURVIVAL" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::TOASTER_REPAIR)
                << "\' TOASTER REPAIR" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::WEAPON_MODDING)
                << "\' WEAPON MODDING" << endl;

            cout << ind2 << "SOCIAL SKILLS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::BARTER)
                << "\' BARTER" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::HARD_ASS)
                << "\' HARD ASS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::KISS_ASS)
                << "\' KISS ASS" << endl;
            cout << ind3 << '\'' << static_cast<int>(Object::Skill::Type::LEADERSHIP)
                << "\' LEADERSHIP" << endl;

            cout << ind1 << "Select a skill:" << endl;
            Object::Skill::Type t{ Object::Skill::Type::INVALID };
            int n = getPosNumber();
            if (n > static_cast<int>(Object::Skill::Type::INVALID) &&
                n < static_cast<int>(Object::Skill::Type::NUMBER_OF)) {
                t = static_cast<Object::Skill::Type>(n);
            }
            return t;
        }

    }
}
