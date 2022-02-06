
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include"factory.hpp"
#include<memory>
#include<assert.h>

namespace game {
namespace global {

class Locator {
public:
    static void initialize();

    static bool isInitialized() { return initialized_; }

    static const global::Factory& getFactory() noexcept {
        return factory_;
    }

    static global::PlainText& getPlainText() noexcept {
        assert(option_ != nullptr);
        return *plainText_;
    }

    static global::Option& getOption() noexcept {
        assert(option_ != nullptr);
        return *option_;
    }

private:
    static global::Factory                                  factory_;
    static std::unique_ptr<global::PlainText>               plainText_;
    static std::unique_ptr<global::Option>                  option_;

    static bool                                             initialized_;
};

} // namespace global
} // namespace game

#endif // !LOCATOR_HPP
