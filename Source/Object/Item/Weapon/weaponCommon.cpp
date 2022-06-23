
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"weaponCommon.hpp"
#include<unordered_map>
#include<utility>

namespace game {
namespace common {

object::WeaponModelBiMap::map_t     object::WeaponModelBiMap::map_;
bool                                object::WeaponModelBiMap::initialized_{ false };

///************************************************************************************************

void object::WeaponModelBiMap::init()
{
    using object::Weapon__Model;
    using fbWeapon::FB_WeaponModel;

    add(Weapon__Model::__INVALID, FB_WeaponModel::FB_WeaponModel_INVALID);

    add(Weapon__Model::AR_KALASH97, FB_WeaponModel::FB_WeaponModel_AR_KALASH97);
    add(Weapon__Model::AR_SOCOM, FB_WeaponModel::FB_WeaponModel_AR_SOCOM);
    add(Weapon__Model::SMG_RIPPER, FB_WeaponModel::FB_WeaponModel_SMG_RIPPER);
}

} // namespace common

///************************************************************************************************

namespace object {

using namespace std;

bool isCompatible(Weapon__Type id1, Weapon__Type id2)
{
    if (common::isValidEnum(id1) && common::isValidEnum(id2)) {
        if (id1 == id2) return true;
        return false;
    }
    if (common::isValidEnumAux(id1) && common::isValidEnumAux(id2)) {
        return false;
    }
    if (common::isValidEnumAux(id2)) {
        swap(id1, id2);
    }
    switch (id1) {
    case Weapon__Type::GROUP_ANY:
        return isAny(id2);
    default:
        return false;
    }
}

Weapon__Type toWeaponType(fbWeapon::FB_WeaponType id)
{
    static unordered_map<fbWeapon::FB_WeaponType, Weapon__Type> map{
        { fbWeapon::FB_WeaponType_INVALID, Weapon__Type::__INVALID },
        { fbWeapon::FB_WeaponType_AR, Weapon__Type::AR },
        { fbWeapon::FB_WeaponType_SMG, Weapon__Type::SMG },
        { fbWeapon::FB_WeaponType_SEMI_AUTO_PISTOL, Weapon__Type::SEMI_AUTO_PISTOL },
        { fbWeapon::FB_WeaponType_REVOLVER, Weapon__Type::REVOLVER },
        { fbWeapon::FB_WeaponType_AUTO_SHOTGUN, Weapon__Type::AUTO_SHOTGUN },
        { fbWeapon::FB_WeaponType_PUMP_SHOTGUN, Weapon__Type::PUMP_SHOTGUN },
        { fbWeapon::FB_WeaponType_SNIPER, Weapon__Type::SNIPER },
        { fbWeapon::FB_WeaponType_FLAMETHROWER, Weapon__Type::FLAMETHROWER },
        { fbWeapon::FB_WeaponType_HMG, Weapon__Type::HMG },
        { fbWeapon::FB_WeaponType_ROCKET, Weapon__Type::ROCKET },
        { fbWeapon::FB_WeaponType_LASER, Weapon__Type::LASER },
        { fbWeapon::FB_WeaponType_BLADED, Weapon__Type::BLADED },
        { fbWeapon::FB_WeaponType_BLUNT, Weapon__Type::BLUNT },
        { fbWeapon::FB_WeaponType_BRAWLING, Weapon__Type::BRAWLING },
        { fbWeapon::FB_WeaponType_GROUP_ANY, Weapon__Type::GROUP_ANY }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
