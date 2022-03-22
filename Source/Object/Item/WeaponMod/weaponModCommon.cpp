
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weaponModCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

bool isCompatible(WeaponMod__Type id1, WeaponMod__Type id2)
{
    if (id1 == id2) return true;
    return false;
}

WeaponMod__Model toWeaponModModel(fbWeaponMod::FB_WeaponModModel id)
{
    static unordered_map<fbWeaponMod::FB_WeaponModModel, WeaponMod__Model> map{
        { fbWeaponMod::FB_WeaponModModel_INVALID, WeaponMod__Model::INVALID },
        { fbWeaponMod::FB_WeaponModModel_BARREL_SHORTENED, WeaponMod__Model::BARREL_SHORTENED },
        { fbWeaponMod::FB_WeaponModModel_BARREL_LIGHTWEIGHT, WeaponMod__Model::BARREL_LIGHTWEIGHT },
        { fbWeaponMod::FB_WeaponModModel_BARREL_HAMMERFORGE_RIFLED, WeaponMod__Model::BARREL_HAMMERFORGE_RIFLED },
        { fbWeaponMod::FB_WeaponModModel_BARREL_TITANIUM_COBALT, WeaponMod__Model::BARREL_TITANIUM_COBALT },
        { fbWeaponMod::FB_WeaponModModel_BARREL_BROACH_RIFLED, WeaponMod__Model::BARREL_BROACH_RIFLED },
        { fbWeaponMod::FB_WeaponModModel_BARREL_COLUMBIUM, WeaponMod__Model::BARREL_COLUMBIUM },
        { fbWeaponMod::FB_WeaponModModel_BARREL_CUT_RIFLED, WeaponMod__Model::BARREL_CUT_RIFLED },
        { fbWeaponMod::FB_WeaponModModel_BARREL_ALLOY, WeaponMod__Model::BARREL_ALLOY },

        { fbWeaponMod::FB_WeaponModModel_MAG_QUICKFIRE, WeaponMod__Model::MAG_QUICKFIRE },
        { fbWeaponMod::FB_WeaponModModel_MAG_ADVANCED_MATERIALS, WeaponMod__Model::MAG_ADVANCED_MATERIALS },
        { fbWeaponMod::FB_WeaponModModel_MAG_OVERSIZED, WeaponMod__Model::MAG_OVERSIZED },
        { fbWeaponMod::FB_WeaponModModel_MAG_MAX_CAPACITY, WeaponMod__Model::MAG_MAX_CAPACITY },
        { fbWeaponMod::FB_WeaponModModel_MAG_EXTENDED, WeaponMod__Model::MAG_EXTENDED },
        { fbWeaponMod::FB_WeaponModModel_MAG_LONG, WeaponMod__Model::MAG_LONG },

        { fbWeaponMod::FB_WeaponModModel_SCOPE_FARSIGHT, WeaponMod__Model::SCOPE_FARSIGHT },
        { fbWeaponMod::FB_WeaponModModel_SCOPE_DEADEYE, WeaponMod__Model::SCOPE_DEADEYE },
        { fbWeaponMod::FB_WeaponModModel_SCOPE_38MM, WeaponMod__Model::SCOPE_38MM },
        { fbWeaponMod::FB_WeaponModModel_SCOPE_32MM, WeaponMod__Model::SCOPE_32MM },
        { fbWeaponMod::FB_WeaponModModel_SCOPE_21MM, WeaponMod__Model::SCOPE_21MM },
        { fbWeaponMod::FB_WeaponModModel_SCOPE_HOLOGRAPHIC, WeaponMod__Model::SCOPE_HOLOGRAPHIC },
        { fbWeaponMod::FB_WeaponModModel_SCOPE_RED_DOT, WeaponMod__Model::SCOPE_RED_DOT },
        { fbWeaponMod::FB_WeaponModModel_SCOPE_REFLEX, WeaponMod__Model::SCOPE_REFLEX },

        { fbWeaponMod::FB_WeaponModModel_UB_HE_FUSE_LINKAGE, WeaponMod__Model::UB_HE_FUSE_LINKAGE },
        { fbWeaponMod::FB_WeaponModModel_UB_PLASMA_LINKAGE, WeaponMod__Model::UB_PLASMA_LINKAGE },
        { fbWeaponMod::FB_WeaponModModel_UB_CRYOCELL_LINKAGE, WeaponMod__Model::UB_CRYOCELL_LINKAGE },
        { fbWeaponMod::FB_WeaponModModel_UB_INCENDIARY_LINKAGE, WeaponMod__Model::UB_INCENDIARY_LINKAGE },
        { fbWeaponMod::FB_WeaponModModel_UB_SWAT_LIGHT, WeaponMod__Model::UB_SWAT_LIGHT },
        { fbWeaponMod::FB_WeaponModModel_UB_TACTICAL_LIGHT, WeaponMod__Model::UB_TACTICAL_LIGHT },
        { fbWeaponMod::FB_WeaponModModel_UB_UNDERBARREL_LIGHT, WeaponMod__Model::UB_UNDERBARREL_LIGHT },
        { fbWeaponMod::FB_WeaponModModel_UB_COMP_ASSISTED_LS, WeaponMod__Model::UB_COMP_ASSISTED_LS },
        { fbWeaponMod::FB_WeaponModModel_UB_ULTRAVIOLET_LS, WeaponMod__Model::UB_ULTRAVIOLET_LS },
        { fbWeaponMod::FB_WeaponModModel_UB_SPEC_OPS_LS, WeaponMod__Model::UB_SPEC_OPS_LS },
        { fbWeaponMod::FB_WeaponModModel_UB_LASER_SIGHT, WeaponMod__Model::UB_LASER_SIGHT }
    };
    return map.at(id);
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
