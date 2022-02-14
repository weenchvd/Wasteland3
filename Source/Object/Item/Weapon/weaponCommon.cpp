
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

Weapon__Model toWeaponModel(std::string& key)
{
    static unordered_map<string, Weapon__Model> map{
        { "INVALID", Weapon__Model::INVALID },
        { "Kalash97", Weapon__Model::AR_KALASH97 },
        { "Socom", Weapon__Model::AR_SOCOM },
        { "Ripper", Weapon__Model::SMG_RIPPER }
    };
    return map.at(key);
}

Weapon__Type toWeaponType(std::string& key)
{
    static unordered_map<string, Weapon__Type> map{
        { "INVALID", Weapon__Type::INVALID },
        { "AR", Weapon__Type::AR },
        { "SMG", Weapon__Type::SMG },
        { "Pistol", Weapon__Type::SEMI_AUTO_PISTOL },
        { "Revolver", Weapon__Type::REVOLVER },
        { "AutoSG", Weapon__Type::AUTO_SHOTGUN },
        { "PumpSG", Weapon__Type::PUMP_SHOTGUN },
        { "Sniper", Weapon__Type::SNIPER },
        { "FT", Weapon__Type::FLAMETHROWER },
        { "HMG", Weapon__Type::HMG },
        { "Explosive", Weapon__Type::EXPLOSIVE },
        { "Science", Weapon__Type::SCIENCE },
        { "Bladed", Weapon__Type::BLADED },
        { "Blunt", Weapon__Type::BLUNT },
        { "Brawling", Weapon__Type::BRAWLING },
        { "G_Any", Weapon__Type::GROUP_ANY }
    };
    return map.at(key);
}

} // namespace object
} // namespace game
