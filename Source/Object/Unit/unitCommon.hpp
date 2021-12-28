
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef UNIT_COMMON_HPP
#define UNIT_COMMON_HPP

namespace Game
{
    namespace Object
    {
        using UnitBaseType                  = short int;
        using Unit__Model                   = UnitBaseType;

        enum class Unit__Type : UnitBaseType {
            INVALID = -1,                   /// invalid, must be the first

            CHARACTER,
            HUMAN,
            MUTANT,
            ANIMAL,
            VEHICLE,
            ROBOT,
            SYNTH,

            NUMBER_OF                       /// must be the last
        };

    }
}

#endif // !UNIT_COMMON_HPP
