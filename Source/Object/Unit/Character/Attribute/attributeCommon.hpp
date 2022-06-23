
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_COMMON_HPP
#define ATTRIBUTE_COMMON_HPP

#include"attributeTypeFB_generated.h"

namespace game {
namespace object {

enum class Attribute__Type : char {
    __INVALID = -1,                 /// invalid, must be the first
    // vvv TYPES vvv
    COORDINATION,
    LUCK,
    AWARENESS,
    STRENGTH,
    SPEED,
    INTELLIGENCE,
    CHARISMA,
    // ^^^ TYPES ^^^
    __NUMBER_OF,
    __END                           /// must be the last
};

///************************************************************************************************

Attribute__Type toAttributeType(fbAttribute::FB_AttributeType id);

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_COMMON_HPP
