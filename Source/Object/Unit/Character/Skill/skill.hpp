
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_HPP
#define SKILL_HPP

#include"distribution.hpp"
#include"specStorage.hpp"
#include"effectSkill.hpp"
#include"skillAux.hpp"
#include"skillCommon.hpp"
#include"skillFB_generated.h"
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
    using point_t       = common::PointSkill;
    using level_t       = common::LevelSkill;

public:
    Skill(Character& character);

    Skill(const Skill&) = delete;
    Skill& operator=(const Skill&) = delete;

    void initialize(const SkillInitializer& initializer);

    bool isInitialized(bool) const noexcept { return initialized_; }

    static void initialize();

    static bool isInitialized();

public:
    bool addLevel(Skill::Type type, level_t shift) noexcept;

    void addPoint(point_t shift) noexcept {
        pStor_.add(shift);
    }

    bool isModified() const noexcept;

    void accept() noexcept;

    void reject() noexcept;

    void reset() noexcept;

public:
    const common::SpecStorage<level_t>& level(Skill::Type type) const noexcept;

private:
    common::SpecStorage<level_t>& level(Skill::Type type) noexcept;

public:
    const common::SpecStorage<point_t>& storage() const noexcept {
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

    static std::vector<common::SpecStorage<level_t>>  initLevels();

///********** serialization
public:
    flatbuffers::Offset<fbSkill::FB_Skill> serialize(
        flatbuffers::FlatBufferBuilder& fbb) const;

    static std::unique_ptr<Skill> deserialize(
        const fbSkill::FB_Skill* fb,
        Character& character);

private:
    Character&                                              char_;
    std::vector<common::SpecStorage<level_t>>               levels_;
    common::SpecStorage<point_t>                            pStor_;
    common::Distribution<point_t, level_t>                  pDist_;
    common::Distribution<EffectSkillAutomatic, level_t>     automDist_;
    common::Distribution<EffectSkillBigGuns, level_t>       bigGunsDist_;
    common::Distribution<EffectSkillBrawling, level_t>      brawlDist_;
    common::Distribution<EffectSkillMelee, level_t>         meleeDist_;
    common::Distribution<EffectSkillSmallArms, level_t>     smallDist_;
    common::Distribution<EffectSkillSniper, level_t>        sniperDist_;
    common::Distribution<EffectSkillAnimal, level_t>        animalDist_;
    common::Distribution<EffectSkillExplosive, level_t>     explosDist_;
    common::Distribution<EffectSkillFirstAid, level_t>      aidDist_;
    common::Distribution<EffectSkillSneakyShit, level_t>    sneakyDist_;
    common::Distribution<EffectSkillWeirdScience, level_t>  weirdDist_;
    common::Distribution<EffectSkillMechanics, level_t>     mechDist_;
    common::Distribution<EffectSkillSurvival, level_t>      survDist_;
    common::Distribution<EffectSkillWeaponMod, level_t>     weaponModDist_;
    common::Distribution<EffectSkillBarter, level_t>        barterDist_;
    common::Distribution<EffectSkillLeadership, level_t>    leaderDist_;

    bool                                                    initialized_;

    static const SkillReference                             ref_;
    static const SkillText                                  text_;
};

///************************************************************************************************

inline void Skill::initialize()
{
    SkillReference::initialize();
    SkillText::initialize();
}

inline bool Skill::isInitialized()
{
    return ref_.isInitialized() &&
           text_.isInitialized();
}

inline const common::SpecStorage<Skill::level_t>& Skill::level(
    Skill::Type type) const noexcept
{
    assert(common::isValidEnum(type));
    return levels_[common::toUnderlying(type)];
}

inline common::SpecStorage<Skill::level_t>& Skill::level(
    Skill::Type type) noexcept
{
    assert(common::isValidEnum(type));
    return levels_[common::toUnderlying(type)];
}

} // namespace object
} // namespace game

#endif // !SKILL_HPP
