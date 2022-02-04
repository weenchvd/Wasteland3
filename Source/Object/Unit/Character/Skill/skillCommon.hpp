
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_COMMON_HPP
#define SKILL_COMMON_HPP

namespace Game {
namespace Object {

enum class Skill__Type : char {
    INVALID = -1,                   /// invalid, must be the first

    // Combat skills
    AUTOMATIC_WEAPONS,
    BIG_GUNS,
    BRAWLING,
    MELEE_COMBAT,
    SMALL_ARMS,
    SNIPER_RIFLES,
            
    // General skills
    ANIMAL_WHISPERER,
    EXPLOSIVES,
    FIRST_AID,
    SNEAKY_SHIT,
    WEIRD_SCIENCE,

    // Exploration skills
    ARMOR_MODDING,
    LOCKPICKING,
    NERD_STUFF,
    MECHANICS,
    SURVIVAL,
    TOASTER_REPAIR,
    WEAPON_MODDING,

    // Social skills
    BARTER,
    HARD_ASS,
    KISS_ASS,
    LEADERSHIP,

    NUMBER_OF                       /// must be the last
};

enum class Skill__Group : char {
    INVALID = -1,                   /// invalid, must be the first

    COMBAT,
    GENERAL,
    EXPLORATION,
    SOCIAL,

    NUMBER_OF                       /// must be the last
};

} // namespace Object
} // namespace Game

#endif // !SKILL_COMMON_HPP
