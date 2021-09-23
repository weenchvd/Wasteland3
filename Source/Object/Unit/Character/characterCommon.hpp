
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_COMMON_HPP
#define CHARACTER_COMMON_HPP

#include"unitCommon.hpp"

namespace Game
{
    namespace Object
    {
        enum class CharacterModel : CommonUnitBase {
            INVALID,                        /// invalid model, must be the first
            MINIMUM,                        // minimum valid stats

            RANGER_COMMON,

            NUMBER_OF_MODELS                /// must be the last
        };

        enum class CharacterType : unsigned char {
            INVALID,                        /// invalid class, must be the first

            RANGER,
            COMPANION
        };

    }
}

#endif // !CHARACTER_COMMON_HPP
