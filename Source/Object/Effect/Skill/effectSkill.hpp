
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef EFFECT_SKILL_HPP
#define EFFECT_SKILL_HPP

#include"common.hpp"
#include"effect.hpp"
#include<memory>

namespace game {
namespace object {

class EffectSkillAutomatic : public Effect {
public:
    EffectSkillAutomatic()
        :
        chaHitAR_   { 0 },
        chaHitSMG_  { 0 }
    {}

    EffectSkillAutomatic(
        common::Chance arHitChance,
        common::Chance smgHitChance);

    virtual ~EffectSkillAutomatic() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillAutomatic& operator+=(const EffectSkillAutomatic& other);
    EffectSkillAutomatic& operator-=(const EffectSkillAutomatic& other);

private:
    common::Chance              chaHitAR_;      // assault rifle hit chance
    common::Chance              chaHitSMG_;     // submachine gun hit chance
};

EffectSkillAutomatic operator+(const EffectSkillAutomatic& left, const EffectSkillAutomatic& right);
EffectSkillAutomatic operator-(const EffectSkillAutomatic& left, const EffectSkillAutomatic& right);

///------------------------------------------------------------------------------------------------

class EffectSkillBigGuns : public Effect {
public:
    EffectSkillBigGuns()
        :
        chaHitHMG_  { 0 },
        chaHitFT_   { 0 }
    {}

    EffectSkillBigGuns(
        common::Chance hmgHitChance,
        common::Chance flamethrowerHitChance);

    virtual ~EffectSkillBigGuns() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillBigGuns& operator+=(const EffectSkillBigGuns& other);
    EffectSkillBigGuns& operator-=(const EffectSkillBigGuns& other);

private:
    common::Chance              chaHitHMG_;     // heavy machine gun hit chance
    common::Chance              chaHitFT_;      // flamethrower hit chance
};

EffectSkillBigGuns operator+(const EffectSkillBigGuns& left, const EffectSkillBigGuns& right);
EffectSkillBigGuns operator-(const EffectSkillBigGuns& left, const EffectSkillBigGuns& right);

///------------------------------------------------------------------------------------------------

class EffectSkillBrawling : public Effect {
public:
    EffectSkillBrawling()
        :
        mulSpeed_       { 0 },
        chaHitBrawl_    { 0 }
    {}

    EffectSkillBrawling(
        common::Multiplier combatSpeed,
        common::Chance brawlingHitChance);

    virtual ~EffectSkillBrawling() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillBrawling& operator+=(const EffectSkillBrawling& other);
    EffectSkillBrawling& operator-=(const EffectSkillBrawling& other);

private:
    common::Multiplier          mulSpeed_;      // combat speed multiplier
    common::Chance              chaHitBrawl_;   // brawling weapon hit chance
};

EffectSkillBrawling operator+(const EffectSkillBrawling& left, const EffectSkillBrawling& right);
EffectSkillBrawling operator-(const EffectSkillBrawling& left, const EffectSkillBrawling& right);

///------------------------------------------------------------------------------------------------

class EffectSkillMelee : public Effect {
public:
    EffectSkillMelee()
        :
        chaHitBlunt_    { 0 },
        chaHitBladed_   { 0 }
    {}

    EffectSkillMelee(
        common::Chance bluntHitChance,
        common::Chance bladedHitChance);

    virtual ~EffectSkillMelee() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillMelee& operator+=(const EffectSkillMelee& other);
    EffectSkillMelee& operator-=(const EffectSkillMelee& other);

private:
    common::Chance              chaHitBlunt_;   // blunt weapon hit chance
    common::Chance              chaHitBladed_;  // bladed weapon hit chance
};

EffectSkillMelee operator+(const EffectSkillMelee& left, const EffectSkillMelee& right);
EffectSkillMelee operator-(const EffectSkillMelee& left, const EffectSkillMelee& right);

///------------------------------------------------------------------------------------------------

class EffectSkillSmallArms : public Effect {
public:
    EffectSkillSmallArms()
        :
        chaHitSAPistol_ { 0 },
        chaHitRevolver_ { 0 },
        chaHitPumpSG_   { 0 },
        chaHitAutoSG_   { 0 }
    {}

