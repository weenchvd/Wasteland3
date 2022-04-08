
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_COMMON_HPP
#define WEAPON_MOD_COMMON_HPP

#include"itemCommon.hpp"
#include"weaponModModelFB_generated.h"
#include"weaponModTypeFB_generated.h"

namespace game {
namespace object {

enum class WeaponMod__Model : ItemBaseType {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    BARREL_SHORTENED,
    BARREL_LIGHTWEIGHT,
    BARREL_HAMMERFORGE_RIFLED,
    BARREL_BROACH_RIFLED,
    BARREL_CUT_RIFLED,
    BARREL_TITANIUM_COBALT,
    BARREL_COLUMBIUM,
    BARREL_ALLOY,
    BARREL_PHASE_SILENCER,
    BARREL_SOUND_SUPRESSOR,
    BARREL_BLAST_MUFFLER,

    MAG_QUICKFIRE,
    MAG_ADVANCED_MATERIALS,
    MAG_OVERSIZED,
    MAG_MAX_CAPACITY,
    MAG_EXTENDED,
    MAG_LONG,

    SCOPE_FARSIGHT,
    SCOPE_DEADEYE,
    SCOPE_38MM,
    SCOPE_32MM,
    SCOPE_21MM,
    SCOPE_HOLOGRAPHIC,
    SCOPE_RED_DOT,
    SCOPE_REFLEX,

    UB_HE_FUSE_LINKAGE,
    UB_PLASMA_LINKAGE,
    UB_CRYOCELL_LINKAGE,
    UB_INCENDIARY_LINKAGE,
    ///UB_________LIGHT,
    UB_SWAT_LIGHT,
    UB_TACTICAL_LIGHT,
    UB_UNDERBARREL_LIGHT,
    UB_COMP_ASSISTED_LS,
    UB_ULTRAVIOLET_LS,
    UB_SPEC_OPS_LS,
    UB_LASER_SIGHT,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

enum class WeaponMod__Type : char {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    CHOKE,
    BARREL,
    UNDERBARREL,
    SCOPE,
    MAGAZINE,
    WEIGHT,
    HANDLE,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

///************************************************************************************************

// @brief Check if the types are compatible.
// @param "id1" - must be a type;
// @param "id2" - must be a type;
bool isCompatible(WeaponMod__Type id1, WeaponMod__Type id2);

WeaponMod__Model toWeaponModModel(fbWeaponMod::FB_WeaponModModel id);

WeaponMod__Type toWeaponModType(fbWeaponMod::FB_WeaponModType id);

} // namespace object
} // namespace game

#endif // !WEAPON_MOD_COMMON_HPP
