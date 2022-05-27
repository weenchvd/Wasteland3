
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommonText.hpp"
#include"menuSkill.hpp"
#include"menuSkillText.hpp"
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
    const auto& text{ MenuSkillText::main() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << " (" << character.name() << ")" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionSkill::SHOW_ALL, text.showSkills()) << endl;
        printNumBar(os, ind1, actionSkill::SHOW_ALL_ACCEPTED, text.showSkillsAccepted()) << endl;
        printNumBar(os, ind1, actionSkill::MODIFY, text.modify()) << endl;
        printNumBar(os, ind1, actionSkill::SAVE_CHANGES, comT.saveChanges()) << endl;
        printNumBar(os, ind1, actionSkill::CANCEL_CHANGES, comT.cancelChanges()) << endl;
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
        case actionSkill::SAVE_CHANGES:
            character.skill().accept();
            break;
        case actionSkill::CANCEL_CHANGES:
            character.skill().reject();
            break;
        case actionCommon::EXIT:
            if (character.skill().isModified()) {
                os << ind0 << text.questionSaveChanges() << endl;
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
    const auto& text{ MenuSkillText::modify() };
    auto nameWidth{ utf8Size(character.skill().skillText().name(type)) + skillSpaces };
    auto width{ utf8Size(text.skillAccepted()) };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << " (" << character.name() << ")" << endl;
        showSkillPoints(is, os, character, ind0);
        os << ind0 << fillWithPlaseholders(text.skill(), width, space) << space
            << stringSkill(character, type, nameWidth, space, false) << endl;
        os << ind0 << fillWithPlaseholders(text.skillAccepted(), width, space) << space
            << stringSkill(character, type, nameWidth, space, true) << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionModifySkill::SHOW_DESCRIPTION, text.showDescription()) << endl;
        printNumBar(os, ind1, actionModifySkill::INCREASE_LEVEL, text.increaseLevel()) << endl;
        printNumBar(os, ind1, actionModifySkill::DECREASE_LEVEL, text.decreaseLevel()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionModifySkill::SHOW_DESCRIPTION:
            os << ind1 << character.skill().skillText().descr(type) << endl;
            break;
        case actionModifySkill::INCREASE_LEVEL: {
            changeLevel(is, os, character, type, indent, true);
            break;
        }
        case actionModifySkill::DECREASE_LEVEL: {
            changeLevel(is, os, character, type, indent, false);
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
    const auto& text{ MenuSkillText::common() };

    showSkillPoints(is, os, character, ind0, accepted);
    os << ind0 << (accepted ? text.skillsAccepted() : text.skills()) << endl;

    unsigned int width{ 0 };
    for (int i{ common::toUnderlying(common::firstEnum<object::Skill::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Skill::Type>()); ++i)
    {
        auto size{ utf8Size(character.skill().skillText().name(
            static_cast<object::Skill::Type>(i)))
        };
        if (width < size) {
            width = size;
        }
    }
    width += skillSpaces;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::COMBAT) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::AUTOMATIC_WEAPONS,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::BIG_GUNS,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::BRAWLING,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::MELEE_COMBAT,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SMALL_ARMS,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SNIPER_RIFLES,
        width, space, accepted) << endl;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::GENERAL) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::ANIMAL_WHISPERER,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::EXPLOSIVES,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::FIRST_AID,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SNEAKY_SHIT,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::WEIRD_SCIENCE,
        width, space, accepted) << endl;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::EXPLORATION) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::ARMOR_MODDING,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::LOCKPICKING,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::NERD_STUFF,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::MECHANICS,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::SURVIVAL,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::TOASTER_REPAIR,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::WEAPON_MODDING,
        width, space, accepted) << endl;

    os << ind1 << character.skill().skillText().group(object::Skill::Group::SOCIAL) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::BARTER,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::HARD_ASS,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::KISS_ASS,
        width, space, accepted) << endl;
    os << ind2 << stringSkill(character, object::Skill::Type::LEADERSHIP,
        width, space, accepted) << endl;
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
    const auto& text{ MenuSkillText::common() };

    os << indent << (accepted ? text.skillPointsAccepted() : text.skillPoints())
        << space << (accepted ? character.skill().storage().getAccepted() :
            character.skill().storage().get()) << endl;
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
    const auto& text{ MenuSkillText::common() };

    os << ind0 << text.skills() << endl;
    for (int i{ common::toUnderlying(common::firstEnum<object::Skill::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Skill::Type>()); ++i)
    {
        printNumBar(os, ind1, i, character.skill().skillText().name(
            static_cast<object::Skill::Type>(i))) << endl;
    }

    os << ind0 << text.selectSkill() << endl;
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

void changeLevel(
    istream& is,
    ostream& os,
    object::Character& character,
    object::Skill::Type type,
    const Indent indent,
    bool increase)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuSkillText::common() };

    os << ind1 << text.enterNumOfLevels() << endl;

    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        if (pair.first >= 0 &&
            pair.first <= numeric_limits<std::underlying_type_t<common::LevelSkill>>::max())
        {
            auto success{ character.skill().addLevel(type, common::LevelSkill{
                static_cast<std::underlying_type_t<common::LevelSkill>>(
                    (increase ? pair.first : -pair.first)) })
            };
            if (success) return;
        }
        os << comT.errorSymbol() << text.invalidNumOfLevels() << endl;
    }
}

} // namespace menu
} // namespace game
