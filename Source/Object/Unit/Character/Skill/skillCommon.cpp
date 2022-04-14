
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"skillCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Skill__Type toSkillType(fbSkill::FB_SkillType id)
{
    static unordered_map<fbSkill::FB_SkillType, Skill__Type> map{
        { fbSkill::FB_SkillType_INVALID, Skill__Type::INVALID },
        { fbSkill::FB_SkillType_AUTOMATIC_WEAPONS, Skill__Type::AUTOMATIC_WEAPONS },
        { fbSkill::FB_SkillType_BIG_GUNS, Skill__Type::BIG_GUNS },
        { fbSkill::FB_SkillType_BRAWLING, Skill__Type::BRAWLING },
        { fbSkill::FB_SkillType_MELEE_COMBAT, Skill__Type::MELEE_COMBAT },
        { fbSkill::FB_SkillType_SMALL_ARMS, Skill__Type::SMALL_ARMS },
        { fbSkill::FB_SkillType_SNIPER_RIFLES, Skill__Type::SNIPER_RIFLES },
        { fbSkill::FB_SkillType_ANIMAL_WHISPERER, Skill__Type::ANIMAL_WHISPERER },
        { fbSkill::FB_SkillType_EXPLOSIVES, Skill__Type::EXPLOSIVES },
        { fbSkill::FB_SkillType_FIRST_AID, Skill__Type::FIRST_AID },
        { fbSkill::FB_SkillType_SNEAKY_SHIT, Skill__Type::SNEAKY_SHIT },
        { fbSkill::FB_SkillType_WEIRD_SCIENCE, Skill__Type::WEIRD_SCIENCE },
        { fbSkill::FB_SkillType_ARMOR_MODDING, Skill__Type::ARMOR_MODDING },
        { fbSkill::FB_SkillType_LOCKPICKING, Skill__Type::LOCKPICKING },
        { fbSkill::FB_SkillType_NERD_STUFF, Skill__Type::NERD_STUFF },
        { fbSkill::FB_SkillType_MECHANICS, Skill__Type::MECHANICS },
        { fbSkill::FB_SkillType_SURVIVAL, Skill__Type::SURVIVAL },
        { fbSkill::FB_SkillType_TOASTER_REPAIR, Skill__Type::TOASTER_REPAIR },
        { fbSkill::FB_SkillType_WEAPON_MODDING, Skill__Type::WEAPON_MODDING },
        { fbSkill::FB_SkillType_BARTER, Skill__Type::BARTER },
        { fbSkill::FB_SkillType_HARD_ASS, Skill__Type::HARD_ASS },
        { fbSkill::FB_SkillType_KISS_ASS, Skill__Type::KISS_ASS },
        { fbSkill::FB_SkillType_LEADERSHIP, Skill__Type::LEADERSHIP }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
