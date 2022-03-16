
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_OPTION_HPP
#define MENU_OPTION_HPP

#include"menuCommon.hpp"
#include"plainText.hpp"
#include<iostream>

namespace game {
namespace menu {

constexpr int optionWidth{ 30 };

namespace actionOption {

enum ActionOption {
    LANGUAGE = actionCommon::__NEXT_ACTION_NUMBER
};

} // namespace actionOption

void menuOption(std::istream& is, std::ostream& os, const Indent indent);

namespace actionLanguage {

enum ActionLanguage {
    CHANGE_LANGUAGE = actionCommon::__NEXT_ACTION_NUMBER
};

} // namespace actionLanguage

void menuLanguage(std::istream& is, std::ostream& os, const Indent indent);

///************************************************************************************************

global::PlainText::Language pickLanguage(std::istream& is, std::ostream& os, const Indent indent);

} // namespace menu
} // namespace game

#endif // !MENU_OPTION_HPP
