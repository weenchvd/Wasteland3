
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

///************************************************************************************************

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
    return common::changeLevel(level(type), pStor_, pDist_, shift);
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
    auto& lvl{ level(type) };
    auto accLevel{ lvl.getAccepted() };
    auto curLevel{ lvl.get() };
    if (accLevel != curLevel) {
        switch (type) {
        case Skill::Type::AUTOMATIC_WEAPONS: {
            EffectSkillAutomatic sum{ automDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::BIG_GUNS: {
            EffectSkillBigGuns sum{ bigGunsDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::BRAWLING: {
            EffectSkillBrawling sum{ brawlDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::MELEE_COMBAT: {
            EffectSkillMelee sum{ meleeDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::SMALL_ARMS: {
            EffectSkillSmallArms sum{ smallDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::SNIPER_RIFLES: {
            EffectSkillSniper sum{ sniperDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::ANIMAL_WHISPERER: {
            EffectSkillAnimal sum{ animalDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::EXPLOSIVES: {
            EffectSkillExplosive sum{ explosDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::FIRST_AID: {
            EffectSkillFirstAid sum{ aidDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::SNEAKY_SHIT: {
            EffectSkillSneakyShit sum{ sneakyDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::WEIRD_SCIENCE: {
            EffectSkillWeirdScience sum{ weirdDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::MECHANICS: {
            EffectSkillMechanics sum{ mechDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::SURVIVAL: {
            EffectSkillSurvival sum{ survDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::WEAPON_MODDING: {
            EffectSkillWeaponMod sum{ weaponModDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::BARTER: {
            EffectSkillBarter sum{ barterDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Skill::Type::LEADERSHIP: {
            EffectSkillLeadership sum{ leaderDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        default:
            break;
        }
    }
}

vector<common::SpecStorage<Skill::level_t>> Skill::initLevels()
{
    constexpr auto nSkills{ common::numberOf<Skill::Type>() };
    const common::SpecStorage<level_t> tempLevel{
        ref_.minSkillLevel_,
        ref_.maxSkillLevel_
    };
    return vector<common::SpecStorage<level_t>>(nSkills, tempLevel);
}

flatbuffers::Offset<fbSkill::FB_Skill> Skill::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    using sk_t = fbSkill::FB_Skill;
    using common::checkedEnum;

    fbSkill::FB_SkillBuilder b{ fbb };
    b.add_skill_points(checkedEnum<decltype(&sk_t::skill_points), sk_t>(storage().getAccepted()));

    b.add_automatic_level(checkedEnum<decltype(&sk_t::automatic_level), sk_t>(
        level(Type::AUTOMATIC_WEAPONS).getAccepted()));
    b.add_big_guns_level(checkedEnum<decltype(&sk_t::big_guns_level), sk_t>(
        level(Type::BIG_GUNS).getAccepted()));
    b.add_brawling_level(checkedEnum<decltype(&sk_t::brawling_level), sk_t>(
        level(Type::BRAWLING).getAccepted()));
    b.add_melee_level(checkedEnum<decltype(&sk_t::melee_level), sk_t>(
        level(Type::MELEE_COMBAT).getAccepted()));
    b.add_small_arms_level(checkedEnum<decltype(&sk_t::small_arms_level), sk_t>(
        level(Type::SMALL_ARMS).getAccepted()));
    b.add_sniper_level(checkedEnum<decltype(&sk_t::sniper_level), sk_t>(
        level(Type::SNIPER_RIFLES).getAccepted()));

    b.add_animal_whisperer_level(checkedEnum<decltype(&sk_t::animal_whisperer_level), sk_t>(
        level(Type::ANIMAL_WHISPERER).getAccepted()));
    b.add_explosives_level(checkedEnum<decltype(&sk_t::explosives_level), sk_t>(
        level(Type::EXPLOSIVES).getAccepted()));
    b.add_first_aid_level(checkedEnum<decltype(&sk_t::first_aid_level), sk_t>(
        level(Type::FIRST_AID).getAccepted()));
    b.add_sneaky_shit_level(checkedEnum<decltype(&sk_t::sneaky_shit_level), sk_t>(
        level(Type::SNEAKY_SHIT).getAccepted()));
    b.add_weird_science_level(checkedEnum<decltype(&sk_t::weird_science_level), sk_t>(
        level(Type::WEIRD_SCIENCE).getAccepted()));

    b.add_armor_modding_level(checkedEnum<decltype(&sk_t::armor_modding_level), sk_t>(
        level(Type::ARMOR_MODDING).getAccepted()));
    b.add_lockpicking_level(checkedEnum<decltype(&sk_t::lockpicking_level), sk_t>(
        level(Type::LOCKPICKING).getAccepted()));
    b.add_nerd_stuff_level(checkedEnum<decltype(&sk_t::nerd_stuff_level), sk_t>(
        level(Type::NERD_STUFF).getAccepted()));
    b.add_mechanics_level(checkedEnum<decltype(&sk_t::mechanics_level), sk_t>(
        level(Type::MECHANICS).getAccepted()));
    b.add_survival_level(checkedEnum<decltype(&sk_t::survival_level), sk_t>(
        level(Type::SURVIVAL).getAccepted()));
    b.add_toaster_repair_level(checkedEnum<decltype(&sk_t::toaster_repair_level), sk_t>(
        level(Type::TOASTER_REPAIR).getAccepted()));
    b.add_weapon_modding_level(checkedEnum<decltype(&sk_t::weapon_modding_level), sk_t>(
        level(Type::WEAPON_MODDING).getAccepted()));

    b.add_barter_level(checkedEnum<decltype(&sk_t::barter_level), sk_t>(
        level(Type::BARTER).getAccepted()));
    b.add_hard_ass_level(checkedEnum<decltype(&sk_t::hard_ass_level), sk_t>(
        level(Type::HARD_ASS).getAccepted()));
    b.add_kiss_ass_level(checkedEnum<decltype(&sk_t::kiss_ass_level), sk_t>(
        level(Type::KISS_ASS).getAccepted()));
    b.add_leadership_level(checkedEnum<decltype(&sk_t::leadership_level), sk_t>(
        level(Type::LEADERSHIP).getAccepted()));
    return b.Finish();
}

unique_ptr<Skill> Skill::deserialize(
    const fbSkill::FB_Skill* fb,
    Character& character)
{
    assert(fb != nullptr);
    auto s{ make_unique<Skill>(character) };
    s->pStor_.add(point_t{ fb->skill_points() });
    s->pStor_.accept();

    s->level(Type::AUTOMATIC_WEAPONS).add(level_t{ fb->automatic_level() });
    s->level(Type::AUTOMATIC_WEAPONS).accept();
    s->level(Type::BIG_GUNS).add(level_t{ fb->big_guns_level() });
    s->level(Type::BIG_GUNS).accept();
    s->level(Type::BRAWLING).add(level_t{ fb->brawling_level() });
    s->level(Type::BRAWLING).accept();
    s->level(Type::MELEE_COMBAT).add(level_t{ fb->melee_level() });
    s->level(Type::MELEE_COMBAT).accept();
    s->level(Type::SMALL_ARMS).add(level_t{ fb->small_arms_level() });
    s->level(Type::SMALL_ARMS).accept();
    s->level(Type::SNIPER_RIFLES).add(level_t{ fb->sniper_level() });
    s->level(Type::SNIPER_RIFLES).accept();

    s->level(Type::ANIMAL_WHISPERER).add(level_t{ fb->animal_whisperer_level() });
    s->level(Type::ANIMAL_WHISPERER).accept();
    s->level(Type::EXPLOSIVES).add(level_t{ fb->explosives_level() });
    s->level(Type::EXPLOSIVES).accept();
    s->level(Type::FIRST_AID).add(level_t{ fb->first_aid_level() });
    s->level(Type::FIRST_AID).accept();
    s->level(Type::SNEAKY_SHIT).add(level_t{ fb->sneaky_shit_level() });
    s->level(Type::SNEAKY_SHIT).accept();
    s->level(Type::WEIRD_SCIENCE).add(level_t{ fb->weird_science_level() });
    s->level(Type::WEIRD_SCIENCE).accept();

    s->level(Type::ARMOR_MODDING).add(level_t{ fb->armor_modding_level() });
    s->level(Type::ARMOR_MODDING).accept();
    s->level(Type::LOCKPICKING).add(level_t{ fb->lockpicking_level() });
    s->level(Type::LOCKPICKING).accept();
    s->level(Type::NERD_STUFF).add(level_t{ fb->nerd_stuff_level() });
    s->level(Type::NERD_STUFF).accept();
    s->level(Type::MECHANICS).add(level_t{ fb->mechanics_level() });
    s->level(Type::MECHANICS).accept();
    s->level(Type::SURVIVAL).add(level_t{ fb->survival_level() });
    s->level(Type::SURVIVAL).accept();
    s->level(Type::TOASTER_REPAIR).add(level_t{ fb->toaster_repair_level() });
    s->level(Type::TOASTER_REPAIR).accept();
    s->level(Type::WEAPON_MODDING).add(level_t{ fb->weapon_modding_level() });
    s->level(Type::WEAPON_MODDING).accept();

    s->level(Type::BARTER).add(level_t{ fb->barter_level() });
    s->level(Type::BARTER).accept();
    s->level(Type::HARD_ASS).add(level_t{ fb->hard_ass_level() });
    s->level(Type::HARD_ASS).accept();
    s->level(Type::KISS_ASS).add(level_t{ fb->kiss_ass_level() });
    s->level(Type::KISS_ASS).accept();
    s->level(Type::LEADERSHIP).add(level_t{ fb->leadership_level() });
    s->level(Type::LEADERSHIP).accept();
    return s;
}

} //namespace object
} // namespace game
