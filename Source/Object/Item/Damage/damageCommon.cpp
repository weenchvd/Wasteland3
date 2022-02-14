
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
    static unordered_map<string, Damage__Type> map{
        { "INVALID", Damage__Type::INVALID },
        { "Norm", Damage__Type::NORMAL },
        { "Fire", Damage__Type::FIRE },
        { "Cold", Damage__Type::COLD },
        { "Ener", Damage__Type::ENERGY },
        { "Expl", Damage__Type::EXPLOSIVE },
    };
    return map.at(key);
}

} // namespace object
} // namespace game
