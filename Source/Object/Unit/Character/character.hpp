
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include"attribute.hpp"
#include"characterCommon.hpp"
#include"characterReference.hpp"
#include"common.hpp"
#include"skill.hpp"
#include"slot.hpp"
#include"unit.hpp"
#include"weapon.hpp"
#include<memory>

namespace game {

namespace global {

class Factory;

} // namespace global

namespace object {

class Character : public Unit {
public:
    using Model = Character__Model;
    using Type  = Character__Type;

private:
    friend global::Factory;

    static constexpr auto nWSlots_{ CharacterReference::nWSlots_ }; // number of weapon slots

protected:
    explicit Character(Character::Model model);

    explicit Character(const CharacterReference& ref);

public:
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    virtual ~Character() noexcept {}

    static void initialize();

    static bool isInitialized();

    virtual void accept(UnitVisitor& visitor) noexcept override {
        visitor.visitCharacter(*this);
    }

    void apply() noexcept;

private:
    void initCtor();

    void check() noexcept;

/// character parameters
public:
    virtual Unit::Type unitType() const noexcept override {
        return Unit::Type::CHARACTER;
    }

    virtual Unit::Model unitModel() const noexcept override {
        return static_cast<Unit::Model>(base_.model_);
    }

    Character::Model model() const noexcept {
        return base_.model_;
    }

    Character::Type type() const noexcept {
        return base_.type_;
    }

    common::Text name() const noexcept;
    void name(common::Text name) noexcept { enteredName_ = name; }

    common::Time timeDetection() const noexcept { return timeDetect_; }
    void timeDetectionAdd(common::Time shift) noexcept { timeDetect_ += shift; }

    common::Experience experience() const noexcept { return xp_; }
    void experienceAdd(common::Experience shift) noexcept { xp_ += shift; }

    common::Experience experienceReward() const noexcept { return xpReward_; }
    void experienceRewardAdd(common::Experience shift) noexcept { xpReward_ += shift; }

    common::Range rangeLeadership() const noexcept { return rangeLeader_; }
    void rangeLeadershipAdd(common::Range shift) noexcept { rangeLeader_ += shift; }

    common::Constitution constitutionMaximum() const noexcept { return conMax_; }
    void constitutionMaximumAdd(common::Constitution shift) noexcept { conMax_ += shift; }

    common::Constitution constitutionCurrent() const noexcept { return conCur_; }
    void constitutionCurrentAdd(common::Constitution shift) noexcept { conCur_ += shift; }

    common::Constitution constitutionPerLevel() const noexcept { return conPerLvl_; }
    void constitutionPerLevelAdd(common::Constitution shift) noexcept { conPerLvl_ += shift; }

    common::Multiplier multiplierCritDamage() const noexcept { return mulCritDmg_; }
    void multiplierCritDamageAdd(common::Multiplier shift) noexcept { mulCritDmg_ += shift; }

    common::Multiplier multiplierCombatSpeed() const noexcept { return mulSpeed_; }
    void multiplierCombatSpeedAdd(common::Multiplier shift) noexcept { mulSpeed_ += shift; }

    common::Multiplier multiplierThrowingRange() const noexcept { return mulThrow_; }
    void multiplierThrowingRangeAdd(common::Multiplier shift) noexcept { mulThrow_ += shift; }

    common::Chance chanceHit() const noexcept { return chaHit_; }
    void chanceHitAdd(common::Chance shift) noexcept { chaHit_ += shift; }

    common::Chance chanceHitAR() const noexcept { return chaHitAR_; }
    void chanceHitARAdd(common::Chance shift) noexcept { chaHitAR_ += shift; }

    common::Chance chanceHitSMG() const noexcept { return chaHitSMG_; }
    void chanceHitSMGAdd(common::Chance shift) noexcept { chaHitSMG_ += shift; }

    common::Chance chanceHitHMG() const noexcept { return chaHitHMG_; }
    void chanceHitHMGAdd(common::Chance shift) noexcept { chaHitHMG_ += shift; }

    common::Chance chanceHitFlamethrower() const noexcept { return chaHitFT_; }
    void chanceHitFlamethrowerAdd(common::Chance shift) noexcept { chaHitFT_ += shift; }

    common::Chance chanceHitBrawling() const noexcept { return chaHitBrawl_; }
    void chanceHitBrawlingAdd(common::Chance shift) noexcept { chaHitBrawl_ += shift; }

    common::Chance chanceHitBlunt() const noexcept { return chaHitBlunt_; }
    void chanceHitBluntAdd(common::Chance shift) noexcept { chaHitBlunt_ += shift; }

