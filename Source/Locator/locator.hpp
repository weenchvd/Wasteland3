
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include"factory.hpp"
#include<memory>
#include<assert.h>

namespace Game {
namespace Global {

class Locator {
public:
    static void initialize();

    static bool isInitialized() { return initialized_; }

    static const Game::Global::Factory& getFactory() noexcept {
        return factory_;
    }

    static Game::Global::PlainText& getPlainText() noexcept {
        assert(option_ != nullptr);
        return *plainText_;
    }

    static Game::Global::Option& getOption() noexcept {
        assert(option_ != nullptr);
        return *option_;
    }

private:
    static Game::Global::Factory                            factory_;
    static std::unique_ptr<Game::Global::PlainText>         plainText_;
    static std::unique_ptr<Game::Global::Option>            option_;

    static bool                                             initialized_;
};

} // namespace Global
} // namespace Game

#endif // !LOCATOR_HPP
