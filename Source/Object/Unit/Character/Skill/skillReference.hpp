
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

namespace Game {
namespace Object {

struct SkillReference {
    using PointSkill        = Common::PointSkill;
    using LevelStat         = Common::LevelStat;

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
    static Common::Distribution<PointSkill>                 pDist_;             // distribution of skill points
    static Common::Distribution<EffectSkillAutomatic>       automDist_;
    static Common::Distribution<EffectSkillBigGuns>         bigGunsDist_;
    static Common::Distribution<EffectSkillBrawling>        brawlDist_;
    static Common::Distribution<EffectSkillMelee>           meleeDist_;
    static Common::Distribution<EffectSkillSmallArms>       smallDist_;
    static Common::Distribution<EffectSkillSniper>          sniperDist_;
    static Common::Distribution<EffectSkillAnimal>          animalDist_;
    static Common::Distribution<EffectSkillExplosive>       explosDist_;
    static Common::Distribution<EffectSkillFirstAid>        aidDist_;
    static Common::Distribution<EffectSkillSneakyShit>      sneakyDist_;
    static Common::Distribution<EffectSkillWeirdScience>    weirdDist_;
    static Common::Distribution<EffectSkillMechanics>       mechDist_;
    static Common::Distribution<EffectSkillSurvival>        survDist_;
    static Common::Distribution<EffectSkillWeaponMod>       weaponModDist_;
    static Common::Distribution<EffectSkillBarter>          barterDist_;
    static Common::Distribution<EffectSkillLeadership>      leaderDist_;

    static PointSkill                       minSkillPoints_;    // min skill points
    static PointSkill                       maxSkillPoints_;    // max skill points
    static PointSkill                       initSkillPoints_;   // initial skill points
    static LevelStat                        minSkillLevel_;     // min skill level
    static LevelStat                        maxSkillLevel_;     // max skill level
    static LevelStat                        initSkillLevel_;    // initial skill level
    static bool                             initialized_;
};

} // namespace Object
} // namespace Game

#endif // !SKILL_REFERENCE_HPP
