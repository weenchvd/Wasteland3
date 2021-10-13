
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include"point.hpp"
#include"distribution.hpp"
#include"effectAttribute.hpp"
#include"attributeCommon.hpp"
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        constexpr unsigned short int initAttributePoints = 21;
        constexpr unsigned char initAttributeLevel = 1;
        constexpr unsigned char minAttributeLevel = 0;
        constexpr unsigned char maxAttributeLevel = 10;
        constexpr std::initializer_list<unsigned char> pointDist{ 0, 1 };

        // ATTRIBUTE LEVEL:
        //  0     1     2     3     4     5     6     7     8     9    10
        /// COORDINATION
        constexpr std::initializer_list<Common::Resistance> coordStatEffDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   70 };
        constexpr std::initializer_list<Common::ActionPoint> coordAPDist{
            0,    0,    1,    0,    1,    0,    1,    0,    1,    0,    1 };
        constexpr std::initializer_list<Common::ActionPoint> coordAPMaxDist{
            0,    0,    1,    0,    1,    0,    1,    0,    1,    0,    1 };
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
        /// AWARENESS
        constexpr std::initializer_list<Common::Chance> awarHitDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   30 };
        constexpr std::initializer_list<Common::Perception> awarPercepDist{
            0,    0,    1,    0,    1,    0,    1,    0,    1,    0,    2 };
        constexpr std::initializer_list<Common::Bonus> awarRangedDmgDist{
            0,   30,   30,   30,   30,   30,   30,   30,   30,   30,   80 };
        /// STRENGTH
        constexpr std::initializer_list<Common::Constitution> strConDist{
            0,    5,    5,    5,    5,    5,    5,    5,    5,    5,   30 };
        constexpr std::initializer_list<Common::Constitution> strConPerLvlDist{
            0,    0,    3,    0,    3,    0,    3,    0,    3,    0,    3 };
        constexpr std::initializer_list<Common::Bonus> strMeleeDmgDist{
            0,   30,   30,   30,   30,   30,   30,   30,   30,   30,   80 };
        constexpr std::initializer_list<Common::Multiplier> strThrowRangeDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   20 };
        /// SPEED
        constexpr std::initializer_list<Common::Multiplier> speedCombatSpeedDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   50 };
        constexpr std::initializer_list<Common::Evasion> speedEvasionDist{
            0,   30,   30,   30,   30,   30,   30,   30,   30,   30,   60 };
        constexpr std::initializer_list<Common::Initiative> speedInitDist{
            0,   40,   40,   40,   40,   40,   40,   40,   40,   40,   90 };
        /// INTELLIGENCE
        constexpr std::initializer_list<Common::Chance> intCritDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20 };
        constexpr std::initializer_list<Common::Multiplier> intCritDmgDist{
            0,   10,   10,   10,   10,   10,   10,   10,   10,   10,   20 };
        constexpr std::initializer_list<Common::Chance> intCritHealDist{
            0,   20,   20,   20,   20,   20,   20,   20,   20,   20,   70 };
        constexpr std::initializer_list<Common::Bonus> intCritHealBonusDist{
            0,  100,  100,  100,  100,  100,  100,  100,  100,  100,  200 };
        constexpr std::initializer_list<Common::PointSkill> intSkillPointDist{
            0,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1 };
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
            using Type      = AttributeType;

        public:
            Attribute(Character& character);

            bool addLevel(Attribute::Type type, char levels) noexcept;

            void addPoint(short int points) noexcept {
                pStor_.add(points);
            }

            void accept() noexcept;

            void reject() noexcept;

            void reset() noexcept;

        public:
            const Common::CustomLevel& level(Attribute::Type type) const noexcept;

            const Common::PointsStorage& storage() const noexcept;

        private:
            static std::vector<Common::CustomLevel> initCustomLevels();
            static std::vector<EffectAttCoord>      initCoordDist();
            static std::vector<EffectAttLuck>       initLuckDist();

        private:
            Character&                              char_;
            std::vector<Common::CustomLevel>        cLevels_;
            Common::CustomLevelManager              manag_;
            Common::PointsDistribution              pDist_;
            Common::PointsStorage                   pStor_;
            Common::Distribution<EffectAttCoord>    cooDist_;
            Common::Distribution<EffectAttLuck>     lucDist_;
        };

    }
}

#endif // !ATTRIBUTE_HPP
