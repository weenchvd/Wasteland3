
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ARMOR_COMMON_HPP
#define ARMOR_COMMON_HPP

#include"itemCommon.hpp"

namespace Game
{
    namespace Object
    {
        enum class ArmorModel : ItemBaseType {
            INVALID,                        /// invalid model, must be the first



            NUMBER_OF_MODELS                /// must be the last
        };

        enum class ArmorType : unsigned char {
            INVALID,                        /// invalid class, must be the first

            HEAD,
            CHEST,
            LEG,
            UTILITY
        };

    }
}

#endif // !ARMOR_COMMON_HPP
