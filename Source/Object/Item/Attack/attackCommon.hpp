
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTACK_COMMON_HPP
#define ATTACK_COMMON_HPP

#include"attackFB_generated.h"

namespace game {
namespace object {

enum class Attack__Type : char {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    SINGLE_TARGET,
    CHAIN_OF_SINGLE_TARGETS,
    STRAIGHT_LINE,
    CONICAL_AREA_BEHIND_TARGET,
    CONICAL_AREA,
    REMOTE_CIRCULAR_AREA,
    CIRCULAR_AREA,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

///************************************************************************************************

Attack__Type toAttackType(fbAttack::FB_AttackType id);

} // namespace object
} // namespace game

#endif // !ATTACK_COMMON_HPP
