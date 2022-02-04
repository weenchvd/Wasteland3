
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_SKILL_HPP
#define MENU_SKILL_HPP

#include"character.hpp"
#include"menuCommon.hpp"
#include<iostream>

namespace Game {
namespace Menu {

constexpr int skillWidth{ 30 };

namespace ActionSkill
{
    enum ActionSkill {
        SHOW_ALL = ActionCommon::NEXT,
        SHOW_ALL_ACCEPTED,
        MODIFY
    };
}

void menuSkill(Object::Character& character, const Indent indent);

namespace ActionModifySkill
{
    enum ActionModifySkill {
        SHOW_ACCEPTED = ActionCommon::NEXT,
        INCREASE_LEVEL,
        DECREASE_LEVEL
    };
}

void menuModifySkill(
    Object::Character& character,
    Object::Skill::Type type,
    const Indent indent);

///------------------------------------------------------------------------------------------------

void showAllSkills(
    const Object::Character& character,
    const Indent indent,
    bool accepted = false);

Common::Text stringSkill(
    const Object::Character& character,
    Object::Skill::Type type,
    unsigned char width,
    char placeholder,
    bool accepted = false);

void showSkillPoints(
    const Object::Character& character,
    const Indent indent,
    bool accepted = false);

Object::Skill::Type pickSkill(
    const Object::Character& character,
    const Indent indent);

} // namespace Menu
} // namespace Game

#endif // !MENU_SKILL_HPP
