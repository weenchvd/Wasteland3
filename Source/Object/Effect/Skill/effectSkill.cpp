
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"effectSkill.hpp"
#include"character.hpp"
#include"operators.hpp"
#include<cmath>

namespace game {
namespace object {

EffectSkillAutomatic::EffectSkillAutomatic(
    common::Chance arHitChance,
    common::Chance smgHitChance)
    :
    chaHitAR_   { arHitChance },
    chaHitSMG_  { smgHitChance }
{}

void EffectSkillAutomatic::apply(Character& character) noexcept
{
    character.chanceHitARAdd(chaHitAR_);
    character.chanceHitSMGAdd(chaHitSMG_);
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
    return common::operatorPlus(left, right);
}

EffectSkillAutomatic operator-(const EffectSkillAutomatic& left, const EffectSkillAutomatic& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillBigGuns::EffectSkillBigGuns(
    common::Chance hmgHitChance,
    common::Chance flamethrowerHitChance)
    :
    chaHitHMG_  { hmgHitChance },
    chaHitFT_   { flamethrowerHitChance }
{}

void EffectSkillBigGuns::apply(Character& character) noexcept
{
    character.chanceHitHMGAdd(chaHitHMG_);
    character.chanceHitFlamethrowerAdd(chaHitFT_);
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
    return common::operatorPlus(left, right);
}

EffectSkillBigGuns operator-(const EffectSkillBigGuns& left, const EffectSkillBigGuns& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillBrawling::EffectSkillBrawling(
    common::Multiplier combatSpeed,
    common::Chance brawlingHitChance)
    :
    mulSpeed_       { combatSpeed },
    chaHitBrawl_    { brawlingHitChance }
{}

void EffectSkillBrawling::apply(Character& character) noexcept
{
    character.multiplierCombatSpeedAdd(mulSpeed_);
    character.chanceHitBrawlingAdd(chaHitBrawl_);
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
    return common::operatorPlus(left, right);
}

EffectSkillBrawling operator-(const EffectSkillBrawling& left, const EffectSkillBrawling& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillMelee::EffectSkillMelee(
    common::Chance bluntHitChance,
    common::Chance bladedHitChance)
    :
    chaHitBlunt_   { bluntHitChance },
    chaHitBladed_  { bladedHitChance }
{}

void EffectSkillMelee::apply(Character& character) noexcept
{
    character.chanceHitBluntAdd(chaHitBlunt_);
    character.chanceHitBladedAdd(chaHitBladed_);
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
    return common::operatorPlus(left, right);
}

EffectSkillMelee operator-(const EffectSkillMelee& left, const EffectSkillMelee& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillSmallArms::EffectSkillSmallArms(
    common::Chance semiAutoPistolHitChance,
    common::Chance revolverHitChance,
    common::Chance pumpShotgunHitChance,
    common::Chance autoShotgunHitChance)
    :
    chaHitSAPistol_ { semiAutoPistolHitChance },
    chaHitRevolver_ { revolverHitChance },
    chaHitPumpSG_   { pumpShotgunHitChance },
    chaHitAutoSG_   { autoShotgunHitChance }
{}

void EffectSkillSmallArms::apply(Character& character) noexcept
{
    character.chanceHitSemiAutoPistolAdd(chaHitSAPistol_);
    character.chanceHitRevolverAdd(chaHitRevolver_);
    character.chanceHitPumpSGAdd(chaHitPumpSG_);
    character.chanceHitAutoSGAdd(chaHitAutoSG_);
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
    return common::operatorPlus(left, right);
}

EffectSkillSmallArms operator-(const EffectSkillSmallArms& left, const EffectSkillSmallArms& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillSniper::EffectSkillSniper(
    common::Chance sniperRifleHitChance)
    :
    chaHitSR_{ sniperRifleHitChance }
{}

void EffectSkillSniper::apply(Character& character) noexcept
{
    character.chanceHitSRAdd(chaHitSR_);
}

EffectSkillSniper& EffectSkillSniper::operator+=(const EffectSkillSniper& other)
{
    this->chaHitSR_ += other.chaHitSR_;
    return *this;
}

EffectSkillSniper& EffectSkillSniper::operator-=(const EffectSkillSniper& other)
{
    this->chaHitSR_ -= other.chaHitSR_;
    return *this;
}

EffectSkillSniper operator+(const EffectSkillSniper& left, const EffectSkillSniper& right)
{
    return common::operatorPlus(left, right);
}

EffectSkillSniper operator-(const EffectSkillSniper& left, const EffectSkillSniper& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillAnimal::EffectSkillAnimal(
    common::Bonus animalCompanionDamageBonus)
    :
    bonAnimalDmg_{ animalCompanionDamageBonus }
{}

void EffectSkillAnimal::apply(Character& character) noexcept
{
    character.bonusAnimalCompanionDamageAdd(bonAnimalDmg_);
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
    return common::operatorPlus(left, right);
}

EffectSkillAnimal operator-(const EffectSkillAnimal& left, const EffectSkillAnimal& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillExplosive::EffectSkillExplosive(
    common::Resistance explosiveDamageResistance,
    common::Bonus explosiveDamageBonus)
    :
    resExplDmg_{ explosiveDamageResistance },
    bonExplDmg_{ explosiveDamageBonus }
{}

void EffectSkillExplosive::apply(Character& character) noexcept
{
    character.resistanceExplosiveDamageAdd(resExplDmg_);
    character.bonusExplosiveDamageAdd(bonExplDmg_);
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
    return common::operatorPlus(left, right);
}

EffectSkillExplosive operator-(const EffectSkillExplosive& left, const EffectSkillExplosive& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillFirstAid::EffectSkillFirstAid(
    common::Bonus healingBonus,
    common::Bonus healingWhenRevivingAlliesBonus)
    :
    bonHeal_        { healingBonus },
    bonHealRevive_  { healingWhenRevivingAlliesBonus }
{}

void EffectSkillFirstAid::apply(Character& character) noexcept
{
    character.bonusHealingAdd(bonHeal_);
    character.bonusHealingWhenRevivingAlliesAdd(bonHealRevive_);
}

EffectSkillFirstAid& EffectSkillFirstAid::operator+=(const EffectSkillFirstAid& other)
{
    this->bonHeal_          += other.bonHeal_;
    this->bonHealRevive_    += other.bonHealRevive_;
    return *this;
}

EffectSkillFirstAid& EffectSkillFirstAid::operator-=(const EffectSkillFirstAid& other)
{
    this->bonHeal_          -= other.bonHeal_;
    this->bonHealRevive_    -= other.bonHealRevive_;
    return *this;
}

EffectSkillFirstAid operator+(const EffectSkillFirstAid& left, const EffectSkillFirstAid& right)
{
    return common::operatorPlus(left, right);
}

EffectSkillFirstAid operator-(const EffectSkillFirstAid& left, const EffectSkillFirstAid& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillSneakyShit::EffectSkillSneakyShit(
    common::Time detectionTime,
    common::Initiative initiative,
    common::Bonus sneakAttackDamageBonus,
    common::Perception perception)
    :
    timeDetect_     { detectionTime },
    initiat_        { initiative },
    bonSneakDmg_    { sneakAttackDamageBonus },
    percept_        { perception }
{}

void EffectSkillSneakyShit::apply(Character& character) noexcept
{
    character.timeDetectionAdd(timeDetect_);
    character.initiativeAdd(initiat_);
    character.bonusSneakAttackDamageAdd(bonSneakDmg_);
    character.perceptionAdd(percept_);
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
    return common::operatorPlus(left, right);
}

EffectSkillSneakyShit operator-(const EffectSkillSneakyShit& left, const EffectSkillSneakyShit& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillWeirdScience::EffectSkillWeirdScience(
    common::Bonus energyDamageBonus,
    common::Bonus fireDamageBonus,
    common::Bonus coldDamageBonus)
    :
    bonEnerDmg_{ energyDamageBonus },
    bonFireDmg_{ fireDamageBonus },
    bonColdDmg_{ coldDamageBonus }
{}

void EffectSkillWeirdScience::apply(Character& character) noexcept
{
    character.bonusEnergyDamageAdd(bonEnerDmg_);
    character.bonusFireDamageAdd(bonFireDmg_);
    character.bonusColdDamageAdd(bonColdDmg_);
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
    return common::operatorPlus(left, right);
}

EffectSkillWeirdScience operator-(const EffectSkillWeirdScience& left, const EffectSkillWeirdScience& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillMechanics::EffectSkillMechanics(
    common::Bonus damageBonusVsRobots,
    common::Bonus damageBonusVsVehicles,
    common::Bonus damageBonusVsSynths,
    common::Bonus repairBonus)
    :
    bonDmgVsRobot_  { damageBonusVsRobots },
    bonDmgVsVehic_  { damageBonusVsVehicles },
    bonDmgVsSynth_  { damageBonusVsSynths },
    bonRepair_      { repairBonus }
{}

void EffectSkillMechanics::apply(Character& character) noexcept
{
    character.bonusDamageVsRobotsAdd(bonDmgVsRobot_);
    character.bonusDamageVsVehiclesAdd(bonDmgVsVehic_);
    character.bonusDamageVsSynthsAdd(bonDmgVsSynth_);
    character.bonusRepairAdd(bonRepair_);
}

EffectSkillMechanics& EffectSkillMechanics::operator+=(const EffectSkillMechanics& other)
{
    this->bonDmgVsRobot_    += other.bonDmgVsRobot_;
    this->bonDmgVsVehic_    += other.bonDmgVsVehic_;
    this->bonDmgVsSynth_    += other.bonDmgVsSynth_;
    this->bonRepair_        += other.bonRepair_;
    return *this;
}

EffectSkillMechanics& EffectSkillMechanics::operator-=(const EffectSkillMechanics& other)
{
    this->bonDmgVsRobot_    -= other.bonDmgVsRobot_;
    this->bonDmgVsVehic_    -= other.bonDmgVsVehic_;
    this->bonDmgVsSynth_    -= other.bonDmgVsSynth_;
    this->bonRepair_        -= other.bonRepair_;
    return *this;
}

EffectSkillMechanics operator+(const EffectSkillMechanics& left, const EffectSkillMechanics& right)
{
    return common::operatorPlus(left, right);
}

EffectSkillMechanics operator-(const EffectSkillMechanics& left, const EffectSkillMechanics& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillSurvival::EffectSkillSurvival(
    common::Bonus damageBonusVsAnimals,
    common::Bonus damageBonusVsMutants)
    :
    bonDmgVsAnimal_{ damageBonusVsAnimals },
    bonDmgVsMutant_{ damageBonusVsMutants }
{}

void EffectSkillSurvival::apply(Character& character) noexcept
{
    character.bonusDamageVsAnimalsAdd(bonDmgVsAnimal_);
    character.bonusDamageVsMutantsAdd(bonDmgVsMutant_);
}

EffectSkillSurvival& EffectSkillSurvival::operator+=(const EffectSkillSurvival& other)
{
    this->bonDmgVsAnimal_ += other.bonDmgVsAnimal_;
    this->bonDmgVsMutant_ += other.bonDmgVsMutant_;
    return *this;
}

EffectSkillSurvival& EffectSkillSurvival::operator-=(const EffectSkillSurvival& other)
{
    this->bonDmgVsAnimal_ -= other.bonDmgVsAnimal_;
    this->bonDmgVsMutant_ -= other.bonDmgVsMutant_;
    return *this;
}

EffectSkillSurvival operator+(const EffectSkillSurvival& left, const EffectSkillSurvival& right)
{
    return common::operatorPlus(left, right);
}

EffectSkillSurvival operator-(const EffectSkillSurvival& left, const EffectSkillSurvival& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillWeaponMod::EffectSkillWeaponMod(
    common::Bonus fieldStrippingScrapBonus)
    :
    bonScrap_{ fieldStrippingScrapBonus }
{}

void EffectSkillWeaponMod::apply(Character& character) noexcept
{
    character.bonusFieldStrippingScrapAdd(bonScrap_);
}

EffectSkillWeaponMod& EffectSkillWeaponMod::operator+=(const EffectSkillWeaponMod& other)
{
    this->bonScrap_ += other.bonScrap_;
    return *this;
}

EffectSkillWeaponMod& EffectSkillWeaponMod::operator-=(const EffectSkillWeaponMod& other)
{
    this->bonScrap_ -= other.bonScrap_;
    return *this;
}

EffectSkillWeaponMod operator+(const EffectSkillWeaponMod& left, const EffectSkillWeaponMod& right)
{
    return common::operatorPlus(left, right);
}

EffectSkillWeaponMod operator-(const EffectSkillWeaponMod& left, const EffectSkillWeaponMod& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillBarter::EffectSkillBarter(
    common::Bonus sellValueBonus,
    common::Bonus buyCostBonus)
    :
    bonSellValue_   { sellValueBonus },
    bonBuyCost_     { buyCostBonus }
{}

void EffectSkillBarter::apply(Character& character) noexcept
{
    character.bonusSellValueAdd(bonSellValue_);
    character.bonusBuyCostAdd(bonBuyCost_);
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
    return common::operatorPlus(left, right);
}

EffectSkillBarter operator-(const EffectSkillBarter& left, const EffectSkillBarter& right)
{
    return common::operatorMinus(left, right);
}

///------------------------------------------------------------------------------------------------

EffectSkillLeadership::EffectSkillLeadership(
    common::Chance baseHitChanceOfNearbyAllies,
    common::Bonus normalDamageBonusOnBossKill,
    common::Chance baseCriticalDamageChanceOnMultiKill,
    common::Bonus conHealedBonusOnRevive)
    :
    chaHitNearbyAllies_     { baseHitChanceOfNearbyAllies },
    bonNormDmgBossKill_     { normalDamageBonusOnBossKill },
    chaCritDmgMultiKill_    { baseCriticalDamageChanceOnMultiKill },
    bonCONHealedRevive_     { conHealedBonusOnRevive }
{}

void EffectSkillLeadership::apply(Character& character) noexcept
{
    character.chanceHitOfNearbyAlliesAdd(chaHitNearbyAllies_);
    character.bonusNormalDamageOnBossKillAdd(bonNormDmgBossKill_);
    character.chanceCritDamageOnMultiKillAdd(chaCritDmgMultiKill_);
    character.bonusCONHealedOnReviveAdd(bonCONHealedRevive_);
}

EffectSkillLeadership& EffectSkillLeadership::operator+=(const EffectSkillLeadership& other)
{
    this->chaHitNearbyAllies_   += other.chaHitNearbyAllies_;
    this->bonNormDmgBossKill_   += other.bonNormDmgBossKill_;
    this->chaCritDmgMultiKill_  += other.chaCritDmgMultiKill_;
    this->bonCONHealedRevive_   += other.bonCONHealedRevive_;
    return *this;
}

EffectSkillLeadership& EffectSkillLeadership::operator-=(const EffectSkillLeadership& other)
{
    this->chaHitNearbyAllies_   -= other.chaHitNearbyAllies_;
    this->bonNormDmgBossKill_   -= other.bonNormDmgBossKill_;
    this->chaCritDmgMultiKill_  -= other.chaCritDmgMultiKill_;
    this->bonCONHealedRevive_   -= other.bonCONHealedRevive_;
    return *this;
}

EffectSkillLeadership operator+(const EffectSkillLeadership& left, const EffectSkillLeadership& right)
{
    return common::operatorPlus(left, right);
}

EffectSkillLeadership operator-(const EffectSkillLeadership& left, const EffectSkillLeadership& right)
{
    return common::operatorMinus(left, right);
}

} // namespace object
} // namespace game
