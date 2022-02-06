
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"distribution.hpp"
#include"flatbuffersAux.hpp"
#include"skillPath.hpp"
#include"skillReference.hpp"
#include<assert.h>
#include<memory>
#include<type_traits>
#include<vector>

namespace game {
namespace object {

using namespace std;

common::Distribution<SkillReference::PointSkill>    SkillReference::pDist_{
    std::vector<SkillReference::PointSkill>()
};
common::Distribution<EffectSkillAutomatic>          SkillReference::automDist_{
    std::vector<EffectSkillAutomatic>()
};
common::Distribution<EffectSkillBigGuns>            SkillReference::bigGunsDist_{
    std::vector<EffectSkillBigGuns>()
};
common::Distribution<EffectSkillBrawling>           SkillReference::brawlDist_{
    std::vector<EffectSkillBrawling>()
};
common::Distribution<EffectSkillMelee>              SkillReference::meleeDist_{
    std::vector<EffectSkillMelee>()
};
common::Distribution<EffectSkillSmallArms>          SkillReference::smallDist_{
    std::vector<EffectSkillSmallArms>()
};
common::Distribution<EffectSkillSniper>             SkillReference::sniperDist_{
    std::vector<EffectSkillSniper>()
};
common::Distribution<EffectSkillAnimal>             SkillReference::animalDist_{
    std::vector<EffectSkillAnimal>()
};
common::Distribution<EffectSkillExplosive>          SkillReference::explosDist_{
    std::vector<EffectSkillExplosive>()
};
common::Distribution<EffectSkillFirstAid>           SkillReference::aidDist_{
    std::vector<EffectSkillFirstAid>()
};
common::Distribution<EffectSkillSneakyShit>         SkillReference::sneakyDist_{
    std::vector<EffectSkillSneakyShit>()
};
common::Distribution<EffectSkillWeirdScience>       SkillReference::weirdDist_{
    std::vector<EffectSkillWeirdScience>()
};
common::Distribution<EffectSkillMechanics>          SkillReference::mechDist_{
    std::vector<EffectSkillMechanics>()
};
common::Distribution<EffectSkillSurvival>           SkillReference::survDist_{
    std::vector<EffectSkillSurvival>()
};
common::Distribution<EffectSkillWeaponMod>          SkillReference::weaponModDist_{
    std::vector<EffectSkillWeaponMod>()
};
common::Distribution<EffectSkillBarter>             SkillReference::barterDist_{
    std::vector<EffectSkillBarter>()
};
common::Distribution<EffectSkillLeadership>         SkillReference::leaderDist_{
    std::vector<EffectSkillLeadership>()
};

common::PointSkill      SkillReference::minSkillPoints_ { 0 };
common::PointSkill      SkillReference::maxSkillPoints_ { 0 };
common::PointSkill      SkillReference::initSkillPoints_{ 0 };
common::LevelStat       SkillReference::minSkillLevel_  { 0 };
common::LevelStat       SkillReference::maxSkillLevel_  { 0 };
common::LevelStat       SkillReference::initSkillLevel_ { 0 };
bool                    SkillReference::initialized_    { false };

void SkillReference::initialize()
{
    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(SKILL_REF_FB_BIN_FILE__NATIVE_REL_PATH)
    };

    const fbSkill::FB_Skill* skill = fbSkill::GetFB_Skill(buffer.get());
    assert(skill != nullptr);

    initPointDist(skill);
    initAutomaticDist(skill);
    initBigGunsDist(skill);
    initBrawlingDist(skill);
    initMeleeDist(skill);
    initSmallArmsDist(skill);
    initSniperDist(skill);
    initAnimalDist(skill);
    initExplosiveDist(skill);
    initFirstAidDist(skill);
    initSneakyShitDist(skill);
    initWeirdScienceDist(skill);
    initMechanicsDist(skill);
    initSurvivalDist(skill);
    initWeaponModDist(skill);
    initBarterDist(skill);
    initLeadershipDist(skill);

