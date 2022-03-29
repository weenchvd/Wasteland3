
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_OPTIONS_HPP
#define MENU_OPTIONS_HPP

#include"menuCommon.hpp"
#include"plainTextBase.hpp"
#include<iostream>

namespace game {
namespace menu {

namespace actionOptions {

enum ActionOptions {
    GENERAL_OPTIONS = actionCommon::__NEXT_ACTION_NUMBER,
    SAVE_CHANGES,
    CANCEL_CHANGES
};

} // namespace actionOptions

void menuOptions(std::istream& is, std::ostream& os, const Indent indent);

namespace actionGeneralOptions {

enum GeneralOptions {
    CHANGE_LANGUAGE = actionCommon::__NEXT_ACTION_NUMBER,
    SAVE_CHANGES,
    CANCEL_CHANGES
};

} // namespace actionGeneralOptions

void menuGeneralOptions(std::istream& is, std::ostream& os, const Indent indent);

///************************************************************************************************

global::PlainTextBase::Language pickLanguage(std::istream& is, std::ostream& os, const Indent indent);

} // namespace menu
} // namespace game

#endif // !MENU_OPTIONS_HPP
