
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

namespace Game {
namespace Object {

using namespace std;

Common::Distribution<SkillReference::PointSkill>    SkillReference::pDist_{
    std::vector<SkillReference::PointSkill>()
};
Common::Distribution<EffectSkillAutomatic>          SkillReference::automDist_{
    std::vector<EffectSkillAutomatic>()
};
Common::Distribution<EffectSkillBigGuns>            SkillReference::bigGunsDist_{
    std::vector<EffectSkillBigGuns>()
};
Common::Distribution<EffectSkillBrawling>           SkillReference::brawlDist_{
    std::vector<EffectSkillBrawling>()
};
Common::Distribution<EffectSkillMelee>              SkillReference::meleeDist_{
    std::vector<EffectSkillMelee>()
};
Common::Distribution<EffectSkillSmallArms>          SkillReference::smallDist_{
    std::vector<EffectSkillSmallArms>()
};
Common::Distribution<EffectSkillSniper>             SkillReference::sniperDist_{
    std::vector<EffectSkillSniper>()
};
Common::Distribution<EffectSkillAnimal>             SkillReference::animalDist_{
    std::vector<EffectSkillAnimal>()
};
Common::Distribution<EffectSkillExplosive>          SkillReference::explosDist_{
    std::vector<EffectSkillExplosive>()
};
Common::Distribution<EffectSkillFirstAid>           SkillReference::aidDist_{
    std::vector<EffectSkillFirstAid>()
};
Common::Distribution<EffectSkillSneakyShit>         SkillReference::sneakyDist_{
    std::vector<EffectSkillSneakyShit>()
};
Common::Distribution<EffectSkillWeirdScience>       SkillReference::weirdDist_{
    std::vector<EffectSkillWeirdScience>()
};
Common::Distribution<EffectSkillMechanics>          SkillReference::mechDist_{
    std::vector<EffectSkillMechanics>()
};
Common::Distribution<EffectSkillSurvival>           SkillReference::survDist_{
    std::vector<EffectSkillSurvival>()
};
Common::Distribution<EffectSkillWeaponMod>          SkillReference::weaponModDist_{
    std::vector<EffectSkillWeaponMod>()
};
Common::Distribution<EffectSkillBarter>             SkillReference::barterDist_{
    std::vector<EffectSkillBarter>()
};
Common::Distribution<EffectSkillLeadership>         SkillReference::leaderDist_{
    std::vector<EffectSkillLeadership>()
};

Common::PointSkill      SkillReference::minSkillPoints_ { 0 };
Common::PointSkill      SkillReference::maxSkillPoints_ { 0 };
Common::PointSkill      SkillReference::initSkillPoints_{ 0 };
Common::LevelStat       SkillReference::minSkillLevel_  { 0 };
Common::LevelStat       SkillReference::maxSkillLevel_  { 0 };
Common::LevelStat       SkillReference::initSkillLevel_ { 0 };
bool                    SkillReference::initialized_    { false };

void SkillReference::initialize()
{
    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        Common::getFlatBuffer(SKILL_REF_FB_BIN_FILE__NATIVE_REL_PATH)
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
    pDist_ = move(Common::Distribution<SkillReference::PointSkill>{
        Common::convertToVector<Common::PointSkill>(skill->point_skill_distr()->p())
    });
}

void SkillReference::initAutomaticDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->automatic_distr();

    automDist_ = move(Common::Distribution<EffectSkillAutomatic>{
        Common::initializeDistribution<EffectSkillAutomatic,
            Common::Chance,
            Common::Chance
        >(
            Common::convertToVector<Common::Chance>(dist->ar_hit()),
            Common::convertToVector<Common::Chance>(dist->smg_hit())
            )
    });
}

void SkillReference::initBigGunsDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->big_guns_distr();

    bigGunsDist_ = move(Common::Distribution<EffectSkillBigGuns>{
        Common::initializeDistribution<EffectSkillBigGuns,
            Common::Chance,
            Common::Chance
        >(
            Common::convertToVector<Common::Chance>(dist->hmg_hit()),
            Common::convertToVector<Common::Chance>(dist->ft_hit())
            )
    });
}

void SkillReference::initBrawlingDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->brawling_distr();

    brawlDist_ = move(Common::Distribution<EffectSkillBrawling>{
        Common::initializeDistribution<EffectSkillBrawling,
            Common::Multiplier,
            Common::Chance
        >(
            Common::convertToVector<Common::Multiplier>(dist->combat_speed()),
            Common::convertToVector<Common::Chance>(dist->weapon_hit())
            )
    });
}

void SkillReference::initMeleeDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->melee_distr();

    meleeDist_ = move(Common::Distribution<EffectSkillMelee>{
        Common::initializeDistribution<EffectSkillMelee,
            Common::Chance,
            Common::Chance
        >(
            Common::convertToVector<Common::Chance>(dist->blunt_hit()),
            Common::convertToVector<Common::Chance>(dist->bladed_hit())
            )
    });
}

void SkillReference::initSmallArmsDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->small_arms_distr();

    smallDist_ = move(Common::Distribution<EffectSkillSmallArms>{
        Common::initializeDistribution<EffectSkillSmallArms,
            Common::Chance,
            Common::Chance,
            Common::Chance,
            Common::Chance
        >(
            Common::convertToVector<Common::Chance>(dist->sa_pistol_hit()),
            Common::convertToVector<Common::Chance>(dist->revolver_hit()),
            Common::convertToVector<Common::Chance>(dist->pump_sg_hit()),
            Common::convertToVector<Common::Chance>(dist->auto_sg_hit())
            )
    });
}

