
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

class SkillReference {
public:
    using point_t = common::PointSkill;
    using level_t = common::LevelStat;

private:
    friend class Skill;

private:
    SkillReference() noexcept {}

public:
    SkillReference(const SkillReference&) = delete;
    SkillReference& operator=(const SkillReference&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static point_t initialSkillPoints() noexcept { return initSkillPoints_; }

    static point_t initialSkillLevel() noexcept { return initSkillLevel_; }

private:
    static void initPointDist(const fbSkill::FB_Skill* fb);
    static void initAutomaticDist(const fbSkill::FB_Skill* fb);
    static void initBigGunsDist(const fbSkill::FB_Skill* fb);
    static void initBrawlingDist(const fbSkill::FB_Skill* fb);
    static void initMeleeDist(const fbSkill::FB_Skill* fb);
    static void initSmallArmsDist(const fbSkill::FB_Skill* fb);
    static void initSniperDist(const fbSkill::FB_Skill* fb);
    static void initAnimalDist(const fbSkill::FB_Skill* fb);
    static void initExplosiveDist(const fbSkill::FB_Skill* fb);
    static void initFirstAidDist(const fbSkill::FB_Skill* fb);
    static void initSneakyShitDist(const fbSkill::FB_Skill* fb);
    static void initWeirdScienceDist(const fbSkill::FB_Skill* fb);
    static void initMechanicsDist(const fbSkill::FB_Skill* fb);
    static void initSurvivalDist(const fbSkill::FB_Skill* fb);
    static void initWeaponModDist(const fbSkill::FB_Skill* fb);
    static void initBarterDist(const fbSkill::FB_Skill* fb);
    static void initLeadershipDist(const fbSkill::FB_Skill* fb);

private:
    static common::Distribution<point_t>                    pDist_;         // distribution of skill points
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

    static point_t                          minSkillPoints_;    // min skill points
    static point_t                          maxSkillPoints_;    // max skill points
    static point_t                          initSkillPoints_;   // initial skill points
    static level_t                          minSkillLevel_;     // min skill level
    static level_t                          maxSkillLevel_;     // max skill level
    static level_t                          initSkillLevel_;    // initial skill level
    static bool                             initialized_;
};

} // namespace object
} // namespace game

#endif // !SKILL_REFERENCE_HPP
