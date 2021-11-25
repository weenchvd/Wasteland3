
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"skill.hpp"
#include"character.hpp"

namespace Game
{
    namespace Object
    {
        using namespace std;

        Skill::Skill(Character& character)
            :
            char_           { character },
            levels_         { initLevels() },
            pDist_          { initPointDist() },
            pStor_          { minSkillPoints, maxSkillPoints },
            automDist_      { initAutomaticDist() },
            bigGunsDist_    { initBigGunsDist() },
            brawlDist_      { initBrawlingDist() },
            meleeDist_      { initMeleeDist() },
            smallDist_      { initSmallArmsDist() },
            sniperDist_     { initSniperDist() },
            animalDist_     { initAnimalDist() },
            explosDist_     { initExplosiveDist() },
            aidDist_        { initFirstAidDist() },
            sneakyDist_     { initSneakyShitDist() },
            weirdDist_      { initWeirdScienceDist() },
            mechDist_       { initMechanicsDist() },
            survDist_       { initSurvivalDist() },
            weaponModDist_  { initWeaponModDist() },
            barterDist_     { initBarterDist() },
            leaderDist_     { initLeadershipDist() }
        {}

        void Skill::addLevel(Skill::Type type, Common::LevelStat shift) noexcept
        {
            auto index = static_cast<underlying_type_t<Attribute::Type>>(type);
            Common::changeLevel(levels_[index], pStor_, pDist_, shift);
        }

        bool Skill::isModified() const noexcept
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

        void Skill::accept() noexcept
        {
            apply();
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.accept();
            }
            pStor_.accept();
        }

