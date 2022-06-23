
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef COMMON_HPP
#define COMMON_HPP

#include"boost/config.hpp"
#include<assert.h>
#include<iostream>
#include<string>
#include<sys/stat.h>
#include<type_traits>

namespace game {
namespace common {

using Text                  = std::string;

enum class Time             : int {};       // 0.001s (1s == 1000 Time)
enum class Experience       : int {};
enum class Damage           : short int {};
enum class Price            : short int {};
enum class Range            : short int {};
enum class Capacity         : short int {};
enum class Constitution     : short int {};
enum class Angle            : short int {};
enum class Quantity         : short int {};

enum class Multiplier       : short int {}; // 0.01X (1X == 100 Multiplier)
enum class Chance           : short int {}; // 0.1% (1% == 10 Chance)
enum class Bonus            : short int {}; // 0.1% (1% == 10 Bonus)
enum class Evasion          : short int {}; // 0.1% (1% == 10 Evasion)
enum class Resistance       : short int {}; // 0.1% (1% == 10 Resistance)
enum class Initiative       : short int {}; // 0.1% (1% == 10 Initiative)
enum class Strike           : short int {}; // 0.1% (1% == 10 Strike)

enum class Level            : char {};
enum class Armor            : char {};
enum class ActionPoint      : char {};
enum class NumberMoves      : char {};
enum class NumberShots      : char {};
enum class Perception       : char {};
enum class Radiation        : char {};

enum class PointSkill       : short int {};
enum class LevelSkill       : char {};
enum class PointAttribute   : char {};
enum class LevelAttribute   : char {};

enum class Money            : long long int {};


constexpr int timeX         { 1000 };       // multiplier for Time
constexpr int multiplierX   { 100 };        // multiplier for Multiplier
constexpr int chanceX       { 10 };         // multiplier for Chance
constexpr int bonusX        { 10 };         // multiplier for Bonus
constexpr int evasionX      { 10 };         // multiplier for Evasion
constexpr int resistanceX   { 10 };         // multiplier for Resistance
constexpr int initiativeX   { 10 };         // multiplier for Initiative
constexpr int strikeX       { 10 };         // multiplier for Strike

///************************************************************************************************

template <class Enum>
constexpr auto toUnderlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template <class Enum>
constexpr void verifyEnum() noexcept
{
    assert(toUnderlying(Enum::__INVALID) == -1);
    assert(Enum::__INVALID      < Enum::__NUMBER_OF);
    assert(Enum::__NUMBER_OF    < Enum::__END);
}

template <class Enum>
constexpr bool isValidEnum(Enum e) noexcept
{
    verifyEnum<Enum>();
    return (e > Enum::__INVALID && e < Enum::__NUMBER_OF);
}

template <class Enum>
constexpr bool isValidEnumAux(Enum e) noexcept
{
    verifyEnum<Enum>();
    return (e > Enum::__NUMBER_OF && e < Enum::__END);
}

template <class Enum>
constexpr auto numberOf() noexcept
{
    verifyEnum<Enum>();
    return toUnderlying(Enum::__NUMBER_OF);
}

template <class Enum>
constexpr auto firstEnum() noexcept
{
    auto e{ static_cast<Enum>(toUnderlying(Enum::__INVALID) + 1) };
    assert(isValidEnum(e));
    return e;
}

template <class Enum>
constexpr auto lastEnum() noexcept
{
    auto e{ static_cast<Enum>(toUnderlying(Enum::__NUMBER_OF) - 1) };
    assert(isValidEnum(e));
    return e;
}

constexpr auto toInt(char c) noexcept
{
    return static_cast<int>(c);
}

///************************************************************************************************

#if(BOOST_CXX_VERSION >= 201703L)

template <class PtrToMemberFunc, class Class, class T>
constexpr auto checked(T v)
{
    return std::invoke_result_t<PtrToMemberFunc, Class>{ v };
}

template <class PtrToMemberFunc, class Class, class T>
constexpr auto checkedEnum(T v)
{
    return std::invoke_result_t<PtrToMemberFunc, Class>{ toUnderlying(v) };
}

#endif

///************************************************************************************************

inline bool fileExists(const std::string& fileName)
{
    return fileExists(fileName.c_str());
}

inline bool fileExists(const char* fileName)
{
    struct stat buffer;
    return (stat(fileName, &buffer) == 0);
}

///************************************************************************************************

template<class Enum>
inline Enum& operator+=(Enum& lhs, const Enum& rhs)
{
    lhs = Enum{ toUnderlying(lhs) + toUnderlying(rhs) };
    return lhs;
}

template<class Enum>
inline Enum& operator-=(Enum& lhs, const Enum& rhs)
{
    lhs = Enum{ toUnderlying(lhs) - toUnderlying(rhs) };
    return lhs;
}

template<class Enum>
inline Enum operator+(const Enum& lhs, const Enum& rhs)
{
    return Enum{ toUnderlying(lhs) + toUnderlying(rhs) };
}

template<class Enum>
inline Enum operator-(const Enum& lhs, const Enum& rhs)
{
    return Enum{ toUnderlying(lhs) - toUnderlying(rhs) };
}



inline std::ostream& operator<<(std::ostream& os, const Time& value)
{
    os << static_cast<double>(value) / timeX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Experience& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Damage& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Price& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Range& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Capacity& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Constitution& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Angle& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Quantity& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Multiplier& value)
{
    os << static_cast<double>(value) / multiplierX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Chance& value)
{
    os << static_cast<double>(value) / chanceX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Bonus& value)
{
    os << static_cast<double>(value) / bonusX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Evasion& value)
{
    os << static_cast<double>(value) / evasionX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Resistance& value)
{
    os << static_cast<double>(value) / resistanceX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Initiative& value)
{
    os << static_cast<double>(value) / initiativeX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Strike& value)
{
    os << static_cast<double>(value) / strikeX;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Level& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Armor& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ActionPoint& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const NumberMoves& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const NumberShots& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Perception& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Radiation& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const PointSkill& value)
{
    os << toUnderlying(value);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const LevelSkill& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const PointAttribute& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const LevelAttribute& value)
{
    os << toInt(toUnderlying(value));
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Money& value)
{
    os << toUnderlying(value);
    return os;
}

} // namespace common
} // namespace game

#endif // !COMMON_HPP
