
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

inline bool isAny(Weapon__Type id)
{
    return common::isValidEnum(id);
}

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

Weapon__Model toWeaponModel(std::string& key)
{
    static unordered_map<string, Weapon__Model> map;
    map.emplace("INVALID", Weapon__Model::INVALID);
    map.emplace("Kalash97", Weapon__Model::AR_KALASH97);
    map.emplace("Socom", Weapon__Model::AR_SOCOM);
    map.emplace("Ripper", Weapon__Model::SMG_RIPPER);
    return map.at(key);
}

Weapon__Type toWeaponType(std::string& key)
{
    static unordered_map<string, Weapon__Type> map;
    map.emplace("INVALID", Weapon__Type::INVALID);
    map.emplace("AR", Weapon__Type::AR);
    map.emplace("SMG", Weapon__Type::SMG);
    map.emplace("Pistol", Weapon__Type::SEMI_AUTO_PISTOL);
    map.emplace("Revolver", Weapon__Type::REVOLVER);
    map.emplace("AutoSG", Weapon__Type::AUTO_SHOTGUN);
    map.emplace("PumpSG", Weapon__Type::PUMP_SHOTGUN);
    map.emplace("Sniper", Weapon__Type::SNIPER);
    map.emplace("FT", Weapon__Type::FLAMETHROWER);
    map.emplace("HMG", Weapon__Type::HMG);
    map.emplace("Explosive", Weapon__Type::EXPLOSIVE);
    map.emplace("Science", Weapon__Type::SCIENCE);
    map.emplace("Bladed", Weapon__Type::BLADED);
    map.emplace("Blunt", Weapon__Type::BLUNT);
    map.emplace("Brawling", Weapon__Type::BRAWLING);
    map.emplace("G_Any", Weapon__Type::GROUP_ANY);
    return map.at(key);
}

} // namespace object
} // namespace game
