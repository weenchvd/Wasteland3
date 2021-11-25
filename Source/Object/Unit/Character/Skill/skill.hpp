
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_HPP
#define SKILL_HPP

#include"distribution.hpp"
#include"specStorage.hpp"
#include"effectSkill.hpp"
#include"skillCommon.hpp"
#include<initializer_list>
#include<limits>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        constexpr Common::PointSkill minSkillPoints     { 0 };
        constexpr Common::PointSkill maxSkillPoints     { std::numeric_limits<Common::PointSkill>::max() };
        constexpr Common::PointSkill initSkillPoints    { 4 };

        constexpr Common::LevelStat minSkillLevel   { 0 };
        constexpr Common::LevelStat maxSkillLevel   { 10 };

        constexpr std::initializer_list<Common::PointSkill>
            pointSkillDist{ 0, -1, -1, -1, -2, -2, -3, -3, -4, -5, -6 };

        /// --------------------Combat skills--------------------
        /// SKILL LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// AUTOMATIC WEAPONS
        constexpr std::initializer_list<Common::Chance> automaticARHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Chance> automaticSMGHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        /// BIG GUNS
        constexpr std::initializer_list<Common::Chance> bigHMGHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Chance> bigFlamethrowerHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        /// BRAWLING
        constexpr std::initializer_list<Common::Multiplier> brawlingCombatSpeedDist{
            0,    5/*,  5,    5,    5,    5,    5,    5,    5,    5,    5*/ };
        constexpr std::initializer_list<Common::Chance> brawlingWeaponHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        /// MELEE COMBAT
        constexpr std::initializer_list<Common::Chance> meleeBluntWeaponHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Chance> meleeBladedWeaponHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        /// SMALL ARMS
        constexpr std::initializer_list<Common::Chance> smallSAPistolHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Chance> smallRevolverHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Chance> smallPumpShotgunHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Chance> smallAutoShotgunHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        /// SNIPER
        constexpr std::initializer_list<Common::Chance> sniperRifleHitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };

        /// --------------------General skills--------------------
        /// SKILL LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// ANIMAL WHISPERER
        constexpr std::initializer_list<Common::Bonus> animalCompanionDamageDist{
            0,   50/*, 50,   50,   50,   50,   50,   50,   50,   50,   50*/ };
        /// EXPLOSIVES
        constexpr std::initializer_list<Common::Resistance> explosiveDamageResDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> explosiveDamageDist{
            0,   50/*, 50,   50,   50,   50,   50,   50,   50,   50,   50*/ };
        /// FIRST AID
        constexpr std::initializer_list<Common::Bonus> aidHealingItemDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> aidHealingReviveDist{
            0,  100/*,100,  100,  100,  100,  100,  100,  100,  100,  100*/ };
        /// SNEAKY SHIT
        constexpr std::initializer_list<Common::Perception> sneakyPerceptionDist{
            0,    1/*,  1,    1,    1,    1,    1,    1,    1,    1,    1*/ };
        constexpr std::initializer_list<Common::Initiative> sneakyInitiativeDist{
            0,   40/*, 40,   40,   40,   40,   40,   40,   40,   40,   40*/ };
        constexpr std::initializer_list<Common::Time> sneakyDetectionDist{
            0,  300/*,300,  300,  300,  300,  300,  300,  300,  300,  300*/ };
        constexpr std::initializer_list<Common::Bonus> sneakyAttackDamageDist{
            0,  100/*,100,  100,  100,  100,  100,  100,  100,  100,  100*/ };
        /// WEIRD SCIENCE
        constexpr std::initializer_list<Common::Bonus> weirdEnergyDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> weirdFireDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> weirdColdDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };

        /// --------------------Exploration skills--------------------
        /// SKILL LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// MECHANICS
        constexpr std::initializer_list<Common::Bonus> mechRobotDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> mechVehicleDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> mechSynthDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> mechRepairKitDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        /// SURVIVAL
        constexpr std::initializer_list<Common::Bonus> survAnimalDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        constexpr std::initializer_list<Common::Bonus> survMutantDamageDist{
            0,   30/*, 30,   30,   30,   30,   30,   30,   30,   30,   30*/ };
        /// WEAPON MODDING
        constexpr std::initializer_list<Common::Bonus> weaponModScrapDist{
            0,  100/*,100,  100,  100,  100,  100,  100,  100,  100,  100*/ };

        /// --------------------Social skills--------------------
        /// SKILL LEVEL:
        /// 0     1     2     3     4     5     6     7     8     9    10
        /// BARTER
        constexpr std::initializer_list<Common::Bonus> barterSellValueDist{
            0,  500/*,500,  500,  500,  500,  500,  500,  500,  500,  500*/ };
        constexpr std::initializer_list<Common::Bonus> barterBuyCostDist{
            0,  -10/*,-10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10*/ };
        /// LEADERSHIP
        constexpr std::initializer_list<Common::Chance> leaderHitChanceGainDist{
            0,   10/*, 10,   10,   10,   10,   10,   10,   10,   10,   10*/ };
        constexpr std::initializer_list<Common::Bonus> leaderBossKillDamageGainDist{
            0,   25/*, 25,   25,   25,   25,   25,   25,   25,   25,   25*/ };
        constexpr std::initializer_list<Common::Chance> leaderMultiKillCritChanceGainDist{
            0,   10/*, 10,   10,   10,   10,   10,   10,   10,   10,   10*/ };
        constexpr std::initializer_list<Common::Bonus> leaderReviveCONHealedDist{
            0,   20/*, 20,   20,   20,   20,   20,   20,   20,   20,   20*/ };


        class Character;

        class Skill {
        public:
            using Type      = SkillType;

        public:
            Skill(Character& character);

            void addLevel(Skill::Type type, Common::LevelStat shift) noexcept;

            void addPoint(Common::PointSkill shift) noexcept {
                pStor_.add(shift);
            }

            bool isModified() const noexcept;

            void accept() noexcept;

            void reject() noexcept;

            void reset() noexcept;

        public:
            const Common::SpecStorage<Common::LevelStat>& level(Skill::Type type) const noexcept {
                return levels_[static_cast<std::underlying_type_t<Skill::Type>>(type)];
            }

            const Common::SpecStorage<Common::PointSkill>& storage() const noexcept {
                return pStor_;
            }

        private:
            void apply() noexcept;

            void apply(Skill::Type type) noexcept;

        private:
            static std::vector<Common::SpecStorage<Common::LevelStat>>  initLevels();
            static std::vector<Common::PointSkill>                      initPointDist();
            static std::vector<EffectSkillAutomatic>                    initAutomaticDist();
            static std::vector<EffectSkillBigGuns>                      initBigGunsDist();
            static std::vector<EffectSkillBrawling>                     initBrawlingDist();
            static std::vector<EffectSkillMelee>                        initMeleeDist();
            static std::vector<EffectSkillSmallArms>                    initSmallArmsDist();
            static std::vector<EffectSkillSniper>                       initSniperDist();
            static std::vector<EffectSkillAnimal>                       initAnimalDist();
            static std::vector<EffectSkillExplosive>                    initExplosiveDist();
            static std::vector<EffectSkillFirstAid>                     initFirstAidDist();
            static std::vector<EffectSkillSneakyShit>                   initSneakyShitDist();
            static std::vector<EffectSkillWeirdScience>                 initWeirdScienceDist();
            static std::vector<EffectSkillMechanics>                    initMechanicsDist();
            static std::vector<EffectSkillSurvival>                     initSurvivalDist();
            static std::vector<EffectSkillWeaponMod>                    initWeaponModDist();
            static std::vector<EffectSkillBarter>                       initBarterDist();
            static std::vector<EffectSkillLeadership>                   initLeadershipDist();

        private:
            Character&                                              char_;
            std::vector<Common::SpecStorage<Common::LevelStat>>     levels_;
            Common::SpecStorage<Common::PointSkill>                 pStor_;
            Common::Distribution<Common::PointSkill>                pDist_;
            Common::Distribution<EffectSkillAutomatic>              automDist_;
            Common::Distribution<EffectSkillBigGuns>                bigGunsDist_;
            Common::Distribution<EffectSkillBrawling>               brawlDist_;
            Common::Distribution<EffectSkillMelee>                  meleeDist_;
            Common::Distribution<EffectSkillSmallArms>              smallDist_;
            Common::Distribution<EffectSkillSniper>                 sniperDist_;
            Common::Distribution<EffectSkillAnimal>                 animalDist_;
            Common::Distribution<EffectSkillExplosive>              explosDist_;
            Common::Distribution<EffectSkillFirstAid>               aidDist_;
            Common::Distribution<EffectSkillSneakyShit>             sneakyDist_;
            Common::Distribution<EffectSkillWeirdScience>           weirdDist_;
            Common::Distribution<EffectSkillMechanics>              mechDist_;
            Common::Distribution<EffectSkillSurvival>               survDist_;
            Common::Distribution<EffectSkillWeaponMod>              weaponModDist_;
            Common::Distribution<EffectSkillBarter>                 barterDist_;
            Common::Distribution<EffectSkillLeadership>             leaderDist_;
        };

    }
}

#endif // !SKILL_HPP
