
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"skillAux.hpp"
#include<assert.h>

namespace game {
namespace object {

using namespace std;

SkillInitializer::SkillInitializer() noexcept
    :
    skillPoints_            { 0 },
    automaticLevel_         { 0 },
    bigGunsLevel_           { 0 },
    brawlingLevel_          { 0 },
    meleeLevel_             { 0 },
    smallArmsLevel_         { 0 },
    sniperLevel_            { 0 },
    animalWhispererLevel_   { 0 },
    explosivesLevel_        { 0 },
    firstAidLevel_          { 0 },
    sneakyShitLevel_        { 0 },
    weirdScienceLevel_      { 0 },
    armorModdingLevel_      { 0 },
    lockpickingLevel_       { 0 },
    nerdStuffLevel_         { 0 },
    mechanicsLevel_         { 0 },
    survivalLevel_          { 0 },
    toasterRepairLevel_     { 0 },
    weaponModdingLevel_     { 0 },
    barterLevel_            { 0 },
    hardAssLevel_           { 0 },
    kissAssLevel_           { 0 },
    leadershipLevel_        { 0 },
    initialized_            { false }
{}

SkillInitializer::SkillInitializer(const fbSkill::FB_Skill* fb) noexcept
    :
    skillPoints_            { 0 },
    automaticLevel_         { 0 },
    bigGunsLevel_           { 0 },
    brawlingLevel_          { 0 },
    meleeLevel_             { 0 },
    smallArmsLevel_         { 0 },
    sniperLevel_            { 0 },
    animalWhispererLevel_   { 0 },
    explosivesLevel_        { 0 },
    firstAidLevel_          { 0 },
    sneakyShitLevel_        { 0 },
    weirdScienceLevel_      { 0 },
    armorModdingLevel_      { 0 },
    lockpickingLevel_       { 0 },
    nerdStuffLevel_         { 0 },
    mechanicsLevel_         { 0 },
    survivalLevel_          { 0 },
    toasterRepairLevel_     { 0 },
    weaponModdingLevel_     { 0 },
    barterLevel_            { 0 },
    hardAssLevel_           { 0 },
    kissAssLevel_           { 0 },
    leadershipLevel_        { 0 },
    initialized_            { false }
{
    initialize(fb);
}

void SkillInitializer::initialize(const fbSkill::FB_Skill* fb) noexcept
{
    assert(fb != nullptr);

    skillPoints_            = point_t{ fb->skill_points() };
    automaticLevel_         = level_t{ fb->automatic_level() };
    bigGunsLevel_           = level_t{ fb->big_guns_level() };
    brawlingLevel_          = level_t{ fb->brawling_level() };
    meleeLevel_             = level_t{ fb->melee_level() };
    smallArmsLevel_         = level_t{ fb->small_arms_level() };
    sniperLevel_            = level_t{ fb->sniper_level() };
    animalWhispererLevel_   = level_t{ fb->animal_whisperer_level() };
    explosivesLevel_        = level_t{ fb->explosives_level() };
    firstAidLevel_          = level_t{ fb->first_aid_level() };
    sneakyShitLevel_        = level_t{ fb->sneaky_shit_level() };
    weirdScienceLevel_      = level_t{ fb->weird_science_level() };
    armorModdingLevel_      = level_t{ fb->armor_modding_level() };
    lockpickingLevel_       = level_t{ fb->lockpicking_level() };
    nerdStuffLevel_         = level_t{ fb->nerd_stuff_level() };
    mechanicsLevel_         = level_t{ fb->mechanics_level() };
    survivalLevel_          = level_t{ fb->survival_level() };
    toasterRepairLevel_     = level_t{ fb->toaster_repair_level() };
    weaponModdingLevel_     = level_t{ fb->weapon_modding_level() };
    barterLevel_            = level_t{ fb->barter_level() };
    hardAssLevel_           = level_t{ fb->hard_ass_level() };
    kissAssLevel_           = level_t{ fb->kiss_ass_level() };
    leadershipLevel_        = level_t{ fb->leadership_level() };

    initialized_            = true;
}

} // namespace object
} // namespace game
