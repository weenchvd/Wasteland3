
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_REFERENCE_HPP
#define CHARACTER_REFERENCE_HPP

#include"common.hpp"
#include"weapon.hpp"
#include"characterCommon.hpp"
#include<array>

namespace game {
namespace object {

constexpr unsigned int nASlots = 4; // number of armor slots
constexpr unsigned int nWSlots = 2; // number of weapon slots
constexpr unsigned int nQSlots = 5; // number of quick slots

//using Slot_ArmorTypes       = std::array<ArmorType, nASlots>;
using Slot_WeaponTypes      = std::array<Weapon::Type, nWSlots>;
//using Slot_ConsumableTypes  = std::array<ConsumableType, nQSlots>;

struct CharacterReference {
    explicit CharacterReference() noexcept
        :
        model_              { Character__Model::INVALID },
        type_               { Character__Type::INVALID },
        //armorTypes_         { Armor::Type::HEAD,
        //                      Armor::Type::CHEST,
        //                      Armor::Type::LEG,
        //                      Armor::Type::UTILITY },
        weaponTypes_        { Weapon::Type::GROUP_ANY,
                              Weapon::Type::GROUP_ANY },
        //consumTypes_        { Consumable::Type::GROUP_ANY,
        //                      Consumable::Type::GROUP_ANY,
        //                      Consumable::Type::GROUP_ANY,
        //                      Consumable::Type::GROUP_ANY,
        //                      Consumable::Type::GROUP_ANY },
        name_               {},
        timeDetect_         { 1'700 },
        xp_                 { 0 },
        xpReward_           { 0 },
        rangeLeader_        { 0 },
        conMax_             { 50 },
        conCur_             { 50 },
        conPerLvl_          { 0 },
        mulCritDmg_         { 100 },
        mulSpeed_           { 140 },
        mulThrow_           { 100 },
        chaHit_             { 0 },
        chaHitAR_           { 0 },
        chaHitSMG_          { 0 },
        chaHitHMG_          { 0 },
        chaHitFT_           { 0 },
        chaHitBrawl_        { 0 },
        chaHitBlunt_        { 0 },
        chaHitBladed_       { 0 },
        chaHitSAPistol_     { 0 },
        chaHitRevolver_     { 0 },
        chaHitPumpSG_       { 0 },
        chaHitAutoSG_       { 0 },
        chaHitSR_           { 0 },
        chaHitNearbyAllies_ { 0 },
        chaCritDmgMultiKill_{ 0 },
        chaCritDmg_         { 0 },
        chaCritHeal_        { 0 },
        chaLuckAction_      { 0 },
        chaLuckCritDmg_     { 0 },
        chaLuckMegaCritDmg_ { 0 },
        chaLuckEvade_       { 0 },
        chaLuckCritRes_     { 0 },
        chaLuckDblHeal_     { 0 },
        chaLuckDblMoney_    { 0 },
        chaLuckDblScrap_    { 0 },
        bonHeal_            { 1'000 },
        bonCritHeal_        { 1'000 },
        bonHealRevive_      { 1'000 },
        bonRepair_          { 1'000 },
        bonXP_              { 1'000 },
        bonMissionRew_      { 1'000 },
        bonScrap_           { 1'000 },
        bonSellValue_       { 1'000 },
        bonBuyCost_         { 1'000 },
        bonSneakDmg_        { 1'000 },
        bonNormDmg_         { 1'000 },
        bonMeleeDmg_        { 1'000 },
        bonRangeDmg_        { 1'000 },
        bonFireDmg_         { 1'000 },
        bonColdDmg_         { 1'000 },
        bonEnerDmg_         { 1'000 },
        bonExplDmg_         { 1'000 },
        bonAnimalDmg_       { 1'000 },
        bonDmgVsRobot_      { 1'000 },
        bonDmgVsVehic_      { 1'000 },
        bonDmgVsSynth_      { 1'000 },
        bonDmgVsAnimal_     { 1'000 },
        bonDmgVsMutant_     { 1'000 },
        bonNormDmgBossKill_ { 1'000 }, // TODO consider
        bonCONHealedRevive_ { 1'000 },
        resStatEff_         { 0 },
        resCritDmg_         { 0 },
        resFireDmg_         { 0 },
        resColdDmg_         { 0 },
        resEnerDmg_         { 0 },
        resExplDmg_         { 0 },
        evasion_            { 0 },
        initiat_            { 0 },
        strike_             { 60 },
        level_              { 1 },
        armor_              { 0 },
        armorPen_           { 0 },
        apMax_              { 6 },
        apCur_              { 6 },
        movDowned_          { 3 },
        percept_            { 0 },
        radRes_             { 0 }
    {}

    CharacterReference(const CharacterReference&) = delete;
    CharacterReference& operator=(const CharacterReference&) = delete;
    CharacterReference(CharacterReference&&) = default;
    CharacterReference& operator=(CharacterReference&&) = default;

    void characterModel(Character__Model model) noexcept                { model_ = model; }
    void characterType(Character__Type type) noexcept                   { type_ = type; }
    //void slotArmorTypes(Slot_ArmorTypes types) noexcept                 { armorTypes_ = types; }
    void slotWeaponTypes(Slot_WeaponTypes types) noexcept               { weaponTypes_ = types; }
    //void slotConsumableTypes(Slot_ConsumableTypes types) noexcept       { consumTypes_ = types; }
    void name(common::Text name) noexcept                               { name_ = name; }
    void timeDetection(common::Time time) noexcept                      { timeDetect_ = time; }
    void experience(common::Experience xp) noexcept                     { xp_ = xp; }
    void experienceReward(common::Experience xp) noexcept               { xpReward_ = xp; }
    void rangeLeadership(common::Range range) noexcept                  { rangeLeader_ = range; }
    void constitutionMaximum(common::Constitution con) noexcept         { conMax_ = con; }
    void constitutionCurrent(common::Constitution con) noexcept         { conCur_ = con; }
    void constitutionPerLevel(common::Constitution con) noexcept        { conPerLvl_ = con; }
    void multiplierCritDamage(common::Multiplier mul) noexcept          { mulCritDmg_ = mul; }
    void multiplierCombatSpeed(common::Multiplier mul) noexcept         { mulSpeed_ = mul; }
    void multiplierThrowingRange(common::Multiplier mul) noexcept       { mulThrow_ = mul; }
    void chanceHit(common::Chance chance) noexcept                      { chaHit_ = chance; }
    void chanceHitAssaultRifle(common::Chance chance) noexcept          { chaHitAR_ = chance; }
    void chanceHitSubMachineGun(common::Chance chance) noexcept         { chaHitSMG_ = chance; }
    void chanceHitHeavyMachineGun(common::Chance chance) noexcept       { chaHitHMG_ = chance; }
    void chanceHitFlameThrower(common::Chance chance) noexcept          { chaHitFT_ = chance; }
    void chanceHitBrawlingWeapon(common::Chance chance) noexcept        { chaHitBrawl_ = chance; }
    void chanceHitBluntWeapon(common::Chance chance) noexcept           { chaHitBlunt_ = chance; }
    void chanceHitBladedWeapon(common::Chance chance) noexcept          { chaHitBladed_ = chance; }
    void chanceHitSemiAutoPistol(common::Chance chance) noexcept        { chaHitSAPistol_ = chance; }
    void chanceHitRevolver(common::Chance chance) noexcept              { chaHitRevolver_ = chance; }
    void chanceHitPumpShotgun(common::Chance chance) noexcept           { chaHitPumpSG_ = chance; }
    void chanceHitAutoShotgun(common::Chance chance) noexcept           { chaHitAutoSG_ = chance; }
    void chanceHitSniperRifle(common::Chance chance) noexcept           { chaHitSR_ = chance; }
    void chanceHitOfNearbyAllies(common::Chance chance) noexcept        { chaHitNearbyAllies_ = chance; }
    void chanceCritDamageOnMultiKill(common::Chance chance) noexcept    { chaCritDmgMultiKill_ = chance; }
    void chanceCritDamage(common::Chance chance) noexcept               { chaCritDmg_ = chance; }
    void chanceCritHealing(common::Chance chance) noexcept              { chaCritHeal_ = chance; }
    void chanceLuckyAction(common::Chance chance) noexcept              { chaLuckAction_ = chance; }
    void chanceLuckyCritDamage(common::Chance chance) noexcept          { chaLuckCritDmg_ = chance; }
    void chanceLuckyMegaCritDamage(common::Chance chance) noexcept      { chaLuckMegaCritDmg_ = chance; }
    void chanceLuckyEvade(common::Chance chance) noexcept               { chaLuckEvade_ = chance; }
    void chanceLuckyCritResist(common::Chance chance) noexcept          { chaLuckCritRes_ = chance; }
    void chanceLuckyDoubleHealing(common::Chance chance) noexcept       { chaLuckDblHeal_ = chance; }
    void chanceLuckyDoubleMoney(common::Chance chance) noexcept         { chaLuckDblMoney_ = chance; }
    void chanceLuckyDoubleScrap(common::Chance chance) noexcept         { chaLuckDblScrap_ = chance; }
    void bonusHealing(common::Bonus bonus) noexcept                     { bonHeal_ = bonus; }
    void bonusCritHealing(common::Bonus bonus) noexcept                 { bonCritHeal_ = bonus; }
    void bonusHealingWhenRevivingAllies(common::Bonus bonus) noexcept   { bonHealRevive_ = bonus; }
    void bonusRepair(common::Bonus bonus) noexcept                      { bonRepair_ = bonus; }
    void bonusExperience(common::Bonus bonus) noexcept                  { bonXP_ = bonus; }
    void bonusMissionReward(common::Bonus bonus) noexcept               { bonMissionRew_ = bonus; }
    void bonusFieldStrippingScrap(common::Bonus bonus) noexcept         { bonScrap_ = bonus; }
    void bonusSellValue(common::Bonus bonus) noexcept                   { bonSellValue_ = bonus; }
    void bonusBuyCost(common::Bonus bonus) noexcept                     { bonBuyCost_ = bonus; }
    void bonusSneakAttackDamage(common::Bonus bonus) noexcept           { bonSneakDmg_ = bonus; }
    void bonusNormalDamage(common::Bonus bonus) noexcept                { bonNormDmg_ = bonus; }
    void bonusMeleeDamage(common::Bonus bonus) noexcept                 { bonMeleeDmg_ = bonus; }
    void bonusRangedDamage(common::Bonus bonus) noexcept                { bonRangeDmg_ = bonus; }
    void bonusFireDamage(common::Bonus bonus) noexcept                  { bonFireDmg_ = bonus; }
    void bonusColdDamage(common::Bonus bonus) noexcept                  { bonColdDmg_ = bonus; }
    void bonusEnergyDamage(common::Bonus bonus) noexcept                { bonEnerDmg_ = bonus; }
    void bonusExplosiveDamage(common::Bonus bonus) noexcept             { bonExplDmg_ = bonus; }
    void bonusAnimalCompanionDamage(common::Bonus bonus) noexcept       { bonAnimalDmg_ = bonus; }
    void bonusDamageVsRobots(common::Bonus bonus) noexcept              { bonDmgVsRobot_ = bonus; }
    void bonusDamageVsVehicles(common::Bonus bonus) noexcept            { bonDmgVsVehic_ = bonus; }
    void bonusDamageVsSynths(common::Bonus bonus) noexcept              { bonDmgVsSynth_ = bonus; }
    void bonusDamageVsAnimals(common::Bonus bonus) noexcept             { bonDmgVsAnimal_ = bonus; }
    void bonusDamageVsMutants(common::Bonus bonus) noexcept             { bonDmgVsMutant_ = bonus; }
    void bonusNormalDamageOnBossKill(common::Bonus bonus) noexcept      { bonNormDmgBossKill_ = bonus; }
    void bonusCONHealedOnRevive(common::Bonus bonus) noexcept           { bonCONHealedRevive_ = bonus; }
    void resistanceStatusEffect(common::Resistance res) noexcept        { resStatEff_ = res; }
    void resistanceCritDamage(common::Resistance res) noexcept          { resCritDmg_ = res; }
    void resistanceFireDamage(common::Resistance res) noexcept          { resFireDmg_ = res; }
    void resistanceColdDamage(common::Resistance res) noexcept          { resColdDmg_ = res; }
    void resistanceEnergyDamage(common::Resistance res) noexcept        { resEnerDmg_ = res; }
    void resistanceExplosiveDamage(common::Resistance res) noexcept     { resExplDmg_ = res; }
    void evasion(common::Evasion ev) noexcept                           { evasion_ = ev; }
    void initiative(common::Initiative init) noexcept                   { initiat_ = init; }
    void strikeRate(common::Strike strike) noexcept                     { strike_ = strike; }
    void level(common::Level lvl) noexcept                              { level_ = lvl; }
    void armor(common::Armor ar) noexcept                               { armor_ = ar; }
    void armorPenetration(common::Armor ar) noexcept                    { armorPen_ = ar; }
    void actionPointMaximum(common::ActionPoint ap) noexcept            { apMax_ = ap; }
    void actionPointCurrent(common::ActionPoint ap) noexcept            { apCur_ = ap; }
    void downedTime(common::NumberMoves num) noexcept                   { movDowned_ = num; }
    void perception(common::Perception perc) noexcept                   { percept_ = perc; }
    void radiationResistance(common::Radiation rad) noexcept            { radRes_ = rad; }

    Character__Model            model_;         // character model
    Character__Type             type_;          // character type
    //Slot_ArmorTypes             armorTypes_;    // list of slot types
    Slot_WeaponTypes            weaponTypes_;   // list of slot types
    //Slot_ConsumableTypes        consumTypes_;   // list of slot types

    common::Text                name_;          // name

    common::Time                timeDetect_;    // detection time
    common::Experience          xp_;            // experience
    common::Experience          xpReward_;      // experience reward for killing
            
    common::Range               rangeLeader_;   // leadership range
    common::Constitution        conMax_;        // constitution max value
    common::Constitution        conCur_;        // constitution current value
    common::Constitution        conPerLvl_;     // constitution per level
    common::Multiplier          mulCritDmg_;    // critical damage multiplier
    common::Multiplier          mulSpeed_;      // combat speed multiplier
    common::Multiplier          mulThrow_;      // throwing range multiplier
    common::Chance              chaHit_;        // base hit chance
    common::Chance              chaHitAR_;      // assault rifle hit chance
    common::Chance              chaHitSMG_;     // submachine gun hit chance
    common::Chance              chaHitHMG_;     // heavy machine gun hit chance
    common::Chance              chaHitFT_;      // flamethrower hit chance
    common::Chance              chaHitBrawl_;   // brawling weapon hit chance
    common::Chance              chaHitBlunt_;   // blunt weapon hit chance
    common::Chance              chaHitBladed_;  // bladed weapon hit chance
    common::Chance              chaHitSAPistol_;    // semi-auto pistol hit chance
    common::Chance              chaHitRevolver_;    // revolver hit chance
    common::Chance              chaHitPumpSG_;      // pump shotgun hit chance
    common::Chance              chaHitAutoSG_;      // auto shotgun hit chance
    common::Chance              chaHitSR_;      // sniper rifle hit chance
    common::Chance              chaHitNearbyAllies_;  // base hit chance of nearby allies
    common::Chance              chaCritDmgMultiKill_; // base critical damage chance on multi-kill
    common::Chance              chaCritDmg_;    // base critical damage chance
    common::Chance              chaCritHeal_;   // base critical healing chance
    common::Chance              chaLuckAction_;     // lucky action chance
    common::Chance              chaLuckCritDmg_;    // lucky critical damage chance
    common::Chance              chaLuckMegaCritDmg_;// lucky mega critical damage chance
    common::Chance              chaLuckEvade_;      // lucky evade chance
    common::Chance              chaLuckCritRes_;    // lucky critical resist chance
    common::Chance              chaLuckDblHeal_;    // lucky double healing chance
    common::Chance              chaLuckDblMoney_;   // lucky double money chance
    common::Chance              chaLuckDblScrap_;   // lucky double scrap chance
    common::Bonus               bonHeal_;       // healing bonus
    common::Bonus               bonCritHeal_;   // critical healing bonus
    common::Bonus               bonHealRevive_; // healing when reviving allies bonus
    common::Bonus               bonRepair_;     // repair bonus
    common::Bonus               bonXP_;         // experience bonus
    common::Bonus               bonMissionRew_; // mission reward bonus
    common::Bonus               bonScrap_;      // field stripping scrap bonus
    common::Bonus               bonSellValue_;  // sell value bonus
    common::Bonus               bonBuyCost_;    // buy cost bonus
    common::Bonus               bonSneakDmg_;   // sneak attack damage bonus
    common::Bonus               bonNormDmg_;    // normal damage bonus
    common::Bonus               bonMeleeDmg_;   // melee damage bonus
    common::Bonus               bonRangeDmg_;   // ranged damage bonus
    common::Bonus               bonFireDmg_;    // fire damage bonus
    common::Bonus               bonColdDmg_;    // cold damage bonus
    common::Bonus               bonEnerDmg_;    // energy damage bonus
    common::Bonus               bonExplDmg_;    // explosive damage bonus
    common::Bonus               bonAnimalDmg_;  // animal companion damage bonus
    common::Bonus               bonDmgVsRobot_; // damage bonus vs robots
    common::Bonus               bonDmgVsVehic_; // damage bonus vs vehicles
    common::Bonus               bonDmgVsSynth_; // damage bonus vs synths
    common::Bonus               bonDmgVsAnimal_;    // damage bonus vs animals
    common::Bonus               bonDmgVsMutant_;    // damage bonus vs mutants
    common::Bonus               bonNormDmgBossKill_;  // normal damage bonus on boss kill
    common::Bonus               bonCONHealedRevive_;  // CON healed bonus on revive
    common::Resistance          resStatEff_;    // status effect resistance
    common::Resistance          resCritDmg_;    // critical damage resistance
    common::Resistance          resFireDmg_;    // fire damage resistance
    common::Resistance          resColdDmg_;    // cold damage resistance
    common::Resistance          resEnerDmg_;    // energy damage resistance
    common::Resistance          resExplDmg_;    // explosive damage resistance
    common::Evasion             evasion_;       // evasion
    common::Initiative          initiat_;       // initiative
    common::Strike              strike_;        // strike rate
            
    common::Level               level_;         // character level
    common::Armor               armor_;         // armor
    common::Armor               armorPen_;      // penetration
    common::ActionPoint         apMax_;         // action points (maximum)
    common::ActionPoint         apCur_;         // action points (current)
    common::NumberMoves         movDowned_;     // downed time
    common::Perception          percept_;       // perception
    common::Radiation           radRes_;        // radiation resistance
};
        
} // namespace object
} // namespace game

#endif // !CHARACTER_REFERENCE_HPP
