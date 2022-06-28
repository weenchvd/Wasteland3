
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"exception.hpp"
#include"locator.hpp"

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
    attrib_->initialize(base_.attrInitializer_);
    skill_->initialize(base_.skillInitializer_);
}

bool Character::hasValidValues() const noexcept
{
    // TODO
    return true;
}

common::Text Character::name() const noexcept
{
    switch (base_.type_) {
    case Character::Type::RANGER:   return enteredName_;
    default:                        return base_.name();
    }
}

bool Character::setWeapon(common::Slot<Weapon, nWSlots_>::slot_number_t slotNumber,
                          unique_ptr<Item>& source)
{
    assert(hasValidValues());
    if (slotWeapon_.set(slotNumber, source, isCompatible)) {
        apply();
        if (hasValidValues()) return true;
        slotWeapon_.unset(slotNumber, source);
        apply();
        assert(hasValidValues());
    }
    return false;
}

bool Character::unsetWeapon(common::Slot<Weapon, nWSlots_>::slot_number_t slotNumber,
                            unique_ptr<Item>& receiver)
{
    if (slotWeapon_.unset(slotNumber, receiver)) {
        apply();
        return true;
    }
    return false;
}

flatbuffers::Offset<fbCharacter::FB_Character> Character::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    using ch_t = fbCharacter::FB_Character;
    using common::checkedEnum;

    auto attrOffset{ attribute().serialize(fbb) };
    auto skillOffset{ skill().serialize(fbb) };

    vector<flatbuffers::Offset<fbWeapon::FB_Weapon>> weaponOffsets;
    for (int i = 0; i < slotWeapon_.size(); ++i) {
        if (slotWeapon_[i] != nullptr) {
            weaponOffsets.push_back(slotWeapon_[i]->serialize(fbb));
        }
    }
    auto weaponVectorOffset{ fbb.CreateVector(weaponOffsets) };
    auto enteredNameOffset{ fbb.CreateString(enteredName_) };

    fbCharacter::FB_CharacterBuilder b{ fbb };
    b.add_attributes(attrOffset);
    b.add_skills(skillOffset);
    b.add_weapons(weaponVectorOffset);
    b.add_model(CharacterModelBiMap::toRightType(model()));
    b.add_entered_name(enteredNameOffset);

    b.add_time_detect(checkedEnum<decltype(&ch_t::time_detect), ch_t>(timeDetect_));
    b.add_xp(checkedEnum<decltype(&ch_t::xp), ch_t>(xp_));
    b.add_xp_reward(checkedEnum<decltype(&ch_t::xp_reward), ch_t>(xpReward_));

    b.add_range_leader(checkedEnum<decltype(&ch_t::range_leader), ch_t>(rangeLeader_));
    b.add_con_max(checkedEnum<decltype(&ch_t::con_max), ch_t>(conMax_));
    b.add_con_cur(checkedEnum<decltype(&ch_t::con_cur), ch_t>(conCur_));
    b.add_con_per_lvl(checkedEnum<decltype(&ch_t::con_per_lvl), ch_t>(conPerLvl_));
    b.add_mul_crit_dmg(checkedEnum<decltype(&ch_t::mul_crit_dmg), ch_t>(mulCritDmg_));
    b.add_mul_speed(checkedEnum<decltype(&ch_t::mul_speed), ch_t>(mulSpeed_));
    b.add_mul_throw(checkedEnum<decltype(&ch_t::mul_throw), ch_t>(mulThrow_));
    b.add_cha_hit(checkedEnum<decltype(&ch_t::cha_hit), ch_t>(chaHit_));
    b.add_cha_hit_ar(checkedEnum<decltype(&ch_t::cha_hit_ar), ch_t>(chaHitAR_));
    b.add_cha_hit_smg(checkedEnum<decltype(&ch_t::cha_hit_smg), ch_t>(chaHitSMG_));
    b.add_cha_hit_hmg(checkedEnum<decltype(&ch_t::cha_hit_hmg), ch_t>(chaHitHMG_));
    b.add_cha_hit_ft(checkedEnum<decltype(&ch_t::cha_hit_ft), ch_t>(chaHitFT_));
    b.add_cha_hit_brawl(checkedEnum<decltype(&ch_t::cha_hit_brawl), ch_t>(chaHitBrawl_));
    b.add_cha_hit_blunt(checkedEnum<decltype(&ch_t::cha_hit_blunt), ch_t>(chaHitBlunt_));
    b.add_cha_hit_bladed(checkedEnum<decltype(&ch_t::cha_hit_bladed), ch_t>(chaHitBladed_));
    b.add_cha_hit_sa_pistol(checkedEnum<decltype(&ch_t::cha_hit_sa_pistol), ch_t>(chaHitSAPistol_));
    b.add_cha_hit_revolver(checkedEnum<decltype(&ch_t::cha_hit_revolver), ch_t>(chaHitRevolver_));
    b.add_cha_hit_pump_sg(checkedEnum<decltype(&ch_t::cha_hit_pump_sg), ch_t>(chaHitPumpSG_));
    b.add_cha_hit_auto_sg(checkedEnum<decltype(&ch_t::cha_hit_auto_sg), ch_t>(chaHitAutoSG_));
    b.add_cha_hit_sr(checkedEnum<decltype(&ch_t::cha_hit_sr), ch_t>(chaHitSR_));
    b.add_cha_hit_nearby_allies(checkedEnum<decltype(&ch_t::cha_hit_nearby_allies), ch_t>(chaHitNearbyAllies_));
    b.add_cha_crit_dmg_multi_kill(checkedEnum<decltype(&ch_t::cha_crit_dmg_multi_kill), ch_t>(chaCritDmgMultiKill_));
    b.add_cha_crit_dmg(checkedEnum<decltype(&ch_t::cha_crit_dmg), ch_t>(chaCritDmg_));
    b.add_cha_crit_heal(checkedEnum<decltype(&ch_t::cha_crit_heal), ch_t>(chaCritHeal_));
    b.add_cha_luck_action(checkedEnum<decltype(&ch_t::cha_luck_action), ch_t>(chaLuckAction_));
    b.add_cha_luck_crit_dmg(checkedEnum<decltype(&ch_t::cha_luck_crit_dmg), ch_t>(chaLuckCritDmg_));
    b.add_cha_luck_mega_crit_dmg(checkedEnum<decltype(&ch_t::cha_luck_mega_crit_dmg), ch_t>(chaLuckMegaCritDmg_));
    b.add_cha_luck_evade(checkedEnum<decltype(&ch_t::cha_luck_evade), ch_t>(chaLuckEvade_));
    b.add_cha_luck_crit_res(checkedEnum<decltype(&ch_t::cha_luck_crit_res), ch_t>(chaLuckCritRes_));
    b.add_cha_luck_dbl_heal(checkedEnum<decltype(&ch_t::cha_luck_dbl_heal), ch_t>(chaLuckDblHeal_));
    b.add_cha_luck_dbl_money(checkedEnum<decltype(&ch_t::cha_luck_dbl_money), ch_t>(chaLuckDblMoney_));
    b.add_cha_luck_dbl_scrap(checkedEnum<decltype(&ch_t::cha_luck_dbl_scrap), ch_t>(chaLuckDblScrap_));
    b.add_bon_heal(checkedEnum<decltype(&ch_t::bon_heal), ch_t>(bonHeal_));
    b.add_bon_crit_heal(checkedEnum<decltype(&ch_t::bon_crit_heal), ch_t>(bonCritHeal_));
    b.add_bon_heal_revive(checkedEnum<decltype(&ch_t::bon_heal_revive), ch_t>(bonHealRevive_));
    b.add_bon_repair(checkedEnum<decltype(&ch_t::bon_repair), ch_t>(bonRepair_));
    b.add_bon_xp(checkedEnum<decltype(&ch_t::bon_xp), ch_t>(bonXP_));
    b.add_bon_mission_rew(checkedEnum<decltype(&ch_t::bon_mission_rew), ch_t>(bonMissionRew_));
    b.add_bon_scrap(checkedEnum<decltype(&ch_t::bon_scrap), ch_t>(bonScrap_));
    b.add_bon_sell_value(checkedEnum<decltype(&ch_t::bon_sell_value), ch_t>(bonSellValue_));
    b.add_bon_buy_cost(checkedEnum<decltype(&ch_t::bon_buy_cost), ch_t>(bonBuyCost_));
    b.add_bon_sneak_dmg(checkedEnum<decltype(&ch_t::bon_sneak_dmg), ch_t>(bonSneakDmg_));
    b.add_bon_norm_dmg(checkedEnum<decltype(&ch_t::bon_norm_dmg), ch_t>(bonNormDmg_));
    b.add_bon_melee_dmg(checkedEnum<decltype(&ch_t::bon_melee_dmg), ch_t>(bonMeleeDmg_));
    b.add_bon_range_dmg(checkedEnum<decltype(&ch_t::bon_range_dmg), ch_t>(bonRangeDmg_));
    b.add_bon_fire_dmg(checkedEnum<decltype(&ch_t::bon_fire_dmg), ch_t>(bonFireDmg_));
    b.add_bon_cold_dmg(checkedEnum<decltype(&ch_t::bon_cold_dmg), ch_t>(bonColdDmg_));
    b.add_bon_ener_dmg(checkedEnum<decltype(&ch_t::bon_ener_dmg), ch_t>(bonEnerDmg_));
    b.add_bon_expl_dmg(checkedEnum<decltype(&ch_t::bon_expl_dmg), ch_t>(bonExplDmg_));
    b.add_bon_animal_dmg(checkedEnum<decltype(&ch_t::bon_animal_dmg), ch_t>(bonAnimalDmg_));
    b.add_bon_dmg_vs_robot(checkedEnum<decltype(&ch_t::bon_dmg_vs_robot), ch_t>(bonDmgVsRobot_));
    b.add_bon_dmg_vs_vehic(checkedEnum<decltype(&ch_t::bon_dmg_vs_vehic), ch_t>(bonDmgVsVehic_));
    b.add_bon_dmg_vs_synth(checkedEnum<decltype(&ch_t::bon_dmg_vs_synth), ch_t>(bonDmgVsSynth_));
    b.add_bon_dmg_vs_animal(checkedEnum<decltype(&ch_t::bon_dmg_vs_animal), ch_t>(bonDmgVsAnimal_));
    b.add_bon_dmg_vs_mutant(checkedEnum<decltype(&ch_t::bon_dmg_vs_mutant), ch_t>(bonDmgVsMutant_));
    b.add_bon_norm_dmg_boss_kill(checkedEnum<decltype(&ch_t::bon_norm_dmg_boss_kill), ch_t>(bonNormDmgBossKill_));
    b.add_bon_con_healed_revive(checkedEnum<decltype(&ch_t::bon_con_healed_revive), ch_t>(bonCONHealedRevive_));
    b.add_res_stat_eff(checkedEnum<decltype(&ch_t::res_stat_eff), ch_t>(resStatEff_));
    b.add_res_crit_dmg(checkedEnum<decltype(&ch_t::res_crit_dmg), ch_t>(resCritDmg_));
    b.add_res_fire_dmg(checkedEnum<decltype(&ch_t::res_fire_dmg), ch_t>(resFireDmg_));
    b.add_res_cold_dmg(checkedEnum<decltype(&ch_t::res_cold_dmg), ch_t>(resColdDmg_));
    b.add_res_ener_dmg(checkedEnum<decltype(&ch_t::res_ener_dmg), ch_t>(resEnerDmg_));
    b.add_res_expl_dmg(checkedEnum<decltype(&ch_t::res_expl_dmg), ch_t>(resExplDmg_));
    b.add_evasion(checkedEnum<decltype(&ch_t::evasion), ch_t>(evasion_));
    b.add_initiat(checkedEnum<decltype(&ch_t::initiat), ch_t>(initiat_));
    b.add_strike(checkedEnum<decltype(&ch_t::strike), ch_t>(strike_));

    b.add_level(checkedEnum<decltype(&ch_t::level), ch_t>(level_));
    b.add_armor(checkedEnum<decltype(&ch_t::armor), ch_t>(armor_));
    b.add_armor_pen(checkedEnum<decltype(&ch_t::armor_pen), ch_t>(armorPen_));
    b.add_ap_max(checkedEnum<decltype(&ch_t::ap_max), ch_t>(apMax_));
    b.add_ap_cur(checkedEnum<decltype(&ch_t::ap_cur), ch_t>(apCur_));
    b.add_mov_downed(checkedEnum<decltype(&ch_t::mov_downed), ch_t>(movDowned_));
    b.add_percept(checkedEnum<decltype(&ch_t::percept), ch_t>(percept_));
    b.add_rad_res(checkedEnum<decltype(&ch_t::rad_res), ch_t>(radRes_));

    return b.Finish();
}

