
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef EFFECT_ATTRIBUTE_HPP
#define EFFECT_ATTRIBUTE_HPP

#include"common.hpp"
#include"effect.hpp"
#include<memory>

namespace Game
{
    namespace Object
    {
        class EffectAttCoord : public Effect {
        public:
            EffectAttCoord() noexcept
                :
                resStatEff_ { 0 },
                apMax_      { 0 },
                apCur_      { 0 }
            {}

            EffectAttCoord(
                Common::Resistance statusEffect,
                Common::ActionPoint maximum,
                Common::ActionPoint current) noexcept;

            virtual ~EffectAttCoord() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttCoord& operator+=(const EffectAttCoord& other) noexcept;
            EffectAttCoord& operator-=(const EffectAttCoord& other) noexcept;

        private:
            Common::Resistance          resStatEff_;    // status effect resistance
            Common::ActionPoint         apMax_;         // action points (maximum)
            Common::ActionPoint         apCur_;         // action points (current)
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
                Common::Armor penetration,
                Common::Chance luckyAction,
                Common::Chance luckyCritDamage,
                Common::Chance luckyMegaCritDamage,
                Common::Chance luckyEvade,
                Common::Chance luckyCritResist,
                Common::Chance luckyDoubleHealing,
                Common::Chance luckyDoubleMoney,
                Common::Chance luckyDoubleScrap) noexcept;

            virtual ~EffectAttLuck() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttLuck& operator+=(const EffectAttLuck& other) noexcept;
            EffectAttLuck& operator-=(const EffectAttLuck& other) noexcept;

        private:
            Common::Armor               armorPen_;          // penetration
            Common::Chance              chaLuckAction_;     // lucky action chance
            Common::Chance              chaLuckCritDmg_;    // lucky critical damage chance
            Common::Chance              chaLuckMegaCritDmg_;// lucky mega critical damage chance
            Common::Chance              chaLuckEvade_;      // lucky evade chance
            Common::Chance              chaLuckCritRes_;    // lucky critical resist chance
            Common::Chance              chaLuckDblHeal_;    // lucky double healing chance
            Common::Chance              chaLuckDblMoney_;   // lucky double money chance
            Common::Chance              chaLuckDblScrap_;   // lucky double scrap chance
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
                Common::Chance hit,
                Common::Perception perception,
                Common::Bonus rangedDamage) noexcept;

            virtual ~EffectAttAware() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttAware& operator+=(const EffectAttAware& other) noexcept;
            EffectAttAware& operator-=(const EffectAttAware& other) noexcept;

        private:
            Common::Chance              chaHit_;        // base hit chance
            Common::Perception          percept_;       // perception
            Common::Bonus               bonRangeDmg_;   // ranged damage bonus
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
                Common::Constitution maximum,
                Common::Constitution perLevel,
                Common::Bonus meleeDamage,
                Common::Multiplier throwingRange) noexcept;

            virtual ~EffectAttStr() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttStr& operator+=(const EffectAttStr& other) noexcept;
            EffectAttStr& operator-=(const EffectAttStr& other) noexcept;

        private:
            Common::Constitution        conMax_;        // constitution max value
            Common::Constitution        conPerLvl_;     // constitution per level
            Common::Bonus               bonMeleeDmg_;   // melee damage bonus
            Common::Multiplier          mulThrow_;      // throwing range multiplier
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
                Common::Multiplier combatSpeed,
                Common::Evasion evasion,
                Common::Initiative initiative) noexcept;

            virtual ~EffectAttSpeed() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttSpeed& operator+=(const EffectAttSpeed& other) noexcept;
            EffectAttSpeed& operator-=(const EffectAttSpeed& other) noexcept;

        private:
            Common::Multiplier          mulSpeed_;      // combat speed multiplier
            Common::Evasion             evasion_;       // evasion
            Common::Initiative          initiat_;       // initiative
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
                Common::Chance critDamageChance,
                Common::Multiplier critDamageMult,
                Common::Chance critHealChance,
                Common::Bonus critHealBonus,
                Common::PointSkill point) noexcept;

            virtual ~EffectAttInt() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttInt& operator+=(const EffectAttInt& other) noexcept;
            EffectAttInt& operator-=(const EffectAttInt& other) noexcept;

        private:
            Common::Chance              chaCritDmg_;    // base critical damage chance
            Common::Multiplier          mulCritDmg_;    // critical damage multiplier
            Common::Chance              chaCritHeal_;   // base critical healing chance
            Common::Bonus               bonCritHeal_;   // critical healing bonus
            Common::PointSkill          poSkill_;       // skill point
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
                Common::Strike strikeRate,
                Common::Range leadershipRange,
                Common::Bonus experience,
                Common::Bonus missionReward) noexcept;

            virtual ~EffectAttCha() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttCha& operator+=(const EffectAttCha& other) noexcept;
            EffectAttCha& operator-=(const EffectAttCha& other) noexcept;

        private:
            Common::Strike              strike_;        // strike rate
            Common::Range               rangeLeader_;   // leadership range
            Common::Bonus               bonXP_;         // experience bonus
            Common::Bonus               bonMissionRew_; // mission reward bonus
        };

        EffectAttCha operator+(const EffectAttCha& left, const EffectAttCha& right) noexcept;
        EffectAttCha operator-(const EffectAttCha& left, const EffectAttCha& right) noexcept;

    }
}

#endif // !EFFECT_ATTRIBUTE_HPP
