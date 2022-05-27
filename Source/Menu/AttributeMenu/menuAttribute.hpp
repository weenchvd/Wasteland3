
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ATTRIBUTE_HPP
#define MENU_ATTRIBUTE_HPP

#include"character.hpp"
#include"menuCommon.hpp"
#include<iostream>

namespace game {
namespace menu {

namespace actionAttribute {

enum ActionAttribute {
    SHOW_ALL = actionCommon::__NEXT_ACTION_NUMBER,
    SHOW_ALL_ACCEPTED,
    MODIFY,
    SAVE_CHANGES,
    CANCEL_CHANGES,

    __NEXT_ACTION_NUMBER
};

} // namespace actionAttribute

void menuAttribute(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    const Indent indent
);

namespace actionModifyAttribute {

enum ActionModifyAttribute {
    SHOW_DESCRIPTION = actionCommon::__NEXT_ACTION_NUMBER,
    INCREASE_LEVEL,
    DECREASE_LEVEL,

    __NEXT_ACTION_NUMBER
};

} // namespace actionModifyAttribute

void menuModifyAttribute(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    object::Attribute::Type type,
    const Indent indent
);

///************************************************************************************************

constexpr int attributeSpaces{ 2 };

void showAllAttributes(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted = false
);

common::Text stringAttribute(
    const object::Character& character,
    object::Attribute::Type type,
    unsigned char width,
    char placeholder,
    bool accepted = false
);

void showAttPoints(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted = false
);

object::Attribute::Type pickAttribute(
    std::istream& is,
    std::ostream& os,
    const object::Character& character,
    const Indent indent
);

void changeLevel(
    std::istream& is,
    std::ostream& os,
    object::Character& character,
    object::Attribute::Type type,
    const Indent indent,
    bool increase
);

} // namespace menu
} // namespace game

#endif // !MENU_ATTRIBUTE_HPP
