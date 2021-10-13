
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
            EffectAttCoord()
                :
                resStatEff_ { 0 },
                apMax_      { 0 },
                apCur_      { 0 }
            {}

            EffectAttCoord(
                Common::Resistance statusEffectRes,
                Common::ActionPoint apMaximum,
                Common::ActionPoint apCurrent);

            virtual ~EffectAttCoord() noexcept {}

            //static std::unique_ptr<Effect> create(
            //    Common::Resistance statusEffectRes,
            //    Common::ActionPoint apMaximum,
            //    Common::ActionPoint apCurrent)
            //{
            //    return std::unique_ptr<Effect>(new EffectAttCoord(statusEffectRes, apMaximum, apCurrent));
            //}

            virtual void apply(Character& character) noexcept override;

            EffectAttCoord& operator+=(const EffectAttCoord& other);
            EffectAttCoord& operator-=(const EffectAttCoord& other);

        private:
            Common::Resistance          resStatEff_;    // status effect resistance
            Common::ActionPoint         apMax_;         // action points (maximum)
            Common::ActionPoint         apCur_;         // action points (current)
        };

        EffectAttCoord operator+(const EffectAttCoord& left, const EffectAttCoord& right);
        EffectAttCoord operator-(const EffectAttCoord& left, const EffectAttCoord& right);


        class EffectAttLuck : public Effect {
        public:
            EffectAttLuck()
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
                Common::Chance luckyDoubleScrap);

            virtual ~EffectAttLuck() noexcept {}

            virtual void apply(Character& character) noexcept override;

            EffectAttLuck& operator+=(const EffectAttLuck& other);
            EffectAttLuck& operator-=(const EffectAttLuck& other);

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

        EffectAttLuck operator+(const EffectAttLuck& left, const EffectAttLuck& right);
        EffectAttLuck operator-(const EffectAttLuck& left, const EffectAttLuck& right);

    }
}

#endif // !EFFECT_ATTRIBUTE_HPP
