
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
            attrib_->addPoint(Attribute::attributeReference().initAttrPoints_);
            attrib_->addLevelToAll(Attribute::attributeReference().initAttrLevel_);
            attrib_->accept();
            skill_->addPoint(initSkillPoints);
            skill_->accept();
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
            ref_.resize(static_cast<underlying_type_t<Character::Model>>(Character::Model::NUMBER_OF));

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
                refMin.chanceHitAssaultRifle(0);
                refMin.chanceHitSubMachineGun(0);
                refMin.chanceHitHeavyMachineGun(0);
                refMin.chanceHitFlameThrower(0);
                refMin.chanceHitBrawlingWeapon(0);
                refMin.chanceHitBluntWeapon(0);
                refMin.chanceHitBladedWeapon(0);
                refMin.chanceHitSemiAutoPistol(0);
                refMin.chanceHitRevolver(0);
                refMin.chanceHitPumpShotgun(0);
                refMin.chanceHitAutoShotgun(0);
                refMin.chanceHitSniperRifle(0);
                refMin.chanceHitOfNearbyAllies(0);
                refMin.chanceCritDamageOnMultiKill(0);
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
                refMin.bonusHealingWhenRevivingAllies(0);
                refMin.bonusRepair(0);
                refMin.bonusExperience(0);
                refMin.bonusMissionReward(0);
                refMin.bonusFieldStrippingScrap(0);
                refMin.bonusSellValue(0);
                refMin.bonusBuyCost(0);
                refMin.bonusSneakAttackDamage(0);
                refMin.bonusNormalDamage(0);
                refMin.bonusMeleeDamage(0);
                refMin.bonusRangedDamage(0);
                refMin.bonusFireDamage(0);
                refMin.bonusColdDamage(0);
                refMin.bonusEnergyDamage(0);
                refMin.bonusExplosiveDamage(0);
                refMin.bonusAnimalCompanionDamage(0);
                refMin.bonusDamageVsRobots(0);
                refMin.bonusDamageVsVehicles(0);
                refMin.bonusDamageVsSynths(0);
                refMin.bonusDamageVsAnimals(0);
                refMin.bonusDamageVsMutants(0);
                refMin.bonusNormalDamageOnBossKill(0);
                refMin.bonusCONHealedOnRevive(0);
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
                    ref.characterModel(Character::Model::RANGER_COMMON);
                    ref.characterType(Character::Type::RANGER);

                    add(move(ref));
                }
            }

        }

    }
}
