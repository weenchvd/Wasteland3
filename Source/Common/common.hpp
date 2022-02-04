
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef COMMON_HPP
#define COMMON_HPP

#include<string>
#include<type_traits>

namespace Game {
namespace Common {

using Text                  = std::string;
using Time                  = int;          // 0.001s (1s == 1000 Time)
using Experience            = int;
using Damage                = short int;
using Price                 = short int;
using Range                 = short int;
using Capacity              = short int;
using Constitution          = short int;

using Multiplier            = short int;    // 0.01X (1X == 100 Multiplier)
using Chance                = short int;    // 0.1% (1% == 10 Chance)
using Bonus                 = short int;    // 0.1% (1% == 10 Bonus)
using Evasion               = short int;    // 0.1% (1% == 10 Evasion)
using Resistance            = short int;    // 0.1% (1% == 10 Resistance)
using Initiative            = short int;    // 0.1% (1% == 10 Initiative)
using Strike                = short int;    // 0.1% (1% == 10 Strike)

using Level                 = char;
using Armor                 = char;
using ActionPoint           = char;
using NumberMoves           = char;
using NumberShots           = char;
using Perception            = char;
using Radiation             = char;


using PointSkill            = short int;
using LevelSkill            = char;         // skill level
using PointAttribute        = char;
using LevelStat             = char;         // statistic level


using Money                 = long long int;


template <class Enum>
constexpr auto toUnderlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template <class Enum>
constexpr bool isValidEnum(Enum e) noexcept
{
    return (e > Enum::INVALID && e < Enum::NUMBER_OF);
}

} // namespace Common
} // namespace Game

#endif // !COMMON_HPP
