
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTION_HPP
#define OPTION_HPP

#include"plainText.hpp"
#include<memory>

namespace Game
{
    namespace Global
    {
        class Factory;

        class Option {
        public:
            friend Factory;

        protected:
            Option();

        public:
            Option(const Option&) = delete;
            Option& operator=(const Option&) = delete;

            ~Option() noexcept {}

            Game::Global::PlainText::Language getLanguage() const noexcept;

            void setLanguage(Game::Global::PlainText::Language lang) const noexcept;

        private:

        };

    }
}

#endif // !OPTION_HPP
