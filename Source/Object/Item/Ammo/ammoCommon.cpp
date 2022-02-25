
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammoCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Ammo__Type toAmmoType(fbAmmo::FB_AmmoType id)
{
    static unordered_map<fbAmmo::FB_AmmoType, Ammo__Type> map{
        { fbAmmo::FB_AmmoType_INVALID, Ammo__Type::INVALID },
        { fbAmmo::FB_AmmoType_NONE, Ammo__Type::NONE },
        { fbAmmo::FB_AmmoType_A_5_56, Ammo__Type::A_5_56 },
        { fbAmmo::FB_AmmoType_A_7_62, Ammo__Type::A_7_62 },
        { fbAmmo::FB_AmmoType_SPIKES, Ammo__Type::SPIKES },
        { fbAmmo::FB_AmmoType_BOLTS, Ammo__Type::BOLTS },
        { fbAmmo::FB_AmmoType_A_9_MM, Ammo__Type::A_9_MM },
        { fbAmmo::FB_AmmoType_A_D45, Ammo__Type::A_D45 },
        { fbAmmo::FB_AmmoType_A_D38, Ammo__Type::A_D38 },
        { fbAmmo::FB_AmmoType_A_D30_06, Ammo__Type::A_D30_06 },
        { fbAmmo::FB_AmmoType_A_D50, Ammo__Type::A_D50 },
        { fbAmmo::FB_AmmoType_SHOTGUN_SHELLS, Ammo__Type::SHOTGUN_SHELLS },
        { fbAmmo::FB_AmmoType_FLAMETHROWER_FUEL, Ammo__Type::FLAMETHROWER_FUEL },
        { fbAmmo::FB_AmmoType_ENERGY_CELLS, Ammo__Type::ENERGY_CELLS },
        { fbAmmo::FB_AmmoType_FROZEN_FERRET, Ammo__Type::FROZEN_FERRET },
        { fbAmmo::FB_AmmoType_ROCKET, Ammo__Type::ROCKET },
        { fbAmmo::FB_AmmoType_TACTICAL_NUKE, Ammo__Type::TACTICAL_NUKE }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
