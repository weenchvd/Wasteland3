
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weaponModCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

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
        { fbWeaponMod::FB_WeaponModModel_MAG_LONG, WeaponMod__Model::MAG_LONG }
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
