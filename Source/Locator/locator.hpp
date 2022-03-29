
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
private:
    Locator() noexcept {}

public:
    Locator(const Locator&) = delete;
    Locator& operator=(const Locator&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

public:
    static const global::Factory& getFactory() noexcept { return factory_; }

    static global::Options& getOptions() noexcept;

private:
    static global::Factory                                  factory_;
    static std::unique_ptr<global::Options>                 options_;
    static bool                                             initialized_;
};

///************************************************************************************************

inline global::Options& Locator::getOptions() noexcept {
    assert(options_ != nullptr);
    return *options_;
}

} // namespace global
} // namespace game

#endif // !LOCATOR_HPP
