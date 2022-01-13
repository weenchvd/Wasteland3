
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include"distribution.hpp"
#include"specStorage.hpp"
#include"effectAttribute.hpp"
#include"attributeCommon.hpp"
#include"attribute_generated.h"
#include<array>
#include<initializer_list>
#include<limits>
#include<memory>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        constexpr Common::PointAttribute minAttributePoints     { 0 };
        constexpr Common::PointAttribute maxAttributePoints     { std::numeric_limits<Common::PointAttribute>::max() };
        constexpr Common::PointAttribute initAttributePoints    { 21 };

        //constexpr Common::LevelStat minAttributeLevel   { 0 };
        //constexpr Common::LevelStat maxAttributeLevel   { 10 };
        constexpr Common::LevelStat initAttributeLevel  { 1 };

        constexpr std::initializer_list<Common::PointAttribute> pointAttDist{ 0, -1 };

        /// ATTRIBUTE LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// COORDINATION
        constexpr std::initializer_list<Common::Resistance> coordStatEffDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   70 };
        constexpr std::initializer_list<Common::ActionPoint> coordAPDist{
            0,    0,    1,    0,    1,    0,    1,    0,    1,    0,    1 };
        constexpr std::initializer_list<Common::ActionPoint> coordAPMaxDist{
            0,    0,    1,    0,    1,    0,    1,    0,    1,    0,    1 };

        /// ATTRIBUTE LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// LUCK
        constexpr std::initializer_list<Common::Armor> luckPenetDist{
            0,    0,    1,    0,    1,    0,    1,    0,    1,    0,    2 };
        constexpr std::initializer_list<Common::Chance> luckActionDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10 };
        constexpr std::initializer_list<Common::Chance> luckCritDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10 };
        constexpr std::initializer_list<Common::Chance> luckMegaCritDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10 };
        constexpr std::initializer_list<Common::Chance> luckEvadeDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20 };
        constexpr std::initializer_list<Common::Chance> luckCritResistDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20 };
        constexpr std::initializer_list<Common::Chance> luckDoubleHealDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20 };
        constexpr std::initializer_list<Common::Chance> luckDoubleMoneyDist{
            0,    5,    5,    5,    5,    5,    5,    5,    5,    5,    5 };
        constexpr std::initializer_list<Common::Chance> luckDoubleScrapDist{
            0,    5,    5,    5,    5,    5,    5,    5,    5,    5,    5 };

        /// ATTRIBUTE LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// AWARENESS
        constexpr std::initializer_list<Common::Chance> awareHitDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   30 };
        constexpr std::initializer_list<Common::Perception> awarePercepDist{
            0,    0,    1,    0,    1,    0,    1,    0,    1,    0,    2 };
        constexpr std::initializer_list<Common::Bonus> awareRangedDmgDist{
            0,   30,   30,   30,   30,   30,   30,   30,   30,   30,   80 };

        /// ATTRIBUTE LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// STRENGTH
        constexpr std::initializer_list<Common::Constitution> strMaxDist{
            0,    5,    5,    5,    5,    5,    5,    5,    5,    5,   30 };
        constexpr std::initializer_list<Common::Constitution> strPerLvlDist{
            0,    0,    3,    0,    3,    0,    3,    0,    3,    0,    3 };
        constexpr std::initializer_list<Common::Bonus> strMeleeDmgDist{
            0,   30,   30,   30,   30,   30,   30,   30,   30,   30,   80 };
        constexpr std::initializer_list<Common::Multiplier> strThrowRangeDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   20 };

        /// ATTRIBUTE LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// SPEED
        constexpr std::initializer_list<Common::Multiplier> speedCombatSpeedDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   50 };
        constexpr std::initializer_list<Common::Evasion> speedEvasionDist{
            0,   30,   30,   30,   30,   30,   30,   30,   30,   30,   60 };
        constexpr std::initializer_list<Common::Initiative> speedInitDist{
            0,   40,   40,   40,   40,   40,   40,   40,   40,   40,   90 };

        /// ATTRIBUTE LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// INTELLIGENCE
        constexpr std::initializer_list<Common::Chance> intCritDmgChanceDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20 };
        constexpr std::initializer_list<Common::Multiplier> intCritDmgMultDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   20 };
        constexpr std::initializer_list<Common::Chance> intCritHealChanceDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   70 };
        constexpr std::initializer_list<Common::Bonus> intCritHealBonusDist{
            0,  100,  100,  100,  100,  100,  100,  100,  100,  100,  200 };
        constexpr std::initializer_list<Common::PointSkill> intSkillPointDist{
            0,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1 };

        /// ATTRIBUTE LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// CHARISMA
        constexpr std::initializer_list<Common::Strike> chaStrikeRateDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   40 };
        constexpr std::initializer_list<Common::Range> chaLeadershipDist{
            0,    2,    2,    2,    2,    2,    2,    2,    2,    2,    4 };
        constexpr std::initializer_list<Common::Bonus> chaExperienceDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,  120 };
        constexpr std::initializer_list<Common::Bonus> chaMisRewardDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10 };


        class Character;

        class Attribute {
        public:
            using Type          = Attribute__Type;

        public:
            Attribute(Character& character);

            void addLevel(Attribute::Type type, Common::LevelStat shift) noexcept;

            void addLevelToAll(Common::LevelStat shift) noexcept;

            void addPoint(Common::PointAttribute shift) noexcept {
                pStor_.add(shift);
            }

            bool isModified() const noexcept;

            void accept() noexcept;

            void reject() noexcept;

            void reset() noexcept;

        public:
            const Common::SpecStorage<Common::LevelStat>& level(Attribute::Type type) const noexcept {
                return levels_[Common::toUnderlying(type)];
            }

            const Common::SpecStorage<Common::PointAttribute>& storage() const noexcept {
                return pStor_;
            }

        public:
            using Text = Game::Common::Text;

            static void initializeText();

            static const Text& name(Attribute::Type id) noexcept;

            static const Text& descr(Attribute::Type id) noexcept;

        private:
            void apply() noexcept;

            void apply(Attribute::Type type) noexcept;

        private:
            static std::unique_ptr<const char>                          initBuffer();
            std::vector<Common::SpecStorage<Common::LevelStat>>         initLevels();
            static std::vector<Common::PointAttribute>                  initPointDist();
            static std::vector<EffectAttCoord>                          initCoordDist();
            static std::vector<EffectAttLuck>                           initLuckDist();
            static std::vector<EffectAttAware>                          initAwareDist();
            static std::vector<EffectAttStr>                            initStrDist();
            static std::vector<EffectAttSpeed>                          initSpeedDist();
            static std::vector<EffectAttInt>                            initIntDist();
            static std::vector<EffectAttCha>                            initCharismaDist();

        private:
            std::unique_ptr<const char>                         buffer_;
            Character&                                          char_;
            std::vector<Common::SpecStorage<Common::LevelStat>> levels_;
            Common::SpecStorage<Common::PointAttribute>         pStor_;
            Common::Distribution<Common::PointAttribute>        pDist_;
            Common::Distribution<EffectAttCoord>                cooDist_;
            Common::Distribution<EffectAttLuck>                 lucDist_;
            Common::Distribution<EffectAttAware>                awaDist_;
            Common::Distribution<EffectAttStr>                  strDist_;
            Common::Distribution<EffectAttSpeed>                spdDist_;
            Common::Distribution<EffectAttInt>                  intDist_;
            Common::Distribution<EffectAttCha>                  chaDist_;

        private:
            static constexpr int sizeName_ = Common::toUnderlying(Attribute::Type::NUMBER_OF);
            static constexpr int sizeDescr_ = Common::toUnderlying(Attribute::Type::NUMBER_OF);

            static std::array<Text, sizeName_>                  tName_;
            static std::array<Text, sizeDescr_>                 tDescr_;
        };

    }
}

#endif // !ATTRIBUTE_HPP
