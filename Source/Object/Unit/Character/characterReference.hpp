
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

namespace Game {
namespace Object {

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
        weaponTypes_        { Weapon::Type::ANY,
                              Weapon::Type::ANY },
        //consumTypes_        { Consumable::Type::ANY,
        //                      Consumable::Type::ANY,
        //                      Consumable::Type::ANY,
        //                      Consumable::Type::ANY,
        //                      Consumable::Type::ANY },
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
    void name(Common::Text name) noexcept                               { name_ = name; }
    void timeDetection(Common::Time time) noexcept                      { timeDetect_ = time; }
    void experience(Common::Experience xp) noexcept                     { xp_ = xp; }
    void experienceReward(Common::Experience xp) noexcept               { xpReward_ = xp; }
    void rangeLeadership(Common::Range range) noexcept                  { rangeLeader_ = range; }
    void constitutionMaximum(Common::Constitution con) noexcept         { conMax_ = con; }
    void constitutionCurrent(Common::Constitution con) noexcept         { conCur_ = con; }
    void constitutionPerLevel(Common::Constitution con) noexcept        { conPerLvl_ = con; }
    void multiplierCritDamage(Common::Multiplier mul) noexcept          { mulCritDmg_ = mul; }
    void multiplierCombatSpeed(Common::Multiplier mul) noexcept         { mulSpeed_ = mul; }
    void multiplierThrowingRange(Common::Multiplier mul) noexcept       { mulThrow_ = mul; }
    void chanceHit(Common::Chance chance) noexcept                      { chaHit_ = chance; }
    void chanceHitAssaultRifle(Common::Chance chance) noexcept          { chaHitAR_ = chance; }
    void chanceHitSubMachineGun(Common::Chance chance) noexcept         { chaHitSMG_ = chance; }
    void chanceHitHeavyMachineGun(Common::Chance chance) noexcept       { chaHitHMG_ = chance; }
    void chanceHitFlameThrower(Common::Chance chance) noexcept          { chaHitFT_ = chance; }
    void chanceHitBrawlingWeapon(Common::Chance chance) noexcept        { chaHitBrawl_ = chance; }
    void chanceHitBluntWeapon(Common::Chance chance) noexcept           { chaHitBlunt_ = chance; }
    void chanceHitBladedWeapon(Common::Chance chance) noexcept          { chaHitBladed_ = chance; }
    void chanceHitSemiAutoPistol(Common::Chance chance) noexcept        { chaHitSAPistol_ = chance; }
    void chanceHitRevolver(Common::Chance chance) noexcept              { chaHitRevolver_ = chance; }
    void chanceHitPumpShotgun(Common::Chance chance) noexcept           { chaHitPumpSG_ = chance; }
    void chanceHitAutoShotgun(Common::Chance chance) noexcept           { chaHitAutoSG_ = chance; }
    void chanceHitSniperRifle(Common::Chance chance) noexcept           { chaHitSR_ = chance; }
    void chanceHitOfNearbyAllies(Common::Chance chance) noexcept        { chaHitNearbyAllies_ = chance; }
    void chanceCritDamageOnMultiKill(Common::Chance chance) noexcept    { chaCritDmgMultiKill_ = chance; }
    void chanceCritDamage(Common::Chance chance) noexcept               { chaCritDmg_ = chance; }
    void chanceCritHealing(Common::Chance chance) noexcept              { chaCritHeal_ = chance; }
    void chanceLuckyAction(Common::Chance chance) noexcept              { chaLuckAction_ = chance; }
    void chanceLuckyCritDamage(Common::Chance chance) noexcept          { chaLuckCritDmg_ = chance; }
    void chanceLuckyMegaCritDamage(Common::Chance chance) noexcept      { chaLuckMegaCritDmg_ = chance; }
    void chanceLuckyEvade(Common::Chance chance) noexcept               { chaLuckEvade_ = chance; }
    void chanceLuckyCritResist(Common::Chance chance) noexcept          { chaLuckCritRes_ = chance; }
    void chanceLuckyDoubleHealing(Common::Chance chance) noexcept       { chaLuckDblHeal_ = chance; }
    void chanceLuckyDoubleMoney(Common::Chance chance) noexcept         { chaLuckDblMoney_ = chance; }
    void chanceLuckyDoubleScrap(Common::Chance chance) noexcept         { chaLuckDblScrap_ = chance; }
    void bonusHealing(Common::Bonus bonus) noexcept                     { bonHeal_ = bonus; }
    void bonusCritHealing(Common::Bonus bonus) noexcept                 { bonCritHeal_ = bonus; }
    void bonusHealingWhenRevivingAllies(Common::Bonus bonus) noexcept   { bonHealRevive_ = bonus; }
    void bonusRepair(Common::Bonus bonus) noexcept                      { bonRepair_ = bonus; }
    void bonusExperience(Common::Bonus bonus) noexcept                  { bonXP_ = bonus; }
    void bonusMissionReward(Common::Bonus bonus) noexcept               { bonMissionRew_ = bonus; }
    void bonusFieldStrippingScrap(Common::Bonus bonus) noexcept         { bonScrap_ = bonus; }
    void bonusSellValue(Common::Bonus bonus) noexcept                   { bonSellValue_ = bonus; }
    void bonusBuyCost(Common::Bonus bonus) noexcept                     { bonBuyCost_ = bonus; }
    void bonusSneakAttackDamage(Common::Bonus bonus) noexcept           { bonSneakDmg_ = bonus; }
    void bonusNormalDamage(Common::Bonus bonus) noexcept                { bonNormDmg_ = bonus; }
    void bonusMeleeDamage(Common::Bonus bonus) noexcept                 { bonMeleeDmg_ = bonus; }
    void bonusRangedDamage(Common::Bonus bonus) noexcept                { bonRangeDmg_ = bonus; }
    void bonusFireDamage(Common::Bonus bonus) noexcept                  { bonFireDmg_ = bonus; }
    void bonusColdDamage(Common::Bonus bonus) noexcept                  { bonColdDmg_ = bonus; }
    void bonusEnergyDamage(Common::Bonus bonus) noexcept                { bonEnerDmg_ = bonus; }
    void bonusExplosiveDamage(Common::Bonus bonus) noexcept             { bonExplDmg_ = bonus; }
    void bonusAnimalCompanionDamage(Common::Bonus bonus) noexcept       { bonAnimalDmg_ = bonus; }
    void bonusDamageVsRobots(Common::Bonus bonus) noexcept              { bonDmgVsRobot_ = bonus; }
    void bonusDamageVsVehicles(Common::Bonus bonus) noexcept            { bonDmgVsVehic_ = bonus; }
    void bonusDamageVsSynths(Common::Bonus bonus) noexcept              { bonDmgVsSynth_ = bonus; }
    void bonusDamageVsAnimals(Common::Bonus bonus) noexcept             { bonDmgVsAnimal_ = bonus; }
    void bonusDamageVsMutants(Common::Bonus bonus) noexcept             { bonDmgVsMutant_ = bonus; }
    void bonusNormalDamageOnBossKill(Common::Bonus bonus) noexcept      { bonNormDmgBossKill_ = bonus; }
    void bonusCONHealedOnRevive(Common::Bonus bonus) noexcept           { bonCONHealedRevive_ = bonus; }
    void resistanceStatusEffect(Common::Resistance res) noexcept        { resStatEff_ = res; }
    void resistanceCritDamage(Common::Resistance res) noexcept          { resCritDmg_ = res; }
    void resistanceFireDamage(Common::Resistance res) noexcept          { resFireDmg_ = res; }
    void resistanceColdDamage(Common::Resistance res) noexcept          { resColdDmg_ = res; }
    void resistanceEnergyDamage(Common::Resistance res) noexcept        { resEnerDmg_ = res; }
    void resistanceExplosiveDamage(Common::Resistance res) noexcept     { resExplDmg_ = res; }
    void evasion(Common::Evasion ev) noexcept                           { evasion_ = ev; }
    void initiative(Common::Initiative init) noexcept                   { initiat_ = init; }
    void strikeRate(Common::Strike strike) noexcept                     { strike_ = strike; }
    void level(Common::Level lvl) noexcept                              { level_ = lvl; }
    void armor(Common::Armor ar) noexcept                               { armor_ = ar; }
    void armorPenetration(Common::Armor ar) noexcept                    { armorPen_ = ar; }
    void actionPointMaximum(Common::ActionPoint ap) noexcept            { apMax_ = ap; }
    void actionPointCurrent(Common::ActionPoint ap) noexcept            { apCur_ = ap; }
    void downedTime(Common::NumberMoves num) noexcept                   { movDowned_ = num; }
    void perception(Common::Perception perc) noexcept                   { percept_ = perc; }
    void radiationResistance(Common::Radiation rad) noexcept            { radRes_ = rad; }

