
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_COMMON_HPP
#define CHARACTER_COMMON_HPP

#include"unitCommon.hpp"

namespace Game {
namespace Object {

enum class Character__Model : UnitBaseType {
    INVALID = -1,                   /// invalid, must be the first
    MINIMUM,                        // minimum valid stats

    RANGER_COMMON,

    NUMBER_OF                       /// must be the last
};

enum class Character__Type : char {
    INVALID = -1,                   /// invalid, must be the first

    RANGER,
    COMPANION,

    NUMBER_OF                       /// must be the last
};

} // namespace Object
} // namespace Game

#endif // !CHARACTER_COMMON_HPP