    EffectSkillSmallArms(
        common::Chance semiAutoPistolHitChance,
        common::Chance revolverHitChance,
        common::Chance pumpShotgunHitChance,
        common::Chance autoShotgunHitChance);

    virtual ~EffectSkillSmallArms() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillSmallArms& operator+=(const EffectSkillSmallArms& other);
    EffectSkillSmallArms& operator-=(const EffectSkillSmallArms& other);

private:
    common::Chance              chaHitSAPistol_;    // semi-auto pistol hit chance
    common::Chance              chaHitRevolver_;    // revolver hit chance
    common::Chance              chaHitPumpSG_;      // pump shotgun hit chance
    common::Chance              chaHitAutoSG_;      // auto shotgun hit chance
};

EffectSkillSmallArms operator+(const EffectSkillSmallArms& left, const EffectSkillSmallArms& right);
EffectSkillSmallArms operator-(const EffectSkillSmallArms& left, const EffectSkillSmallArms& right);

///------------------------------------------------------------------------------------------------

class EffectSkillSniper : public Effect {
public:
    EffectSkillSniper()
        :
        chaHitSR_{ 0 }
    {}

    EffectSkillSniper(
        common::Chance sniperRifleHitChance);

    virtual ~EffectSkillSniper() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillSniper& operator+=(const EffectSkillSniper& other);
    EffectSkillSniper& operator-=(const EffectSkillSniper& other);

private:
    common::Chance              chaHitSR_;      // sniper rifle hit chance
};

EffectSkillSniper operator+(const EffectSkillSniper& left, const EffectSkillSniper& right);
EffectSkillSniper operator-(const EffectSkillSniper& left, const EffectSkillSniper& right);

///------------------------------------------------------------------------------------------------

class EffectSkillAnimal : public Effect {
public:
    EffectSkillAnimal()
        :
        bonAnimalDmg_{ 0 }
    {}

    EffectSkillAnimal(
        common::Bonus animalCompanionDamageBonus);

    virtual ~EffectSkillAnimal() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillAnimal& operator+=(const EffectSkillAnimal& other);
    EffectSkillAnimal& operator-=(const EffectSkillAnimal& other);

private:
    common::Bonus               bonAnimalDmg_;  // animal companion damage bonus
};

EffectSkillAnimal operator+(const EffectSkillAnimal& left, const EffectSkillAnimal& right);
EffectSkillAnimal operator-(const EffectSkillAnimal& left, const EffectSkillAnimal& right);

///------------------------------------------------------------------------------------------------

class EffectSkillExplosive : public Effect {
public:
    EffectSkillExplosive()
        :
        resExplDmg_{ 0 },
        bonExplDmg_{ 0 }
    {}

    EffectSkillExplosive(
        common::Resistance explosiveDamageResistance,
        common::Bonus explosiveDamageBonus);

    virtual ~EffectSkillExplosive() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillExplosive& operator+=(const EffectSkillExplosive& other);
    EffectSkillExplosive& operator-=(const EffectSkillExplosive& other);

private:
    common::Resistance          resExplDmg_;    // explosive damage resistance
    common::Bonus               bonExplDmg_;    // explosive damage bonus
};

EffectSkillExplosive operator+(const EffectSkillExplosive& left, const EffectSkillExplosive& right);
EffectSkillExplosive operator-(const EffectSkillExplosive& left, const EffectSkillExplosive& right);

///------------------------------------------------------------------------------------------------

class EffectSkillFirstAid : public Effect {
public:
    EffectSkillFirstAid()
        :
        bonHeal_        { 0 },
        bonHealRevive_  { 0 }
    {}

    EffectSkillFirstAid(
        common::Bonus healingBonus,
        common::Bonus healingWhenRevivingAlliesBonus);