    Character__Model            model_;         // character model
    Character__Type             type_;          // character type
    //Slot_ArmorTypes             armorTypes_;    // list of slot types
    Slot_WeaponTypes            weaponTypes_;   // list of slot types
    //Slot_ConsumableTypes        consumTypes_;   // list of slot types

    Common::Text                name_;          // name

    Common::Time                timeDetect_;    // detection time
    Common::Experience          xp_;            // experience
    Common::Experience          xpReward_;      // experience reward for killing
            
    Common::Range               rangeLeader_;   // leadership range
    Common::Constitution        conMax_;        // constitution max value
    Common::Constitution        conCur_;        // constitution current value
    Common::Constitution        conPerLvl_;     // constitution per level
    Common::Multiplier          mulCritDmg_;    // critical damage multiplier
    Common::Multiplier          mulSpeed_;      // combat speed multiplier
    Common::Multiplier          mulThrow_;      // throwing range multiplier
    Common::Chance              chaHit_;        // base hit chance
    Common::Chance              chaHitAR_;      // assault rifle hit chance
    Common::Chance              chaHitSMG_;     // submachine gun hit chance
    Common::Chance              chaHitHMG_;     // heavy machine gun hit chance
    Common::Chance              chaHitFT_;      // flamethrower hit chance
    Common::Chance              chaHitBrawl_;   // brawling weapon hit chance
    Common::Chance              chaHitBlunt_;   // blunt weapon hit chance
    Common::Chance              chaHitBladed_;  // bladed weapon hit chance
    Common::Chance              chaHitSAPistol_;    // semi-auto pistol hit chance
    Common::Chance              chaHitRevolver_;    // revolver hit chance
    Common::Chance              chaHitPumpSG_;      // pump shotgun hit chance
    Common::Chance              chaHitAutoSG_;      // auto shotgun hit chance
    Common::Chance              chaHitSR_;      // sniper rifle hit chance
    Common::Chance              chaHitNearbyAllies_;  // base hit chance of nearby allies
    Common::Chance              chaCritDmgMultiKill_; // base critical damage chance on multi-kill
    Common::Chance              chaCritDmg_;    // base critical damage chance
    Common::Chance              chaCritHeal_;   // base critical healing chance
    Common::Chance              chaLuckAction_;     // lucky action chance
    Common::Chance              chaLuckCritDmg_;    // lucky critical damage chance
    Common::Chance              chaLuckMegaCritDmg_;// lucky mega critical damage chance
    Common::Chance              chaLuckEvade_;      // lucky evade chance
    Common::Chance              chaLuckCritRes_;    // lucky critical resist chance
    Common::Chance              chaLuckDblHeal_;    // lucky double healing chance
    Common::Chance              chaLuckDblMoney_;   // lucky double money chance
    Common::Chance              chaLuckDblScrap_;   // lucky double scrap chance
    Common::Bonus               bonHeal_;       // healing bonus
    Common::Bonus               bonCritHeal_;   // critical healing bonus
    Common::Bonus               bonHealRevive_; // healing when reviving allies bonus
    Common::Bonus               bonRepair_;     // repair bonus
    Common::Bonus               bonXP_;         // experience bonus
    Common::Bonus               bonMissionRew_; // mission reward bonus
    Common::Bonus               bonScrap_;      // field stripping scrap bonus
    Common::Bonus               bonSellValue_;  // sell value bonus
    Common::Bonus               bonBuyCost_;    // buy cost bonus
    Common::Bonus               bonSneakDmg_;   // sneak attack damage bonus
    Common::Bonus               bonNormDmg_;    // normal damage bonus
    Common::Bonus               bonMeleeDmg_;   // melee damage bonus
    Common::Bonus               bonRangeDmg_;   // ranged damage bonus
    Common::Bonus               bonFireDmg_;    // fire damage bonus
    Common::Bonus               bonColdDmg_;    // cold damage bonus
    Common::Bonus               bonEnerDmg_;    // energy damage bonus
    Common::Bonus               bonExplDmg_;    // explosive damage bonus
    Common::Bonus               bonAnimalDmg_;  // animal companion damage bonus
    Common::Bonus               bonDmgVsRobot_; // damage bonus vs robots
    Common::Bonus               bonDmgVsVehic_; // damage bonus vs vehicles
    Common::Bonus               bonDmgVsSynth_; // damage bonus vs synths
    Common::Bonus               bonDmgVsAnimal_;    // damage bonus vs animals
    Common::Bonus               bonDmgVsMutant_;    // damage bonus vs mutants
    Common::Bonus               bonNormDmgBossKill_;  // normal damage bonus on boss kill
    Common::Bonus               bonCONHealedRevive_;  // CON healed bonus on revive
    Common::Resistance          resStatEff_;    // status effect resistance
    Common::Resistance          resCritDmg_;    // critical damage resistance
    Common::Resistance          resFireDmg_;    // fire damage resistance
    Common::Resistance          resColdDmg_;    // cold damage resistance
    Common::Resistance          resEnerDmg_;    // energy damage resistance
    Common::Resistance          resExplDmg_;    // explosive damage resistance
    Common::Evasion             evasion_;       // evasion
    Common::Initiative          initiat_;       // initiative
    Common::Strike              strike_;        // strike rate
            
    Common::Level               level_;         // character level
    Common::Armor               armor_;         // armor
    Common::Armor               armorPen_;      // penetration
    Common::ActionPoint         apMax_;         // action points (maximum)
    Common::ActionPoint         apCur_;         // action points (current)
    Common::NumberMoves         movDowned_;     // downed time
    Common::Perception          percept_;       // perception
    Common::Radiation           radRes_;        // radiation resistance
};
        
} // namespace Object
} // namespace Game

#endif // !CHARACTER_REFERENCE_HPP
