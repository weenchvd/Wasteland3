
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_COMMON_HPP
#define WEAPON_MOD_COMMON_HPP

#include"itemCommon.hpp"

namespace Game
{
    namespace Object
    {
        enum class WeaponModModel : CommonItemBase {
            INVALID,                        /// invalid model, must be the first

            BARREL_SHORTENED,
            BARREL_LIGHTWEIGHT,
            BARREL_HAMMERFORGE_RIFLED,
            BARREL_TITANIUM_COBALT,
            BARREL_BROACH_RIFLED,
            BARREL_COLUMBIUM,
            BARREL_CUT_RIFLED,
            BARREL_ALLOY,

            MAG_QUICKFIRE,
            MAG_ADVANCED_MATERIALS,
            MAG_OVERSIZED,
            MAG_MAX_CAPACITY,
            MAG_EXTENDED,
            MAG_LONG,

            NUMBER_OF_MODELS                /// must be the last
        };
        
        enum class WeaponModType : unsigned char {
            INVALID,                        /// invalid class, must be the first
            ANY,                            // any type

            CHOKE,
            BARREL,
            UNDERBARREL,
            SCOPE,
            MAGAZINE,
            WEIGHT,
            HANDLE
        };

    }
}

#endif // !WEAPON_MOD_COMMON_HPP
