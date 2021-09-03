
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_COMMON_HPP
#define AMMO_COMMON_HPP

namespace Game
{
    namespace Object
    {
        enum class AmmoType : unsigned char {
            INVALID,                        /// invalid type, must be the first

            NONE,                           // without ammo
            A_5_56,                         // 5.56
            A_7_62                          // 7.62
        };

    }
}

#endif // !AMMO_COMMON_HPP
