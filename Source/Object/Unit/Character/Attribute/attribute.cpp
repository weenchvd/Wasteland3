
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

        void Attribute::addLevel(Attribute::Type type, Common::LevelStat shift) noexcept
        {
            auto index = static_cast<underlying_type_t<Attribute::Type>>(type);
            Common::changeLevel(levels_[index], pStor_, pDist_, shift);
        }
        
        void Attribute::addLevelToAll(Common::LevelStat shift) noexcept
        {
            addLevel(Attribute::Type::COORDINATION, shift);
            addLevel(Attribute::Type::LUCK,         shift);
            addLevel(Attribute::Type::AWARENESS,    shift);
            addLevel(Attribute::Type::STRENGTH,     shift);
            addLevel(Attribute::Type::SPEED,        shift);
            addLevel(Attribute::Type::INTELLIGENCE, shift);
            addLevel(Attribute::Type::CHARISMA,     shift);
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
            apply();
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
        }

        void Attribute::apply() noexcept
        {
            apply(Attribute::Type::COORDINATION);
            apply(Attribute::Type::LUCK);
            apply(Attribute::Type::AWARENESS);
            apply(Attribute::Type::STRENGTH);
            apply(Attribute::Type::SPEED);
            apply(Attribute::Type::INTELLIGENCE);
            apply(Attribute::Type::CHARISMA);
        }

        void Attribute::apply(Attribute::Type type) noexcept
        {
            auto index = static_cast<underlying_type_t<Attribute::Type>>(type);
            auto accLevel = levels_[index].getAccepted();
            auto curLevel = levels_[index].get();
            if (accLevel != curLevel) {
                switch (type) {
                case Attribute::Type::COORDINATION: {
                    EffectAttCoord sum = cooDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::LUCK: {
                    EffectAttLuck sum = lucDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::AWARENESS: {
                    EffectAttAware sum = awaDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::STRENGTH: {
                    EffectAttStr sum = strDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::SPEED: {
                    EffectAttSpeed sum = spdDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::INTELLIGENCE: {
                    EffectAttInt sum = intDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::CHARISMA: {
                    EffectAttCha sum = chaDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                default:
                    break;
                }
            }
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
            return vector<Common::PointAttribute>(pointAttDist);
        }

        vector<EffectAttCoord> Attribute::initCoordDist()
        {
            return Common::initializeDistribution<EffectAttCoord,
                Common::Resistance,
                Common::ActionPoint,
                Common::ActionPoint
            >(
                vector<Common::Resistance>  (coordStatEffDist),
                vector<Common::ActionPoint> (coordAPMaxDist),
                vector<Common::ActionPoint> (coordAPDist));
        }

        vector<EffectAttLuck> Attribute::initLuckDist()
        {
            return Common::initializeDistribution<EffectAttLuck,
                Common::Armor,
                Common::Chance,
                Common::Chance,
                Common::Chance,
                Common::Chance,
                Common::Chance,
                Common::Chance,
                Common::Chance,
                Common::Chance
            >(
                vector<Common::Armor>   (luckPenetDist),
                vector<Common::Chance>  (luckActionDist),
                vector<Common::Chance>  (luckCritDist),
                vector<Common::Chance>  (luckMegaCritDist),
                vector<Common::Chance>  (luckEvadeDist),
                vector<Common::Chance>  (luckCritResistDist),
                vector<Common::Chance>  (luckDoubleHealDist),
                vector<Common::Chance>  (luckDoubleMoneyDist),
                vector<Common::Chance>  (luckDoubleScrapDist));
        }

        vector<EffectAttAware> Attribute::initAwareDist()
        {
            return Common::initializeDistribution<EffectAttAware,
                Common::Chance,
                Common::Perception,
                Common::Bonus
            >(
                vector<Common::Chance>      (awareHitDist),
                vector<Common::Perception>  (awarePercepDist),
                vector<Common::Bonus>       (awareRangedDmgDist));
        }

        vector<EffectAttStr> Attribute::initStrDist()
        {
            return Common::initializeDistribution<EffectAttStr,
                Common::Constitution,
                Common::Constitution,
                Common::Bonus,
                Common::Multiplier
            >(
                vector<Common::Constitution>(strMaxDist),
                vector<Common::Constitution>(strPerLvlDist),
                vector<Common::Bonus>       (strMeleeDmgDist),
                vector<Common::Multiplier>  (strThrowRangeDist));
        }

        vector<EffectAttSpeed> Attribute::initSpeedDist()
        {
            return Common::initializeDistribution<EffectAttSpeed,
                Common::Multiplier,
                Common::Evasion,
                Common::Initiative
            >(
                vector<Common::Multiplier>  (speedCombatSpeedDist),
                vector<Common::Evasion>     (speedEvasionDist),
                vector<Common::Initiative>  (speedInitDist));
        }

        vector<EffectAttInt> Attribute::initIntDist()
        {
            return Common::initializeDistribution<EffectAttInt,
                Common::Chance,
                Common::Multiplier,
                Common::Chance,
                Common::Bonus,
                Common::PointSkill
            >(
                vector<Common::Chance>      (intCritDmgChanceDist),
                vector<Common::Multiplier>  (intCritDmgMultDist),
                vector<Common::Chance>      (intCritHealChanceDist),
                vector<Common::Bonus>       (intCritHealBonusDist),
                vector<Common::PointSkill>  (intSkillPointDist));
        }

        vector<EffectAttCha> Attribute::initCharismaDist()
        {
            return Common::initializeDistribution<EffectAttCha,
                Common::Strike,
                Common::Range,
                Common::Bonus,
                Common::Bonus
            >(
                vector<Common::Strike>  (chaStrikeRateDist),
                vector<Common::Range>   (chaLeadershipDist),
                vector<Common::Bonus>   (chaExperienceDist),
                vector<Common::Bonus>   (chaMisRewardDist));
        }

    }
}