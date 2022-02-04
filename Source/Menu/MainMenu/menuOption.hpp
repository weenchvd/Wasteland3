
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_OPTION_HPP
#define MENU_OPTION_HPP

#include"menuCommon.hpp"
#include"plainText.hpp"
#include<iostream>

namespace Game {
namespace Menu {

constexpr int optionWidth{ 30 };

namespace ActionOption {

enum ActionOption {
    LANGUAGE = ActionCommon::NEXT
};

} // namespace ActionOption

void menuOption(const Indent indent);

namespace ActionLanguage {

enum ActionLanguage {
    CHANGE_LANGUAGE = ActionCommon::NEXT
};

} // namespace ActionLanguage

void menuLanguage(const Indent indent);

///------------------------------------------------------------------------------------------------

Game::Global::PlainText::Language pickLanguage(const Indent indent);

} // namespace Menu
} // namespace Game

#endif // !MENU_OPTION_HPP
