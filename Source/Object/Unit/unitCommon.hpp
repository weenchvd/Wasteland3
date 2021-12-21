
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
        using UnitBaseType                  = unsigned short int;
        using UnitModel                     = UnitBaseType;

        enum class UnitType : UnitBaseType {
            Character,
            Human,
            Mutant,
            Animal,
            Vehicle,
            Robot,
            Synth
        };

    }
}

#endif // !UNIT_COMMON_HPP
