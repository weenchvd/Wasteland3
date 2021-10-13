
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
            Common::Chance chanceLuckyAction() const noexcept {
                return chaLuckAction_;
            }

            void chanceLuckyActionAdd(Common::Chance shift) noexcept {
                chaLuckAction_ += shift;
            }

            Common::Chance chanceLuckyCritDamage() const noexcept {
                return chaLuckCritDmg_;
            }

            void chanceLuckyCritDamageAdd(Common::Chance shift) noexcept {
                chaLuckCritDmg_ += shift;
            }

            Common::Chance chanceLuckyMegaCritDamage() const noexcept {
                return chaLuckMegaCritDmg_;
            }

            void chanceLuckyMegaCritDamageAdd(Common::Chance shift) noexcept {
                chaLuckMegaCritDmg_ += shift;
            }

            Common::Chance chanceLuckyEvade() const noexcept {
                return chaLuckEvade_;
            }

            void chanceLuckyEvadeAdd(Common::Chance shift) noexcept {
                chaLuckEvade_ += shift;
            }

            Common::Chance chanceLuckyCritResist() const noexcept {
                return chaLuckCritRes_;
            }

            void chanceLuckyCritResistAdd(Common::Chance shift) noexcept {
                chaLuckCritRes_ += shift;
            }

            Common::Chance chanceLuckyDoubleHealing() const noexcept {
                return chaLuckDblHeal_;
            }

            void chanceLuckyDoubleHealingAdd(Common::Chance shift) noexcept {
                chaLuckDblHeal_ += shift;
            }

            Common::Chance chanceLuckyDoubleMoney() const noexcept {
                return chaLuckDblMoney_;
            }

            void chanceLuckyDoubleMoneyAdd(Common::Chance shift) noexcept {
                chaLuckDblMoney_ += shift;
            }

            Common::Chance chanceLuckyDoubleScrap() const noexcept {
                return chaLuckDblScrap_;
            }

            void chanceLuckyDoubleScrapAdd(Common::Chance shift) noexcept {
                chaLuckDblScrap_ += shift;
            }

            Common::Resistance resistanceStatusEffect() const noexcept {
                return resStatEff_;
            }

            void resistanceStatusEffectAdd(Common::Resistance shift) noexcept {
                resStatEff_ += shift;
            }

            Common::Level level() const noexcept {
                return level_;
            }

            void levelAdd(Common::Level shift) noexcept {
                level_ += shift;
            }

            Common::Armor armorPenetration() const noexcept {
                return armorPen_;
            }

            void armorPenetrationAdd(Common::Armor shift) noexcept {
                armorPen_ += shift;
            }

            Common::ActionPoint actionPointMaximum() const noexcept {
                return apMax_;
            }

            void actionPointMaximumAdd(Common::ActionPoint shift) noexcept {
                apMax_ += shift;
            }

            Common::ActionPoint actionPointCurrent() const noexcept {
                return apCur_;
            }

            void actionPointCurrentAdd(Common::ActionPoint shift) noexcept {
                apCur_ += shift;
            }

        /// slots
        public:
            const Common::Slot<Weapon, nWSlots>& slotWeapon() const noexcept {
                return slotWeapon_;
            }

            Common::Slot<Weapon, nWSlots>& slotWeapon() noexcept {
                return slotWeapon_;
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

            //Common::Slot<Armor, nASlots>            slotArmor_;
            Common::Slot<Weapon, nWSlots>           slotWeapon_;
            //Common::Slot<Consumable, nQSlots>       slotConsum_;

            std::unique_ptr<Attribute>              attrib_;

            static std::vector<CharacterReference>  ref_;       // references
        };

        ///------------------------------------------------------------------------------------------------

    }
}

#endif // !CHARACTER_HPP