unique_ptr<Unit> Character::deserialize(const fbCharacter::FB_Character* fb)
{
    using common::Text;
    using common::Time;
    using common::Experience;
    using common::Range;
    using common::Constitution;
    using common::Multiplier;
    using common::Chance;
    using common::Bonus;
    using common::Resistance;
    using common::Evasion;
    using common::Initiative;
    using common::Strike;
    using common::Level;
    using common::Armor;
    using common::ActionPoint;
    using common::NumberMoves;
    using common::Perception;
    using common::Radiation;

    assert(fb != nullptr);
    const auto& f{ global::Locator::getFactory() };
    auto characterModel{ CharacterModelBiMap::toLeftType(fb->model()) };
    auto unit{ f.createUnit<Character>(characterModel) };

    auto& c{ static_cast<Character&>(*unit.get()) };
    c.attrib_.reset(Attribute::deserialize(fb->attributes(), c).release());
    c.skill_.reset(Skill::deserialize(fb->skills(), c).release());
    const auto* weapons{ fb->weapons() };
    if (weapons != nullptr) {
        assert(c.slotWeapon_.size() >= weapons->size());
        for (int i = 0; i < weapons->size(); ++i) {
            assert(weapons->Get(i) != nullptr);
            auto weapon{ Weapon::deserialize(weapons->Get(i)) };
            if (!c.setWeapon(i, weapon)) {
                throw common::SerializationError{ u8"[Character::deserialize] The weapon is not set" };
            }
        }
    }
    c.enteredName_          = Text{ fb->entered_name()->c_str() };

    c.timeDetect_           = Time{ fb->time_detect() };
    c.xp_                   = Experience{ fb->xp() };
    c.xpReward_             = Experience{ fb->xp_reward() };

    c.rangeLeader_          = Range{ fb->range_leader() };
    c.conMax_               = Constitution{ fb->con_max() };
    c.conCur_               = Constitution{ fb->con_cur() };
    c.conPerLvl_            = Constitution{ fb->con_per_lvl() };
    c.mulCritDmg_           = Multiplier{ fb->mul_crit_dmg() };
    c.mulSpeed_             = Multiplier{ fb->mul_speed() };
    c.mulThrow_             = Multiplier{ fb->mul_throw() };
    c.chaHit_               = Chance{ fb->cha_hit() };
    c.chaHitAR_             = Chance{ fb->cha_hit_ar() };
    c.chaHitSMG_            = Chance{ fb->cha_hit_smg() };
    c.chaHitHMG_            = Chance{ fb->cha_hit_hmg() };
    c.chaHitFT_             = Chance{ fb->cha_hit_ft() };
    c.chaHitBrawl_          = Chance{ fb->cha_hit_brawl() };
    c.chaHitBlunt_          = Chance{ fb->cha_hit_blunt() };
    c.chaHitBladed_         = Chance{ fb->cha_hit_bladed() };
    c.chaHitSAPistol_       = Chance{ fb->cha_hit_sa_pistol() };
    c.chaHitRevolver_       = Chance{ fb->cha_hit_revolver() };
    c.chaHitPumpSG_         = Chance{ fb->cha_hit_pump_sg() };
    c.chaHitAutoSG_         = Chance{ fb->cha_hit_auto_sg() };
    c.chaHitSR_             = Chance{ fb->cha_hit_sr() };
    c.chaHitNearbyAllies_   = Chance{ fb->cha_hit_nearby_allies() };
    c.chaCritDmgMultiKill_  = Chance{ fb->cha_crit_dmg_multi_kill() };
    c.chaCritDmg_           = Chance{ fb->cha_crit_dmg() };
    c.chaCritHeal_          = Chance{ fb->cha_crit_heal() };
    c.chaLuckAction_        = Chance{ fb->cha_luck_action() };
    c.chaLuckCritDmg_       = Chance{ fb->cha_luck_crit_dmg() };
    c.chaLuckMegaCritDmg_   = Chance{ fb->cha_luck_mega_crit_dmg() };
    c.chaLuckEvade_         = Chance{ fb->cha_luck_evade() };
    c.chaLuckCritRes_       = Chance{ fb->cha_luck_crit_res() };
    c.chaLuckDblHeal_       = Chance{ fb->cha_luck_dbl_heal() };
    c.chaLuckDblMoney_      = Chance{ fb->cha_luck_dbl_money() };
    c.chaLuckDblScrap_      = Chance{ fb->cha_luck_dbl_scrap() };
    c.bonHeal_              = Bonus{ fb->bon_heal() };
    c.bonCritHeal_          = Bonus{ fb->bon_crit_heal() };
    c.bonHealRevive_        = Bonus{ fb->bon_heal_revive() };
    c.bonRepair_            = Bonus{ fb->bon_repair() };
    c.bonXP_                = Bonus{ fb->bon_xp() };
    c.bonMissionRew_        = Bonus{ fb->bon_mission_rew() };
    c.bonScrap_             = Bonus{ fb->bon_scrap() };
    c.bonSellValue_         = Bonus{ fb->bon_sell_value() };
    c.bonBuyCost_           = Bonus{ fb->bon_buy_cost() };
    c.bonSneakDmg_          = Bonus{ fb->bon_sneak_dmg() };
    c.bonNormDmg_           = Bonus{ fb->bon_norm_dmg() };
    c.bonMeleeDmg_          = Bonus{ fb->bon_melee_dmg() };
    c.bonRangeDmg_          = Bonus{ fb->bon_range_dmg() };
    c.bonFireDmg_           = Bonus{ fb->bon_fire_dmg() };
    c.bonColdDmg_           = Bonus{ fb->bon_cold_dmg() };
    c.bonEnerDmg_           = Bonus{ fb->bon_ener_dmg() };
    c.bonExplDmg_           = Bonus{ fb->bon_expl_dmg() };
    c.bonAnimalDmg_         = Bonus{ fb->bon_animal_dmg() };
    c.bonDmgVsRobot_        = Bonus{ fb->bon_dmg_vs_robot() };
    c.bonDmgVsVehic_        = Bonus{ fb->bon_dmg_vs_vehic() };
    c.bonDmgVsSynth_        = Bonus{ fb->bon_dmg_vs_synth() };
    c.bonDmgVsAnimal_       = Bonus{ fb->bon_dmg_vs_animal() };
    c.bonDmgVsMutant_       = Bonus{ fb->bon_dmg_vs_mutant() };
    c.bonNormDmgBossKill_   = Bonus{ fb->bon_norm_dmg_boss_kill() };
    c.bonCONHealedRevive_   = Bonus{ fb->bon_con_healed_revive() };
    c.resStatEff_           = Resistance{ fb->res_stat_eff() };
    c.resCritDmg_           = Resistance{ fb->res_crit_dmg() };
    c.resFireDmg_           = Resistance{ fb->res_fire_dmg() };
    c.resColdDmg_           = Resistance{ fb->res_cold_dmg() };
    c.resEnerDmg_           = Resistance{ fb->res_ener_dmg() };
    c.resExplDmg_           = Resistance{ fb->res_expl_dmg() };
    c.evasion_              = Evasion{ fb->evasion() };
    c.initiat_              = Initiative{ fb->initiat() };
    c.strike_               = Strike{ fb->strike() };

    c.level_                = Level{ fb->level() };
    c.armor_                = Armor{ fb->armor() };
    c.armorPen_             = Armor{ fb->armor_pen() };
    c.apMax_                = ActionPoint{ fb->ap_max() };
    c.apCur_                = ActionPoint{ fb->ap_cur() };
    c.movDowned_            = NumberMoves{ fb->mov_downed() };
    c.percept_              = Perception{ fb->percept() };
    c.radRes_               = Radiation{ fb->rad_res() };

    return unit;
}

