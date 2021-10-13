
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"effectAttribute.hpp"
#include"character.hpp"

namespace Game
{
    namespace Object
    {
        EffectAttCoord::EffectAttCoord(
            Common::Resistance statusEffectRes,
            Common::ActionPoint apMaximum,
            Common::ActionPoint apCurrent)
            :
            resStatEff_{ statusEffectRes },
            apMax_{ apMaximum },
            apCur_{ apCurrent }
        {}

        void EffectAttCoord::apply(Character& character) noexcept
        {
            character.resistanceStatusEffectAdd(resStatEff_);
            character.actionPointMaximumAdd(apMax_);
            character.actionPointCurrentAdd(apCur_);
        }

        EffectAttCoord& EffectAttCoord::operator+=(const EffectAttCoord& other)
        {
            this->resStatEff_   += other.resStatEff_;
            this->apCur_        += other.apCur_;
            this->apMax_        += other.apMax_;
            return *this;
        }

        EffectAttCoord& EffectAttCoord::operator-=(const EffectAttCoord& other)
        {
            this->resStatEff_   -= other.resStatEff_;
            this->apCur_        -= other.apCur_;
            this->apMax_        -= other.apMax_;
            return *this;
        }

        EffectAttCoord operator+(const EffectAttCoord& left, const EffectAttCoord& right)
        {
            EffectAttCoord temp{ left };
            temp += right;
            return temp;
        }

        EffectAttCoord operator-(const EffectAttCoord& left, const EffectAttCoord& right)
        {
            EffectAttCoord temp{ left };
            temp -= right;
            return temp;
        }

        EffectAttLuck::EffectAttLuck(
            Common::Armor penetration,
            Common::Chance luckyAction,
            Common::Chance luckyCritDamage,
            Common::Chance luckyMegaCritDamage,
            Common::Chance luckyEvade,
            Common::Chance luckyCritResist,
            Common::Chance luckyDoubleHealing,
            Common::Chance luckyDoubleMoney,
            Common::Chance luckyDoubleScrap)
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

        EffectAttLuck& EffectAttLuck::operator+=(const EffectAttLuck& other)
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

        EffectAttLuck& EffectAttLuck::operator-=(const EffectAttLuck& other)
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

        EffectAttLuck operator+(const EffectAttLuck& left, const EffectAttLuck& right)
        {
            EffectAttLuck temp{ left };
            temp += right;
            return temp;
        }

        EffectAttLuck operator-(const EffectAttLuck& left, const EffectAttLuck& right)
        {
            EffectAttLuck temp{ left };
            temp -= right;
            return temp;
        }

    }
}
