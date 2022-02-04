
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_COMMON_HPP
#define WEAPON_COMMON_HPP

#include"itemCommon.hpp"

namespace Game {
namespace Object {

enum class Weapon__Model : ItemBaseType {
    INVALID = -1,                   /// invalid, must be the first
    MINIMUM,                        // minimum valid stats

    AR_KALASH97,
    AR_SOCOM,

    SMG_RIPPER,

    NUMBER_OF                       /// must be the last
};

enum class Weapon__Type : char {
    INVALID = -1,                   /// invalid, must be the first
    ANY,                            // any type

    AR,
    SMG,
    SEMI_AUTO_PISTOL,
    REVOLVER,
    AUTO_SHOTGUN,
    PUMP_SHOTGUN,
    SNIPER,
    FLAMETHROWER,
    HMG,
    EXPLOSIVE,
    SCIENCE,
    BLADED,
    BLUNT,
    BRAWLING,

    NUMBER_OF                       /// must be the last
};

} // namespace Object
} // namespace Game

#endif // !WEAPON_COMMON_HPP
