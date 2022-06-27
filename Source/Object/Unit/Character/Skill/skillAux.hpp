
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_AUX_HPP
#define SKILL_AUX_HPP

#include"skillFB_generated.h"
#include"common.hpp"

namespace game {
namespace object {

class SkillInitializer {
public:
    using point_t = common::PointSkill;
    using level_t = common::LevelSkill;

private:
    friend class Skill;

public:
    SkillInitializer() noexcept;

    SkillInitializer(const fbSkill::FB_Skill* fb) noexcept;

    SkillInitializer(const SkillInitializer&) = delete;
    SkillInitializer& operator=(const SkillInitializer&) = delete;
    SkillInitializer(SkillInitializer&&) = default;
    SkillInitializer& operator=(SkillInitializer&&) = default;

    void initialize(const fbSkill::FB_Skill* fb) noexcept;

    bool isInitialized() const noexcept { return initialized_; }

private:
    point_t                                 skillPoints_;
    level_t                                 automaticLevel_;
    level_t                                 bigGunsLevel_;
    level_t                                 brawlingLevel_;
    level_t                                 meleeLevel_;
    level_t                                 smallArmsLevel_;
    level_t                                 sniperLevel_;
    level_t                                 animalWhispererLevel_;
    level_t                                 explosivesLevel_;
    level_t                                 firstAidLevel_;
    level_t                                 sneakyShitLevel_;
    level_t                                 weirdScienceLevel_;
    level_t                                 armorModdingLevel_;
    level_t                                 lockpickingLevel_;
    level_t                                 nerdStuffLevel_;
    level_t                                 mechanicsLevel_;
    level_t                                 survivalLevel_;
    level_t                                 toasterRepairLevel_;
    level_t                                 weaponModdingLevel_;
    level_t                                 barterLevel_;
    level_t                                 hardAssLevel_;
    level_t                                 kissAssLevel_;
    level_t                                 leadershipLevel_;

    bool                                    initialized_;
};

} // namespace object
} // namespace game

#endif // !SKILL_AUX_HPP