///************************************************************************************************

bool equipWeapon(Character& character,
                 Inventory& inventory,
                 InventoryIterator iterItem,
                 unsigned int weaponSlotNumber)
{
    assert(iterItem.isValid());
    if (!iterItem.isValid()) {
        return false;
    }
    if (!unequipWeapon(character, inventory, weaponSlotNumber)) {
        return false;
    }
    unique_ptr<object::Item> newWeapon{ inventory.extract(iterItem) };
    if (!newWeapon) {
        return false;
    }
    if (character.setWeapon(weaponSlotNumber, newWeapon)) {
        return true;
    }
    InventoryIterator iter{ inventory.insert(newWeapon) };
    assert(iter.isValid());
    return false;
}

bool unequipWeapon(Character& character,
                   Inventory& inventory,
                   unsigned int weaponSlotNumber)
{
    if (!character.slotWeapon()[weaponSlotNumber]) {
        return true;
    }
    unique_ptr<object::Item> oldWeapon{};
    if (!character.unsetWeapon(weaponSlotNumber, oldWeapon)) {
        return false;
    }
    assert(!character.slotWeapon()[weaponSlotNumber]);
    InventoryIterator iterItem{ inventory.insert(oldWeapon) };
    assert(iterItem.isValid());
    return true;
}

} // namespace object
} // namespace game
