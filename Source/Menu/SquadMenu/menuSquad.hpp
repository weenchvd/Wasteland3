
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_SQUAD_HPP
#define MENU_SQUAD_HPP

#include"common.hpp"
#include"menuCommon.hpp"
#include"squad.hpp"
#include<iostream>
#include<utility>

namespace game {
namespace menu {

namespace memberCounter {

constexpr auto countFrom{ 1 };

} // namespace memberCounter

namespace actionSquad {

enum ActionSquad {
    SHOW_MEMBERS = actionCommon::__NEXT_ACTION_NUMBER,
    MENU_CHARACTER,

    __NEXT_ACTION_NUMBER
};

} // namespace actionSquad

void menuSquad(std::istream& is, std::ostream& os, object::Squad& squad, const Indent indent);

///************************************************************************************************

std::pair<int, bool> pickCharacter(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    const Indent indent
);

void showSquad(
    std::istream& is,
    std::ostream& os,
    const object::Squad& squad,
    const Indent indent
);

} // namespace menu
} // namespace game

#endif // !MENU_SQUAD_HPP
