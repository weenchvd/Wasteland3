
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
        { fbAmmo::FB_AmmoType_A_7_62, Ammo__Type::A_7_62 }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
