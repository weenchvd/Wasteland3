
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef COMMON_HPP
#define COMMON_HPP

#include<string>
#include<type_traits>

namespace game {
namespace common {

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

///************************************************************************************************

constexpr inline double getTime(Time time)
{
    return static_cast<double>(time) / 1000;
}

constexpr inline double getMult(Multiplier mult)
{
    return static_cast<double>(mult) / 100;
}

constexpr inline double getChance(Chance chance)
{
    return static_cast<double>(chance) / 10;
}

constexpr inline double getBonus(Bonus bonus)
{
    return static_cast<double>(bonus) / 10;
}

constexpr inline double getEvasion(Evasion evasion)
{
    return static_cast<double>(evasion) / 10;
}

constexpr inline double getResist(Resistance res)
{
    return static_cast<double>(res) / 10;
}

constexpr inline double getInit(Initiative init)
{
    return static_cast<double>(init) / 10;
}

constexpr inline double getStrike(Strike strike)
{
    return static_cast<double>(strike) / 10;
}

constexpr inline int getLv(Level value)
{
    return static_cast<int>(value);
}

constexpr inline int getArmor(Armor value)
{
    return static_cast<int>(value);
}

constexpr inline int getAP(ActionPoint value)
{
    return static_cast<int>(value);
}

constexpr inline int getMoves(NumberMoves value)
{
    return static_cast<int>(value);
}

constexpr inline int getShots(NumberShots value)
{
    return static_cast<int>(value);
}

constexpr inline int getPercep(Perception value)
{
    return static_cast<int>(value);
}

constexpr inline int getRad(Radiation value)
{
    return static_cast<int>(value);
}

constexpr inline int getLvSkill(LevelSkill value)
{
    return static_cast<int>(value);
}

constexpr inline int getPAttr(PointAttribute value)
{
    return static_cast<int>(value);
}

constexpr inline int getLvStat(LevelStat value)
{
    return static_cast<int>(value);
}

///************************************************************************************************

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

} // namespace common
} // namespace game

#endif // !COMMON_HPP
