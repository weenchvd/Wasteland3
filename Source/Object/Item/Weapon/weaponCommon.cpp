
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"weaponCommon.hpp"
#include<unordered_map>
#include<utility>

namespace game {
namespace object {

using namespace std;

bool isCompatible(Weapon__Type id1, Weapon__Type id2)
{
    if (common::isValidEnum(id1) && common::isValidEnum(id2)) {
        if (id1 == id2) return true;
        return false;
    }
    if (id1 > Weapon__Type::NUMBER_OF && id2 > Weapon__Type::NUMBER_OF) {
        return false;
    }
    if (id2 > Weapon__Type::NUMBER_OF) {
        swap(id1, id2);
    }
    switch (id1) {
    case Weapon__Type::GROUP_ANY:
        return isAny(id2);
    default:
        return false;
    }
}

Weapon__Model toWeaponModel(fbWeapon::FB_WeaponModel id)
{
    static unordered_map<fbWeapon::FB_WeaponModel, Weapon__Model> map{
        { fbWeapon::FB_WeaponModel_INVALID, Weapon__Model::INVALID },
        { fbWeapon::FB_WeaponModel_AR_KALASH97, Weapon__Model::AR_KALASH97 },
        { fbWeapon::FB_WeaponModel_AR_SOCOM, Weapon__Model::AR_SOCOM },
        { fbWeapon::FB_WeaponModel_SMG_RIPPER, Weapon__Model::SMG_RIPPER }
    };
    return map.at(id);
}

Weapon__Type toWeaponType(fbWeapon::FB_WeaponType id)
{
    static unordered_map<fbWeapon::FB_WeaponType, Weapon__Type> map{
        { fbWeapon::FB_WeaponType_INVALID, Weapon__Type::INVALID },
        { fbWeapon::FB_WeaponType_AR, Weapon__Type::AR },
        { fbWeapon::FB_WeaponType_SMG, Weapon__Type::SMG },
        { fbWeapon::FB_WeaponType_SEMI_AUTO_PISTOL, Weapon__Type::SEMI_AUTO_PISTOL },
        { fbWeapon::FB_WeaponType_REVOLVER, Weapon__Type::REVOLVER },
        { fbWeapon::FB_WeaponType_AUTO_SHOTGUN, Weapon__Type::AUTO_SHOTGUN },
        { fbWeapon::FB_WeaponType_PUMP_SHOTGUN, Weapon__Type::PUMP_SHOTGUN },
        { fbWeapon::FB_WeaponType_SNIPER, Weapon__Type::SNIPER },
        { fbWeapon::FB_WeaponType_FLAMETHROWER, Weapon__Type::FLAMETHROWER },
        { fbWeapon::FB_WeaponType_HMG, Weapon__Type::HMG },
        { fbWeapon::FB_WeaponType_EXPLOSIVE, Weapon__Type::EXPLOSIVE },
        { fbWeapon::FB_WeaponType_SCIENCE, Weapon__Type::SCIENCE },
        { fbWeapon::FB_WeaponType_BLADED, Weapon__Type::BLADED },
        { fbWeapon::FB_WeaponType_BLUNT, Weapon__Type::BLUNT },
        { fbWeapon::FB_WeaponType_BRAWLING, Weapon__Type::BRAWLING },
        { fbWeapon::FB_WeaponType_GROUP_ANY, Weapon__Type::GROUP_ANY }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