    virtual ~EffectSkillFirstAid() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillFirstAid& operator+=(const EffectSkillFirstAid& other);
    EffectSkillFirstAid& operator-=(const EffectSkillFirstAid& other);

private:
    common::Bonus               bonHeal_;       // healing bonus
    common::Bonus               bonHealRevive_; // healing when reviving allies bonus
};

EffectSkillFirstAid operator+(const EffectSkillFirstAid& left, const EffectSkillFirstAid& right);
EffectSkillFirstAid operator-(const EffectSkillFirstAid& left, const EffectSkillFirstAid& right);

///------------------------------------------------------------------------------------------------

class EffectSkillSneakyShit : public Effect {
public:
    EffectSkillSneakyShit()
        :
        timeDetect_     { 0 },
        initiat_        { 0 },
        bonSneakDmg_    { 0 },
        percept_        { 0 }
    {}

    EffectSkillSneakyShit(
        common::Time detectionTime,
        common::Initiative initiative,
        common::Bonus sneakAttackDamageBonus,
        common::Perception perception);

    virtual ~EffectSkillSneakyShit() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillSneakyShit& operator+=(const EffectSkillSneakyShit& other);
    EffectSkillSneakyShit& operator-=(const EffectSkillSneakyShit& other);

private:
    common::Time                timeDetect_;    // detection time
    common::Initiative          initiat_;       // initiative
    common::Bonus               bonSneakDmg_;   // sneak attack damage bonus
    common::Perception          percept_;       // perception
};

EffectSkillSneakyShit operator+(const EffectSkillSneakyShit& left, const EffectSkillSneakyShit& right);
EffectSkillSneakyShit operator-(const EffectSkillSneakyShit& left, const EffectSkillSneakyShit& right);

///------------------------------------------------------------------------------------------------

class EffectSkillWeirdScience : public Effect {
public:
    EffectSkillWeirdScience()
        :
        bonEnerDmg_{ 0 },
        bonFireDmg_{ 0 },
        bonColdDmg_{ 0 }
    {}

    EffectSkillWeirdScience(
        common::Bonus energyDamageBonus,
        common::Bonus fireDamageBonus,
        common::Bonus coldDamageBonus);

    virtual ~EffectSkillWeirdScience() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillWeirdScience& operator+=(const EffectSkillWeirdScience& other);
    EffectSkillWeirdScience& operator-=(const EffectSkillWeirdScience& other);

private:
    common::Bonus               bonEnerDmg_;    // energy damage bonus
    common::Bonus               bonFireDmg_;    // fire damage bonus
    common::Bonus               bonColdDmg_;    // cold damage bonus
};

EffectSkillWeirdScience operator+(const EffectSkillWeirdScience& left, const EffectSkillWeirdScience& right);
EffectSkillWeirdScience operator-(const EffectSkillWeirdScience& left, const EffectSkillWeirdScience& right);

///------------------------------------------------------------------------------------------------

class EffectSkillMechanics : public Effect {
public:
    EffectSkillMechanics()
        :
        bonDmgVsRobot_  { 0 },
        bonDmgVsVehic_  { 0 },
        bonDmgVsSynth_  { 0 },
        bonRepair_      { 0 }
    {}

    EffectSkillMechanics(
        common::Bonus damageBonusVsRobots,
        common::Bonus damageBonusVsVehicles,
        common::Bonus damageBonusVsSynths,
        common::Bonus repairBonus);

    virtual ~EffectSkillMechanics() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillMechanics& operator+=(const EffectSkillMechanics& other);
    EffectSkillMechanics& operator-=(const EffectSkillMechanics& other);

private:
    common::Bonus               bonDmgVsRobot_; // damage bonus vs robots
    common::Bonus               bonDmgVsVehic_; // damage bonus vs vehicles
    common::Bonus               bonDmgVsSynth_; // damage bonus vs synths
    common::Bonus               bonRepair_;     // repair bonus
};

EffectSkillMechanics operator+(const EffectSkillMechanics& left, const EffectSkillMechanics& right);
EffectSkillMechanics operator-(const EffectSkillMechanics& left, const EffectSkillMechanics& right);

///------------------------------------------------------------------------------------------------

class EffectSkillSurvival : public Effect {
public:
    EffectSkillSurvival()
        :
        bonDmgVsAnimal_{ 0 },
        bonDmgVsMutant_{ 0 }
    {}

