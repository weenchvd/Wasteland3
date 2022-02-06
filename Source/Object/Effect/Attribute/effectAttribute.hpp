
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef EFFECT_ATTRIBUTE_HPP
#define EFFECT_ATTRIBUTE_HPP

#include"common.hpp"
#include"effect.hpp"
#include<memory>

namespace game {
namespace object {

class EffectAttCoord : public Effect {
public:
    EffectAttCoord() noexcept
        :
        resStatEff_ { 0 },
        apMax_      { 0 },
        apCur_      { 0 }
    {}

    EffectAttCoord(
        common::Resistance statusEffect,
        common::ActionPoint maximum,
        common::ActionPoint current) noexcept;

    virtual ~EffectAttCoord() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectAttCoord& operator+=(const EffectAttCoord& other) noexcept;
    EffectAttCoord& operator-=(const EffectAttCoord& other) noexcept;

private:
    common::Resistance          resStatEff_;    // status effect resistance
    common::ActionPoint         apMax_;         // action points (maximum)
    common::ActionPoint         apCur_;         // action points (current)
};

EffectAttCoord operator+(const EffectAttCoord& left, const EffectAttCoord& right) noexcept;
EffectAttCoord operator-(const EffectAttCoord& left, const EffectAttCoord& right) noexcept;

///------------------------------------------------------------------------------------------------

class EffectAttLuck : public Effect {
public:
    EffectAttLuck() noexcept
        :
        armorPen_           { 0 },
        chaLuckAction_      { 0 },
        chaLuckCritDmg_     { 0 },
        chaLuckMegaCritDmg_ { 0 },
        chaLuckEvade_       { 0 },
        chaLuckCritRes_     { 0 },
        chaLuckDblHeal_     { 0 },
        chaLuckDblMoney_    { 0 },
        chaLuckDblScrap_    { 0 }
    {}

    EffectAttLuck(
        common::Armor penetration,
        common::Chance luckyAction,
        common::Chance luckyCritDamage,
        common::Chance luckyMegaCritDamage,
        common::Chance luckyEvade,
        common::Chance luckyCritResist,
        common::Chance luckyDoubleHealing,
        common::Chance luckyDoubleMoney,
        common::Chance luckyDoubleScrap) noexcept;

    virtual ~EffectAttLuck() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectAttLuck& operator+=(const EffectAttLuck& other) noexcept;
    EffectAttLuck& operator-=(const EffectAttLuck& other) noexcept;

private:
    common::Armor               armorPen_;          // penetration
    common::Chance              chaLuckAction_;     // lucky action chance
    common::Chance              chaLuckCritDmg_;    // lucky critical damage chance
    common::Chance              chaLuckMegaCritDmg_;// lucky mega critical damage chance
    common::Chance              chaLuckEvade_;      // lucky evade chance
    common::Chance              chaLuckCritRes_;    // lucky critical resist chance
    common::Chance              chaLuckDblHeal_;    // lucky double healing chance
    common::Chance              chaLuckDblMoney_;   // lucky double money chance
    common::Chance              chaLuckDblScrap_;   // lucky double scrap chance
};

EffectAttLuck operator+(const EffectAttLuck& left, const EffectAttLuck& right) noexcept;
EffectAttLuck operator-(const EffectAttLuck& left, const EffectAttLuck& right) noexcept;

///------------------------------------------------------------------------------------------------

class EffectAttAware : public Effect {
public:
    EffectAttAware() noexcept
        :
        chaHit_         { 0 },
        percept_        { 0 },
        bonRangeDmg_    { 0 }
    {}

    EffectAttAware(
        common::Chance hit,
        common::Perception perception,
        common::Bonus rangedDamage) noexcept;

    virtual ~EffectAttAware() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectAttAware& operator+=(const EffectAttAware& other) noexcept;
    EffectAttAware& operator-=(const EffectAttAware& other) noexcept;

private:
    common::Chance              chaHit_;        // base hit chance
    common::Perception          percept_;       // perception
    common::Bonus               bonRangeDmg_;   // ranged damage bonus
};

EffectAttAware operator+(const EffectAttAware& left, const EffectAttAware& right) noexcept;
EffectAttAware operator-(const EffectAttAware& left, const EffectAttAware& right) noexcept;

///------------------------------------------------------------------------------------------------

class EffectAttStr : public Effect {
public:
    EffectAttStr() noexcept
        :
        conMax_         { 0 },
        conPerLvl_      { 0 },
        bonMeleeDmg_    { 0 },
        mulThrow_       { 0 }
    {}

