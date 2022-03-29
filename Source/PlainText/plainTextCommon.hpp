
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAINTEXT_COMMON_HPP
#define PLAINTEXT_COMMON_HPP

namespace game {
namespace global {

enum class PlainText__Language : char {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    EN,                             // english
    RU,                             // russian
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

} // namespace global
} // namespace game

#endif // !PLAINTEXT_COMMON_HPP
