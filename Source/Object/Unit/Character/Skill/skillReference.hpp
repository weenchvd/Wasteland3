
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
    using level_t = common::LevelSkill;

private:
    friend class Skill;

private:
    SkillReference() noexcept {}

public:
    SkillReference(const SkillReference&) = delete;
    SkillReference& operator=(const SkillReference&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

private:
    static void initPointDist(const fbSkill::FB_SkillReference* fb);
    static void initAutomaticDist(const fbSkill::FB_SkillReference* fb);
    static void initBigGunsDist(const fbSkill::FB_SkillReference* fb);
    static void initBrawlingDist(const fbSkill::FB_SkillReference* fb);
    static void initMeleeDist(const fbSkill::FB_SkillReference* fb);
    static void initSmallArmsDist(const fbSkill::FB_SkillReference* fb);
    static void initSniperDist(const fbSkill::FB_SkillReference* fb);
    static void initAnimalDist(const fbSkill::FB_SkillReference* fb);
    static void initExplosiveDist(const fbSkill::FB_SkillReference* fb);
    static void initFirstAidDist(const fbSkill::FB_SkillReference* fb);
    static void initSneakyShitDist(const fbSkill::FB_SkillReference* fb);
    static void initWeirdScienceDist(const fbSkill::FB_SkillReference* fb);
    static void initMechanicsDist(const fbSkill::FB_SkillReference* fb);
    static void initSurvivalDist(const fbSkill::FB_SkillReference* fb);
    static void initWeaponModDist(const fbSkill::FB_SkillReference* fb);
    static void initBarterDist(const fbSkill::FB_SkillReference* fb);
    static void initLeadershipDist(const fbSkill::FB_SkillReference* fb);

private:
    static common::Distribution<point_t, level_t>                   pDist_;         // distribution of skill points
    static common::Distribution<EffectSkillAutomatic, level_t>      automDist_;
    static common::Distribution<EffectSkillBigGuns, level_t>        bigGunsDist_;
    static common::Distribution<EffectSkillBrawling, level_t>       brawlDist_;
    static common::Distribution<EffectSkillMelee, level_t>          meleeDist_;
    static common::Distribution<EffectSkillSmallArms, level_t>      smallDist_;
    static common::Distribution<EffectSkillSniper, level_t>         sniperDist_;
    static common::Distribution<EffectSkillAnimal, level_t>         animalDist_;
    static common::Distribution<EffectSkillExplosive, level_t>      explosDist_;
    static common::Distribution<EffectSkillFirstAid, level_t>       aidDist_;
    static common::Distribution<EffectSkillSneakyShit, level_t>     sneakyDist_;
    static common::Distribution<EffectSkillWeirdScience, level_t>   weirdDist_;
    static common::Distribution<EffectSkillMechanics, level_t>      mechDist_;
    static common::Distribution<EffectSkillSurvival, level_t>       survDist_;
    static common::Distribution<EffectSkillWeaponMod, level_t>      weaponModDist_;
    static common::Distribution<EffectSkillBarter, level_t>         barterDist_;
    static common::Distribution<EffectSkillLeadership, level_t>     leaderDist_;

    static point_t                          minSkillPoints_;    // min skill points
    static point_t                          maxSkillPoints_;    // max skill points
    static level_t                          minSkillLevel_;     // min skill level
    static level_t                          maxSkillLevel_;     // max skill level
    static bool                             initialized_;
};

} // namespace object
} // namespace game

#endif // !SKILL_REFERENCE_HPP
