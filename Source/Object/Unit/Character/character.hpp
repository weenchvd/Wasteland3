
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
#include<array>
#include<memory>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        constexpr unsigned int nASlots = 4; // number of armor slots
        constexpr unsigned int nWSlots = 2; // number of weapon slots
        constexpr unsigned int nQSlots = 5; // number of quick slots

        //using Slot_ArmorTypes       = std::array<ArmorType, nASlots>;
        using Slot_WeaponTypes      = std::array<WeaponType, nWSlots>;
        //using Slot_ConsumableTypes  = std::array<ConsumableType, nQSlots>;

        struct CharacterReference {
            explicit CharacterReference() noexcept
                :
                model_              { CharacterModel::INVALID },
                type_               { CharacterType::INVALID },
                //armorTypes_         { ArmorType::HEAD,
                //                      ArmorType::CHEST,
                //                      ArmorType::LEG,
                //                      ArmorType::UTILITY },
                weaponTypes_        { WeaponType::ANY,
                                      WeaponType::ANY },
                //consumTypes_        { ConsumableType::ANY,
                //                      ConsumableType::ANY,
                //                      ConsumableType::ANY,
                //                      ConsumableType::ANY,
                //                      ConsumableType::ANY },
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
                bonXP_              { 1'000 },
                bonMissionRew_      { 1'000 },
                bonSneakDmg_        { 1'000 },
                bonNormDmg_         { 1'000 },
                bonMeleeDmg_        { 1'000 },
                bonRangeDmg_        { 1'000 },
                bonFireDmg_         { 1'000 },
                bonColdDmg_         { 1'000 },
                bonEnerDmg_         { 1'000 },
                bonExplDmg_         { 1'000 },
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

            void characterModel(CharacterModel model) noexcept                  { model_ = model; }
            void characterType(CharacterType type) noexcept                     { type_ = type; }
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
            void bonusExperience(Common::Bonus bonus) noexcept                  { bonXP_ = bonus; }
            void bonusMissionReward(Common::Bonus bonus) noexcept               { bonMissionRew_ = bonus; }
            void bonusSneakAttackDamage(Common::Bonus bonus) noexcept           { bonSneakDmg_ = bonus; }
            void bonusNormalDamage(Common::Bonus bonus) noexcept                { bonNormDmg_ = bonus; }
            void bonusMeleeDamage(Common::Bonus bonus) noexcept                 { bonMeleeDmg_ = bonus; }
            void bonusRangedDamage(Common::Bonus bonus) noexcept                { bonRangeDmg_ = bonus; }
            void bonusFireDamage(Common::Bonus bonus) noexcept                  { bonFireDmg_ = bonus; }
            void bonusColdDamage(Common::Bonus bonus) noexcept                  { bonColdDmg_ = bonus; }
            void bonusEnergyDamage(Common::Bonus bonus) noexcept                { bonEnerDmg_ = bonus; }
            void bonusExplisiveDamage(Common::Bonus bonus) noexcept             { bonExplDmg_ = bonus; }
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

            CharacterModel              model_;         // character model
            CharacterType               type_;          // character type
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
            Common::Bonus               bonXP_;         // experience bonus
            Common::Bonus               bonMissionRew_; // mission reward bonus
            Common::Bonus               bonSneakDmg_;   // sneak attack damage bonus
            Common::Bonus               bonNormDmg_;    // normal damage bonus
            Common::Bonus               bonMeleeDmg_;   // melee damage bonus
            Common::Bonus               bonRangeDmg_;   // ranged damage bonus
            Common::Bonus               bonFireDmg_;    // fire damage bonus
            Common::Bonus               bonColdDmg_;    // cold damage bonus
            Common::Bonus               bonEnerDmg_;    // energy damage bonus
            Common::Bonus               bonExplDmg_;    // explosive damage bonus
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
        
        
        class Character : public Unit {
        public:
            using Model     = CharacterModel;
            using Type      = CharacterType;

        protected:
            explicit Character(CharacterModel model); //TODO replace CharacterModel -> Character::Model

        public:
            Character(const Character&) = delete;
            Character& operator=(const Character&) = delete;

            virtual ~Character() noexcept {}

            static std::unique_ptr<Unit> create(CharacterModel model) {
                if (ref_.size() == 0) initRef();
                return std::unique_ptr<Unit>(new Character(std::move(model)));
            }

            virtual void accept(UnitVisitor& visitor) noexcept override {
                visitor.visitCharacter(*this);
            }

            void apply() noexcept;

        private:
            void check() noexcept;

            static void initRef();

            static void add(CharacterReference common) {
                ref_[static_cast<std::underlying_type_t<CharacterModel>>(common.model_)] = std::move(common);
            }

        public:
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

            Common::Bonus bonusExperience() const noexcept { return bonXP_; }
            void bonusExperienceAdd(Common::Bonus shift) noexcept { bonXP_ += shift; }

            Common::Bonus bonusMissionReward() const noexcept { return bonMissionRew_; }
            void bonusMissionRewardAdd(Common::Bonus shift) noexcept { bonMissionRew_ += shift; }

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

            Common::Bonus bonusExplisiveDamage() const noexcept { return bonExplDmg_; }
            void bonusExplisiveDamageAdd(Common::Bonus shift) noexcept { bonExplDmg_ += shift; }

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
            //Common::Chance              chaHitAR_;      // assault rifle hit chance
            //Common::Chance              chaHitSMG_;     // submachine gun hit chance
            //Common::Chance              chaHitHMG_;     // heavy machine gun hit chance
            //Common::Chance              chaHitFT_;      // flamethrower hit chance
            //Common::Chance              chaHitBrawl_;   // brawling weapon hit chance
            //Common::Chance              chaHitBlunt_;   // blunt weapon hit chance
            //Common::Chance              chaHitBladed_;  // bladed weapon hit chance
            //Common::Chance              chaHitSAPistol_;    // semi-auto pistol hit chance
            //Common::Chance              chaHitRevolver_;    // revolver hit chance
            //Common::Chance              chaHitPumpSG_;      // pump shotgun hit chance
            //Common::Chance              chaHitAutoSG_;      // auto shotgun hit chance
            //Common::Chance              chaHitSniper_;  // sniper rifle hit chance
            //Common::Chance              chaHitOfNearbyAllies_;  // base hit chance of nearby allies
            //Common::Chance              chaCritDmgOnMultiKill_; // base critical damage chance on multi-kill
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
            //Common::Bonus               bonRepair_;     // repair bonus
            Common::Bonus               bonXP_;         // experience bonus
            Common::Bonus               bonMissionRew_; // mission reward bonus
            //Common::Bonus               bonScrap_;      // field stripping scrap bonus
            //Common::Bonus               bonSellValue_;  // sell value bonus
            //Common::Bonus               bonBuyCost_;    // buy cost bonus
            Common::Bonus               bonSneakDmg_;   // sneak attack damage bonus
            Common::Bonus               bonNormDmg_;    // normal damage bonus
            Common::Bonus               bonMeleeDmg_;   // melee damage bonus
            Common::Bonus               bonRangeDmg_;   // ranged damage bonus
            Common::Bonus               bonFireDmg_;    // fire damage bonus
            Common::Bonus               bonColdDmg_;    // cold damage bonus
            Common::Bonus               bonEnerDmg_;    // energy damage bonus
            Common::Bonus               bonExplDmg_;    // explosive damage bonus
            //Common::Bonus               bonAnimalDmg_;  // animal companion damage bonus
            //Common::Bonus               bonDmgVsRobot_; // damage bonus vs robots
            //Common::Bonus               bonDmgVsVehic_; // damage bonus vs vehicles
            //Common::Bonus               bonDmgVsSynth_; // damage bonus vs synths
            //Common::Bonus               bonDmgVsAnimal_;    // damage bonus vs animals
            //Common::Bonus               bonDmgVsMutant_;    // damage bonus vs mutants
            //Common::Bonus               bonNormDmgOnBossKill_;  // normal damage bonus on boss kill
            //Common::Bonus               bonCONHealedOnRevive_;  // CON healed bonus on revive
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