        void Skill::reject() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reject();
            }
            pStor_.reject();
        }

        void Skill::reset() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reset();
            }
            pStor_.reset();
        }

        void Skill::apply() noexcept
        {
            apply(Skill::Type::AUTOMATIC_WEAPONS);
            apply(Skill::Type::BIG_GUNS);
            apply(Skill::Type::BRAWLING);
            apply(Skill::Type::MELEE_COMBAT);
            apply(Skill::Type::SMALL_ARMS);
            apply(Skill::Type::SNIPER_RIFLES);
            apply(Skill::Type::ANIMAL_WHISPERER);
            apply(Skill::Type::EXPLOSIVES);
            apply(Skill::Type::FIRST_AID);
            apply(Skill::Type::SNEAKY_SHIT);
            apply(Skill::Type::WEIRD_SCIENCE);
            apply(Skill::Type::ARMOR_MODDING);
            apply(Skill::Type::LOCKPICKING);
            apply(Skill::Type::NERD_STUFF);
            apply(Skill::Type::MECHANICS);
            apply(Skill::Type::SURVIVAL);
            apply(Skill::Type::TOASTER_REPAIR);
            apply(Skill::Type::WEAPON_MODDING);
            apply(Skill::Type::BARTER);
            apply(Skill::Type::HARD_ASS);
            apply(Skill::Type::KISS_ASS);
            apply(Skill::Type::LEADERSHIP);
        }

        void Skill::apply(Skill::Type type) noexcept
        {
            auto index = static_cast<underlying_type_t<Attribute::Type>>(type);
            auto accLevel = levels_[index].getAccepted();
            auto curLevel = levels_[index].get();
            if (accLevel != curLevel) {
                switch (type) {
                case Skill::Type::AUTOMATIC_WEAPONS: {
                    EffectSkillAutomatic sum = automDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::BIG_GUNS: {
                    EffectSkillBigGuns sum = bigGunsDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::BRAWLING: {
                    EffectSkillBrawling sum = brawlDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::MELEE_COMBAT: {
                    EffectSkillMelee sum = meleeDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::SMALL_ARMS: {
                    EffectSkillSmallArms sum = smallDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::SNIPER_RIFLES: {
                    EffectSkillSniper sum = sniperDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::ANIMAL_WHISPERER: {
                    EffectSkillAnimal sum = animalDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::EXPLOSIVES: {
                    EffectSkillExplosive sum = explosDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::FIRST_AID: {
                    EffectSkillFirstAid sum = aidDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::SNEAKY_SHIT: {
                    EffectSkillSneakyShit sum = sneakyDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::WEIRD_SCIENCE: {
                    EffectSkillWeirdScience sum = weirdDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::MECHANICS: {
                    EffectSkillMechanics sum = mechDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::SURVIVAL: {
                    EffectSkillSurvival sum = survDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::WEAPON_MODDING: {
                    EffectSkillWeaponMod sum = weaponModDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::BARTER: {
                    EffectSkillBarter sum = barterDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Skill::Type::LEADERSHIP: {
                    EffectSkillLeadership sum = leaderDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                default:
                    break;
                }
            }
        }

        vector<Common::SpecStorage<Common::LevelStat>> Skill::initLevels()
        {
            Common::SpecStorage<Common::LevelStat> tempLevel{ minSkillLevel, maxSkillLevel };
            auto nSkills = static_cast<underlying_type_t<Skill::Type>>
                (Skill::Type::NUMBER_OF);
            return vector<Common::SpecStorage<Common::LevelStat>>(nSkills, tempLevel);
        }

        inline vector<Common::PointSkill> Skill::initPointDist()
        {
            return vector<Common::PointSkill>(pointSkillDist);
        }

        vector<EffectSkillAutomatic> Skill::initAutomaticDist()
        {
            return Common::initializeDistribution<EffectSkillAutomatic,
                Common::Chance,
                Common::Chance
            >(
                vector<Common::Chance>(automaticARHitDist),
                vector<Common::Chance>(automaticSMGHitDist));
        }

        vector<EffectSkillBigGuns> Skill::initBigGunsDist()
        {
            return Common::initializeDistribution<EffectSkillBigGuns,
                Common::Chance,
                Common::Chance
            >(
                vector<Common::Chance>(bigHMGHitDist),
                vector<Common::Chance>(bigFlamethrowerHitDist));
        }

        vector<EffectSkillBrawling> Skill::initBrawlingDist()
        {
            return Common::initializeDistribution<EffectSkillBrawling,
                Common::Multiplier,
                Common::Chance
            >(
                vector<Common::Multiplier>(brawlingCombatSpeedDist),
                vector<Common::Chance>(brawlingWeaponHitDist));
        }

        vector<EffectSkillMelee> Skill::initMeleeDist()
        {
            return Common::initializeDistribution<EffectSkillMelee,
                Common::Chance,
                Common::Chance
            >(
                vector<Common::Chance>(meleeBluntWeaponHitDist),
                vector<Common::Chance>(meleeBladedWeaponHitDist));
        }

        vector<EffectSkillSmallArms> Skill::initSmallArmsDist()
        {
            return Common::initializeDistribution<EffectSkillSmallArms,
                Common::Chance,
                Common::Chance,
                Common::Chance,
                Common::Chance
            >(
                vector<Common::Chance>(smallSAPistolHitDist),
                vector<Common::Chance>(smallRevolverHitDist),
                vector<Common::Chance>(smallPumpShotgunHitDist),
                vector<Common::Chance>(smallAutoShotgunHitDist));
        }

        vector<EffectSkillSniper> Skill::initSniperDist()
        {
            return Common::initializeDistribution<EffectSkillSniper,
                Common::Chance
            >(
                vector<Common::Chance>(sniperRifleHitDist));
        }

        vector<EffectSkillAnimal> Skill::initAnimalDist()
        {
            return Common::initializeDistribution<EffectSkillAnimal,
                Common::Bonus
            >(
                vector<Common::Bonus>(animalCompanionDamageDist));
        }

        vector<EffectSkillExplosive> Skill::initExplosiveDist()
        {
            return Common::initializeDistribution<EffectSkillExplosive,
                Common::Resistance,
                Common::Bonus
            >(
                vector<Common::Resistance>(explosiveDamageResDist),
                vector<Common::Bonus>(explosiveDamageDist));
        }

        vector<EffectSkillFirstAid> Skill::initFirstAidDist()
        {
            return Common::initializeDistribution<EffectSkillFirstAid,
                Common::Bonus,
                Common::Bonus
            >(
                vector<Common::Bonus>(aidHealingItemDist),
                vector<Common::Bonus>(aidHealingReviveDist));
        }

        vector<EffectSkillSneakyShit> Skill::initSneakyShitDist()
        {
            return Common::initializeDistribution<EffectSkillSneakyShit,
                Common::Time,
                Common::Initiative,
                Common::Bonus,
                Common::Perception
            >(
                vector<Common::Time>(sneakyDetectionDist),
                vector<Common::Initiative>(sneakyInitiativeDist),
                vector<Common::Bonus>(sneakyAttackDamageDist),
                vector<Common::Perception>(sneakyPerceptionDist));
        }

        vector<EffectSkillWeirdScience> Skill::initWeirdScienceDist()
        {
            return Common::initializeDistribution<EffectSkillWeirdScience,
                Common::Bonus,
                Common::Bonus,
                Common::Bonus
            >(
                vector<Common::Bonus>(weirdEnergyDamageDist),
                vector<Common::Bonus>(weirdFireDamageDist),
                vector<Common::Bonus>(weirdColdDamageDist));
        }

        vector<EffectSkillMechanics> Skill::initMechanicsDist()
        {
            return Common::initializeDistribution<EffectSkillMechanics,
                Common::Bonus,
                Common::Bonus,
                Common::Bonus,
                Common::Bonus
            >(
                vector<Common::Bonus>(mechRobotDamageDist),
                vector<Common::Bonus>(mechVehicleDamageDist),
                vector<Common::Bonus>(mechSynthDamageDist),
                vector<Common::Bonus>(mechRepairKitDist));
        }

        vector<EffectSkillSurvival> Skill::initSurvivalDist()
        {
            return Common::initializeDistribution<EffectSkillSurvival,
                Common::Bonus,
                Common::Bonus
            >(
                vector<Common::Bonus>(survAnimalDamageDist),
                vector<Common::Bonus>(survMutantDamageDist));
        }

        vector<EffectSkillWeaponMod> Skill::initWeaponModDist()
        {
            return Common::initializeDistribution<EffectSkillWeaponMod,
                Common::Bonus
            >(
                vector<Common::Bonus>(weaponModScrapDist));
        }

        vector<EffectSkillBarter> Skill::initBarterDist()
        {
            return Common::initializeDistribution<EffectSkillBarter,
                Common::Bonus,
                Common::Bonus
            >(
                vector<Common::Bonus>(barterSellValueDist),
                vector<Common::Bonus>(barterBuyCostDist));
        }

        vector<EffectSkillLeadership> Skill::initLeadershipDist()
        {
            return Common::initializeDistribution<EffectSkillLeadership,
                Common::Chance,
                Common::Bonus,
                Common::Chance,
                Common::Bonus
            >(
                vector<Common::Chance>(leaderHitChanceGainDist),
                vector<Common::Bonus>(leaderBossKillDamageGainDist),
                vector<Common::Chance>(leaderMultiKillCritChanceGainDist),
                vector<Common::Bonus>(leaderReviveCONHealedDist));
        }

    }
}