    minSkillPoints_     = { skill->min_skill_points() };
    maxSkillPoints_     = { skill->max_skill_points() };
    initSkillPoints_    = { skill->init_skill_points() };
    minSkillLevel_      = { skill->min_skill_level() };
    maxSkillLevel_      = { skill->max_skill_level() };
    initSkillLevel_     = { skill->init_skill_level() };

    initialized_        = true;
}

void SkillReference::initPointDist(const fbSkill::FB_Skill* skill)
{
    pDist_ = move(common::Distribution<SkillReference::PointSkill>{
        common::convertToVector<common::PointSkill>(skill->point_skill_distr()->p())
    });
}

void SkillReference::initAutomaticDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->automatic_distr();

    automDist_ = move(common::Distribution<EffectSkillAutomatic>{
        common::initializeDistribution<EffectSkillAutomatic,
            common::Chance,
            common::Chance
        >(
            common::convertToVector<common::Chance>(dist->ar_hit()),
            common::convertToVector<common::Chance>(dist->smg_hit())
            )
    });
}

void SkillReference::initBigGunsDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->big_guns_distr();

    bigGunsDist_ = move(common::Distribution<EffectSkillBigGuns>{
        common::initializeDistribution<EffectSkillBigGuns,
            common::Chance,
            common::Chance
        >(
            common::convertToVector<common::Chance>(dist->hmg_hit()),
            common::convertToVector<common::Chance>(dist->ft_hit())
            )
    });
}

void SkillReference::initBrawlingDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->brawling_distr();

    brawlDist_ = move(common::Distribution<EffectSkillBrawling>{
        common::initializeDistribution<EffectSkillBrawling,
            common::Multiplier,
            common::Chance
        >(
            common::convertToVector<common::Multiplier>(dist->combat_speed()),
            common::convertToVector<common::Chance>(dist->weapon_hit())
            )
    });
}

void SkillReference::initMeleeDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->melee_distr();

    meleeDist_ = move(common::Distribution<EffectSkillMelee>{
        common::initializeDistribution<EffectSkillMelee,
            common::Chance,
            common::Chance
        >(
            common::convertToVector<common::Chance>(dist->blunt_hit()),
            common::convertToVector<common::Chance>(dist->bladed_hit())
            )
    });
}

void SkillReference::initSmallArmsDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->small_arms_distr();

    smallDist_ = move(common::Distribution<EffectSkillSmallArms>{
        common::initializeDistribution<EffectSkillSmallArms,
            common::Chance,
            common::Chance,
            common::Chance,
            common::Chance
        >(
            common::convertToVector<common::Chance>(dist->sa_pistol_hit()),
            common::convertToVector<common::Chance>(dist->revolver_hit()),
            common::convertToVector<common::Chance>(dist->pump_sg_hit()),
            common::convertToVector<common::Chance>(dist->auto_sg_hit())
            )
    });
}

void SkillReference::initSniperDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->sniper_distr();

    sniperDist_ = move(common::Distribution<EffectSkillSniper>{
        common::initializeDistribution<EffectSkillSniper,
            common::Chance
        >(
            common::convertToVector<common::Chance>(dist->sr_hit())
            )
    });
}

void SkillReference::initAnimalDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->animal_whisperer_disrt();

    animalDist_ = move(common::Distribution<EffectSkillAnimal>{
        common::initializeDistribution<EffectSkillAnimal,
            common::Bonus
        >(
            common::convertToVector<common::Bonus>(dist->animal_dmg())
            )
    });
}

void SkillReference::initExplosiveDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->explosives_distr();

    explosDist_ = move(common::Distribution<EffectSkillExplosive>{
        common::initializeDistribution<EffectSkillExplosive,
            common::Resistance,
            common::Bonus
        >(
            common::convertToVector<common::Resistance>(dist->expl_dmg_resist()),
            common::convertToVector<common::Bonus>(dist->expl_dmg_bonus())
            )
    });
}

