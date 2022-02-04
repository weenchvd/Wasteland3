
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAINTEXT_ENUM_HPP
#define PLAINTEXT_ENUM_HPP

namespace Game {
namespace Global {

using PlainTextBaseType             = int;

enum class PlainText__Language : char {
    INVALID = -1,                   /// invalid, must be the first
            
    EN,                             // english
    RU,                             // russian

    NUMBER_OF                       /// must be the last
};

enum class PlainText__General : PlainTextBaseType {
    INVALID = -1,                   /// invalid, must be the first
            
    INVALID_ENUM,
    NO_DATA,

    NUMBER_OF                       /// must be the last
};

} // namespace Global
} // namespace Game

#endif // !PLAINTEXT_ENUM_HPP
