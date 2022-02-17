
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"damageCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Damage__Type toDamageType(fbDamage::FB_DamageType id)
{
    static unordered_map<fbDamage::FB_DamageType, Damage__Type> map{
        { fbDamage::FB_DamageType_INVALID, Damage__Type::INVALID },
        { fbDamage::FB_DamageType_NORMAL, Damage__Type::NORMAL },
        { fbDamage::FB_DamageType_FIRE, Damage__Type::FIRE },
        { fbDamage::FB_DamageType_COLD, Damage__Type::COLD },
        { fbDamage::FB_DamageType_ENERGY, Damage__Type::ENERGY },
        { fbDamage::FB_DamageType_EXPLOSIVE, Damage__Type::EXPLOSIVE }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