void SkillReference::initFirstAidDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->first_aid_distr();

    aidDist_ = move(common::Distribution<EffectSkillFirstAid>{
        common::initializeDistribution<EffectSkillFirstAid,
            common::Bonus,
            common::Bonus
        >(
            common::convertToVector<common::Bonus>(dist->healing_item()),
            common::convertToVector<common::Bonus>(dist->healing_revive())
            )
    });
}

void SkillReference::initSneakyShitDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->sneaky_shit_distr();

    sneakyDist_ = move(common::Distribution<EffectSkillSneakyShit>{
        common::initializeDistribution<EffectSkillSneakyShit,
            common::Time,
            common::Initiative,
            common::Bonus,
            common::Perception
        >(
            common::convertToVector<common::Time>(dist->detection_time()),
            common::convertToVector<common::Initiative>(dist->initiative()),
            common::convertToVector<common::Bonus>(dist->attack_dmg()),
            common::convertToVector<common::Perception>(dist->percep())
            )
    });
}

void SkillReference::initWeirdScienceDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->weird_science_distr();

    weirdDist_ = move(common::Distribution<EffectSkillWeirdScience>{
        common::initializeDistribution<EffectSkillWeirdScience,
            common::Bonus,
            common::Bonus,
            common::Bonus
        >(
            common::convertToVector<common::Bonus>(dist->energy_dmg()),
            common::convertToVector<common::Bonus>(dist->fire_dmg()),
            common::convertToVector<common::Bonus>(dist->cold_dmg())
            )
    });
}

void SkillReference::initMechanicsDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->mechanics_distr();

    mechDist_ = move(common::Distribution<EffectSkillMechanics>{
        common::initializeDistribution<EffectSkillMechanics,
            common::Bonus,
            common::Bonus,
            common::Bonus,
            common::Bonus
        >(
            common::convertToVector<common::Bonus>(dist->robot_dmg()),
            common::convertToVector<common::Bonus>(dist->vehicle_dmg()),
            common::convertToVector<common::Bonus>(dist->synth_dmg()),
            common::convertToVector<common::Bonus>(dist->repair_kit())
            )
    });
}

void SkillReference::initSurvivalDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->survival_distr();

    survDist_ = move(common::Distribution<EffectSkillSurvival>{
        common::initializeDistribution<EffectSkillSurvival,
            common::Bonus,
            common::Bonus
        >(
            common::convertToVector<common::Bonus>(dist->animal_dmg()),
            common::convertToVector<common::Bonus>(dist->mutant_dmg())
            )
    });
}

void SkillReference::initWeaponModDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->weapon_modding_distr();

    weaponModDist_ = move(common::Distribution<EffectSkillWeaponMod>{
        common::initializeDistribution<EffectSkillWeaponMod,
            common::Bonus
        >(
            common::convertToVector<common::Bonus>(dist->scrap())
            )
    });
}

void SkillReference::initBarterDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->barter_distr();

    barterDist_ = move(common::Distribution<EffectSkillBarter>{
        common::initializeDistribution<EffectSkillBarter,
            common::Bonus,
            common::Bonus
        >(
            common::convertToVector<common::Bonus>(dist->sell_value()),
            common::convertToVector<common::Bonus>(dist->buy_cost())
            )
    });
}

void SkillReference::initLeadershipDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->leadership_distr();

    leaderDist_ = move(common::Distribution<EffectSkillLeadership>{
        common::initializeDistribution<EffectSkillLeadership,
            common::Chance,
            common::Bonus,
            common::Chance,
            common::Bonus
        >(
            common::convertToVector<common::Chance>(dist->hit_chance()),
            common::convertToVector<common::Bonus>(dist->boss_kill_dmg()),
            common::convertToVector<common::Chance>(dist->multi_kill_crit_chance()),
            common::convertToVector<common::Bonus>(dist->revive_con_healed())
            )
    });
}

} // namespace object
} // namespace game
