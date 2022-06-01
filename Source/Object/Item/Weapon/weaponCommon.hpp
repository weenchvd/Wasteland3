
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_COMMON_HPP
#define WEAPON_COMMON_HPP

#include"itemCommon.hpp"
#include"weaponModelFB_generated.h"
#include"weaponTypeFB_generated.h"

namespace game {
namespace object {

enum class Weapon__Model : ItemBaseType {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    AR_KALASH97,
    AR_SOCOM,

    SMG_RIPPER,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

enum class Weapon__Type : char {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    AR,
    SMG,
    SEMI_AUTO_PISTOL,
    REVOLVER,
    AUTO_SHOTGUN,
    PUMP_SHOTGUN,
    SNIPER,
    FLAMETHROWER,
    HMG,
    ROCKET,
    LASER,
    BLADED,
    BLUNT,
    BRAWLING,
    // ^^^ TYPES ^^^
    NUMBER_OF,                      /// must be the last
    // vvv GROUPS vvv
    GROUP_ANY,                      // any type
    // ^^^ GROUPS ^^^
    END
};

///************************************************************************************************

// @brief Check if the type are valid.
inline bool isAny(Weapon__Type id)
{
    return common::isValidEnum(id);
}

// @brief Check if the types are compatible.
// @param "id1" - must be a type or a group;
// @param "id2" - must be a type;
bool isCompatible(Weapon__Type id1, Weapon__Type id2);

Weapon__Model toWeaponModel(fbWeapon::FB_WeaponModel id);

Weapon__Type toWeaponType(fbWeapon::FB_WeaponType id);

} // namespace object
} // namespace game

#endif // !WEAPON_COMMON_HPP
