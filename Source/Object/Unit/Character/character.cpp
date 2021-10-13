
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"

namespace Game
{
    namespace Object
    {
        using namespace std;

        Character::Character(CharacterModel model)
            : Unit              { UnitType::Character, static_cast<UnitModel>(model) },
            base_               { ref_[static_cast<underlying_type_t<CharacterModel>>(model)] },
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
            bonXP_              { base_.bonXP_ },
            bonMissionRew_      { base_.bonMissionRew_ },
            bonSneakDmg_        { base_.bonSneakDmg_ },
            bonNormDmg_         { base_.bonNormDmg_ },
            bonMeleeDmg_        { base_.bonMeleeDmg_ },
            bonRangeDmg_        { base_.bonRangeDmg_ },
            bonFireDmg_         { base_.bonFireDmg_ },
            bonColdDmg_         { base_.bonColdDmg_ },
            bonEnerDmg_         { base_.bonEnerDmg_ },
            bonExplDmg_         { base_.bonExplDmg_ },
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
            attrib_             { make_unique<Attribute>(*this) }
        {
            attrib_->addLevel(Attribute::Type::COORDINATION, initAttributeLevel);
            attrib_->addLevel(Attribute::Type::LUCK, initAttributeLevel);
            attrib_->accept();
        }

        void Character::apply() noexcept
        {

        }

        void Character::check() noexcept
        {

        }

        vector<CharacterReference> Character::ref_ = vector<CharacterReference>();

        void Character::initRef()
        {
            ref_.resize(static_cast<underlying_type_t<CharacterModel>>(CharacterModel::NUMBER_OF_MODELS));

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
            //    ref.bonusExperience();
            //    ref.bonusMissionReward();
            //    ref.bonusSneakAttackDamage();
            //    ref.bonusNormalDamage();
            //    ref.bonusMeleeDamage();
            //    ref.bonusRangedDamage();
            //    ref.bonusFireDamage();
            //    ref.bonusColdDamage();
            //    ref.bonusEnergyDamage();
            //    ref.bonusExplisiveDamage();
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
                refMin.characterModel(CharacterModel::MINIMUM);
                refMin.timeDetection(0);
                refMin.experience(0);
                refMin.experienceReward(0);
                refMin.rangeLeadership(0);
                refMin.constitutionMaximum(1);
                refMin.constitutionCurrent(1);
                refMin.constitutionPerLevel(0);
                refMin.multiplierCritDamage(100);
                refMin.multiplierCombatSpeed(10);
                refMin.multiplierThrowingRange(10);
                refMin.chanceHit(0);
                refMin.chanceCritDamage(0);
                refMin.chanceCritHealing(0);
                refMin.chanceLuckyAction(0);
                refMin.chanceLuckyCritDamage(0);
                refMin.chanceLuckyMegaCritDamage(0);
                refMin.chanceLuckyEvade(0);
                refMin.chanceLuckyCritResist(0);
                refMin.chanceLuckyDoubleHealing(0);
                refMin.chanceLuckyDoubleMoney(0);
                refMin.chanceLuckyDoubleScrap(0);
                refMin.bonusHealing(0);
                refMin.bonusCritHealing(1'000);
                refMin.bonusExperience(0);
                refMin.bonusMissionReward(0);
                refMin.bonusSneakAttackDamage(0);
                refMin.bonusNormalDamage(0);
                refMin.bonusMeleeDamage(0);
                refMin.bonusRangedDamage(0);
                refMin.bonusFireDamage(0);
                refMin.bonusColdDamage(0);
                refMin.bonusEnergyDamage(0);
                refMin.bonusExplisiveDamage(0);
                refMin.resistanceStatusEffect(-1'000);
                refMin.resistanceCritDamage(-1'000);
                refMin.resistanceFireDamage(-1'000);
                refMin.resistanceColdDamage(-1'000);
                refMin.resistanceEnergyDamage(-1'000);
                refMin.resistanceExplosiveDamage(-1'000);
                refMin.evasion(-1'000);
                refMin.initiative(-1'000);
                refMin.strikeRate(0);
                refMin.level(1);
                refMin.armor(0);
                refMin.armorPenetration(0);
                refMin.actionPointMaximum(0);
                refMin.actionPointCurrent(0);
                refMin.downedTime(0);
                refMin.perception(0);
                refMin.radiationResistance(0);

                add(move(refMin));
            }

            /// RANGER
            {
                /// COMMON
                {
                    CharacterReference ref;
                    ref.characterModel(CharacterModel::RANGER_COMMON);
                    ref.characterType(CharacterType::RANGER);

                    add(move(ref));
                }
            }

        }

    }
}