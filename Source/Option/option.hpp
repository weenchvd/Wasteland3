
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTION_HPP
#define OPTION_HPP

#include"common.hpp"
#include"plainText.hpp"
#include<assert.h>
#include<memory>
#include<utility>

namespace Game
{
    namespace Global
    {
        class Factory;

        class Option {
        public:
            using Language      = Game::Global::PlainText::Language;

            friend Factory;

        protected:
            Option() noexcept;

        public:
            Option(const Option&) = delete;
            Option& operator=(const Option&) = delete;

            bool isModified() const noexcept;

            void accept() noexcept;

            void reject() noexcept;

        public:
            Game::Global::PlainText::Language getLanguage() const noexcept;

            void setLanguage(Game::Global::PlainText::Language lang) noexcept;

        private:
            std::pair<Language, bool>       lang_;
        };

        ///------------------------------------------------------------------------------------------------

        inline PlainText::Language Option::getLanguage() const noexcept
        {
            return lang_.first;
        }

        inline void Option::setLanguage(PlainText::Language lang) noexcept
        {
            assert(Common::isValidEnum(lang));
            lang_ = { lang, true };
        }

    }
}

#endif // !OPTION_HPP
