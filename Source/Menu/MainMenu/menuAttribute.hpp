
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

constexpr int attrWidth{ 20 };

namespace actionAttribute {

enum ActionAttribute {
    SHOW_ALL = actionCommon::NEXT,
    SHOW_ALL_ACCEPTED,
    MODIFY
};

} // namespace actionAttribute

void menuAttribute(object::Character& character, const Indent indent);

namespace actionModifyAttribute {

enum ActionModifyAttribute {
    SHOW_ACCEPTED = actionCommon::NEXT,
    INCREASE_LEVEL,
    DECREASE_LEVEL
};

} // namespace actionModifyAttribute

void menuModifyAttribute(
    object::Character& character,
    object::Attribute::Type type,
    const Indent indent);

///------------------------------------------------------------------------------------------------

void showAllAttributes(
    const object::Character& character,
    const Indent indent,
    bool accepted = false);

common::Text stringAttribute(
    const object::Character& character,
    object::Attribute::Type type,
    unsigned char width,
    char placeholder,
    bool accepted = false);

void showAttPoints(
    const object::Character& character,
    const Indent indent,
    bool accepted = false);

object::Attribute::Type pickAttribute(
    const object::Character& character,
    const Indent indent);

} // namespace menu
} // namespace game

#endif // !MENU_ATTRIBUTE_HPP
