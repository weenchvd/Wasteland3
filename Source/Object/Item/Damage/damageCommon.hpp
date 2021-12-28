
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DAMAGE_COMMON_HPP
#define DAMAGE_COMMON_HPP

namespace Game
{
    namespace Object
    {
        enum class Damage__Type : char {
            INVALID = -1,                   /// invalid, must be the first

            NORMAL,
            FIRE,
            COLD,
            ENERGY,
            EXPLOSIVE,

            NUMBER_OF                       /// must be the last
        };

    }
}

#endif // !DAMAGE_COMMON_HPP
