
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_HPP
#define SKILL_HPP

#include"distribution.hpp"
#include"specStorage.hpp"
#include"effectSkill.hpp"
#include"skillCommon.hpp"
#include"skillReference.hpp"
#include"skillText.hpp"
#include<vector>

namespace game {
namespace object {

class Character;

class Skill {
public:
    using Type          = Skill__Type;
    using Group         = Skill__Group;

public:
    Skill(Character& character);

    Skill(const Skill&) = delete;
    Skill& operator=(const Skill&) = delete;

    static void initialize();

    static bool isInitialized();

public:
    void addLevel(Skill::Type type, common::LevelStat shift) noexcept;

    void addPoint(common::PointSkill shift) noexcept {
        pStor_.add(shift);
    }

    bool isModified() const noexcept;

    void accept() noexcept;

    void reject() noexcept;

    void reset() noexcept;

public:
    const common::SpecStorage<common::LevelStat>& level(Skill::Type type) const noexcept {
        assert(common::isValidEnum(type));
        return levels_[common::toUnderlying(type)];
    }

    const common::SpecStorage<common::PointSkill>& storage() const noexcept {
        return pStor_;
    }

    static const SkillReference& skillReference() noexcept {
        return ref_;
    }

    static const SkillText& skillText() noexcept {
        return text_;
    }

private:
    void apply() noexcept;

    void apply(Skill::Type type) noexcept;

    static std::vector<common::SpecStorage<common::LevelStat>>  initLevels();

private:
    Character&                                              char_;
    std::vector<common::SpecStorage<common::LevelStat>>     levels_;
    common::SpecStorage<common::PointSkill>                 pStor_;
    common::Distribution<common::PointSkill>                pDist_;
    common::Distribution<EffectSkillAutomatic>              automDist_;
    common::Distribution<EffectSkillBigGuns>                bigGunsDist_;
    common::Distribution<EffectSkillBrawling>               brawlDist_;
    common::Distribution<EffectSkillMelee>                  meleeDist_;
    common::Distribution<EffectSkillSmallArms>              smallDist_;
    common::Distribution<EffectSkillSniper>                 sniperDist_;
    common::Distribution<EffectSkillAnimal>                 animalDist_;
    common::Distribution<EffectSkillExplosive>              explosDist_;
    common::Distribution<EffectSkillFirstAid>               aidDist_;
    common::Distribution<EffectSkillSneakyShit>             sneakyDist_;
    common::Distribution<EffectSkillWeirdScience>           weirdDist_;
    common::Distribution<EffectSkillMechanics>              mechDist_;
    common::Distribution<EffectSkillSurvival>               survDist_;
    common::Distribution<EffectSkillWeaponMod>              weaponModDist_;
    common::Distribution<EffectSkillBarter>                 barterDist_;
    common::Distribution<EffectSkillLeadership>             leaderDist_;

    static const SkillReference                             ref_;
    static const SkillText                                  text_;
};

} // namespace object
} // namespace game

#endif // !SKILL_HPP
