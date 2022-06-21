
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_COMMON_HPP
#define AMMO_COMMON_HPP

#include"ammoTypeFB_generated.h"
#include"bidirectionalMap.hpp"

namespace game {
namespace object {

enum class Ammo__Type : char {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    NONE,                           // without ammo
    A_5_56,                         // 5.56mm ammo
    A_7_62,                         // 7.62mm ammo
    SPIKES,
    BOLTS,
    A_9_MM,                         // 9mm ammo
    A_D45,                          // .45 ammo
    A_D38,                          // .38 ammo
    A_D30_06,                       // .30-06 ammo
    A_D50,                          // .50 ammo
    SHOTGUN_SHELLS,
    FLAMETHROWER_FUEL,
    ENERGY_CELLS,
    FROZEN_FERRET,
    ROCKET,
    TACTICAL_NUKE,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

using AmmoTypeBiMap = common::BidirectionalMap<
    Ammo__Type, Ammo__Type::INVALID,
    fbAmmo::FB_AmmoType, fbAmmo::FB_AmmoType::FB_AmmoType_INVALID
>;

} // namespace object
} // namespace game

#endif // !AMMO_COMMON_HPP
