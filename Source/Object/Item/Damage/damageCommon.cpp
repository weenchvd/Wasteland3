
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"damageCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Damage__Type toDamageType(std::string& key)
{
    static unordered_map<string, Damage__Type> map;
    map.emplace("INVALID", Damage__Type::INVALID);
    map.emplace("Norm", Damage__Type::NORMAL);
    map.emplace("Fire", Damage__Type::FIRE);
    map.emplace("Cold", Damage__Type::COLD);
    map.emplace("Ener", Damage__Type::ENERGY);
    map.emplace("Expl", Damage__Type::EXPLOSIVE);
    return map.at(key);
}

} // namespace object
} // namespace game