    EffectSkillSurvival(
        common::Bonus damageBonusVsAnimals,
        common::Bonus damageBonusVsMutants);

    virtual ~EffectSkillSurvival() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillSurvival& operator+=(const EffectSkillSurvival& other);
    EffectSkillSurvival& operator-=(const EffectSkillSurvival& other);

private:
    common::Bonus               bonDmgVsAnimal_;    // damage bonus vs animals
    common::Bonus               bonDmgVsMutant_;    // damage bonus vs mutants
};

EffectSkillSurvival operator+(const EffectSkillSurvival& left, const EffectSkillSurvival& right);
EffectSkillSurvival operator-(const EffectSkillSurvival& left, const EffectSkillSurvival& right);

///------------------------------------------------------------------------------------------------

class EffectSkillWeaponMod : public Effect {
public:
    EffectSkillWeaponMod()
        :
        bonScrap_{ 0 }
    {}

    EffectSkillWeaponMod(
        common::Bonus fieldStrippingScrapBonus);

    virtual ~EffectSkillWeaponMod() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillWeaponMod& operator+=(const EffectSkillWeaponMod& other);
    EffectSkillWeaponMod& operator-=(const EffectSkillWeaponMod& other);

private:
    common::Bonus               bonScrap_;      // field stripping scrap bonus
};

EffectSkillWeaponMod operator+(const EffectSkillWeaponMod& left, const EffectSkillWeaponMod& right);
EffectSkillWeaponMod operator-(const EffectSkillWeaponMod& left, const EffectSkillWeaponMod& right);

///------------------------------------------------------------------------------------------------

class EffectSkillBarter : public Effect {
public:
    EffectSkillBarter()
        :
        bonSellValue_   { 0 },
        bonBuyCost_     { 0 }
    {}

    EffectSkillBarter(
        common::Bonus sellValueBonus,
        common::Bonus buyCostBonus);

    virtual ~EffectSkillBarter() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillBarter& operator+=(const EffectSkillBarter& other);
    EffectSkillBarter& operator-=(const EffectSkillBarter& other);

private:
    common::Bonus               bonSellValue_;  // sell value bonus
    common::Bonus               bonBuyCost_;    // buy cost bonus
};

EffectSkillBarter operator+(const EffectSkillBarter& left, const EffectSkillBarter& right);
EffectSkillBarter operator-(const EffectSkillBarter& left, const EffectSkillBarter& right);

///------------------------------------------------------------------------------------------------

class EffectSkillLeadership : public Effect {
public:
    EffectSkillLeadership()
        :
        chaHitNearbyAllies_     { 0 },
        bonNormDmgBossKill_     { 0 },
        chaCritDmgMultiKill_    { 0 },
        bonCONHealedRevive_     { 0 }
    {}

    EffectSkillLeadership(
        common::Chance baseHitChanceOfNearbyAllies,
        common::Bonus normalDamageBonusOnBossKill,
        common::Chance baseCriticalDamageChanceOnMultiKill,
        common::Bonus conHealedBonusOnRevive);

    virtual ~EffectSkillLeadership() noexcept {}

    virtual void apply(Character& character) noexcept override;

    EffectSkillLeadership& operator+=(const EffectSkillLeadership& other);
    EffectSkillLeadership& operator-=(const EffectSkillLeadership& other);

private:
    common::Chance              chaHitNearbyAllies_;    // base hit chance of nearby allies
    common::Bonus               bonNormDmgBossKill_;    // normal damage bonus on boss kill
    common::Chance              chaCritDmgMultiKill_;   // base critical damage chance on multi-kill
    common::Bonus               bonCONHealedRevive_;    // CON healed bonus on revive
};

EffectSkillLeadership operator+(const EffectSkillLeadership& left, const EffectSkillLeadership& right);
EffectSkillLeadership operator-(const EffectSkillLeadership& left, const EffectSkillLeadership& right);

} // namespace object
} // namespace game

#endif // !EFFECT_SKILL_HPP
