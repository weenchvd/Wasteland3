
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"

namespace game {
namespace global {

using namespace std;

global::Factory                     Locator::factory_;
unique_ptr<global::Options>         Locator::options_;
bool                                Locator::initialized_{ false };

///************************************************************************************************

void Locator::initialize()
{
    if (isInitialized()) return;

    options_ = Locator::getFactory().createOptions();

    initialized_ = true;
}

} // namespace global
} // namespace game
