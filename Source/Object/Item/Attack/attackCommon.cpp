
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attackCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Attack__Type toAttackType(fbAttack::FB_AttackType id)
{
    static unordered_map<fbAttack::FB_AttackType, Attack__Type> map{
        { fbAttack::FB_AttackType_INVALID, Attack__Type::__INVALID },
        { fbAttack::FB_AttackType_SINGLE_TARGET, Attack__Type::SINGLE_TARGET },
        { fbAttack::FB_AttackType_CHAIN_OF_SINGLE_TARGETS, Attack__Type::CHAIN_OF_SINGLE_TARGETS },
        { fbAttack::FB_AttackType_STRAIGHT_LINE, Attack__Type::STRAIGHT_LINE },
        { fbAttack::FB_AttackType_CONICAL_AREA_BEHIND_TARGET, Attack__Type::CONICAL_AREA_BEHIND_TARGET },
        { fbAttack::FB_AttackType_CONICAL_AREA, Attack__Type::CONICAL_AREA },
        { fbAttack::FB_AttackType_REMOTE_CIRCULAR_AREA, Attack__Type::REMOTE_CIRCULAR_AREA },
        { fbAttack::FB_AttackType_CIRCULAR_AREA, Attack__Type::CIRCULAR_AREA }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
