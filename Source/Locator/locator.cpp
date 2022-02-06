
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include<type_traits>

namespace game {
namespace global {

using namespace std;

global::Factory Locator::factory_;

unique_ptr<global::PlainText> Locator::plainText_;
unique_ptr<global::Option> Locator::option_;

bool Locator::initialized_{ false };

void Locator::initialize()
{
    if (isInitialized()) return;

    plainText_ = Locator::getFactory().createPlainText<global::PlainText>(
        global::PlainText::Language::EN);
    option_ = Locator::getFactory().createOption();

    initialized_ = true;
}

} // namespace global
} // namespace game