    common::Chance chanceHitBladed() const noexcept { return chaHitBladed_; }
    void chanceHitBladedAdd(common::Chance shift) noexcept { chaHitBladed_ += shift; }

    common::Chance chanceHitSemiAutoPistol() const noexcept { return chaHitSAPistol_; }
    void chanceHitSemiAutoPistolAdd(common::Chance shift) noexcept { chaHitSAPistol_ += shift; }

    common::Chance chanceHitRevolver() const noexcept { return chaHitRevolver_; }
    void chanceHitRevolverAdd(common::Chance shift) noexcept { chaHitRevolver_ += shift; }

    common::Chance chanceHitPumpSG() const noexcept { return chaHitPumpSG_; }
    void chanceHitPumpSGAdd(common::Chance shift) noexcept { chaHitPumpSG_ += shift; }

    common::Chance chanceHitAutoSG() const noexcept { return chaHitAutoSG_; }
    void chanceHitAutoSGAdd(common::Chance shift) noexcept { chaHitAutoSG_ += shift; }

    common::Chance chanceHitSR() const noexcept { return chaHitSR_; }
    void chanceHitSRAdd(common::Chance shift) noexcept { chaHitSR_ += shift; }

    common::Chance chanceHitOfNearbyAllies() const noexcept { return chaHitNearbyAllies_; }
    void chanceHitOfNearbyAlliesAdd(common::Chance shift) noexcept { chaHitNearbyAllies_ += shift; }

    common::Chance chanceCritDamageOnMultiKill() const noexcept { return chaCritDmgMultiKill_; }
    void chanceCritDamageOnMultiKillAdd(common::Chance shift) noexcept { chaCritDmgMultiKill_ += shift; }

    common::Chance chanceCritDamage() const noexcept { return chaCritDmg_; }
    void chanceCritDamageAdd(common::Chance shift) noexcept { chaCritDmg_ += shift; }

    common::Chance chanceCritHealing() const noexcept { return chaCritHeal_; }
    void chanceCritHealingAdd(common::Chance shift) noexcept { chaCritHeal_ += shift; }

    common::Chance chanceLuckyAction() const noexcept { return chaLuckAction_; }
    void chanceLuckyActionAdd(common::Chance shift) noexcept { chaLuckAction_ += shift; }

    common::Chance chanceLuckyCritDamage() const noexcept { return chaLuckCritDmg_; }
    void chanceLuckyCritDamageAdd(common::Chance shift) noexcept { chaLuckCritDmg_ += shift; }

    common::Chance chanceLuckyMegaCritDamage() const noexcept { return chaLuckMegaCritDmg_; }
    void chanceLuckyMegaCritDamageAdd(common::Chance shift) noexcept { chaLuckMegaCritDmg_ += shift; }

    common::Chance chanceLuckyEvade() const noexcept { return chaLuckEvade_; }
    void chanceLuckyEvadeAdd(common::Chance shift) noexcept { chaLuckEvade_ += shift; }

    common::Chance chanceLuckyCritResist() const noexcept { return chaLuckCritRes_; }
    void chanceLuckyCritResistAdd(common::Chance shift) noexcept { chaLuckCritRes_ += shift; }

    common::Chance chanceLuckyDoubleHealing() const noexcept { return chaLuckDblHeal_; }
    void chanceLuckyDoubleHealingAdd(common::Chance shift) noexcept { chaLuckDblHeal_ += shift; }

    common::Chance chanceLuckyDoubleMoney() const noexcept { return chaLuckDblMoney_; }
    void chanceLuckyDoubleMoneyAdd(common::Chance shift) noexcept { chaLuckDblMoney_ += shift; }

    common::Chance chanceLuckyDoubleScrap() const noexcept { return chaLuckDblScrap_; }
    void chanceLuckyDoubleScrapAdd(common::Chance shift) noexcept { chaLuckDblScrap_ += shift; }

    common::Bonus bonusHealing() const noexcept { return bonHeal_; }
    void bonusHealingAdd(common::Bonus shift) noexcept { bonHeal_ += shift; }

    common::Bonus bonusCritHealing() const noexcept { return bonCritHeal_; }
    void bonusCritHealingAdd(common::Bonus shift) noexcept { bonCritHeal_ += shift; }

    common::Bonus bonusHealingWhenRevivingAllies() const noexcept { return bonHealRevive_; }
    void bonusHealingWhenRevivingAlliesAdd(common::Bonus shift) noexcept { bonHealRevive_ += shift; }

    common::Bonus bonusRepair() const noexcept { return bonRepair_; }
    void bonusRepairAdd(common::Bonus shift) noexcept { bonRepair_ += shift; }

