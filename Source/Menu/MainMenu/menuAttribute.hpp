
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ATTRIBUTE_HPP
#define MENU_ATTRIBUTE_HPP

#include"character.hpp"
#include"menuCommon.hpp"
#include<iostream>

namespace Game
{
    namespace Menu
    {
        constexpr int attrWidth{ 20 };

        namespace ActionAttribute
        {
            enum ActionAttribute {
                SHOW_ALL = ActionCommon::NEXT,
                SHOW_ALL_ACCEPTED,
                MODIFY
            };
        }

        void menuAttribute(Object::Character& character, const Indent indent);

        namespace ActionModifyAttribute
        {
            enum ActionModifyAttribute {
                SHOW_ACCEPTED = ActionCommon::NEXT,
                INCREASE_LEVEL,
                DECREASE_LEVEL
            };
        }

        void menuModifyAttribute(
            Object::Character& character,
            Object::Attribute::Type type,
            const Indent indent);

        ///------------------------------------------------------------------------------------------------

        void showAllAttributes(
            const Object::Character& character,
            const Indent indent,
            bool accepted = false);

        Game::Common::Text stringAttribute(
            const Object::Character& character,
            Object::Attribute::Type type,
            unsigned char width,
            char placeholder,
            bool accepted = false);

        void showAttPoints(
            const Object::Character& character,
            const Indent indent,
            bool accepted = false);

        Object::Attribute::Type pickAttribute(
            const Object::Character& character,
            const Indent indent);

    }
}

#endif // !MENU_ATTRIBUTE_HPP
