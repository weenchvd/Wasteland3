
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"initialization.hpp"
#include"locator.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<assert.h>

namespace game {
namespace global {

using namespace std;

void initializeGame()
{
    global::Locator::initialize();

    object::Character::initialize();
    object::Weapon::initialize();
    object::WeaponMod::initializeReference();
}

} // namespace global
} // namespace game
