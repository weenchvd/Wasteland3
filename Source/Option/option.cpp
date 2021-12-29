
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"option.hpp"
#include"locator.hpp"
#include<type_traits>

namespace Game
{
    namespace Global
    {
        using namespace std;

        Option::Option()
        {}

        Game::Global::PlainText::Language Option::getLanguage() const noexcept
        {
            return Game::Global::Locator::getPlainText().getLanguage();
        }

        void Option::setLanguage(Game::Global::PlainText::Language lang) const noexcept
        {
            Game::Global::Locator::getPlainText().setLanguage(lang);
        }

    }
}
