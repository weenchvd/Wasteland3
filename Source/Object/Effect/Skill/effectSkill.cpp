
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"effectSkill.hpp"
#include"character.hpp"
#include"operators.hpp"
#include<cmath>

namespace Game
{
    namespace Object
    {
        EffectSkillAutomatic::EffectSkillAutomatic(
            Common::Chance arHitChance,
            Common::Chance smgHitChance)
            :
            chaHitAR_   { arHitChance },
            chaHitSMG_  { smgHitChance }
        {}

        void EffectSkillAutomatic::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillAutomatic& EffectSkillAutomatic::operator+=(const EffectSkillAutomatic& other)
        {
            this->chaHitAR_     += other.chaHitAR_;
            this->chaHitSMG_    += other.chaHitSMG_;
            return *this;
        }

        EffectSkillAutomatic& EffectSkillAutomatic::operator-=(const EffectSkillAutomatic& other)
        {
            this->chaHitAR_     -= other.chaHitAR_;
            this->chaHitSMG_    -= other.chaHitSMG_;
            return *this;
        }

        EffectSkillAutomatic operator+(const EffectSkillAutomatic& left, const EffectSkillAutomatic& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillAutomatic operator-(const EffectSkillAutomatic& left, const EffectSkillAutomatic& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillBigGuns::EffectSkillBigGuns(
            Common::Chance hmgHitChance,
            Common::Chance flamethrowerHitChance)
            :
            chaHitHMG_  { hmgHitChance },
            chaHitFT_   { flamethrowerHitChance }
        {}

        void EffectSkillBigGuns::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillBigGuns& EffectSkillBigGuns::operator+=(const EffectSkillBigGuns& other)
        {
            this->chaHitHMG_    += other.chaHitHMG_;
            this->chaHitFT_     += other.chaHitFT_;
            return *this;
        }

        EffectSkillBigGuns& EffectSkillBigGuns::operator-=(const EffectSkillBigGuns& other)
        {
            this->chaHitHMG_    -= other.chaHitHMG_;
            this->chaHitFT_     -= other.chaHitFT_;
            return *this;
        }

        EffectSkillBigGuns operator+(const EffectSkillBigGuns& left, const EffectSkillBigGuns& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillBigGuns operator-(const EffectSkillBigGuns& left, const EffectSkillBigGuns& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillBrawling::EffectSkillBrawling(
            Common::Multiplier combatSpeed,
            Common::Chance brawlingHitChance)
            :
            mulSpeed_       { combatSpeed },
            chaHitBrawl_    { brawlingHitChance }
        {}

        void EffectSkillBrawling::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillBrawling& EffectSkillBrawling::operator+=(const EffectSkillBrawling& other)
        {
            this->mulSpeed_     += other.mulSpeed_;
            this->chaHitBrawl_  += other.chaHitBrawl_;
            return *this;
        }

        EffectSkillBrawling& EffectSkillBrawling::operator-=(const EffectSkillBrawling& other)
        {
            this->mulSpeed_     -= other.mulSpeed_;
            this->chaHitBrawl_  -= other.chaHitBrawl_;
            return *this;
        }

        EffectSkillBrawling operator+(const EffectSkillBrawling& left, const EffectSkillBrawling& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillBrawling operator-(const EffectSkillBrawling& left, const EffectSkillBrawling& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillMelee::EffectSkillMelee(
            Common::Chance bluntHitChance,
            Common::Chance bladedHitChance)
            :
            chaHitBlunt_   { bluntHitChance },
            chaHitBladed_  { bladedHitChance }
        {}

        void EffectSkillMelee::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillMelee& EffectSkillMelee::operator+=(const EffectSkillMelee& other)
        {
            this->chaHitBlunt_     += other.chaHitBlunt_;
            this->chaHitBladed_    += other.chaHitBladed_;
            return *this;
        }

        EffectSkillMelee& EffectSkillMelee::operator-=(const EffectSkillMelee& other)
        {
            this->chaHitBlunt_     -= other.chaHitBlunt_;
            this->chaHitBladed_    -= other.chaHitBladed_;
            return *this;
        }

        EffectSkillMelee operator+(const EffectSkillMelee& left, const EffectSkillMelee& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillMelee operator-(const EffectSkillMelee& left, const EffectSkillMelee& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillSmallArms::EffectSkillSmallArms(
            Common::Chance semiAutoPistolHitChance,
            Common::Chance revolverHitChance,
            Common::Chance pumpShotgunHitChance,
            Common::Chance autoShotgunHitChance)
            :
            chaHitSAPistol_ { semiAutoPistolHitChance },
            chaHitRevolver_ { revolverHitChance },
            chaHitPumpSG_   { pumpShotgunHitChance },
            chaHitAutoSG_   { autoShotgunHitChance }
        {}

        void EffectSkillSmallArms::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillSmallArms& EffectSkillSmallArms::operator+=(const EffectSkillSmallArms& other)
        {
            this->chaHitSAPistol_   += other.chaHitSAPistol_;
            this->chaHitRevolver_   += other.chaHitRevolver_;
            this->chaHitPumpSG_     += other.chaHitPumpSG_;
            this->chaHitAutoSG_     += other.chaHitAutoSG_;
            return *this;
        }

        EffectSkillSmallArms& EffectSkillSmallArms::operator-=(const EffectSkillSmallArms& other)
        {
            this->chaHitSAPistol_   -= other.chaHitSAPistol_;
            this->chaHitRevolver_   -= other.chaHitRevolver_;
            this->chaHitPumpSG_     -= other.chaHitPumpSG_;
            this->chaHitAutoSG_     -= other.chaHitAutoSG_;
            return *this;
        }

        EffectSkillSmallArms operator+(const EffectSkillSmallArms& left, const EffectSkillSmallArms& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillSmallArms operator-(const EffectSkillSmallArms& left, const EffectSkillSmallArms& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillSniper::EffectSkillSniper(
            Common::Chance sniperRifleHitChance)
            :
            chaHitSniper_{ sniperRifleHitChance }
        {}

        void EffectSkillSniper::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillSniper& EffectSkillSniper::operator+=(const EffectSkillSniper& other)
        {
            this->chaHitSniper_ += other.chaHitSniper_;
            return *this;
        }

        EffectSkillSniper& EffectSkillSniper::operator-=(const EffectSkillSniper& other)
        {
            this->chaHitSniper_ -= other.chaHitSniper_;
            return *this;
        }

        EffectSkillSniper operator+(const EffectSkillSniper& left, const EffectSkillSniper& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillSniper operator-(const EffectSkillSniper& left, const EffectSkillSniper& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillAnimal::EffectSkillAnimal(
            Common::Bonus animalCompanionDamageBonus)
            :
            bonAnimalDmg_{ animalCompanionDamageBonus }
        {}

        void EffectSkillAnimal::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillAnimal& EffectSkillAnimal::operator+=(const EffectSkillAnimal& other)
        {
            this->bonAnimalDmg_ += other.bonAnimalDmg_;
            return *this;
        }

        EffectSkillAnimal& EffectSkillAnimal::operator-=(const EffectSkillAnimal& other)
        {
            this->bonAnimalDmg_ -= other.bonAnimalDmg_;
            return *this;
        }

        EffectSkillAnimal operator+(const EffectSkillAnimal& left, const EffectSkillAnimal& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillAnimal operator-(const EffectSkillAnimal& left, const EffectSkillAnimal& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillExplosive::EffectSkillExplosive(
            Common::Resistance explosiveDamageResistance,
            Common::Bonus explosiveDamageBonus)
            :
            resExplDmg_{ explosiveDamageResistance },
            bonExplDmg_{ explosiveDamageBonus }
        {}

        void EffectSkillExplosive::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillExplosive& EffectSkillExplosive::operator+=(const EffectSkillExplosive& other)
        {
            this->resExplDmg_ += other.resExplDmg_;
            this->bonExplDmg_ += other.bonExplDmg_;
            return *this;
        }

        EffectSkillExplosive& EffectSkillExplosive::operator-=(const EffectSkillExplosive& other)
        {
            this->resExplDmg_ -= other.resExplDmg_;
            this->bonExplDmg_ -= other.bonExplDmg_;
            return *this;
        }

        EffectSkillExplosive operator+(const EffectSkillExplosive& left, const EffectSkillExplosive& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillExplosive operator-(const EffectSkillExplosive& left, const EffectSkillExplosive& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillFirstAid::EffectSkillFirstAid(
            Common::Bonus healingItemBonus,
            Common::Bonus healingWhenRevivingAlliesBonus)
            :
            bonHealItem_    { healingItemBonus },
            bonHealRevive_  { healingWhenRevivingAlliesBonus }
        {}

        void EffectSkillFirstAid::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillFirstAid& EffectSkillFirstAid::operator+=(const EffectSkillFirstAid& other)
        {
            this->bonHealItem_      += other.bonHealItem_;
            this->bonHealRevive_    += other.bonHealRevive_;
            return *this;
        }

        EffectSkillFirstAid& EffectSkillFirstAid::operator-=(const EffectSkillFirstAid& other)
        {
            this->bonHealItem_      -= other.bonHealItem_;
            this->bonHealRevive_    -= other.bonHealRevive_;
            return *this;
        }

        EffectSkillFirstAid operator+(const EffectSkillFirstAid& left, const EffectSkillFirstAid& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillFirstAid operator-(const EffectSkillFirstAid& left, const EffectSkillFirstAid& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillSneakyShit::EffectSkillSneakyShit(
            Common::Time detectionTime,
            Common::Initiative initiative,
            Common::Bonus sneakAttackDamageBonus,
            Common::Perception perception)
            :
            timeDetect_     { detectionTime },
            initiat_        { initiative },
            bonSneakDmg_    { sneakAttackDamageBonus },
            percept_        { perception }
        {}

        void EffectSkillSneakyShit::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillSneakyShit& EffectSkillSneakyShit::operator+=(const EffectSkillSneakyShit& other)
        {
            this->timeDetect_   += other.timeDetect_;
            this->initiat_      += other.initiat_;
            this->bonSneakDmg_  += other.bonSneakDmg_;
            this->percept_      += other.percept_;
            return *this;
        }

        EffectSkillSneakyShit& EffectSkillSneakyShit::operator-=(const EffectSkillSneakyShit& other)
        {
            this->timeDetect_   -= other.timeDetect_;
            this->initiat_      -= other.initiat_;
            this->bonSneakDmg_  -= other.bonSneakDmg_;
            this->percept_      -= other.percept_;
            return *this;
        }

        EffectSkillSneakyShit operator+(const EffectSkillSneakyShit& left, const EffectSkillSneakyShit& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillSneakyShit operator-(const EffectSkillSneakyShit& left, const EffectSkillSneakyShit& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillWeirdScience::EffectSkillWeirdScience(
            Common::Bonus energyDamageBonus,
            Common::Bonus fireDamageBonus,
            Common::Bonus coldDamageBonus)
            :
            bonEnerDmg_{ energyDamageBonus },
            bonFireDmg_{ fireDamageBonus },
            bonColdDmg_{ coldDamageBonus }
        {}

        void EffectSkillWeirdScience::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillWeirdScience& EffectSkillWeirdScience::operator+=(const EffectSkillWeirdScience& other)
        {
            this->bonEnerDmg_ += other.bonEnerDmg_;
            this->bonFireDmg_ += other.bonFireDmg_;
            this->bonColdDmg_ += other.bonColdDmg_;
            return *this;
        }

        EffectSkillWeirdScience& EffectSkillWeirdScience::operator-=(const EffectSkillWeirdScience& other)
        {
            this->bonEnerDmg_ -= other.bonEnerDmg_;
            this->bonFireDmg_ -= other.bonFireDmg_;
            this->bonColdDmg_ -= other.bonColdDmg_;
            return *this;
        }

        EffectSkillWeirdScience operator+(const EffectSkillWeirdScience& left, const EffectSkillWeirdScience& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillWeirdScience operator-(const EffectSkillWeirdScience& left, const EffectSkillWeirdScience& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillMechanics::EffectSkillMechanics(
            Common::Bonus robotDamageBonus,
            Common::Bonus vehicleDamageBonus,
            Common::Bonus synthDamageBonus,
            Common::Bonus repairKitBonus)
            :
            bonRobotDmg_    { robotDamageBonus },
            bonVehicDmg_    { vehicleDamageBonus },
            bonSynthDmg_    { synthDamageBonus },
            bonRepairKit_   { repairKitBonus }
        {}

        void EffectSkillMechanics::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillMechanics& EffectSkillMechanics::operator+=(const EffectSkillMechanics& other)
        {
            this->bonRobotDmg_  += other.bonRobotDmg_;
            this->bonVehicDmg_  += other.bonVehicDmg_;
            this->bonSynthDmg_  += other.bonSynthDmg_;
            this->bonRepairKit_ += other.bonRepairKit_;
            return *this;
        }

        EffectSkillMechanics& EffectSkillMechanics::operator-=(const EffectSkillMechanics& other)
        {
            this->bonRobotDmg_  -= other.bonRobotDmg_;
            this->bonVehicDmg_  -= other.bonVehicDmg_;
            this->bonSynthDmg_  -= other.bonSynthDmg_;
            this->bonRepairKit_ -= other.bonRepairKit_;
            return *this;
        }

        EffectSkillMechanics operator+(const EffectSkillMechanics& left, const EffectSkillMechanics& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillMechanics operator-(const EffectSkillMechanics& left, const EffectSkillMechanics& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillSurvival::EffectSkillSurvival(
            Common::Bonus animalDamageBonus,
            Common::Bonus mutantDamageBonus)
            :
            bonAnimalDmg_{ animalDamageBonus },
            bonMutantDmg_{ mutantDamageBonus }
        {}

        void EffectSkillSurvival::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillSurvival& EffectSkillSurvival::operator+=(const EffectSkillSurvival& other)
        {
            this->bonAnimalDmg_ += other.bonAnimalDmg_;
            this->bonMutantDmg_ += other.bonMutantDmg_;
            return *this;
        }

        EffectSkillSurvival& EffectSkillSurvival::operator-=(const EffectSkillSurvival& other)
        {
            this->bonAnimalDmg_ -= other.bonAnimalDmg_;
            this->bonMutantDmg_ -= other.bonMutantDmg_;
            return *this;
        }

        EffectSkillSurvival operator+(const EffectSkillSurvival& left, const EffectSkillSurvival& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillSurvival operator-(const EffectSkillSurvival& left, const EffectSkillSurvival& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillWeaponMod::EffectSkillWeaponMod(
            Common::Bonus fieldStrippingScrapBonus)
            :
            bonScrapDmg_{ fieldStrippingScrapBonus }
        {}

        void EffectSkillWeaponMod::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillWeaponMod& EffectSkillWeaponMod::operator+=(const EffectSkillWeaponMod& other)
        {
            this->bonScrapDmg_ += other.bonScrapDmg_;
            return *this;
        }

        EffectSkillWeaponMod& EffectSkillWeaponMod::operator-=(const EffectSkillWeaponMod& other)
        {
            this->bonScrapDmg_ -= other.bonScrapDmg_;
            return *this;
        }

        EffectSkillWeaponMod operator+(const EffectSkillWeaponMod& left, const EffectSkillWeaponMod& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillWeaponMod operator-(const EffectSkillWeaponMod& left, const EffectSkillWeaponMod& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillBarter::EffectSkillBarter(
            Common::Bonus sellValueBonus,
            Common::Bonus buyCostBonus)
            :
            bonSellValue_   { sellValueBonus },
            bonBuyCost_     { buyCostBonus }
        {}

        void EffectSkillBarter::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillBarter& EffectSkillBarter::operator+=(const EffectSkillBarter& other)
        {
            this->bonSellValue_ += other.bonSellValue_;
            this->bonBuyCost_   += other.bonBuyCost_;
            return *this;
        }

        EffectSkillBarter& EffectSkillBarter::operator-=(const EffectSkillBarter& other)
        {
            this->bonSellValue_ -= other.bonSellValue_;
            this->bonBuyCost_   -= other.bonBuyCost_;
            return *this;
        }

        EffectSkillBarter operator+(const EffectSkillBarter& left, const EffectSkillBarter& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillBarter operator-(const EffectSkillBarter& left, const EffectSkillBarter& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------

        EffectSkillLeadership::EffectSkillLeadership(
            Common::Chance baseHitChance,
            Common::Bonus normalDamageBonusOnBossKill,
            Common::Chance baseCriticalDamageChanceOnMultiKill,
            Common::Bonus conHealedBonusOnRevive)
            :
            chaHit_         { baseHitChance },
            bonNormDmg_     { normalDamageBonusOnBossKill },
            chaCritDmg_     { baseCriticalDamageChanceOnMultiKill },
            bonCONHealed_   { conHealedBonusOnRevive }
        {}

        void EffectSkillLeadership::apply(Character& character) noexcept
        {
            //TODO character.resistanceStatusEffectAdd(resStatEff_);
        }

        EffectSkillLeadership& EffectSkillLeadership::operator+=(const EffectSkillLeadership& other)
        {
            this->chaHit_       += other.chaHit_;
            this->bonNormDmg_   += other.bonNormDmg_;
            this->chaCritDmg_   += other.chaCritDmg_;
            this->bonCONHealed_ += other.bonCONHealed_;
            return *this;
        }

        EffectSkillLeadership& EffectSkillLeadership::operator-=(const EffectSkillLeadership& other)
        {
            this->chaHit_       -= other.chaHit_;
            this->bonNormDmg_   -= other.bonNormDmg_;
            this->chaCritDmg_   -= other.chaCritDmg_;
            this->bonCONHealed_ -= other.bonCONHealed_;
            return *this;
        }

        EffectSkillLeadership operator+(const EffectSkillLeadership& left, const EffectSkillLeadership& right)
        {
            return Common::operatorPlus(left, right);
        }

        EffectSkillLeadership operator-(const EffectSkillLeadership& left, const EffectSkillLeadership& right)
        {
            return Common::operatorMinus(left, right);
        }

        ///------------------------------------------------------------------------------------------------


        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        

    }
}