    common::Bonus bonusExperience() const noexcept { return bonXP_; }
    void bonusExperienceAdd(common::Bonus shift) noexcept { bonXP_ += shift; }

    common::Bonus bonusMissionReward() const noexcept { return bonMissionRew_; }
    void bonusMissionRewardAdd(common::Bonus shift) noexcept { bonMissionRew_ += shift; }

    common::Bonus bonusFieldStrippingScrap() const noexcept { return bonScrap_; }
    void bonusFieldStrippingScrapAdd(common::Bonus shift) noexcept { bonScrap_ += shift; }

    common::Bonus bonusSellValue() const noexcept { return bonSellValue_; }
    void bonusSellValueAdd(common::Bonus shift) noexcept { bonSellValue_ += shift; }

    common::Bonus bonusBuyCost() const noexcept { return bonBuyCost_; }
    void bonusBuyCostAdd(common::Bonus shift) noexcept { bonBuyCost_ += shift; }

    common::Bonus bonusSneakAttackDamage() const noexcept { return bonSneakDmg_; }
    void bonusSneakAttackDamageAdd(common::Bonus shift) noexcept { bonSneakDmg_ += shift; }

    common::Bonus bonusNormalDamage() const noexcept { return bonNormDmg_; }
    void bonusNormalDamageAdd(common::Bonus shift) noexcept { bonNormDmg_ += shift; }

    common::Bonus bonusMeleeDamage() const noexcept { return bonMeleeDmg_; }
    void bonusMeleeDamageAdd(common::Bonus shift) noexcept { bonMeleeDmg_ += shift; }

    common::Bonus bonusRangedDamage() const noexcept { return bonRangeDmg_; }
    void bonusRangedDamageAdd(common::Bonus shift) noexcept { bonRangeDmg_ += shift; }

    common::Bonus bonusFireDamage() const noexcept { return bonFireDmg_; }
    void bonusFireDamageAdd(common::Bonus shift) noexcept { bonFireDmg_ += shift; }

    common::Bonus bonusColdDamage() const noexcept { return bonColdDmg_; }
    void bonusColdDamageAdd(common::Bonus shift) noexcept { bonColdDmg_ += shift; }

    common::Bonus bonusEnergyDamage() const noexcept { return bonEnerDmg_; }
    void bonusEnergyDamageAdd(common::Bonus shift) noexcept { bonEnerDmg_ += shift; }

    common::Bonus bonusExplosiveDamage() const noexcept { return bonExplDmg_; }
    void bonusExplosiveDamageAdd(common::Bonus shift) noexcept { bonExplDmg_ += shift; }

    common::Bonus bonusAnimalCompanionDamage() const noexcept { return bonAnimalDmg_; }
    void bonusAnimalCompanionDamageAdd(common::Bonus shift) noexcept { bonAnimalDmg_ += shift; }

    common::Bonus bonusDamageVsRobots() const noexcept { return bonDmgVsRobot_; }
    void bonusDamageVsRobotsAdd(common::Bonus shift) noexcept { bonDmgVsRobot_ += shift; }

    common::Bonus bonusDamageVsVehicles() const noexcept { return bonDmgVsVehic_; }
    void bonusDamageVsVehiclesAdd(common::Bonus shift) noexcept { bonDmgVsVehic_ += shift; }

    common::Bonus bonusDamageVsSynths() const noexcept { return bonDmgVsSynth_; }
    void bonusDamageVsSynthsAdd(common::Bonus shift) noexcept { bonDmgVsSynth_ += shift; }

    common::Bonus bonusDamageVsAnimals() const noexcept { return bonDmgVsAnimal_; }
    void bonusDamageVsAnimalsAdd(common::Bonus shift) noexcept { bonDmgVsAnimal_ += shift; }

    common::Bonus bonusDamageVsMutants() const noexcept { return bonDmgVsMutant_; }
    void bonusDamageVsMutantsAdd(common::Bonus shift) noexcept { bonDmgVsMutant_ += shift; }

    common::Bonus bonusNormalDamageOnBossKill() const noexcept { return bonNormDmgBossKill_; }
    void bonusNormalDamageOnBossKillAdd(common::Bonus shift) noexcept { bonNormDmgBossKill_ += shift; }

    common::Bonus bonusCONHealedOnRevive() const noexcept { return bonCONHealedRevive_; }
    void bonusCONHealedOnReviveAdd(common::Bonus shift) noexcept { bonCONHealedRevive_ += shift; }

    common::Resistance resistanceStatusEffect() const noexcept { return resStatEff_; }
    void resistanceStatusEffectAdd(common::Resistance shift) noexcept { resStatEff_ += shift; }

