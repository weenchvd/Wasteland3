
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_SKILL_HPP
#define MENU_SKILL_HPP

#include"character.hpp"
#include"menuCommon.hpp"
#include<iostream>

namespace game {
namespace menu {

constexpr int skillWidth{ 30 };

namespace actionSkill {

enum ActionSkill {
    SHOW_ALL = actionCommon::NEXT,
    SHOW_ALL_ACCEPTED,
    MODIFY
};

} // namespace actionSkill

void menuSkill(object::Character& character, const Indent indent);

namespace actionModifySkill {

enum ActionModifySkill {
    SHOW_ACCEPTED = actionCommon::NEXT,
    INCREASE_LEVEL,
    DECREASE_LEVEL
};

} // namespace actionModifySkill

void menuModifySkill(
    object::Character& character,
    object::Skill::Type type,
    const Indent indent);

///------------------------------------------------------------------------------------------------

void showAllSkills(
    const object::Character& character,
    const Indent indent,
    bool accepted = false);

common::Text stringSkill(
    const object::Character& character,
    object::Skill::Type type,
    unsigned char width,
    char placeholder,
    bool accepted = false);

void showSkillPoints(
    const object::Character& character,
    const Indent indent,
    bool accepted = false);

object::Skill::Type pickSkill(
    const object::Character& character,
    const Indent indent);

} // namespace menu
} // namespace game

#endif // !MENU_SKILL_HPP
