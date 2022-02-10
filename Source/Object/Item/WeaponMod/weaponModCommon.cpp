
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weaponModCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

WeaponMod__Model toWeaponModModel(std::string& key)
{
    static unordered_map<string, WeaponMod__Model> map;
    map.emplace("INVALID", WeaponMod__Model::INVALID);
    map.emplace("BarShort", WeaponMod__Model::BARREL_SHORTENED);
    map.emplace("BarLight", WeaponMod__Model::BARREL_LIGHTWEIGHT);
    map.emplace("BarHamRifled", WeaponMod__Model::BARREL_HAMMERFORGE_RIFLED);
    map.emplace("BarTitCobalt", WeaponMod__Model::BARREL_TITANIUM_COBALT);
    map.emplace("BarBroachRifled", WeaponMod__Model::BARREL_BROACH_RIFLED);
    map.emplace("BarColumbium", WeaponMod__Model::BARREL_COLUMBIUM);
    map.emplace("BarCutRifled", WeaponMod__Model::BARREL_CUT_RIFLED);
    map.emplace("BarAlloy", WeaponMod__Model::BARREL_ALLOY);
    map.emplace("MagQuickfire", WeaponMod__Model::MAG_QUICKFIRE);
    map.emplace("MagAdvMaterials", WeaponMod__Model::MAG_ADVANCED_MATERIALS);
    map.emplace("MagOversized", WeaponMod__Model::MAG_OVERSIZED);
    map.emplace("MagMaxCapacity", WeaponMod__Model::MAG_MAX_CAPACITY);
    map.emplace("MagExtended", WeaponMod__Model::MAG_EXTENDED);
    map.emplace("MagLong", WeaponMod__Model::MAG_LONG);
    return map.at(key);
}

WeaponMod__Type toWeaponModType(std::string& key)
{
    static unordered_map<string, WeaponMod__Type> map;
    map.emplace("INVALID", WeaponMod__Type::INVALID);
    map.emplace("Choke", WeaponMod__Type::CHOKE);
    map.emplace("Bar", WeaponMod__Type::BARREL);
    map.emplace("UndBar", WeaponMod__Type::UNDERBARREL);
    map.emplace("Scope", WeaponMod__Type::SCOPE);
    map.emplace("Mag", WeaponMod__Type::MAGAZINE);
    map.emplace("Weight", WeaponMod__Type::WEIGHT);
    map.emplace("Handle", WeaponMod__Type::HANDLE);
    return map.at(key);
}

} // namespace object
} // namespace game
