
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"characterCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Character__Model toCharacterModel(fbCharacter::FB_CharacterModel id)
{
    static unordered_map<fbCharacter::FB_CharacterModel, Character__Model> map{
        { fbCharacter::FB_CharacterModel_INVALID, Character__Model::INVALID },
        { fbCharacter::FB_CharacterModel_RANGER_TEMPLATE, Character__Model::RANGER_TEMPLATE },
        { fbCharacter::FB_CharacterModel_COMPANION_SPIKE, Character__Model::COMPANION_SPIKE }
    };
    return map.at(id);
}

Character__Type toCharacterType(fbCharacter::FB_CharacterType id)
{
    static unordered_map<fbCharacter::FB_CharacterType, Character__Type> map{
        { fbCharacter::FB_CharacterType_INVALID, Character__Type::INVALID },
        { fbCharacter::FB_CharacterType_RANGER, Character__Type::RANGER },
        { fbCharacter::FB_CharacterType_COMPANION, Character__Type::COMPANION }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
