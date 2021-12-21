
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include"common.hpp"
#include"slot.hpp"
#include"weapon.hpp"
#include"unit.hpp"
#include"attribute.hpp"
#include"skill.hpp"
#include"characterCommon.hpp"
#include"characterReference.hpp"
#include<memory>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        namespace Global {
            class Factory;
        }

        class Character : public Unit {
        public:
            using Model     = CharacterModel;
            using Type      = CharacterType;

            friend Game::Global::Factory;

        protected:
            explicit Character(Character::Model model);

        public:
            Character(const Character&) = delete;
            Character& operator=(const Character&) = delete;

            virtual ~Character() noexcept {}

            static void initializeReference() {
                if (ref_.size() == 0) initRef();
            }

            virtual void accept(UnitVisitor& visitor) noexcept override {
                visitor.visitCharacter(*this);
            }

            void apply() noexcept;

        private:
            void check() noexcept;

        /// character parameters
        public:
            virtual Unit::Type unitType() const noexcept override {
                return Unit::Type::Character;
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

            Common::Text name() const noexcept { return name_; }
            void name(Common::Text name) noexcept { name_ = name; }

            Common::Time timeDetection() const noexcept { return timeDetect_; }
            void timeDetectionAdd(Common::Time shift) noexcept { timeDetect_ += shift; }

            Common::Experience experience() const noexcept { return xp_; }
            void experienceAdd(Common::Experience shift) noexcept { xp_ += shift; }

            Common::Experience experienceReward() const noexcept { return xpReward_; }
            void experienceRewardAdd(Common::Experience shift) noexcept { xpReward_ += shift; }

            Common::Range rangeLeadership() const noexcept { return rangeLeader_; }
            void rangeLeadershipAdd(Common::Range shift) noexcept { rangeLeader_ += shift; }

            Common::Constitution constitutionMaximum() const noexcept { return conMax_; }
            void constitutionMaximumAdd(Common::Constitution shift) noexcept { conMax_ += shift; }

            Common::Constitution constitutionCurrent() const noexcept { return conCur_; }
            void constitutionCurrentAdd(Common::Constitution shift) noexcept { conCur_ += shift; }

            Common::Constitution constitutionPerLevel() const noexcept { return conPerLvl_; }
            void constitutionPerLevelAdd(Common::Constitution shift) noexcept { conPerLvl_ += shift; }

            Common::Multiplier multiplierCritDamage() const noexcept { return mulCritDmg_; }
            void multiplierCritDamageAdd(Common::Multiplier shift) noexcept { mulCritDmg_ += shift; }

            Common::Multiplier multiplierCombatSpeed() const noexcept { return mulSpeed_; }
            void multiplierCombatSpeedAdd(Common::Multiplier shift) noexcept { mulSpeed_ += shift; }

            Common::Multiplier multiplierThrowingRange() const noexcept { return mulThrow_; }
            void multiplierThrowingRangeAdd(Common::Multiplier shift) noexcept { mulThrow_ += shift; }

            Common::Chance chanceHit() const noexcept { return chaHit_; }
            void chanceHitAdd(Common::Chance shift) noexcept { chaHit_ += shift; }

            Common::Chance chanceHitAR() const noexcept { return chaHitAR_; }
            void chanceHitARAdd(Common::Chance shift) noexcept { chaHitAR_ += shift; }

            Common::Chance chanceHitSMG() const noexcept { return chaHitSMG_; }
            void chanceHitSMGAdd(Common::Chance shift) noexcept { chaHitSMG_ += shift; }

            Common::Chance chanceHitHMG() const noexcept { return chaHitHMG_; }
            void chanceHitHMGAdd(Common::Chance shift) noexcept { chaHitHMG_ += shift; }

            Common::Chance chanceHitFlamethrower() const noexcept { return chaHitFT_; }
            void chanceHitFlamethrowerAdd(Common::Chance shift) noexcept { chaHitFT_ += shift; }

            Common::Chance chanceHitBrawling() const noexcept { return chaHitBrawl_; }
            void chanceHitBrawlingAdd(Common::Chance shift) noexcept { chaHitBrawl_ += shift; }

            Common::Chance chanceHitBlunt() const noexcept { return chaHitBlunt_; }
            void chanceHitBluntAdd(Common::Chance shift) noexcept { chaHitBlunt_ += shift; }

            Common::Chance chanceHitBladed() const noexcept { return chaHitBladed_; }
            void chanceHitBladedAdd(Common::Chance shift) noexcept { chaHitBladed_ += shift; }

            Common::Chance chanceHitSemiAutoPistol() const noexcept { return chaHitSAPistol_; }
            void chanceHitSemiAutoPistolAdd(Common::Chance shift) noexcept { chaHitSAPistol_ += shift; }

            Common::Chance chanceHitRevolver() const noexcept { return chaHitRevolver_; }
            void chanceHitRevolverAdd(Common::Chance shift) noexcept { chaHitRevolver_ += shift; }

            Common::Chance chanceHitPumpSG() const noexcept { return chaHitPumpSG_; }
            void chanceHitPumpSGAdd(Common::Chance shift) noexcept { chaHitPumpSG_ += shift; }

            Common::Chance chanceHitAutoSG() const noexcept { return chaHitAutoSG_; }
            void chanceHitAutoSGAdd(Common::Chance shift) noexcept { chaHitAutoSG_ += shift; }

            Common::Chance chanceHitSR() const noexcept { return chaHitSR_; }
            void chanceHitSRAdd(Common::Chance shift) noexcept { chaHitSR_ += shift; }

            Common::Chance chanceHitOfNearbyAllies() const noexcept { return chaHitNearbyAllies_; }
            void chanceHitOfNearbyAlliesAdd(Common::Chance shift) noexcept { chaHitNearbyAllies_ += shift; }

            Common::Chance chanceCritDamageOnMultiKill() const noexcept { return chaCritDmgMultiKill_; }
            void chanceCritDamageOnMultiKillAdd(Common::Chance shift) noexcept { chaCritDmgMultiKill_ += shift; }

            Common::Chance chanceCritDamage() const noexcept { return chaCritDmg_; }
            void chanceCritDamageAdd(Common::Chance shift) noexcept { chaCritDmg_ += shift; }

            Common::Chance chanceCritHealing() const noexcept { return chaCritHeal_; }
            void chanceCritHealingAdd(Common::Chance shift) noexcept { chaCritHeal_ += shift; }

            Common::Chance chanceLuckyAction() const noexcept { return chaLuckAction_; }
            void chanceLuckyActionAdd(Common::Chance shift) noexcept { chaLuckAction_ += shift; }

            Common::Chance chanceLuckyCritDamage() const noexcept { return chaLuckCritDmg_; }
            void chanceLuckyCritDamageAdd(Common::Chance shift) noexcept { chaLuckCritDmg_ += shift; }

            Common::Chance chanceLuckyMegaCritDamage() const noexcept { return chaLuckMegaCritDmg_; }
            void chanceLuckyMegaCritDamageAdd(Common::Chance shift) noexcept { chaLuckMegaCritDmg_ += shift; }

            Common::Chance chanceLuckyEvade() const noexcept { return chaLuckEvade_; }
            void chanceLuckyEvadeAdd(Common::Chance shift) noexcept { chaLuckEvade_ += shift; }

            Common::Chance chanceLuckyCritResist() const noexcept { return chaLuckCritRes_; }
            void chanceLuckyCritResistAdd(Common::Chance shift) noexcept { chaLuckCritRes_ += shift; }

            Common::Chance chanceLuckyDoubleHealing() const noexcept { return chaLuckDblHeal_; }
            void chanceLuckyDoubleHealingAdd(Common::Chance shift) noexcept { chaLuckDblHeal_ += shift; }

            Common::Chance chanceLuckyDoubleMoney() const noexcept { return chaLuckDblMoney_; }
            void chanceLuckyDoubleMoneyAdd(Common::Chance shift) noexcept { chaLuckDblMoney_ += shift; }

            Common::Chance chanceLuckyDoubleScrap() const noexcept { return chaLuckDblScrap_; }
            void chanceLuckyDoubleScrapAdd(Common::Chance shift) noexcept { chaLuckDblScrap_ += shift; }

            Common::Bonus bonusHealing() const noexcept { return bonHeal_; }
            void bonusHealingAdd(Common::Bonus shift) noexcept { bonHeal_ += shift; }

            Common::Bonus bonusCritHealing() const noexcept { return bonCritHeal_; }
            void bonusCritHealingAdd(Common::Bonus shift) noexcept { bonCritHeal_ += shift; }

            Common::Bonus bonusHealingWhenRevivingAllies() const noexcept { return bonHealRevive_; }
            void bonusHealingWhenRevivingAlliesAdd(Common::Bonus shift) noexcept { bonHealRevive_ += shift; }

            Common::Bonus bonusRepair() const noexcept { return bonRepair_; }
            void bonusRepairAdd(Common::Bonus shift) noexcept { bonRepair_ += shift; }

            Common::Bonus bonusExperience() const noexcept { return bonXP_; }
            void bonusExperienceAdd(Common::Bonus shift) noexcept { bonXP_ += shift; }

            Common::Bonus bonusMissionReward() const noexcept { return bonMissionRew_; }
            void bonusMissionRewardAdd(Common::Bonus shift) noexcept { bonMissionRew_ += shift; }

            Common::Bonus bonusFieldStrippingScrap() const noexcept { return bonScrap_; }
            void bonusFieldStrippingScrapAdd(Common::Bonus shift) noexcept { bonScrap_ += shift; }

            Common::Bonus bonusSellValue() const noexcept { return bonSellValue_; }
            void bonusSellValueAdd(Common::Bonus shift) noexcept { bonSellValue_ += shift; }

            Common::Bonus bonusBuyCost() const noexcept { return bonBuyCost_; }
            void bonusBuyCostAdd(Common::Bonus shift) noexcept { bonBuyCost_ += shift; }

            Common::Bonus bonusSneakAttackDamage() const noexcept { return bonSneakDmg_; }
            void bonusSneakAttackDamageAdd(Common::Bonus shift) noexcept { bonSneakDmg_ += shift; }

            Common::Bonus bonusNormalDamage() const noexcept { return bonNormDmg_; }
            void bonusNormalDamageAdd(Common::Bonus shift) noexcept { bonNormDmg_ += shift; }

            Common::Bonus bonusMeleeDamage() const noexcept { return bonMeleeDmg_; }
            void bonusMeleeDamageAdd(Common::Bonus shift) noexcept { bonMeleeDmg_ += shift; }

            Common::Bonus bonusRangedDamage() const noexcept { return bonRangeDmg_; }
            void bonusRangedDamageAdd(Common::Bonus shift) noexcept { bonRangeDmg_ += shift; }

            Common::Bonus bonusFireDamage() const noexcept { return bonFireDmg_; }
            void bonusFireDamageAdd(Common::Bonus shift) noexcept { bonFireDmg_ += shift; }

            Common::Bonus bonusColdDamage() const noexcept { return bonColdDmg_; }
            void bonusColdDamageAdd(Common::Bonus shift) noexcept { bonColdDmg_ += shift; }

            Common::Bonus bonusEnergyDamage() const noexcept { return bonEnerDmg_; }
            void bonusEnergyDamageAdd(Common::Bonus shift) noexcept { bonEnerDmg_ += shift; }

            Common::Bonus bonusExplosiveDamage() const noexcept { return bonExplDmg_; }
            void bonusExplosiveDamageAdd(Common::Bonus shift) noexcept { bonExplDmg_ += shift; }

            Common::Bonus bonusAnimalCompanionDamage() const noexcept { return bonAnimalDmg_; }
            void bonusAnimalCompanionDamageAdd(Common::Bonus shift) noexcept { bonAnimalDmg_ += shift; }

            Common::Bonus bonusDamageVsRobots() const noexcept { return bonDmgVsRobot_; }
            void bonusDamageVsRobotsAdd(Common::Bonus shift) noexcept { bonDmgVsRobot_ += shift; }

            Common::Bonus bonusDamageVsVehicles() const noexcept { return bonDmgVsVehic_; }
            void bonusDamageVsVehiclesAdd(Common::Bonus shift) noexcept { bonDmgVsVehic_ += shift; }

            Common::Bonus bonusDamageVsSynths() const noexcept { return bonDmgVsSynth_; }
            void bonusDamageVsSynthsAdd(Common::Bonus shift) noexcept { bonDmgVsSynth_ += shift; }

            Common::Bonus bonusDamageVsAnimals() const noexcept { return bonDmgVsAnimal_; }
            void bonusDamageVsAnimalsAdd(Common::Bonus shift) noexcept { bonDmgVsAnimal_ += shift; }

            Common::Bonus bonusDamageVsMutants() const noexcept { return bonDmgVsMutant_; }
            void bonusDamageVsMutantsAdd(Common::Bonus shift) noexcept { bonDmgVsMutant_ += shift; }

            Common::Bonus bonusNormalDamageOnBossKill() const noexcept { return bonNormDmgBossKill_; }
            void bonusNormalDamageOnBossKillAdd(Common::Bonus shift) noexcept { bonNormDmgBossKill_ += shift; }

            Common::Bonus bonusCONHealedOnRevive() const noexcept { return bonCONHealedRevive_; }
            void bonusCONHealedOnReviveAdd(Common::Bonus shift) noexcept { bonCONHealedRevive_ += shift; }

            Common::Resistance resistanceStatusEffect() const noexcept { return resStatEff_; }
            void resistanceStatusEffectAdd(Common::Resistance shift) noexcept { resStatEff_ += shift; }

            Common::Resistance resistanceCritDamage() const noexcept { return resCritDmg_; }
            void resistanceCritDamageAdd(Common::Resistance shift) noexcept { resCritDmg_ += shift; }

            Common::Resistance resistanceFireDamage() const noexcept { return resFireDmg_; }
            void resistanceFireDamageAdd(Common::Resistance shift) noexcept { resFireDmg_ += shift; }

            Common::Resistance resistanceColdDamage() const noexcept { return resColdDmg_; }
            void resistanceColdDamageAdd(Common::Resistance shift) noexcept { resColdDmg_ += shift; }

            Common::Resistance resistanceEnergyDamage() const noexcept { return resEnerDmg_; }
            void resistanceEnergyDamageAdd(Common::Resistance shift) noexcept { resEnerDmg_ += shift; }

            Common::Resistance resistanceExplosiveDamage() const noexcept { return resExplDmg_; }
            void resistanceExplosiveDamageAdd(Common::Resistance shift) noexcept { resExplDmg_ += shift; }

            Common::Evasion evasion() const noexcept { return evasion_; }
            void evasionAdd(Common::Evasion shift) noexcept { evasion_ += shift; }

            Common::Initiative initiative() const noexcept { return initiat_; }
            void initiativeAdd(Common::Initiative shift) noexcept { initiat_ += shift; }

            Common::Strike strikeRate() const noexcept { return strike_; }
            void strikeRateAdd(Common::Strike shift) noexcept { strike_ += shift; }

            Common::Level level() const noexcept { return level_; }
            void levelAdd(Common::Level shift) noexcept { level_ += shift; }

            Common::Armor armor() const noexcept { return armor_; }
            void armorAdd(Common::Armor shift) noexcept { armor_ += shift; }

            Common::Armor armorPenetration() const noexcept { return armorPen_; }
            void armorPenetrationAdd(Common::Armor shift) noexcept { armorPen_ += shift; }

            Common::ActionPoint actionPointMaximum() const noexcept { return apMax_; }
            void actionPointMaximumAdd(Common::ActionPoint shift) noexcept { apMax_ += shift; }

            Common::ActionPoint actionPointCurrent() const noexcept { return apCur_; }
            void actionPointCurrentAdd(Common::ActionPoint shift) noexcept { apCur_ += shift; }

            Common::NumberMoves downedTime() const noexcept { return movDowned_; }
            void downedTimeAdd(Common::NumberMoves shift) noexcept { movDowned_ += shift; }

            Common::Perception perception() const noexcept { return percept_; }
            void perceptionAdd(Common::Perception shift) noexcept { percept_ += shift; }

            Common::Radiation radiationResistance() const noexcept { return radRes_; }
            void radiationResistanceAdd(Common::Radiation shift) noexcept { radRes_ += shift; }

        /// slots
        public:
            const Common::Slot<Weapon, nWSlots>& slotWeapon() const noexcept { return slotWeapon_; }
            Common::Slot<Weapon, nWSlots>& slotWeapon() noexcept { return slotWeapon_; }

        /// attributes
        public:
            const Attribute& attribute() const noexcept { return *attrib_; }
            Attribute& attribute() noexcept { return *attrib_; }

        /// skills
        public:
            const Skill& skill() const noexcept { return *skill_; }
            Skill& skill() noexcept { return *skill_; }

        private:
            static void initRef();

            static void add(CharacterReference common) {
                ref_[static_cast<std::underlying_type_t<Character::Model>>(common.model_)] = std::move(common);
            }

        private:
            const CharacterReference&   base_;          // reference, sample, template

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
            Common::Chance              chaHitSAPistol_;// semi-auto pistol hit chance
            Common::Chance              chaHitRevolver_;// revolver hit chance
            Common::Chance              chaHitPumpSG_;  // pump shotgun hit chance
            Common::Chance              chaHitAutoSG_;  // auto shotgun hit chance
            Common::Chance              chaHitSR_;      // sniper rifle hit chance
            Common::Chance              chaHitNearbyAllies_;    // base hit chance of nearby allies
            Common::Chance              chaCritDmgMultiKill_;   // base critical damage chance on multi-kill
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
            Common::Bonus               bonDmgVsAnimal_;// damage bonus vs animals
            Common::Bonus               bonDmgVsMutant_;// damage bonus vs mutants
            Common::Bonus               bonNormDmgBossKill_;    // normal damage bonus on boss kill
            Common::Bonus               bonCONHealedRevive_;    // CON healed bonus on revive
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

            //Common::Slot<Armor, nASlots>            slotArmor_;
            Common::Slot<Weapon, nWSlots>           slotWeapon_;
            //Common::Slot<Consumable, nQSlots>       slotConsum_;

            std::unique_ptr<Attribute>              attrib_;
            std::unique_ptr<Skill>                  skill_;

            static std::vector<CharacterReference>  ref_;       // references
        };

        ///------------------------------------------------------------------------------------------------

    }
}

#endif // !CHARACTER_HPP
