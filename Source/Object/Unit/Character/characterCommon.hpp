
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_COMMON_HPP
#define CHARACTER_COMMON_HPP

#include"bidirectionalMap.hpp"
#include"characterModelFB_generated.h"
#include"characterTypeFB_generated.h"
#include"unitCommon.hpp"

namespace game {
namespace object {

enum class Character__Model : UnitBaseType {
    __INVALID = -1,                 /// invalid, must be the first
    // vvv TYPES vvv
    RANGER_TEMPLATE,

    COMPANION_SPIKE,
    // ^^^ TYPES ^^^
    __NUMBER_OF,
    __END                           /// must be the last
};

enum class Character__Type : char {
    __INVALID = -1,                 /// invalid, must be the first
    // vvv TYPES vvv
    RANGER,
    COMPANION,
    // ^^^ TYPES ^^^
    __NUMBER_OF,
    __END                           /// must be the last
};

using CharacterModelBiMap = common::BidirectionalMap<
    Character__Model, Character__Model::__INVALID,
    fbCharacter::FB_CharacterModel, fbCharacter::FB_CharacterModel::FB_CharacterModel_INVALID
>;

///************************************************************************************************

Character__Model toCharacterModel(fbCharacter::FB_CharacterModel id);

Character__Type toCharacterType(fbCharacter::FB_CharacterType id);

} // namespace object
} // namespace game

#endif // !CHARACTER_COMMON_HPP
