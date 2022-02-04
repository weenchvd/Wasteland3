
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPERATORS_HPP
#define OPERATORS_HPP

namespace Game {
namespace Common {

template<class T>
inline T operatorPlus(const T& left, const T& right)
{
    T temp{ left };
    temp += right;
    return temp;
}

template<class T>
inline T operatorMinus(const T& left, const T& right)
{
    T temp{ left };
    temp -= right;
    return temp;
}

} // namespace Common
} // namespace Game

#endif // !OPERATORS_HPP
