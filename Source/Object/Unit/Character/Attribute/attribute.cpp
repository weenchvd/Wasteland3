
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attribute.hpp"
#include"character.hpp"

namespace Game
{
    namespace Object
    {
        using namespace std;

        Attribute::Attribute(Character& character)
            :
            char_       { character },
            levels_     { initLevels() },
            pDist_      { initPointDist() },
            pStor_      { minAttributePoints, maxAttributePoints },
            cooDist_    { initCoordDist() },
            lucDist_    { initLuckDist() },
            awaDist_    { initAwareDist() },
            strDist_    { initStrDist() },
            spdDist_    { initSpeedDist() },
            intDist_    { initIntDist() },
            chaDist_    { initCharismaDist() }
        {}

        bool Attribute::addLevel(Attribute::Type type, Common::LevelStat shift) noexcept
        {
            auto index = static_cast<underlying_type_t<Attribute::Type>>(type);
            auto curLevel = levels_[index].get();
            if (Common::changeLevel(levels_[index], pStor_, pDist_, shift)) {
                switch (type) {
                case Attribute::Type::COORDINATION: {
                    EffectAttCoord sum = cooDist_.total(curLevel, curLevel + shift);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::LUCK: {
                    EffectAttLuck sum = lucDist_.total(curLevel, curLevel + shift);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::AWARENESS: {
                    EffectAttAware sum = awaDist_.total(curLevel, curLevel + shift);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::STRENGTH: {
                    EffectAttStr sum = strDist_.total(curLevel, curLevel + shift);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::SPEED: {
                    EffectAttSpeed sum = spdDist_.total(curLevel, curLevel + shift);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::INTELLIGENCE: {
                    EffectAttInt sum = intDist_.total(curLevel, curLevel + shift);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::CHARISMA: {
                    EffectAttCha sum = chaDist_.total(curLevel, curLevel + shift);
                    sum.apply(char_);
                    return true;
                }
                default:
                    break;
                }
            }
            return false;
        }

        bool Attribute::isModified() const noexcept
        {
            if (pStor_.get() != pStor_.getAccepted()) {
                return true;
            }
            for (const Common::SpecStorage<Common::LevelStat>& level : levels_) {
                if (level.get() != level.getAccepted()) {
                    return true;
                }
            }
            return false;
        }

        void Attribute::accept() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.accept();
            }
            pStor_.accept();
        }

        void Attribute::reject() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reject();
            }
            pStor_.reject();
        }

        void Attribute::reset() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reset();
            }
            pStor_.reset();
            pStor_.add(initAttributePoints + char_.level() - 1);
        }

        vector<Common::SpecStorage<Common::LevelStat>> Attribute::initLevels()
        {
            Common::SpecStorage<Common::LevelStat> tempLevel{ minAttributeLevel, maxAttributeLevel };
            auto nAttributes = static_cast<underlying_type_t<Attribute::Type>>
                (Attribute::Type::NUMBER_OF);
            return vector<Common::SpecStorage<Common::LevelStat>>(nAttributes, tempLevel);
        }

        inline vector<Common::PointAttribute> Attribute::initPointDist()
        {
            return vector<Common::PointAttribute>(pointDist);
        }

        vector<EffectAttCoord> Attribute::initCoordDist()
        {
            vector<Common::Resistance>  res     { coordStatEffDist };
            vector<Common::ActionPoint> ap      { coordAPDist };
            vector<Common::ActionPoint> apMax   { coordAPMaxDist };
            if (res.size() != ap.size() || res.size() != apMax.size()) {
                return vector<EffectAttCoord>{};
            }
            vector<EffectAttCoord> dist;
            dist.reserve(res.size());
            for (int i = 0; i < res.size(); ++i) {
                dist.push_back(EffectAttCoord{
                    res     [i],
                    ap      [i],
                    apMax   [i] });
            }
            return dist;
        }

        vector<EffectAttLuck> Attribute::initLuckDist()
        {
            vector<Common::Armor>   pen         { luckPenetDist };
            vector<Common::Chance>  act         { luckActionDist };
            vector<Common::Chance>  crit        { luckCritDist };
            vector<Common::Chance>  megaCrit    { luckMegaCritDist };
            vector<Common::Chance>  evade       { luckEvadeDist };
            vector<Common::Chance>  critResist  { luckCritResistDist };
            vector<Common::Chance>  doubleHeal  { luckDoubleHealDist };
            vector<Common::Chance>  doubleMoney { luckDoubleMoneyDist };
            vector<Common::Chance>  doubleScrap { luckDoubleScrapDist };
            if (pen.size() != act.size() ||
                pen.size() != crit.size() ||
                pen.size() != megaCrit.size() ||
                pen.size() != evade.size() ||
                pen.size() != critResist.size() ||
                pen.size() != doubleHeal.size() ||
                pen.size() != doubleMoney.size() ||
                pen.size() != doubleScrap.size())
            {
                return vector<EffectAttLuck>{};
            }
            vector<EffectAttLuck> dist;
            dist.reserve(pen.size());
            for (int i = 0; i < pen.size(); ++i) {
                dist.push_back(EffectAttLuck{
                    pen         [i],
                    act         [i],
                    crit        [i],
                    megaCrit    [i],
                    evade       [i],
                    critResist  [i],
                    doubleHeal  [i],
                    doubleMoney [i],
                    doubleScrap [i] });
            }
            return dist;
        }

