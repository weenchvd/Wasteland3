
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

namespace actionSkill {

enum ActionSkill {
    SHOW_ALL = actionCommon::__NEXT_ACTION_NUMBER,
    SHOW_ALL_ACCEPTED,
    MODIFY,
    SAVE_CHANGES,
    CANCEL_CHANGES,

    __NEXT_ACTION_NUMBER
};

} // namespace actionSkill

void menuSkill(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    const Indent indent
);

namespace actionModifySkill {

enum ActionModifySkill {
    SHOW_DESCRIPTION = actionCommon::__NEXT_ACTION_NUMBER,
    INCREASE_LEVEL,
    DECREASE_LEVEL,

    __NEXT_ACTION_NUMBER
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

constexpr int skillSpaces{ 2 };

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

void changeLevel(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    object::Skill::Type type,
    const Indent indent,
    bool increase
);

} // namespace menu
} // namespace game

#endif // !MENU_SKILL_HPP
