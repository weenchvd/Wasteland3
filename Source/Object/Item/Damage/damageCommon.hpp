
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DAMAGE_COMMON_HPP
#define DAMAGE_COMMON_HPP

#include"damageTypeFB_generated.h"

namespace game {
namespace object {

enum class Damage__Type : char {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    NORMAL,
    FIRE,
    COLD,
    ENERGY,
    EXPLOSIVE,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

///************************************************************************************************

Damage__Type toDamageType(fbDamage::FB_DamageType id);

} // namespace object
} // namespace game

#endif // !DAMAGE_COMMON_HPP