        vector<EffectAttAware> Attribute::initAwareDist()
        {
            vector<Common::Chance>      hit     { awareHitDist };
            vector<Common::Perception>  percep  { awarePercepDist };
            vector<Common::Bonus>       rangDmg { awareRangedDmgDist };
            if (hit.size() != percep.size() || hit.size() != rangDmg.size()) {
                return vector<EffectAttAware>{};
            }
            vector<EffectAttAware> dist;
            dist.reserve(hit.size());
            for (int i = 0; i < hit.size(); ++i) {
                dist.push_back(EffectAttAware{
                    hit     [i],
                    percep  [i],
                    rangDmg [i] });
            }
            return dist;
        }

        std::vector<EffectAttStr> Attribute::initStrDist()
        {
            vector<Common::Constitution>    max         { strMaxDist };
            vector<Common::Constitution>    perLevel    { strPerLvlDist };
            vector<Common::Bonus>           meleeDmg    { strMeleeDmgDist };
            vector<Common::Multiplier>      throwRange  { strThrowRangeDist };
            if (max.size() != perLevel.size() ||
                max.size() != meleeDmg.size() ||
                max.size() != throwRange.size())
            {
                return vector<EffectAttStr>{};
            }
            vector<EffectAttStr> dist;
            dist.reserve(max.size());
            for (int i = 0; i < max.size(); ++i) {
                dist.push_back(EffectAttStr{
                    max         [i],
                    perLevel    [i],
                    meleeDmg    [i],
                    throwRange  [i] });
            }
            return dist;
        }

        std::vector<EffectAttSpeed> Attribute::initSpeedDist()
        {
            vector<Common::Multiplier>  combatSpeed { speedCombatSpeedDist };
            vector<Common::Evasion>     evasion     { speedEvasionDist };
            vector<Common::Initiative>  initiative  { speedInitDist };
            if (combatSpeed.size() != evasion.size() || combatSpeed.size() != initiative.size()) {
                return vector<EffectAttSpeed>{};
            }
            vector<EffectAttSpeed> dist;
            dist.reserve(combatSpeed.size());
            for (int i = 0; i < combatSpeed.size(); ++i) {
                dist.push_back(EffectAttSpeed{
                    combatSpeed [i],
                    evasion     [i],
                    initiative  [i] });
            }
            return dist;
        }

        std::vector<EffectAttInt> Attribute::initIntDist()
        {
            vector<Common::Chance>      critDmgChance   { intCritDmgChanceDist };
            vector<Common::Multiplier>  critDmgMult     { intCritDmgMultDist };
            vector<Common::Chance>      critHealChance  { intCritHealChanceDist };
            vector<Common::Bonus>       critHealBonus   { intCritHealBonusDist };
            vector<Common::PointSkill>  skillPoint      { intSkillPointDist };
            if (critDmgChance.size() != critDmgMult.size() ||
                critDmgChance.size() != critHealChance.size() ||
                critDmgChance.size() != critHealBonus.size() ||
                critDmgChance.size() != skillPoint.size())
            {
                return vector<EffectAttInt>{};
            }
            vector<EffectAttInt> dist;
            dist.reserve(critDmgChance.size());
            for (int i = 0; i < critDmgChance.size(); ++i) {
                dist.push_back(EffectAttInt{
                    critDmgChance   [i],
                    critDmgMult     [i],
                    critHealChance  [i],
                    critHealBonus   [i],
                    skillPoint      [i] });
            }
            return dist;
        }

        std::vector<EffectAttCha> Attribute::initCharismaDist()
        {
            vector<Common::Strike>  strike      { chaStrikeRateDist };
            vector<Common::Range>   leadership  { chaLeadershipDist };
            vector<Common::Bonus>   xp          { chaExperienceDist };
            vector<Common::Bonus>   reward      { chaMisRewardDist };
            if (strike.size() != leadership.size() ||
                strike.size() != xp.size() ||
                strike.size() != reward.size())
            {
                return vector<EffectAttCha>{};
            }
            vector<EffectAttCha> dist;
            dist.reserve(strike.size());
            for (int i = 0; i < strike.size(); ++i) {
                dist.push_back(EffectAttCha{
                    strike      [i],
                    leadership  [i],
                    xp          [i],
                    reward      [i] });
            }
            return dist;
        }

    }
}