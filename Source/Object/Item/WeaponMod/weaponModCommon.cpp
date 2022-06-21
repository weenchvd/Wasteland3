
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weaponModCommon.hpp"
#include<unordered_map>

namespace game {
namespace common {

object::WeaponModModelBiMap::map_t  object::WeaponModModelBiMap::map_;
bool                                object::WeaponModModelBiMap::initialized_{ false };

///************************************************************************************************

void object::WeaponModModelBiMap::init()
{
    using object::WeaponMod__Model;
    using fbWeaponMod::FB_WeaponModModel;

    add(WeaponMod__Model::INVALID, FB_WeaponModModel::FB_WeaponModModel_INVALID);

    add(WeaponMod__Model::BARREL_SHORTENED, FB_WeaponModModel::FB_WeaponModModel_BARREL_SHORTENED);
    add(WeaponMod__Model::BARREL_LIGHTWEIGHT, FB_WeaponModModel::FB_WeaponModModel_BARREL_LIGHTWEIGHT);
    add(WeaponMod__Model::BARREL_HAMMERFORGE_RIFLED, FB_WeaponModModel::FB_WeaponModModel_BARREL_HAMMERFORGE_RIFLED);
    add(WeaponMod__Model::BARREL_BROACH_RIFLED, FB_WeaponModModel::FB_WeaponModModel_BARREL_BROACH_RIFLED);
    add(WeaponMod__Model::BARREL_CUT_RIFLED, FB_WeaponModModel::FB_WeaponModModel_BARREL_CUT_RIFLED);
    add(WeaponMod__Model::BARREL_TITANIUM_COBALT, FB_WeaponModModel::FB_WeaponModModel_BARREL_TITANIUM_COBALT);
    add(WeaponMod__Model::BARREL_COLUMBIUM, FB_WeaponModModel::FB_WeaponModModel_BARREL_COLUMBIUM);
    add(WeaponMod__Model::BARREL_ALLOY, FB_WeaponModModel::FB_WeaponModModel_BARREL_ALLOY);
    add(WeaponMod__Model::BARREL_PHASE_SILENCER, FB_WeaponModModel::FB_WeaponModModel_BARREL_PHASE_SILENCER);
    add(WeaponMod__Model::BARREL_SOUND_SUPRESSOR, FB_WeaponModModel::FB_WeaponModModel_BARREL_SOUND_SUPRESSOR);
    add(WeaponMod__Model::BARREL_BLAST_MUFFLER, FB_WeaponModModel::FB_WeaponModModel_BARREL_BLAST_MUFFLER);

    add(WeaponMod__Model::MAG_QUICKFIRE, FB_WeaponModModel::FB_WeaponModModel_MAG_QUICKFIRE);
    add(WeaponMod__Model::MAG_ADVANCED_MATERIALS, FB_WeaponModModel::FB_WeaponModModel_MAG_ADVANCED_MATERIALS);
    add(WeaponMod__Model::MAG_OVERSIZED, FB_WeaponModModel::FB_WeaponModModel_MAG_OVERSIZED);
    add(WeaponMod__Model::MAG_MAX_CAPACITY, FB_WeaponModModel::FB_WeaponModModel_MAG_MAX_CAPACITY);
    add(WeaponMod__Model::MAG_EXTENDED, FB_WeaponModModel::FB_WeaponModModel_MAG_EXTENDED);
    add(WeaponMod__Model::MAG_LONG, FB_WeaponModModel::FB_WeaponModModel_MAG_LONG);

    add(WeaponMod__Model::SCOPE_FARSIGHT, FB_WeaponModModel::FB_WeaponModModel_SCOPE_FARSIGHT);
    add(WeaponMod__Model::SCOPE_DEADEYE, FB_WeaponModModel::FB_WeaponModModel_SCOPE_DEADEYE);
    add(WeaponMod__Model::SCOPE_38MM, FB_WeaponModModel::FB_WeaponModModel_SCOPE_38MM);
    add(WeaponMod__Model::SCOPE_32MM, FB_WeaponModModel::FB_WeaponModModel_SCOPE_32MM);
    add(WeaponMod__Model::SCOPE_21MM, FB_WeaponModModel::FB_WeaponModModel_SCOPE_21MM);
    add(WeaponMod__Model::SCOPE_HOLOGRAPHIC, FB_WeaponModModel::FB_WeaponModModel_SCOPE_HOLOGRAPHIC);
    add(WeaponMod__Model::SCOPE_RED_DOT, FB_WeaponModModel::FB_WeaponModModel_SCOPE_RED_DOT);
    add(WeaponMod__Model::SCOPE_REFLEX, FB_WeaponModModel::FB_WeaponModModel_SCOPE_REFLEX);

    add(WeaponMod__Model::UB_HE_FUSE_LINKAGE, FB_WeaponModModel::FB_WeaponModModel_UB_HE_FUSE_LINKAGE);
    add(WeaponMod__Model::UB_PLASMA_LINKAGE, FB_WeaponModModel::FB_WeaponModModel_UB_PLASMA_LINKAGE);
    add(WeaponMod__Model::UB_CRYOCELL_LINKAGE, FB_WeaponModModel::FB_WeaponModModel_UB_CRYOCELL_LINKAGE);
    add(WeaponMod__Model::UB_INCENDIARY_LINKAGE, FB_WeaponModModel::FB_WeaponModModel_UB_INCENDIARY_LINKAGE);
    add(WeaponMod__Model::UB_SWAT_LIGHT, FB_WeaponModModel::FB_WeaponModModel_UB_SWAT_LIGHT);
    add(WeaponMod__Model::UB_TACTICAL_LIGHT, FB_WeaponModModel::FB_WeaponModModel_UB_TACTICAL_LIGHT);
    add(WeaponMod__Model::UB_UNDERBARREL_LIGHT, FB_WeaponModModel::FB_WeaponModModel_UB_UNDERBARREL_LIGHT);
    add(WeaponMod__Model::UB_COMP_ASSISTED_LS, FB_WeaponModModel::FB_WeaponModModel_UB_COMP_ASSISTED_LS);
    add(WeaponMod__Model::UB_ULTRAVIOLET_LS, FB_WeaponModModel::FB_WeaponModModel_UB_ULTRAVIOLET_LS);
    add(WeaponMod__Model::UB_SPEC_OPS_LS, FB_WeaponModModel::FB_WeaponModModel_UB_SPEC_OPS_LS);
    add(WeaponMod__Model::UB_LASER_SIGHT, FB_WeaponModModel::FB_WeaponModModel_UB_LASER_SIGHT);
}

} // namespace common

///************************************************************************************************

namespace object {

using namespace std;

bool isCompatible(WeaponMod__Type id1, WeaponMod__Type id2)
{
    if (id1 == id2) return true;
    return false;
}

WeaponMod__Type toWeaponModType(fbWeaponMod::FB_WeaponModType id)
{
    static unordered_map<fbWeaponMod::FB_WeaponModType, WeaponMod__Type> map{
        { fbWeaponMod::FB_WeaponModType_INVALID, WeaponMod__Type::INVALID },
        { fbWeaponMod::FB_WeaponModType_CHOKE, WeaponMod__Type::CHOKE },
        { fbWeaponMod::FB_WeaponModType_BARREL, WeaponMod__Type::BARREL },
        { fbWeaponMod::FB_WeaponModType_UNDERBARREL, WeaponMod__Type::UNDERBARREL },
        { fbWeaponMod::FB_WeaponModType_SCOPE, WeaponMod__Type::SCOPE },
        { fbWeaponMod::FB_WeaponModType_MAGAZINE, WeaponMod__Type::MAGAZINE },
        { fbWeaponMod::FB_WeaponModType_WEIGHT, WeaponMod__Type::WEIGHT },
        { fbWeaponMod::FB_WeaponModType_HANDLE, WeaponMod__Type::HANDLE }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
