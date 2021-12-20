
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
        enum class DamageType : unsigned char {
            INVALID,                        /// invalid type, must be the first

            NORMAL,
            FIRE,
            COLD,
            ENERGY,
            EXPLOSIVE
        };

    }
}

#endif // !DAMAGE_COMMON_HPP
