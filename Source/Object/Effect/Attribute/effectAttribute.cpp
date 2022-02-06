
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"effectAttribute.hpp"
#include"character.hpp"
#include"operators.hpp"
#include<cmath>

namespace game {
namespace object {

EffectAttCoord::EffectAttCoord(
    common::Resistance statusEffect,
    common::ActionPoint maximum,
    common::ActionPoint current) noexcept
    :
    resStatEff_ { statusEffect },
    apMax_      { maximum },
    apCur_      { current }
{}

void EffectAttCoord::apply(Character& character) noexcept
{
    character.resistanceStatusEffectAdd(resStatEff_);
    character.actionPointMaximumAdd(apMax_);
    character.actionPointCurrentAdd(apCur_);
}

EffectAttCoord& EffectAttCoord::operator+=(const EffectAttCoord& other) noexcept
{
    this->resStatEff_   += other.resStatEff_;
    this->apCur_        += other.apCur_;
    this->apMax_        += other.apMax_;
    return *this;
}

EffectAttCoord& EffectAttCoord::operator-=(const EffectAttCoord& other) noexcept
{
    this->resStatEff_   -= other.resStatEff_;
    this->apCur_        -= other.apCur_;
    this->apMax_        -= other.apMax_;
    return *this;
}

EffectAttCoord operator+(const EffectAttCoord& left, const EffectAttCoord& right) noexcept
{
    return common::operatorPlus(left, right);
}

EffectAttCoord operator-(const EffectAttCoord& left, const EffectAttCoord& right) noexcept
{
    return common::operatorPlus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectAttLuck::EffectAttLuck(
    common::Armor penetration,
    common::Chance luckyAction,
    common::Chance luckyCritDamage,
    common::Chance luckyMegaCritDamage,
    common::Chance luckyEvade,
    common::Chance luckyCritResist,
    common::Chance luckyDoubleHealing,
    common::Chance luckyDoubleMoney,
    common::Chance luckyDoubleScrap) noexcept
    :
    armorPen_           { penetration },
    chaLuckAction_      { luckyAction },
    chaLuckCritDmg_     { luckyCritDamage },
    chaLuckMegaCritDmg_ { luckyMegaCritDamage },
    chaLuckEvade_       { luckyEvade },
    chaLuckCritRes_     { luckyCritResist },
    chaLuckDblHeal_     { luckyDoubleHealing },
    chaLuckDblMoney_    { luckyDoubleMoney },
    chaLuckDblScrap_    { luckyDoubleScrap }
{}

void EffectAttLuck::apply(Character& character) noexcept
{
    character.armorPenetrationAdd(armorPen_);
    character.chanceLuckyActionAdd(chaLuckAction_);
    character.chanceLuckyCritDamageAdd(chaLuckCritDmg_);
    character.chanceLuckyMegaCritDamageAdd(chaLuckMegaCritDmg_);
    character.chanceLuckyEvadeAdd(chaLuckEvade_);
    character.chanceLuckyCritResistAdd(chaLuckCritRes_);
    character.chanceLuckyDoubleHealingAdd(chaLuckDblHeal_);
    character.chanceLuckyDoubleMoneyAdd(chaLuckDblMoney_);
    character.chanceLuckyDoubleScrapAdd(chaLuckDblScrap_);
}

EffectAttLuck& EffectAttLuck::operator+=(const EffectAttLuck& other) noexcept
{
    this->armorPen_             += other.armorPen_;
    this->chaLuckAction_        += other.chaLuckAction_;
    this->chaLuckCritDmg_       += other.chaLuckCritDmg_;
    this->chaLuckMegaCritDmg_   += other.chaLuckMegaCritDmg_;
    this->chaLuckEvade_         += other.chaLuckEvade_;
    this->chaLuckCritRes_       += other.chaLuckCritRes_;
    this->chaLuckDblHeal_       += other.chaLuckDblHeal_;
    this->chaLuckDblMoney_      += other.chaLuckDblMoney_;
    this->chaLuckDblScrap_      += other.chaLuckDblScrap_;
    return *this;
}

EffectAttLuck& EffectAttLuck::operator-=(const EffectAttLuck& other) noexcept
{
    this->armorPen_             -= other.armorPen_;
    this->chaLuckAction_        -= other.chaLuckAction_;
    this->chaLuckCritDmg_       -= other.chaLuckCritDmg_;
    this->chaLuckMegaCritDmg_   -= other.chaLuckMegaCritDmg_;
    this->chaLuckEvade_         -= other.chaLuckEvade_;
    this->chaLuckCritRes_       -= other.chaLuckCritRes_;
    this->chaLuckDblHeal_       -= other.chaLuckDblHeal_;
    this->chaLuckDblMoney_      -= other.chaLuckDblMoney_;
    this->chaLuckDblScrap_      -= other.chaLuckDblScrap_;
    return *this;
}

EffectAttLuck operator+(const EffectAttLuck& left, const EffectAttLuck& right) noexcept
{
    return common::operatorPlus(left, right);
}

EffectAttLuck operator-(const EffectAttLuck& left, const EffectAttLuck& right) noexcept
{
    return common::operatorPlus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectAttAware::EffectAttAware(
    common::Chance hit,
    common::Perception perception,
    common::Bonus rangedDamage) noexcept
    :
    chaHit_         { hit },
    percept_        { perception },
    bonRangeDmg_    { rangedDamage }
{}

void EffectAttAware::apply(Character& character) noexcept
{
    character.chanceHitAdd(chaHit_);
    character.perceptionAdd(percept_);
    character.bonusRangedDamageAdd(bonRangeDmg_);
}

EffectAttAware& EffectAttAware::operator+=(const EffectAttAware& other) noexcept
{
    this->chaHit_       += other.chaHit_;
    this->percept_      += other.percept_;
    this->bonRangeDmg_  += other.bonRangeDmg_;
    return *this;
}

EffectAttAware& EffectAttAware::operator-=(const EffectAttAware& other) noexcept
{
    this->chaHit_       -= other.chaHit_;
    this->percept_      -= other.percept_;
    this->bonRangeDmg_  -= other.bonRangeDmg_;
    return *this;
}

EffectAttAware operator+(const EffectAttAware& left, const EffectAttAware& right) noexcept
{
    return common::operatorPlus(left, right);
}

EffectAttAware operator-(const EffectAttAware& left, const EffectAttAware& right) noexcept
{
    return common::operatorPlus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectAttStr::EffectAttStr(
    common::Constitution maximum,
    common::Constitution perLevel,
    common::Bonus meleeDamage,
    common::Multiplier throwingRange) noexcept
    :
    conMax_         { maximum },
    conPerLvl_      { perLevel },
    bonMeleeDmg_    { meleeDamage },
    mulThrow_       { throwingRange }
{}

void EffectAttStr::apply(Character& character) noexcept
{
    auto ratio = static_cast<double>(character.constitutionCurrent()) / character.constitutionMaximum();
    auto conCurrent = static_cast<common::Constitution>(round(ratio * conMax_));
    character.constitutionCurrentAdd(conCurrent);
    character.constitutionMaximumAdd(conMax_);
    character.constitutionPerLevelAdd(conPerLvl_);
    character.bonusMeleeDamageAdd(bonMeleeDmg_);
    character.multiplierThrowingRangeAdd(mulThrow_);
}

EffectAttStr& EffectAttStr::operator+=(const EffectAttStr& other) noexcept
{
    this->conMax_       += other.conMax_;
    this->conPerLvl_    += other.conPerLvl_;
    this->bonMeleeDmg_  += other.bonMeleeDmg_;
    this->mulThrow_     += other.mulThrow_;
    return *this;
}

EffectAttStr& EffectAttStr::operator-=(const EffectAttStr& other) noexcept
{
    this->conMax_       -= other.conMax_;
    this->conPerLvl_    -= other.conPerLvl_;
    this->bonMeleeDmg_  -= other.bonMeleeDmg_;
    this->mulThrow_     -= other.mulThrow_;
    return *this;
}

EffectAttStr operator+(const EffectAttStr& left, const EffectAttStr& right) noexcept
{
    return common::operatorPlus(left, right);
}

EffectAttStr operator-(const EffectAttStr& left, const EffectAttStr& right) noexcept
{
    return common::operatorPlus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectAttSpeed::EffectAttSpeed(
    common::Multiplier combatSpeed,
    common::Evasion evasion,
    common::Initiative initiative) noexcept
    :
    mulSpeed_   { combatSpeed },
    evasion_    { evasion },
    initiat_    { initiative }
{}

void EffectAttSpeed::apply(Character& character) noexcept
{
    character.multiplierCombatSpeedAdd(mulSpeed_);
    character.evasionAdd(evasion_);
    character.initiativeAdd(initiat_);
}

EffectAttSpeed& EffectAttSpeed::operator+=(const EffectAttSpeed& other) noexcept
{
    this->mulSpeed_     += other.mulSpeed_;
    this->evasion_      += other.evasion_;
    this->initiat_      += other.initiat_;
    return *this;
}

EffectAttSpeed& EffectAttSpeed::operator-=(const EffectAttSpeed& other) noexcept
{
    this->mulSpeed_     -= other.mulSpeed_;
    this->evasion_      -= other.evasion_;
    this->initiat_      -= other.initiat_;
    return *this;
}

EffectAttSpeed operator+(const EffectAttSpeed& left, const EffectAttSpeed& right) noexcept
{
    return common::operatorPlus(left, right);
}

EffectAttSpeed operator-(const EffectAttSpeed& left, const EffectAttSpeed& right) noexcept
{
    return common::operatorPlus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectAttInt::EffectAttInt(
    common::Chance critDamageChance,
    common::Multiplier critDamageMult,
    common::Chance critHealChance,
    common::Bonus critHealBonus,
    common::PointSkill point) noexcept
    :
    chaCritDmg_     { critDamageChance },
    mulCritDmg_     { critDamageMult },
    chaCritHeal_    { critHealChance },
    bonCritHeal_    { critHealBonus },
    poSkill_        { point }
{}

void EffectAttInt::apply(Character& character) noexcept
{
    character.chanceCritDamageAdd(chaCritDmg_);
    character.multiplierCritDamageAdd(mulCritDmg_);
    character.chanceCritHealingAdd(chaCritHeal_);
    character.bonusCritHealingAdd(bonCritHeal_);
    character.skill().addPoint(poSkill_);
}

EffectAttInt& EffectAttInt::operator+=(const EffectAttInt& other) noexcept
{
    this->chaCritDmg_   += other.chaCritDmg_;
    this->mulCritDmg_   += other.mulCritDmg_;
    this->chaCritHeal_  += other.chaCritHeal_;
    this->bonCritHeal_  += other.bonCritHeal_;
    this->poSkill_      += other.poSkill_;
    return *this;
}

EffectAttInt& EffectAttInt::operator-=(const EffectAttInt& other) noexcept
{
    this->chaCritDmg_   -= other.chaCritDmg_;
    this->mulCritDmg_   -= other.mulCritDmg_;
    this->chaCritHeal_  -= other.chaCritHeal_;
    this->bonCritHeal_  -= other.bonCritHeal_;
    this->poSkill_      -= other.poSkill_;
    return *this;
}

EffectAttInt operator+(const EffectAttInt& left, const EffectAttInt& right) noexcept
{
    return common::operatorPlus(left, right);
}

EffectAttInt operator-(const EffectAttInt& left, const EffectAttInt& right) noexcept
{
    return common::operatorPlus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectAttCha::EffectAttCha(
    common::Strike strikeRate,
    common::Range leadershipRange,
    common::Bonus experience,
    common::Bonus missionReward) noexcept
    :
    strike_         { strikeRate },
    rangeLeader_    { leadershipRange },
    bonXP_          { experience },
    bonMissionRew_  { missionReward }
{}

void EffectAttCha::apply(Character& character) noexcept
{
    character.strikeRateAdd(strike_);
    character.rangeLeadershipAdd(rangeLeader_);
    character.bonusExperienceAdd(bonXP_);
    character.bonusMissionRewardAdd(bonMissionRew_);
}

EffectAttCha& EffectAttCha::operator+=(const EffectAttCha& other) noexcept
{
    this->strike_           += other.strike_;
    this->rangeLeader_      += other.rangeLeader_;
    this->bonXP_            += other.bonXP_;
    this->bonMissionRew_    += other.bonMissionRew_;
    return *this;
}

EffectAttCha& EffectAttCha::operator-=(const EffectAttCha& other) noexcept
{
    this->strike_           -= other.strike_;
    this->rangeLeader_      -= other.rangeLeader_;
    this->bonXP_            -= other.bonXP_;
    this->bonMissionRew_    -= other.bonMissionRew_;
    return *this;
}

EffectAttCha operator+(const EffectAttCha& left, const EffectAttCha& right) noexcept
{
    return common::operatorPlus(left, right);
}

EffectAttCha operator-(const EffectAttCha& left, const EffectAttCha& right) noexcept
{
    return common::operatorPlus(left, right);
}

} // namespace object
} // namespace game
