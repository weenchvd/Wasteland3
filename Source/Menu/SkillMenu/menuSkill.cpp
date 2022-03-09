
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommonText.hpp"
#include"menuSkill.hpp"
#include"locator.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace game {
namespace menu {

using namespace std;


void menuSkill(object::Character& character, const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Skill menu (" << character.name() << ")" << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionSkill::SHOW_ALL << "\' Show skills" << endl;
        cout << ind2 << '\'' << actionSkill::SHOW_ALL_ACCEPTED << "\' Show skills (accepted)" << endl;
        cout << ind2 << '\'' << actionSkill::MODIFY << "\' Modify skill" << endl;

        switch (getAction()) {
        case actionSkill::SHOW_ALL:
            showAllSkills(character, ind1);
            break;
        case actionSkill::SHOW_ALL_ACCEPTED:
            showAllSkills(character, ind1, true);
            break;
        case actionSkill::MODIFY: {
            object::Skill::Type type{ pickSkill(character, ind1) };
            if (type != object::Skill::Type::INVALID) {
                menuModifySkill(character, type, ind1);
            }
            break;
        }
        case actionCommon::EXIT:
            if (character.skill().isModified()) {
                cout << ind1 << "Skills have been changed. Do you want to save the changes?" << endl;
                switch (getYesNo(ind1)) {
                case YesNo::YES:
                    character.skill().accept();
                    return;
                case YesNo::NO:
                    character.skill().reject();
                    return;
                case YesNo::CANCEL:
                default:
                    break;
                }
            }
            else {
                return;
            }
            break;
        case actionCommon::INVALID:
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

void menuModifySkill(
    object::Character& character,
    object::Skill::Type type,
    const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    auto width{ utf8Size(character.skill().skillText().name(type)) + 2 };

    while (true)
    {
        cout << endl << endl;
        showSkillPoints(character, ind1);
        cout << ind1 << "Skill: " << stringSkill(character, type, width, space) << endl;
        cout << ind2 << character.skill().skillText().descr(type) << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionModifySkill::SHOW_ACCEPTED << "\' Show the accepted level" << endl;
        cout << ind2 << '\'' << actionModifySkill::INCREASE_LEVEL << "\' Increase level" << endl;
        cout << ind2 << '\'' << actionModifySkill::DECREASE_LEVEL << "\' Decrease level" << endl;

        switch (getAction()) {
        case actionModifySkill::SHOW_ACCEPTED:
            cout << ind2 << "Skill (accepted): "
                << stringSkill(character, type, width, space, true) << endl;
            break;
        case actionModifySkill::INCREASE_LEVEL: {
            auto pair{ getNumber() };
            if (pair.second == true) {
                if (pair.first >= 0 && pair.first <= numeric_limits<common::LevelStat>::max()) {
                    // TODO ^^^ check or set range
                    character.skill().addLevel(type, pair.first);
                }
                else {
                    // TODO cout << message
                }
            }
            break;
        }
        case actionModifySkill::DECREASE_LEVEL: {
            auto pair{ getNumber() };
            if (pair.second == true) {
                if (pair.first >= 0 && pair.first <= numeric_limits<common::LevelStat>::max()) {
                    // TODO ^^^ check or set range
                    character.skill().addLevel(type, -pair.first);
                }
                else {
                    // TODO cout << message
                }
            }
            break;
        }
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

///------------------------------------------------------------------------------------------------

void showAllSkills(
    const object::Character& character,
    const Indent indent,
    bool accepted)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    Indent ind3{ ind2 + Indent{} };

    showSkillPoints(character, ind1, accepted);
    cout << ind1 << "Skills";
    if (accepted) {
        cout << " (accepted)";
    }
    cout << ":" << endl;

    cout << ind2 << character.skill().skillText().group(object::Skill::Group::COMBAT) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::AUTOMATIC_WEAPONS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::BIG_GUNS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::BRAWLING,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::MELEE_COMBAT,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::SMALL_ARMS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::SNIPER_RIFLES,
        skillWidth, space, accepted) << endl;

    cout << ind2 << character.skill().skillText().group(object::Skill::Group::GENERAL) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::ANIMAL_WHISPERER,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::EXPLOSIVES,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::FIRST_AID,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::SNEAKY_SHIT,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::WEIRD_SCIENCE,
        skillWidth, space, accepted) << endl;

    cout << ind2 << character.skill().skillText().group(object::Skill::Group::EXPLORATION) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::ARMOR_MODDING,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::LOCKPICKING,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::NERD_STUFF,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::MECHANICS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::SURVIVAL,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::TOASTER_REPAIR,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::WEAPON_MODDING,
        skillWidth, space, accepted) << endl;

    cout << ind2 << character.skill().skillText().group(object::Skill::Group::SOCIAL) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::BARTER,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::HARD_ASS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::KISS_ASS,
        skillWidth, space, accepted) << endl;
    cout << ind3 << stringSkill(character, object::Skill::Type::LEADERSHIP,
        skillWidth, space, accepted) << endl;
}

common::Text stringSkill(
    const object::Character& character,
    object::Skill::Type type,
    unsigned char width,
    char placeholder,
    bool accepted)
{
    common::Text t{
        fillWithPlaseholders(
            character.skill().skillText().name(type), width, placeholder)
    };
    t += statLevel(character.skill().level(type), accepted);
    return t;
}

void showSkillPoints(
    const object::Character& character,
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

object::Skill::Type pickSkill(
    const object::Character& character,
    const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    cout << ind1 << "Skills:" << endl;
    for (int i{ common::toUnderlying(common::firstEnum<object::Skill::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Skill::Type>()); ++i)
    {
        cout << ind2 << '\'' << i << "\' "
            << character.skill().skillText().name(
                static_cast<object::Skill::Type>(i)) << endl;
    }

    cout << ind1 << "Select a skill:" << endl;
    object::Skill::Type t{ object::Skill::Type::INVALID };
    auto pair{ getNumber() };
    if (pair.second == true) {
        if (pair.first >= common::toUnderlying(common::firstEnum<object::Skill::Type>()) &&
            pair.first <= common::toUnderlying(common::lastEnum<object::Skill::Type>()))
        {
            t = static_cast<object::Skill::Type>(pair.first);
        }
        else {
            cout << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return t;
}

} // namespace menu
} // namespace game