    EffectAttStr(
        common::Constitution maximum,
        common::Constitution perLevel,
        common::Bonus meleeDamage,
        common::Multiplier throwingRange) noexcept;

    virtual ~EffectAttStr() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectAttStr& operator+=(const EffectAttStr& other) noexcept;
    EffectAttStr& operator-=(const EffectAttStr& other) noexcept;

private:
    common::Constitution        conMax_;        // constitution max value
    common::Constitution        conPerLvl_;     // constitution per level
    common::Bonus               bonMeleeDmg_;   // melee damage bonus
    common::Multiplier          mulThrow_;      // throwing range multiplier
};

EffectAttStr operator+(const EffectAttStr& left, const EffectAttStr& right) noexcept;
EffectAttStr operator-(const EffectAttStr& left, const EffectAttStr& right) noexcept;

///------------------------------------------------------------------------------------------------

class EffectAttSpeed : public Effect {
public:
    EffectAttSpeed() noexcept
        :
        mulSpeed_   { 0 },
        evasion_    { 0 },
        initiat_    { 0 }
    {}

    EffectAttSpeed(
        common::Multiplier combatSpeed,
        common::Evasion evasion,
        common::Initiative initiative) noexcept;

    virtual ~EffectAttSpeed() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectAttSpeed& operator+=(const EffectAttSpeed& other) noexcept;
    EffectAttSpeed& operator-=(const EffectAttSpeed& other) noexcept;

private:
    common::Multiplier          mulSpeed_;      // combat speed multiplier
    common::Evasion             evasion_;       // evasion
    common::Initiative          initiat_;       // initiative
};

EffectAttSpeed operator+(const EffectAttSpeed& left, const EffectAttSpeed& right) noexcept;
EffectAttSpeed operator-(const EffectAttSpeed& left, const EffectAttSpeed& right) noexcept;

///------------------------------------------------------------------------------------------------

class EffectAttInt : public Effect {
public:
    EffectAttInt() noexcept
        :
        chaCritDmg_     { 0 },
        mulCritDmg_     { 0 },
        chaCritHeal_    { 0 },
        bonCritHeal_    { 0 },
        poSkill_        { 0 }
    {}

    EffectAttInt(
        common::Chance critDamageChance,
        common::Multiplier critDamageMult,
        common::Chance critHealChance,
        common::Bonus critHealBonus,
        common::PointSkill point) noexcept;

    virtual ~EffectAttInt() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectAttInt& operator+=(const EffectAttInt& other) noexcept;
    EffectAttInt& operator-=(const EffectAttInt& other) noexcept;

private:
    common::Chance              chaCritDmg_;    // base critical damage chance
    common::Multiplier          mulCritDmg_;    // critical damage multiplier
    common::Chance              chaCritHeal_;   // base critical healing chance
    common::Bonus               bonCritHeal_;   // critical healing bonus
    common::PointSkill          poSkill_;       // skill point
};

EffectAttInt operator+(const EffectAttInt& left, const EffectAttInt& right) noexcept;
EffectAttInt operator-(const EffectAttInt& left, const EffectAttInt& right) noexcept;

///------------------------------------------------------------------------------------------------

class EffectAttCha : public Effect {
public:
    EffectAttCha() noexcept
        :
        strike_         { 0 },
        rangeLeader_    { 0 },
        bonXP_          { 0 },
        bonMissionRew_  { 0 }
    {}

    EffectAttCha(
        common::Strike strikeRate,
        common::Range leadershipRange,
        common::Bonus experience,
        common::Bonus missionReward) noexcept;

    virtual ~EffectAttCha() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectAttCha& operator+=(const EffectAttCha& other) noexcept;
    EffectAttCha& operator-=(const EffectAttCha& other) noexcept;

private:
    common::Strike              strike_;        // strike rate
    common::Range               rangeLeader_;   // leadership range
    common::Bonus               bonXP_;         // experience bonus
    common::Bonus               bonMissionRew_; // mission reward bonus
};

EffectAttCha operator+(const EffectAttCha& left, const EffectAttCha& right) noexcept;
EffectAttCha operator-(const EffectAttCha& left, const EffectAttCha& right) noexcept;

} // namespace object
} // namespace game

#endif // !EFFECT_ATTRIBUTE_HPP
