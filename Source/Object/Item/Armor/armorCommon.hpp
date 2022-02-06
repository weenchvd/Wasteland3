
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ARMOR_COMMON_HPP
#define ARMOR_COMMON_HPP

#include"itemCommon.hpp"

namespace game {
namespace object {

enum class Armor__Model : ItemBaseType {
    INVALID = -1,                   /// invalid, must be the first



    NUMBER_OF                       /// must be the last
};

enum class Armor__Type : char {
    INVALID = -1,                   /// invalid, must be the first

    HEAD,
    CHEST,
    LEG,
    UTILITY,

    NUMBER_OF                       /// must be the last
};

} // namespace object
} // namespace game

#endif // !ARMOR_COMMON_HPP
