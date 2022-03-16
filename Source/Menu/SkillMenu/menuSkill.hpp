
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
    SHOW_ALL = actionCommon::__NEXT_ACTION_NUMBER,
    SHOW_ALL_ACCEPTED,
    MODIFY
};

} // namespace actionSkill

void menuSkill(std::istream& is, std::ostream& os, object::Character& character, const Indent indent);

namespace actionModifySkill {

enum ActionModifySkill {
    SHOW_ACCEPTED = actionCommon::__NEXT_ACTION_NUMBER,
    INCREASE_LEVEL,
    DECREASE_LEVEL
};

} // namespace actionModifySkill

void menuModifySkill(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    object::Skill::Type type,
    const Indent indent
);

///************************************************************************************************

void showAllSkills(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted = false
);

common::Text stringSkill(
    const object::Character& character,
    object::Skill::Type type,
    unsigned char width,
    char placeholder,
    bool accepted = false
);

void showSkillPoints(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted = false
);

object::Skill::Type pickSkill(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_SKILL_HPP
