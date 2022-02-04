
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

namespace Game {
namespace Object {

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
    void addLevel(Skill::Type type, Common::LevelStat shift) noexcept;

    void addPoint(Common::PointSkill shift) noexcept {
        pStor_.add(shift);
    }

    bool isModified() const noexcept;

    void accept() noexcept;

    void reject() noexcept;

    void reset() noexcept;

public:
    const Common::SpecStorage<Common::LevelStat>& level(Skill::Type type) const noexcept {
        assert(Common::isValidEnum(type));
        return levels_[Common::toUnderlying(type)];
    }

    const Common::SpecStorage<Common::PointSkill>& storage() const noexcept {
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

    static std::vector<Common::SpecStorage<Common::LevelStat>>  initLevels();

private:
    Character&                                              char_;
    std::vector<Common::SpecStorage<Common::LevelStat>>     levels_;
    Common::SpecStorage<Common::PointSkill>                 pStor_;
    Common::Distribution<Common::PointSkill>                pDist_;
    Common::Distribution<EffectSkillAutomatic>              automDist_;
    Common::Distribution<EffectSkillBigGuns>                bigGunsDist_;
    Common::Distribution<EffectSkillBrawling>               brawlDist_;
    Common::Distribution<EffectSkillMelee>                  meleeDist_;
    Common::Distribution<EffectSkillSmallArms>              smallDist_;
    Common::Distribution<EffectSkillSniper>                 sniperDist_;
    Common::Distribution<EffectSkillAnimal>                 animalDist_;
    Common::Distribution<EffectSkillExplosive>              explosDist_;
    Common::Distribution<EffectSkillFirstAid>               aidDist_;
    Common::Distribution<EffectSkillSneakyShit>             sneakyDist_;
    Common::Distribution<EffectSkillWeirdScience>           weirdDist_;
    Common::Distribution<EffectSkillMechanics>              mechDist_;
    Common::Distribution<EffectSkillSurvival>               survDist_;
    Common::Distribution<EffectSkillWeaponMod>              weaponModDist_;
    Common::Distribution<EffectSkillBarter>                 barterDist_;
    Common::Distribution<EffectSkillLeadership>             leaderDist_;

    static const SkillReference                             ref_;
    static const SkillText                                  text_;
};

} // namespace Object
} // namespace Game

#endif // !SKILL_HPP
