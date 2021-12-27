
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include<type_traits>

namespace Game
{
    namespace Global
    {
        using namespace std;

        Game::Global::Factory Locator::factory_ = Game::Global::Factory{};

        unique_ptr<Game::Global::PlainText> Locator::plainText_
            = Locator::getFactory().createPlainText<Game::Global::PlainText>(
                Game::Global::PlainText::Language::ENGLISH);

        unique_ptr<Game::Global::Option> Locator::option_
            = Locator::getFactory().createOption();

    }
}
