
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include"factory.hpp"

namespace Game
{
    namespace Global
    {
        class Locator {
        public:
            static Factory& getFactory() noexcept {
                return factory;
            }

        private:
            static Factory                  factory;

        };

    }
}

#endif // !LOCATOR_HPP
