
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_COMMON_HPP
#define ATTRIBUTE_COMMON_HPP

namespace Game
{
    namespace Object
    {
        enum class AttributeType : unsigned char {
            INVALID,                        /// invalid type, must be the first

            COORDINATION,
            LUCK,
            AWARENESS,
            STRENGTH,
            SPEED,
            INTELLIGENCE,
            CHARISMA,

            NUMBER_OF                       /// must be the last
        };

    }
}

#endif // !ATTRIBUTE_COMMON_HPP
