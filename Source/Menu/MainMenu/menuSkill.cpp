
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuSkill.hpp"
#include"locator.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace Game {
namespace Menu {

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
            Object::Skill::Type type{ pickSkill(character, ind1) };
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
                cout << ind1 << "Skills have been changed. Do you want to save the changes?" << endl;
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

void menuModifySkill(
    Object::Character& character,
    Object::Skill::Type type,
    const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};
    auto width{ utf8Size(character.skill().skillText().name(type)) + 2 };

    while (true)
    {
        cout << endl << endl;
        showSkillPoints(character, ind1);
        cout << ind1 << "Skill: " << stringSkill(character, type, width, space) << endl;
        cout << ind2 << character.skill().skillText().descr(type) << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << ActionModifySkill::SHOW_ACCEPTED << "\' Show the accepted level" << endl;
        cout << ind2 << '\'' << ActionModifySkill::INCREASE_LEVEL << "\' Increase level" << endl;
        cout << ind2 << '\'' << ActionModifySkill::DECREASE_LEVEL << "\' Decrease level" << endl;

        switch (getAction()) {
        case ActionModifySkill::SHOW_ACCEPTED:
            cout << ind2 << "Skill (accepted): "
                << stringSkill(character, type, width, space, true) << endl;
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

void showAllSkills(
    const Object::Character& character,
    const Indent indent,
    bool accepted)
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

    cout << ind2 << character.skill().skillText().group(Object::Skill::Group::COMBAT) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::AUTOMATIC_WEAPONS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::BIG_GUNS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::BRAWLING,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::MELEE_COMBAT,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::SMALL_ARMS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::SNIPER_RIFLES,
        skillWidth, space, accepted) << endl;

    cout << ind2 << character.skill().skillText().group(Object::Skill::Group::GENERAL) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::ANIMAL_WHISPERER,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::EXPLOSIVES,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::FIRST_AID,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::SNEAKY_SHIT,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::WEIRD_SCIENCE,
        skillWidth, space, accepted) << endl;

    cout << ind2 << character.skill().skillText().group(Object::Skill::Group::EXPLORATION) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::ARMOR_MODDING,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::LOCKPICKING,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::NERD_STUFF,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::MECHANICS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::SURVIVAL,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::TOASTER_REPAIR,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::WEAPON_MODDING,
        skillWidth, space, accepted) << endl;

    cout << ind2 << character.skill().skillText().group(Object::Skill::Group::SOCIAL) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::BARTER,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::HARD_ASS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::KISS_ASS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, Object::Skill::Type::LEADERSHIP,
        skillWidth, space, accepted) << endl;
}

Common::Text stringSkill(
    const Object::Character& character,
    Object::Skill::Type type,
    unsigned char width,
    char placeholder,
    bool accepted)
{
    Common::Text t{
        fillWithPlaseholders(
            character.skill().skillText().name(type), width, placeholder)
    };
    t += statLevel(character.skill().level(type), accepted);
    return t;
}

void showSkillPoints(
    const Object::Character& character,
    const Indent indent,
    bool accepted)
{
    cout << indent << "Skill points";
    if (accepted) {
        cout << " (accepted): " << static_cast<int>(
            character.skill().storage().getAccepted()) << endl;
    }
    else {
        cout << ": " << static_cast<int>(
            character.skill().storage().get()) << endl;
    }
}

Object::Skill::Type pickSkill(
    const Object::Character& character,
    const Indent indent)
{
    Indent ind1 = indent + Indent{};
    cout << ind1 << "Skills:" << endl;
    Indent ind2 = ind1 + Indent{};

    for (int i = static_cast<int>(Object::Skill::Type::INVALID) + 1;
        i < static_cast<int>(Object::Skill::Type::NUMBER_OF); ++i)
    {
        cout << ind2 << '\'' << i << "\' "
            << character.skill().skillText().name(
                static_cast<Object::Skill::Type>(i)) << endl;
    }

    cout << ind1 << "Select a skill:" << endl;
    Object::Skill::Type t{ Object::Skill::Type::INVALID };
    int n = getPosNumber();
    if (n > static_cast<int>(Object::Skill::Type::INVALID) &&
        n < static_cast<int>(Object::Skill::Type::NUMBER_OF)) {
        t = static_cast<Object::Skill::Type>(n);
    }
    return t;
}

} // namespace Menu
} // namespace Game
