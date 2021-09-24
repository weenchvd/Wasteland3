
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef COMMON_HPP
#define COMMON_HPP

#include<string>

namespace Game
{
    namespace Common
    {
        using Text                  = std::string;
        using Name                  = Text;
        using Description           = Text;
        using Price                 = short int;
        using Level                 = char;

    }

    namespace Common
    {
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
        using NumberAttacks         = char;
        using Perception            = char;
        using Radiation             = char;

    }

    //namespace Common
    //{
    //    using Text                  = std::string;  // Name, Description
    //    using Multiplier            = double;       // Critical, Speed, Throwing range
    //    using Time                  = double;       // Detection
    //    using Experience            = int;
    //    using Damage                = short int;    // Minimum, Maximum 
    //    using Price                 = short int;
    //    using Range                 = short int;
    //    using Capacity              = short int;
    //    using Constitution          = short int;

    //    using Chance                = short int;    // default: 0%
    //    using Modifier              = short int;    // default: 100%
    //    using Evasion               = short int;    // default: 0%
    //    using Resistance            = short int;    // default: 0%
    //    using Initiative            = short int;    // default: 0%
    //    using Strike                = short int;    // default: 0%
    //    using LuckyChance           = short int;    // default: 0% (multiplier: x10; 1% == 10 LuckyChance)

    //    using Level                 = char;
    //    using Armor                 = char;         // Armor, Penetration
    //    using ActionPoint           = char;
    //    using NumberMoves           = char;
    //    using NumberAttacks         = char;
    //    using Perception            = char;
    //    using Radiation             = char;
    //}

    //using Text                  = std::string;  // Name, Description
    //using Multiplier            = double;       // Critical, Speed, Throwing range
    //using Time                  = double;       // Detection
    //using Experience            = int;
    //using Damage                = short int;    // Minimum, Maximum 
    //using Price                 = short int;
    //using Range                 = short int;
    //using Capacity              = short int;
    //using Constitution          = short int;

    //using Chance                = short int;    // Critical, Hit
    //using HealingBonus          = short int;
    //using DamageBonus           = short int;
    //using Evasion               = short int;
    //using Resistance            = short int;
    //using Initiative            = short int;
    //using Rate                  = short int;    // Strike, XP

    //using Level                 = char;
    //using Armor                 = char;         // Armor, Penetration
    //using ActionPoint           = char;
    //using NumberMoves           = char;
    //using NumberAttacks         = char;
    //using Perception            = char;
    //using Radiation             = char;

}

#endif // !COMMON_HPP
