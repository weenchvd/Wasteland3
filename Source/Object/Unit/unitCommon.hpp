
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef UNIT_COMMON_HPP
#define UNIT_COMMON_HPP

namespace game {
namespace object {

using UnitBaseType                  = short int;
using Unit__Model                   = UnitBaseType;

enum class Unit__Type : char {
    __INVALID = -1,                 /// invalid, must be the first
    // vvv TYPES vvv
    CHARACTER,
    ///HUMAN,
    ///MUTANT,
    ///ANIMAL,
    ///VEHICLE,
    ///ROBOT,
    ///SYNTH,
    // ^^^ TYPES ^^^
    __NUMBER_OF,
    __END                           /// must be the last
};

} // namespace object
} // namespace game

#endif // !UNIT_COMMON_HPP
