
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammoCommon.hpp"
#include<unordered_map>

namespace game {
namespace common {

object::AmmoTypeBiMap::map_t        object::AmmoTypeBiMap::map_;
bool                                object::AmmoTypeBiMap::initialized_{ false };

///************************************************************************************************

void object::AmmoTypeBiMap::init()
{
    using object::Ammo__Type;
    using fbAmmo::FB_AmmoType;

    add(Ammo__Type::__INVALID, FB_AmmoType::FB_AmmoType_INVALID);

    add(Ammo__Type::NONE, FB_AmmoType::FB_AmmoType_NONE);
    add(Ammo__Type::A_5_56, FB_AmmoType::FB_AmmoType_A_5_56);
    add(Ammo__Type::A_7_62, FB_AmmoType::FB_AmmoType_A_7_62);
    add(Ammo__Type::SPIKES, FB_AmmoType::FB_AmmoType_SPIKES);
    add(Ammo__Type::BOLTS, FB_AmmoType::FB_AmmoType_BOLTS);
    add(Ammo__Type::A_9_MM, FB_AmmoType::FB_AmmoType_A_9_MM);
    add(Ammo__Type::A_D45, FB_AmmoType::FB_AmmoType_A_D45);
    add(Ammo__Type::A_D38, FB_AmmoType::FB_AmmoType_A_D38);
    add(Ammo__Type::A_D30_06, FB_AmmoType::FB_AmmoType_A_D30_06);
    add(Ammo__Type::A_D50, FB_AmmoType::FB_AmmoType_A_D50);
    add(Ammo__Type::SHOTGUN_SHELLS, FB_AmmoType::FB_AmmoType_SHOTGUN_SHELLS);
    add(Ammo__Type::FLAMETHROWER_FUEL, FB_AmmoType::FB_AmmoType_FLAMETHROWER_FUEL);
    add(Ammo__Type::ENERGY_CELLS, FB_AmmoType::FB_AmmoType_ENERGY_CELLS);
    add(Ammo__Type::FROZEN_FERRET, FB_AmmoType::FB_AmmoType_FROZEN_FERRET);
    add(Ammo__Type::ROCKET, FB_AmmoType::FB_AmmoType_ROCKET);
    add(Ammo__Type::TACTICAL_NUKE, FB_AmmoType::FB_AmmoType_TACTICAL_NUKE);
}

} // namespace common
} // namespace game
