
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_CHARACTER_HPP
#define MENU_CHARACTER_HPP

#include"character.hpp"
#include"common.hpp"
#include"menuCommon.hpp"
#include<iostream>

namespace game {
namespace menu {

namespace actionCharacter {

enum ActionCharacter {
    SHOW_STATS = actionCommon::__NEXT_ACTION_NUMBER,
    SHOW_GEAR,
    SHOW_ATTRIBUTES,
    MENU_ATTRIBUTE,
    SHOW_SKILLS,
    MENU_SKILL,

    __NEXT_ACTION_NUMBER
};

} // namespace actionCharacter

void menuCharacter(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    const Indent indent
);

///************************************************************************************************

void showStats(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent
);

void showGear(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_CHARACTER_HPP
