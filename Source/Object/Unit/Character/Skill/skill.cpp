
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"locator.hpp"
#include"skill.hpp"
#include<assert.h>

namespace game {
namespace object {

using namespace std;

const SkillReference    Skill::ref_;
const SkillText         Skill::text_;

Skill::Skill(Character& character)
    :
    char_           { character },
    levels_         { initLevels() },
    pDist_          { ref_.pDist_ },
    pStor_          { ref_.minSkillPoints_, ref_.maxSkillPoints_ },
    automDist_      { ref_.automDist_ },
    bigGunsDist_    { ref_.bigGunsDist_ },
    brawlDist_      { ref_.brawlDist_ },
    meleeDist_      { ref_.meleeDist_ },
    smallDist_      { ref_.smallDist_ },
    sniperDist_     { ref_.sniperDist_ },
    animalDist_     { ref_.animalDist_ },
    explosDist_     { ref_.explosDist_ },
    aidDist_        { ref_.aidDist_ },
    sneakyDist_     { ref_.sneakyDist_ },
    weirdDist_      { ref_.weirdDist_ },
    mechDist_       { ref_.mechDist_ },
    survDist_       { ref_.survDist_ },
    weaponModDist_  { ref_.weaponModDist_ },
    barterDist_     { ref_.barterDist_ },
    leaderDist_     { ref_.leaderDist_ }
{
    assert(isInitialized());
}

bool Skill::addLevel(Skill::Type type, level_t shift) noexcept
{
    auto index = common::toUnderlying(type);
    return common::changeLevel(levels_[index], pStor_, pDist_, shift);
}

bool Skill::isModified() const noexcept
{
    if (pStor_.get() != pStor_.getAccepted()) {
        return true;
    }
    for (const common::SpecStorage<level_t>& level : levels_) {
        if (level.get() != level.getAccepted()) {
            return true;
        }
    }
    return false;
}

void Skill::accept() noexcept
{
    apply();
    for (common::SpecStorage<level_t>& level : levels_) {
        level.accept();
    }
    pStor_.accept();
}

void Skill::reject() noexcept
{
    for (common::SpecStorage<level_t>& level : levels_) {
        level.reject();
    }
    pStor_.reject();
}

void Skill::reset() noexcept
{
    for (common::SpecStorage<level_t>& level : levels_) {
        level.reset();
    }
    pStor_.reset();
}

void Skill::apply() noexcept
{
    apply(Skill::Type::AUTOMATIC_WEAPONS);
    apply(Skill::Type::BIG_GUNS);
    apply(Skill::Type::BRAWLING);
    apply(Skill::Type::MELEE_COMBAT);
    apply(Skill::Type::SMALL_ARMS);
    apply(Skill::Type::SNIPER_RIFLES);
    apply(Skill::Type::ANIMAL_WHISPERER);
    apply(Skill::Type::EXPLOSIVES);
    apply(Skill::Type::FIRST_AID);
    apply(Skill::Type::SNEAKY_SHIT);
    apply(Skill::Type::WEIRD_SCIENCE);
    apply(Skill::Type::ARMOR_MODDING);
    apply(Skill::Type::LOCKPICKING);
    apply(Skill::Type::NERD_STUFF);
    apply(Skill::Type::MECHANICS);
    apply(Skill::Type::SURVIVAL);
    apply(Skill::Type::TOASTER_REPAIR);
    apply(Skill::Type::WEAPON_MODDING);
    apply(Skill::Type::BARTER);
    apply(Skill::Type::HARD_ASS);
    apply(Skill::Type::KISS_ASS);
    apply(Skill::Type::LEADERSHIP);
}

void Skill::apply(Skill::Type type) noexcept
{
    auto index = common::toUnderlying(type);
    auto accLevel = levels_[index].getAccepted();
    auto curLevel = levels_[index].get();
    if (accLevel != curLevel) {
        switch (type) {
        case Skill::Type::AUTOMATIC_WEAPONS: {
            EffectSkillAutomatic sum = automDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::BIG_GUNS: {
            EffectSkillBigGuns sum = bigGunsDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::BRAWLING: {
            EffectSkillBrawling sum = brawlDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::MELEE_COMBAT: {
            EffectSkillMelee sum = meleeDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::SMALL_ARMS: {
            EffectSkillSmallArms sum = smallDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::SNIPER_RIFLES: {
            EffectSkillSniper sum = sniperDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::ANIMAL_WHISPERER: {
            EffectSkillAnimal sum = animalDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::EXPLOSIVES: {
            EffectSkillExplosive sum = explosDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::FIRST_AID: {
            EffectSkillFirstAid sum = aidDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::SNEAKY_SHIT: {
            EffectSkillSneakyShit sum = sneakyDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::WEIRD_SCIENCE: {
            EffectSkillWeirdScience sum = weirdDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::MECHANICS: {
            EffectSkillMechanics sum = mechDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::SURVIVAL: {
            EffectSkillSurvival sum = survDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::WEAPON_MODDING: {
            EffectSkillWeaponMod sum = weaponModDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::BARTER: {
            EffectSkillBarter sum = barterDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        case Skill::Type::LEADERSHIP: {
            EffectSkillLeadership sum = leaderDist_.total(accLevel, curLevel);
            sum.apply(char_);
            break;
        }
        default:
            break;
        }
    }
}

void Skill::initialize()
{
    SkillReference::initialize();
    SkillText::initialize();
}

bool Skill::isInitialized()
{
    return ref_.isInitialized()
        && text_.isInitialized();
}

vector<common::SpecStorage<Skill::level_t>> Skill::initLevels()
{
    constexpr auto nSkills = common::numberOf<Skill::Type>();
    const common::SpecStorage<level_t> tempLevel{
        ref_.minSkillLevel_,
        ref_.maxSkillLevel_
    };
    return vector<common::SpecStorage<level_t>>(nSkills, tempLevel);
}

} //namespace object
} // namespace game
