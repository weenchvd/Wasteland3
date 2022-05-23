
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


void menuSkill(istream& is, ostream& os, object::Character& character, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Skill menu (" << character.name() << ")" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionSkill::SHOW_ALL, "Show skills") << endl;
        printNumBar(os, ind1, actionSkill::SHOW_ALL_ACCEPTED, "Show skills (accepted)") << endl;
        printNumBar(os, ind1, actionSkill::MODIFY, "Modify skill") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionSkill::SHOW_ALL:
            showAllSkills(is, os, character, ind1);
            break;
        case actionSkill::SHOW_ALL_ACCEPTED:
            showAllSkills(is, os, character, ind1, true);
            break;
        case actionSkill::MODIFY: {
            object::Skill::Type type{ pickSkill(is, os, character, ind1) };
            if (type != object::Skill::Type::INVALID) {
                menuModifySkill(is, os, character, type, ind1);
            }
            break;
        }
        case actionCommon::EXIT:
            if (character.skill().isModified()) {
                os << ind0 << "Skills have been changed. Do you want to save the changes?" << endl;
                switch (getYesNo(is, os, ind0)) {
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
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void menuModifySkill(
    istream& is,
    ostream& os,
    object::Character& character,
    object::Skill::Type type,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    auto width{ utf8Size(character.skill().skillText().name(type)) + 2 };

    while (true)
    {
        verticalIndent(os);
        showSkillPoints(is, os, character, ind0);
        os << ind0 << "Skill: " << stringSkill(character, type, width, space) << endl;
        os << ind1 << character.skill().skillText().descr(type) << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionModifySkill::SHOW_ACCEPTED, "Show the accepted level") << endl;
        printNumBar(os, ind1, actionModifySkill::INCREASE_LEVEL, "Increase level") << endl;
        printNumBar(os, ind1, actionModifySkill::DECREASE_LEVEL, "Decrease level") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionModifySkill::SHOW_ACCEPTED:
            os << ind1 << "Skill (accepted): "
                << stringSkill(character, type, width, space, true) << endl;
            break;
        case actionModifySkill::INCREASE_LEVEL: {
            auto pair{ getNumber(is, os) };
            if (pair.second == true) {
                if (pair.first >= 0 &&
                    pair.first <= numeric_limits<std::underlying_type_t<common::LevelSkill>>::max()) {
                    // TODO ^^^ check or set range
                    character.skill().addLevel(type, common::LevelSkill{
                        static_cast<std::underlying_type_t<common::LevelSkill>>(pair.first) });
                }
                else {
                    // TODO os << message
                }
            }
            break;
        }
        case actionModifySkill::DECREASE_LEVEL: {
            auto pair{ getNumber(is, os) };
            if (pair.second == true) {
                if (pair.first >= 0 &&
                    pair.first <= numeric_limits<std::underlying_type_t<common::LevelSkill>>::max()) {
                    // TODO ^^^ check or set range
                    character.skill().addLevel(type, common::LevelSkill{
                        static_cast<std::underlying_type_t<common::LevelSkill>>(-pair.first) });
                }
                else {
                    // TODO os << message
                }
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

///************************************************************************************************

void showAllSkills(
    istream& is,
    ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    Indent ind2{ ind1 + Indent{} };

    showSkillPoints(is, os, character, ind1, accepted);
    os << ind0 << "Skills";
    if (accepted) {
        os << " (accepted)";
    }
    os << ":" << endl;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::COMBAT) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::AUTOMATIC_WEAPONS,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::BIG_GUNS,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::BRAWLING,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::MELEE_COMBAT,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SMALL_ARMS,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SNIPER_RIFLES,
        skillWidth, space, accepted) << endl;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::GENERAL) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::ANIMAL_WHISPERER,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::EXPLOSIVES,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::FIRST_AID,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SNEAKY_SHIT,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::WEIRD_SCIENCE,
        skillWidth, space, accepted) << endl;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::EXPLORATION) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::ARMOR_MODDING,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::LOCKPICKING,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::NERD_STUFF,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::MECHANICS,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SURVIVAL,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::TOASTER_REPAIR,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::WEAPON_MODDING,
        skillWidth, space, accepted) << endl;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::SOCIAL) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::BARTER,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::HARD_ASS,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::KISS_ASS,
        skillWidth, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::LEADERSHIP,
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
    t += stringLevel(character.skill().level(type), accepted);
    return t;
}

void showSkillPoints(
    istream& is,
    ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted)
{
    os << indent << "Skill points";
    if (accepted) {
        os << " (accepted): " << static_cast<int>(
            character.skill().storage().getAccepted()) << endl;
    }
    else {
        os << ": " << static_cast<int>(
            character.skill().storage().get()) << endl;
    }
}

object::Skill::Type pickSkill(
    istream& is,
    ostream& os,
    const object::Character& character,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    os << ind0 << "Skills:" << endl;
    for (int i{ common::toUnderlying(common::firstEnum<object::Skill::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Skill::Type>()); ++i)
    {
        os << ind1 << '\'' << i << "\' "
            << character.skill().skillText().name(
                static_cast<object::Skill::Type>(i)) << endl;
    }

    os << ind0 << "Select a skill:" << endl;
    object::Skill::Type t{ object::Skill::Type::INVALID };
    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        if (pair.first >= common::toUnderlying(common::firstEnum<object::Skill::Type>()) &&
            pair.first <= common::toUnderlying(common::lastEnum<object::Skill::Type>()))
        {
            t = static_cast<object::Skill::Type>(pair.first);
        }
        else {
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return t;
}

} // namespace menu
} // namespace game
