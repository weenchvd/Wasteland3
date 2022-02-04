
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"initialization.hpp"
#include"locator.hpp"
#include<assert.h>

namespace Game {
namespace Global {

using namespace std;

void initializeGame()
{
    Game::Global::Locator::initialize();
}

} // namespace Global
} // namespace Game
