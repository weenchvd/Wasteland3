
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
            cLevels_    { initCustomLevels() },
            pDist_      { pointDist },
            pStor_      { initAttributePoints },
            cooDist_    { initCoordDist() },
            lucDist_    { initLuckDist() }
        {}

        bool Attribute::addLevel(Attribute::Type type, char levels) noexcept
        {
            auto index = static_cast<underlying_type_t<AttributeType>>(type);
            auto curLevel = cLevels_[index].get();
            if (manag_.changeLevel(cLevels_[index], pStor_, pDist_, levels)) {
                switch (type) {
                case Attribute::Type::COORDINATION: {
                    EffectAttCoord sum = cooDist_.total(curLevel, curLevel + levels);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::LUCK: {
                    EffectAttLuck sum = lucDist_.total(curLevel, curLevel + levels);
                    sum.apply(char_);
                    return true;
                }
                case Attribute::Type::AWARENESS: {

                    return true;
                }
                case Attribute::Type::STRENGTH: {

                    return true;
                }
                case Attribute::Type::SPEED: {

                    return true;
                }
                case Attribute::Type::INTELLIGENCE: {

                    return true;
                }
                case Attribute::Type::CHARISMA: {

                    return true;
                }
                default:
                    break;
                }
            }
            return false;
        }

        void Attribute::accept() noexcept
        {
            for (Common::CustomLevel& level : cLevels_) {
                level.accept();
            }
            pStor_.accept();
        }

        void Attribute::reject() noexcept
        {
            for (Common::CustomLevel& level : cLevels_) {
                level.reject();
            }
            pStor_.reject();
        }

        void Attribute::reset() noexcept
        {
            for (Common::CustomLevel& level : cLevels_) {
                level.reset();
            }
            pStor_.reset();
            pStor_.add(initAttributePoints + char_.level() - 1);
        }

        inline const Common::CustomLevel& Attribute::level(Attribute::Type type) const noexcept
        {
            return cLevels_[static_cast<underlying_type_t<AttributeType>>(type)];
        }

        inline const Common::PointsStorage& Attribute::storage() const noexcept
        {
            return pStor_;
        }

        vector<Common::CustomLevel> Attribute::initCustomLevels()
        {
            Common::CustomLevel tempLevel{ minAttributeLevel, maxAttributeLevel };
            auto numOfAttributes = static_cast<underlying_type_t<AttributeType>>
                (AttributeType::NUMBER_OF_ATTRIBUTES);
            return vector<Common::CustomLevel>(numOfAttributes, tempLevel);
        }

        vector<EffectAttCoord> Attribute::initCoordDist()
        {
            vector<Common::Resistance>  res     { coordStatEffDist };
            vector<Common::ActionPoint> ap      { coordAPDist };
            vector<Common::ActionPoint> apMax   { coordAPMaxDist };
            if (res.size() != ap.size() || res.size() != apMax.size()) {
                return vector<EffectAttCoord>{};
            }
            vector<EffectAttCoord> coordDist;
            coordDist.reserve(res.size());
            for (int i = 0; i < res.size(); ++i) {
                coordDist.push_back(EffectAttCoord{
                    res     [i],
                    ap      [i],
                    apMax   [i] });
            }
            return coordDist;
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
            vector<EffectAttLuck> luckDist;
            luckDist.reserve(pen.size());
            for (int i = 0; i < pen.size(); ++i) {
                luckDist.push_back(EffectAttLuck{
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
            return luckDist;
        }

    }
}