    common::Resistance resistanceCritDamage() const noexcept { return resCritDmg_; }
    void resistanceCritDamageAdd(common::Resistance shift) noexcept { resCritDmg_ += shift; }

    common::Resistance resistanceFireDamage() const noexcept { return resFireDmg_; }
    void resistanceFireDamageAdd(common::Resistance shift) noexcept { resFireDmg_ += shift; }

    common::Resistance resistanceColdDamage() const noexcept { return resColdDmg_; }
    void resistanceColdDamageAdd(common::Resistance shift) noexcept { resColdDmg_ += shift; }

    common::Resistance resistanceEnergyDamage() const noexcept { return resEnerDmg_; }
    void resistanceEnergyDamageAdd(common::Resistance shift) noexcept { resEnerDmg_ += shift; }

    common::Resistance resistanceExplosiveDamage() const noexcept { return resExplDmg_; }
    void resistanceExplosiveDamageAdd(common::Resistance shift) noexcept { resExplDmg_ += shift; }

    common::Evasion evasion() const noexcept { return evasion_; }
    void evasionAdd(common::Evasion shift) noexcept { evasion_ += shift; }

    common::Initiative initiative() const noexcept { return initiat_; }
    void initiativeAdd(common::Initiative shift) noexcept { initiat_ += shift; }

    common::Strike strikeRate() const noexcept { return strike_; }
    void strikeRateAdd(common::Strike shift) noexcept { strike_ += shift; }

    common::Level level() const noexcept { return level_; }
    void levelAdd(common::Level shift) noexcept { level_ += shift; }

    common::Armor armor() const noexcept { return armor_; }
    void armorAdd(common::Armor shift) noexcept { armor_ += shift; }

    common::Armor armorPenetration() const noexcept { return armorPen_; }
    void armorPenetrationAdd(common::Armor shift) noexcept { armorPen_ += shift; }

    common::ActionPoint actionPointMaximum() const noexcept { return apMax_; }
    void actionPointMaximumAdd(common::ActionPoint shift) noexcept { apMax_ += shift; }

    common::ActionPoint actionPointCurrent() const noexcept { return apCur_; }
    void actionPointCurrentAdd(common::ActionPoint shift) noexcept { apCur_ += shift; }

    common::NumberMoves downedTime() const noexcept { return movDowned_; }
    void downedTimeAdd(common::NumberMoves shift) noexcept { movDowned_ += shift; }

    common::Perception perception() const noexcept { return percept_; }
    void perceptionAdd(common::Perception shift) noexcept { percept_ += shift; }

    common::Radiation radiationResistance() const noexcept { return radRes_; }
    void radiationResistanceAdd(common::Radiation shift) noexcept { radRes_ += shift; }

public:
/// slots
    const common::Slot<Weapon, nWSlots_>& slotWeapon() const noexcept { return slotWeapon_; }
    common::Slot<Weapon, nWSlots_>& slotWeapon() noexcept { return slotWeapon_; }

/// attributes
    const Attribute& attribute() const noexcept { return *attrib_; }
    Attribute& attribute() noexcept { return *attrib_; }

/// skills
    const Skill& skill() const noexcept { return *skill_; }
    Skill& skill() noexcept { return *skill_; }

private:
    const CharacterReference&   base_;          // reference, sample, template

    common::Text                enteredName_;   // name entered by the player
            
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
    common::Chance              chaHitSAPistol_;// semi-auto pistol hit chance
    common::Chance              chaHitRevolver_;// revolver hit chance
    common::Chance              chaHitPumpSG_;  // pump shotgun hit chance
    common::Chance              chaHitAutoSG_;  // auto shotgun hit chance
    common::Chance              chaHitSR_;      // sniper rifle hit chance
    common::Chance              chaHitNearbyAllies_;    // base hit chance of nearby allies
    common::Chance              chaCritDmgMultiKill_;   // base critical damage chance on multi-kill
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
    common::Bonus               bonDmgVsAnimal_;// damage bonus vs animals
    common::Bonus               bonDmgVsMutant_;// damage bonus vs mutants
    common::Bonus               bonNormDmgBossKill_;    // normal damage bonus on boss kill
    common::Bonus               bonCONHealedRevive_;    // CON healed bonus on revive
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

    //common::Slot<Armor, nASlots>                slotArmor_;
    common::Slot<Weapon, nWSlots_>              slotWeapon_;
    //common::Slot<Consumable, nQSlots>           slotConsum_;

    std::unique_ptr<Attribute>                  attrib_;
    std::unique_ptr<Skill>                      skill_;

    static const CharacterReferenceContainer    ref_;       // references
};

} // namespace object
} // namespace game

#endif // !CHARACTER_HPP
