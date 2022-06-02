
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"

namespace game {
namespace object {

using namespace std;

const CharacterReferenceContainer       Character::ref_;
const CharacterText                     Character::text_;

///************************************************************************************************

Character::Character(Character::Model model)
    :
    base_               { ref_.characterReference(model) },
    enteredName_        { base_.enteredName_ },
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
    initCtor();
}

Character::Character(const CharacterReference& ref)
    :
    base_               { ref },
    enteredName_        { base_.enteredName_ },
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
    initCtor();
}

void Character::apply() noexcept
{

}

void Character::initCtor()
{
    attrib_->addPoint(Attribute::attributeReference().initialAttributePoints());
    attrib_->addLevelToAll(Attribute::attributeReference().initialAttributeLevel());
    attrib_->accept();
    skill_->addPoint(Skill::skillReference().initialSkillPoints());
    skill_->accept();
}

void Character::check() noexcept
{

}

common::Text Character::name() const noexcept
{
    switch (base_.type_) {
    case Character::Type::RANGER:   return enteredName_;
    default:                        return base_.name();
    }
}

} // namespace object
} // namespace game
