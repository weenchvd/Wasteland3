
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"

namespace game {
namespace object {

using namespace std;

Character::Character(Character::Model model)
    :
    base_               { ref_[static_cast<underlying_type_t<Character::Model>>(model)] },
    name_               { base_.name_ },
    timeDetect_         { base_.timeDetect_ },
    xp_                 { base_.xp_ },
    xpReward_           { base_.xpReward_ },
    rangeLeader_        { base_.rangeLeader_ },
    conMax_             { base_.conMax_ },
    conCur_             { base_.conCur_ },
    conPerLvl_          { base_.conPerLvl_ },
    mulCritDmg_         { base_.mulCritDmg_ },
    mulSpeed_           { base_.mulSpeed_ },
    mulThrow_           { base_.mulThrow_ },
    chaHit_             { base_.chaHit_ },
    chaHitAR_           { base_.chaHitAR_ },
    chaHitSMG_          { base_.chaHitSMG_ },
    chaHitHMG_          { base_.chaHitHMG_ },
    chaHitFT_           { base_.chaHitFT_ },
    chaHitBrawl_        { base_.chaHitBrawl_ },
    chaHitBlunt_        { base_.chaHitBlunt_ },
    chaHitBladed_       { base_.chaHitBladed_ },
    chaHitSAPistol_     { base_.chaHitSAPistol_ },
    chaHitRevolver_     { base_.chaHitRevolver_ },
    chaHitPumpSG_       { base_.chaHitPumpSG_ },
    chaHitAutoSG_       { base_.chaHitAutoSG_ },
    chaHitSR_           { base_.chaHitSR_ },
    chaHitNearbyAllies_ { base_.chaHitNearbyAllies_ },
    chaCritDmgMultiKill_{ base_.chaCritDmgMultiKill_ },
    chaCritDmg_         { base_.chaCritDmg_ },
    chaCritHeal_        { base_.chaCritHeal_ },
    chaLuckAction_      { base_.chaLuckAction_ },
    chaLuckCritDmg_     { base_.chaLuckCritDmg_ },
    chaLuckMegaCritDmg_ { base_.chaLuckMegaCritDmg_ },
    chaLuckEvade_       { base_.chaLuckEvade_ },
    chaLuckCritRes_     { base_.chaLuckCritRes_ },
    chaLuckDblHeal_     { base_.chaLuckDblHeal_ },
    chaLuckDblMoney_    { base_.chaLuckDblMoney_ },
    chaLuckDblScrap_    { base_.chaLuckDblScrap_ },
    bonHeal_            { base_.bonHeal_ },
    bonCritHeal_        { base_.bonCritHeal_ },
    bonHealRevive_      { base_.bonHealRevive_ },
    bonRepair_          { base_.bonRepair_ },
    bonXP_              { base_.bonXP_ },
    bonMissionRew_      { base_.bonMissionRew_ },
    bonScrap_           { base_.bonScrap_ },
    bonSellValue_       { base_.bonSellValue_ },
    bonBuyCost_         { base_.bonBuyCost_ },
    bonSneakDmg_        { base_.bonSneakDmg_ },
    bonNormDmg_         { base_.bonNormDmg_ },
    bonMeleeDmg_        { base_.bonMeleeDmg_ },
    bonRangeDmg_        { base_.bonRangeDmg_ },
    bonFireDmg_         { base_.bonFireDmg_ },
    bonColdDmg_         { base_.bonColdDmg_ },
    bonEnerDmg_         { base_.bonEnerDmg_ },
    bonExplDmg_         { base_.bonExplDmg_ },
    bonAnimalDmg_       { base_.bonAnimalDmg_ },
    bonDmgVsRobot_      { base_.bonDmgVsRobot_ },
    bonDmgVsVehic_      { base_.bonDmgVsVehic_ },
    bonDmgVsSynth_      { base_.bonDmgVsSynth_ },
    bonDmgVsAnimal_     { base_.bonDmgVsAnimal_ },
    bonDmgVsMutant_     { base_.bonDmgVsMutant_ },
    bonNormDmgBossKill_ { base_.bonNormDmgBossKill_ },
    bonCONHealedRevive_ { base_.bonCONHealedRevive_ },
    resStatEff_         { base_.resStatEff_ },
    resCritDmg_         { base_.resCritDmg_ },
    resFireDmg_         { base_.resFireDmg_ },
    resColdDmg_         { base_.resColdDmg_ },
    resEnerDmg_         { base_.resEnerDmg_ },
    resExplDmg_         { base_.resExplDmg_ },
    evasion_            { base_.evasion_ },
    initiat_            { base_.initiat_ },
    strike_             { base_.strike_ },
    level_              { base_.level_ },
    armor_              { base_.armor_ },
    armorPen_           { base_.armorPen_ },
    apMax_              { base_.apMax_ },
    apCur_              { base_.apCur_ },
    movDowned_          { base_.movDowned_ },
    percept_            { base_.percept_ },
    radRes_             { base_.radRes_ },
    //slotArmor_          { base_.armorTypes_ },
    slotWeapon_         { base_.weaponTypes_ },
    //slotConsum_         { base_.consumTypes_ }
    attrib_             { make_unique<Attribute>(*this) },
    skill_              { make_unique<Skill>(*this) }
{
    attrib_->addPoint(Attribute::attributeReference().initialAttributePoints());
    attrib_->addLevelToAll(Attribute::attributeReference().initialAttributeLevel());
    attrib_->accept();
    skill_->addPoint(Skill::skillReference().initialSkillPoints());
    skill_->accept();
}

void Character::apply() noexcept
{

}

void Character::check() noexcept
{

}

vector<CharacterReference> Character::ref_ = vector<CharacterReference>();

void Character::initialize()
{
    Attribute::initialize();
    Skill::initialize();
    initializeReference();
}

bool Character::isInitialized()
{
    return Attribute::isInitialized()
        && Skill::isInitialized()
        ///&& ref_.isInitialized()
        ;
}

void Character::initRef()
{
    ref_.resize(common::numberOf<Character::Model>());

    ///// TEMPLATE
    //{
    //    CharacterReference ref;
    //    ref.characterModel();
    //    ref.characterType();
    //    //ref.slotArmorTypes();
    //    ref.slotWeaponTypes();
    //    //ref.slotConsumableTypes();
    //    ref.name();
    //    ref.timeDetection();
    //    ref.experience();
    //    ref.experienceReward();
    //    ref.rangeLeadership();
    //    ref.constitutionMaximum();
    //    ref.constitutionCurrent();
    //    ref.constitutionPerLevel();
    //    ref.multiplierCritDamage();
    //    ref.multiplierCombatSpeed();
    //    ref.multiplierThrowingRange();
    //    ref.chanceHit();
    //    ref.chanceHitAssaultRifle();
    //    ref.chanceHitSubMachineGun();
    //    ref.chanceHitHeavyMachineGun();
    //    ref.chanceHitFlameThrower();
    //    ref.chanceHitBrawlingWeapon();
    //    ref.chanceHitBluntWeapon();
    //    ref.chanceHitBladedWeapon();
    //    ref.chanceHitSemiAutoPistol();
    //    ref.chanceHitRevolver();
    //    ref.chanceHitPumpShotgun();
    //    ref.chanceHitAutoShotgun();
    //    ref.chanceHitSniperRifle();
    //    ref.chanceHitOfNearbyAllies();
    //    ref.chanceCritDamageOnMultiKill();
    //    ref.chanceCritDamage();
    //    ref.chanceCritHealing();
    //    ref.chanceLuckyAction();
    //    ref.chanceLuckyCritDamage();
    //    ref.chanceLuckyMegaCritDamage();
    //    ref.chanceLuckyEvade();
    //    ref.chanceLuckyCritResist();
    //    ref.chanceLuckyDoubleHealing();
    //    ref.chanceLuckyDoubleMoney();
    //    ref.chanceLuckyDoubleScrap();
    //    ref.bonusHealing();
    //    ref.bonusCritHealing();
    //    ref.bonusHealingWhenRevivingAllies();
    //    ref.bonusRepair();
    //    ref.bonusExperience();
    //    ref.bonusMissionReward();
    //    ref.bonusFieldStrippingScrap();
    //    ref.bonusSellValue();
    //    ref.bonusBuyCost();
    //    ref.bonusSneakAttackDamage();
    //    ref.bonusNormalDamage();
    //    ref.bonusMeleeDamage();
    //    ref.bonusRangedDamage();
    //    ref.bonusFireDamage();
    //    ref.bonusColdDamage();
    //    ref.bonusEnergyDamage();
    //    ref.bonusExplosiveDamage();
    //    ref.bonusAnimalCompanionDamage();
    //    ref.bonusDamageVsRobots();
    //    ref.bonusDamageVsVehicles();
    //    ref.bonusDamageVsSynths();
    //    ref.bonusDamageVsAnimals();
    //    ref.bonusDamageVsMutants();
    //    ref.bonusNormalDamageOnBossKill();
    //    ref.bonusCONHealedOnRevive();
    //    ref.resistanceStatusEffect();
    //    ref.resistanceCritDamage();
    //    ref.resistanceFireDamage();
    //    ref.resistanceColdDamage();
    //    ref.resistanceEnergyDamage();
    //    ref.resistanceExplosiveDamage();
    //    ref.evasion();
    //    ref.initiative();
    //    ref.strikeRate();
    //    ref.level();
    //    ref.armor();
    //    ref.armorPenetration();
    //    ref.actionPointMaximum();
    //    ref.actionPointCurrent();
    //    ref.downedTime();
    //    ref.perception();
    //    ref.radiationResistance();

    //    add(move(ref));
    //}

    /// MINIMUM
    {
        CharacterReference refMin;
        refMin.characterModel(Character::Model::MINIMUM);
        refMin.timeDetection(                   common::Time        { 0 });
        refMin.experience(                      common::Experience  { 0 });
        refMin.experienceReward(                common::Experience  { 0 });
        refMin.rangeLeadership(                 common::Range       { 0 });
        refMin.constitutionMaximum(             common::Constitution{ 1 });
        refMin.constitutionCurrent(             common::Constitution{ 1 });
        refMin.constitutionPerLevel(            common::Constitution{ 0 });
        refMin.multiplierCritDamage(            common::Multiplier  { 100 });
        refMin.multiplierCombatSpeed(           common::Multiplier  { 10 });
        refMin.multiplierThrowingRange(         common::Multiplier  { 10 });
        refMin.chanceHit(                       common::Chance      { 0 });
        refMin.chanceHitAssaultRifle(           common::Chance      { 0 });
        refMin.chanceHitSubMachineGun(          common::Chance      { 0 });
        refMin.chanceHitHeavyMachineGun(        common::Chance      { 0 });
        refMin.chanceHitFlameThrower(           common::Chance      { 0 });
        refMin.chanceHitBrawlingWeapon(         common::Chance      { 0 });
        refMin.chanceHitBluntWeapon(            common::Chance      { 0 });
        refMin.chanceHitBladedWeapon(           common::Chance      { 0 });
        refMin.chanceHitSemiAutoPistol(         common::Chance      { 0 });
        refMin.chanceHitRevolver(               common::Chance      { 0 });
        refMin.chanceHitPumpShotgun(            common::Chance      { 0 });
        refMin.chanceHitAutoShotgun(            common::Chance      { 0 });
        refMin.chanceHitSniperRifle(            common::Chance      { 0 });
        refMin.chanceHitOfNearbyAllies(         common::Chance      { 0 });
        refMin.chanceCritDamageOnMultiKill(     common::Chance      { 0 });
        refMin.chanceCritDamage(                common::Chance      { 0 });
        refMin.chanceCritHealing(               common::Chance      { 0 });
        refMin.chanceLuckyAction(               common::Chance      { 0 });
        refMin.chanceLuckyCritDamage(           common::Chance      { 0 });
        refMin.chanceLuckyMegaCritDamage(       common::Chance      { 0 });
        refMin.chanceLuckyEvade(                common::Chance      { 0 });
        refMin.chanceLuckyCritResist(           common::Chance      { 0 });
        refMin.chanceLuckyDoubleHealing(        common::Chance      { 0 });
        refMin.chanceLuckyDoubleMoney(          common::Chance      { 0 });
        refMin.chanceLuckyDoubleScrap(          common::Chance      { 0 });
        refMin.bonusHealing(                    common::Bonus       { 0 });
        refMin.bonusCritHealing(                common::Bonus       { 1'000 });
        refMin.bonusHealingWhenRevivingAllies(  common::Bonus       { 0 });
        refMin.bonusRepair(                     common::Bonus       { 0 });
        refMin.bonusExperience(                 common::Bonus       { 0 });
        refMin.bonusMissionReward(              common::Bonus       { 0 });
        refMin.bonusFieldStrippingScrap(        common::Bonus       { 0 });
        refMin.bonusSellValue(                  common::Bonus       { 0 });
        refMin.bonusBuyCost(                    common::Bonus       { 0 });
        refMin.bonusSneakAttackDamage(          common::Bonus       { 0 });
        refMin.bonusNormalDamage(               common::Bonus       { 0 });
        refMin.bonusMeleeDamage(                common::Bonus       { 0 });
        refMin.bonusRangedDamage(               common::Bonus       { 0 });
        refMin.bonusFireDamage(                 common::Bonus       { 0 });
        refMin.bonusColdDamage(                 common::Bonus       { 0 });
        refMin.bonusEnergyDamage(               common::Bonus       { 0 });
        refMin.bonusExplosiveDamage(            common::Bonus       { 0 });
        refMin.bonusAnimalCompanionDamage(      common::Bonus       { 0 });
        refMin.bonusDamageVsRobots(             common::Bonus       { 0 });
        refMin.bonusDamageVsVehicles(           common::Bonus       { 0 });
        refMin.bonusDamageVsSynths(             common::Bonus       { 0 });
        refMin.bonusDamageVsAnimals(            common::Bonus       { 0 });
        refMin.bonusDamageVsMutants(            common::Bonus       { 0 });
        refMin.bonusNormalDamageOnBossKill(     common::Bonus       { 0 });
        refMin.bonusCONHealedOnRevive(          common::Bonus       { 0 });
        refMin.resistanceStatusEffect(          common::Resistance  { -1'000 });
        refMin.resistanceCritDamage(            common::Resistance  { -1'000 });
        refMin.resistanceFireDamage(            common::Resistance  { -1'000 });
        refMin.resistanceColdDamage(            common::Resistance  { -1'000 });
        refMin.resistanceEnergyDamage(          common::Resistance  { -1'000 });
        refMin.resistanceExplosiveDamage(       common::Resistance  { -1'000 });
        refMin.evasion(                         common::Evasion     { -1'000 });
        refMin.initiative(                      common::Initiative  { -1'000 });
        refMin.strikeRate(                      common::Strike      { 0 });
        refMin.level(                           common::Level       { 1 });
        refMin.armor(                           common::Armor       { 0 });
        refMin.armorPenetration(                common::Armor       { 0 });
        refMin.actionPointMaximum(              common::ActionPoint { 0 });
        refMin.actionPointCurrent(              common::ActionPoint { 0 });
        refMin.downedTime(                      common::NumberMoves { 0 });
        refMin.perception(                      common::Perception  { 0 });
        refMin.radiationResistance(             common::Radiation   { 0 });

        add(move(refMin));
    }

    /// RANGER
    {
        /// COMMON
        {
            CharacterReference ref;
            ref.characterModel(Character::Model::RANGER_COMMON);
            ref.characterType(Character::Type::RANGER);

            add(move(ref));
        }
    }

}

} // namespace object
} // namespace game