void SkillReference::initSniperDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->sniper_distr();

    sniperDist_ = move(Common::Distribution<EffectSkillSniper>{
        Common::initializeDistribution<EffectSkillSniper,
            Common::Chance
        >(
            Common::convertToVector<Common::Chance>(dist->sr_hit())
            )
    });
}

void SkillReference::initAnimalDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->animal_whisperer_disrt();

    animalDist_ = move(Common::Distribution<EffectSkillAnimal>{
        Common::initializeDistribution<EffectSkillAnimal,
            Common::Bonus
        >(
            Common::convertToVector<Common::Bonus>(dist->animal_dmg())
            )
    });
}

void SkillReference::initExplosiveDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->explosives_distr();

    explosDist_ = move(Common::Distribution<EffectSkillExplosive>{
        Common::initializeDistribution<EffectSkillExplosive,
            Common::Resistance,
            Common::Bonus
        >(
            Common::convertToVector<Common::Resistance>(dist->expl_dmg_resist()),
            Common::convertToVector<Common::Bonus>(dist->expl_dmg_bonus())
            )
    });
}

void SkillReference::initFirstAidDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->first_aid_distr();

    aidDist_ = move(Common::Distribution<EffectSkillFirstAid>{
        Common::initializeDistribution<EffectSkillFirstAid,
            Common::Bonus,
            Common::Bonus
        >(
            Common::convertToVector<Common::Bonus>(dist->healing_item()),
            Common::convertToVector<Common::Bonus>(dist->healing_revive())
            )
    });
}

void SkillReference::initSneakyShitDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->sneaky_shit_distr();

    sneakyDist_ = move(Common::Distribution<EffectSkillSneakyShit>{
        Common::initializeDistribution<EffectSkillSneakyShit,
            Common::Time,
            Common::Initiative,
            Common::Bonus,
            Common::Perception
        >(
            Common::convertToVector<Common::Time>(dist->detection_time()),
            Common::convertToVector<Common::Initiative>(dist->initiative()),
            Common::convertToVector<Common::Bonus>(dist->attack_dmg()),
            Common::convertToVector<Common::Perception>(dist->percep())
            )
    });
}

void SkillReference::initWeirdScienceDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->weird_science_distr();

    weirdDist_ = move(Common::Distribution<EffectSkillWeirdScience>{
        Common::initializeDistribution<EffectSkillWeirdScience,
            Common::Bonus,
            Common::Bonus,
            Common::Bonus
        >(
            Common::convertToVector<Common::Bonus>(dist->energy_dmg()),
            Common::convertToVector<Common::Bonus>(dist->fire_dmg()),
            Common::convertToVector<Common::Bonus>(dist->cold_dmg())
            )
    });
}

void SkillReference::initMechanicsDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->mechanics_distr();

    mechDist_ = move(Common::Distribution<EffectSkillMechanics>{
        Common::initializeDistribution<EffectSkillMechanics,
            Common::Bonus,
            Common::Bonus,
            Common::Bonus,
            Common::Bonus
        >(
            Common::convertToVector<Common::Bonus>(dist->robot_dmg()),
            Common::convertToVector<Common::Bonus>(dist->vehicle_dmg()),
            Common::convertToVector<Common::Bonus>(dist->synth_dmg()),
            Common::convertToVector<Common::Bonus>(dist->repair_kit())
            )
    });
}

void SkillReference::initSurvivalDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->survival_distr();

    survDist_ = move(Common::Distribution<EffectSkillSurvival>{
        Common::initializeDistribution<EffectSkillSurvival,
            Common::Bonus,
            Common::Bonus
        >(
            Common::convertToVector<Common::Bonus>(dist->animal_dmg()),
            Common::convertToVector<Common::Bonus>(dist->mutant_dmg())
            )
    });
}

void SkillReference::initWeaponModDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->weapon_modding_distr();

    weaponModDist_ = move(Common::Distribution<EffectSkillWeaponMod>{
        Common::initializeDistribution<EffectSkillWeaponMod,
            Common::Bonus
        >(
            Common::convertToVector<Common::Bonus>(dist->scrap())
            )
    });
}

void SkillReference::initBarterDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->barter_distr();

    barterDist_ = move(Common::Distribution<EffectSkillBarter>{
        Common::initializeDistribution<EffectSkillBarter,
            Common::Bonus,
            Common::Bonus
        >(
            Common::convertToVector<Common::Bonus>(dist->sell_value()),
            Common::convertToVector<Common::Bonus>(dist->buy_cost())
            )
    });
}

void SkillReference::initLeadershipDist(const fbSkill::FB_Skill* skill)
{
    const auto* dist = skill->leadership_distr();

    leaderDist_ = move(Common::Distribution<EffectSkillLeadership>{
        Common::initializeDistribution<EffectSkillLeadership,
            Common::Chance,
            Common::Bonus,
            Common::Chance,
            Common::Bonus
        >(
            Common::convertToVector<Common::Chance>(dist->hit_chance()),
            Common::convertToVector<Common::Bonus>(dist->boss_kill_dmg()),
            Common::convertToVector<Common::Chance>(dist->multi_kill_crit_chance()),
            Common::convertToVector<Common::Bonus>(dist->revive_con_healed())
            )
    });
}

} // namespace Object
} // namespace Game
