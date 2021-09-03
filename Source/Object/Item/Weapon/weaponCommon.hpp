
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_COMMON_HPP
#define WEAPON_COMMON_HPP

#include"itemCommon.hpp"

namespace Game
{
    namespace Object
    {
        enum class WeaponModel : CommonItemBase {
            INVALID,                        /// invalid model, must be the first

            AR_KALASH97,
            AR_SOCOM,

            SMG_RIPPER,

            NUMBER_OF_MODELS                /// must be the last
        };

        enum class WeaponType : unsigned char {
            INVALID,                        /// invalid class, must be the first

            AR,
            SMG,
            HANDGUN,
            SHOTGUN,
            SNIPER,
            FLAMETHROWER,
            HMG,
            EXPLOSIVE,
            SCIENCE,
            BLADED,
            BLUNT,
            BRAWLING
        };

    }
}

#endif // !WEAPON_COMMON_HPP
