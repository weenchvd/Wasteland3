
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_REFERENCE_HPP
#define SKILL_REFERENCE_HPP

#include"common.hpp"
#include"distribution.hpp"
#include"effectSkill.hpp"
#include"skillReferenceFB_generated.h"

namespace game {
namespace object {

struct SkillReference {
    using PointSkill        = common::PointSkill;
    using LevelStat         = common::LevelStat;

    SkillReference() noexcept {}

    SkillReference(const SkillReference&) = delete;
    SkillReference& operator=(const SkillReference&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

private:
    static void initPointDist(const fbSkill::FB_Skill* skill);
    static void initAutomaticDist(const fbSkill::FB_Skill* skill);
    static void initBigGunsDist(const fbSkill::FB_Skill* skill);
    static void initBrawlingDist(const fbSkill::FB_Skill* skill);
    static void initMeleeDist(const fbSkill::FB_Skill* skill);
    static void initSmallArmsDist(const fbSkill::FB_Skill* skill);
    static void initSniperDist(const fbSkill::FB_Skill* skill);
    static void initAnimalDist(const fbSkill::FB_Skill* skill);
    static void initExplosiveDist(const fbSkill::FB_Skill* skill);
    static void initFirstAidDist(const fbSkill::FB_Skill* skill);
    static void initSneakyShitDist(const fbSkill::FB_Skill* skill);
    static void initWeirdScienceDist(const fbSkill::FB_Skill* skill);
    static void initMechanicsDist(const fbSkill::FB_Skill* skill);
    static void initSurvivalDist(const fbSkill::FB_Skill* skill);
    static void initWeaponModDist(const fbSkill::FB_Skill* skill);
    static void initBarterDist(const fbSkill::FB_Skill* skill);
    static void initLeadershipDist(const fbSkill::FB_Skill* skill);

public:
    static common::Distribution<PointSkill>                 pDist_;             // distribution of skill points
    static common::Distribution<EffectSkillAutomatic>       automDist_;
    static common::Distribution<EffectSkillBigGuns>         bigGunsDist_;
    static common::Distribution<EffectSkillBrawling>        brawlDist_;
    static common::Distribution<EffectSkillMelee>           meleeDist_;
    static common::Distribution<EffectSkillSmallArms>       smallDist_;
    static common::Distribution<EffectSkillSniper>          sniperDist_;
    static common::Distribution<EffectSkillAnimal>          animalDist_;
    static common::Distribution<EffectSkillExplosive>       explosDist_;
    static common::Distribution<EffectSkillFirstAid>        aidDist_;
    static common::Distribution<EffectSkillSneakyShit>      sneakyDist_;
    static common::Distribution<EffectSkillWeirdScience>    weirdDist_;
    static common::Distribution<EffectSkillMechanics>       mechDist_;
    static common::Distribution<EffectSkillSurvival>        survDist_;
    static common::Distribution<EffectSkillWeaponMod>       weaponModDist_;
    static common::Distribution<EffectSkillBarter>          barterDist_;
    static common::Distribution<EffectSkillLeadership>      leaderDist_;

    static PointSkill                       minSkillPoints_;    // min skill points
    static PointSkill                       maxSkillPoints_;    // max skill points
    static PointSkill                       initSkillPoints_;   // initial skill points
    static LevelStat                        minSkillLevel_;     // min skill level
    static LevelStat                        maxSkillLevel_;     // max skill level
    static LevelStat                        initSkillLevel_;    // initial skill level
    static bool                             initialized_;
};

} // namespace object
} // namespace game

#endif // !SKILL_REFERENCE_HPP
