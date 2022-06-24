
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"characterPath.hpp"
#include"characterReference.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include<memory>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase               CharacterReferenceContainer::base_;
vector<CharacterReference>          CharacterReferenceContainer::refs_;
CharacterReference                  CharacterReferenceContainer::refMinimal_;
CharacterReference                  CharacterReferenceContainer::refDefault_;
bool                                CharacterReferenceContainer::initialized_{ false };

///************************************************************************************************

CharacterReference::CharacterReference()
    :
    model_              { Character__Model::__INVALID },
    type_               { Character__Type::__INVALID },
    //armorTypes_         {},
    weaponTypes_        {},
    //consumTypes_        {},
    attrInitializer_    {},
    name_               {},
    descrip_            {},
    enteredName_        {},
    timeDetect_         { 0 },
    xp_                 { 0 },
    xpReward_           { 0 },
    rangeLeader_        { 0 },
    conMax_             { 0 },
    conCur_             { 0 },
    conPerLvl_          { 0 },
    mulCritDmg_         { 0 },
    mulSpeed_           { 0 },
    mulThrow_           { 0 },
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
    bonHeal_            { 0 },
    bonCritHeal_        { 0 },
    bonHealRevive_      { 0 },
    bonRepair_          { 0 },
    bonXP_              { 0 },
    bonMissionRew_      { 0 },
    bonScrap_           { 0 },
    bonSellValue_       { 0 },
    bonBuyCost_         { 0 },
    bonSneakDmg_        { 0 },
    bonNormDmg_         { 0 },
    bonMeleeDmg_        { 0 },
    bonRangeDmg_        { 0 },
    bonFireDmg_         { 0 },
    bonColdDmg_         { 0 },
    bonEnerDmg_         { 0 },
    bonExplDmg_         { 0 },
    bonAnimalDmg_       { 0 },
    bonDmgVsRobot_      { 0 },
    bonDmgVsVehic_      { 0 },
    bonDmgVsSynth_      { 0 },
    bonDmgVsAnimal_     { 0 },
    bonDmgVsMutant_     { 0 },
    bonNormDmgBossKill_ { 0 }, // TODO consider
    bonCONHealedRevive_ { 0 },
    resStatEff_         { 0 },
    resCritDmg_         { 0 },
    resFireDmg_         { 0 },
    resColdDmg_         { 0 },
    resEnerDmg_         { 0 },
    resExplDmg_         { 0 },
    evasion_            { 0 },
    initiat_            { 0 },
    strike_             { 0 },
    level_              { 0 },
    armor_              { 0 },
    armorPen_           { 0 },
    apMax_              { 0 },
    apCur_              { 0 },
    movDowned_          { 0 },
    percept_            { 0 },
    radRes_             { 0 },
    initialized_        { false }
{
    //armorTypes_.fill(Armor::Type::__INVALID);
    weaponTypes_.fill(Weapon::Type::__INVALID);
    //consumTypes_.fill(Consumable::Type::__INVALID);
}

///************************************************************************************************

void CharacterReferenceContainer::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(CHARACTER_REF_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
        CHARACTER_REF_FB_BIN_FILE__HASH);
    const fbCharacter::FB_CharacterReferenceContainer* fb{
        fbCharacter::GetFB_CharacterReferenceContainer(buffer.get())
    };

    initContainer(fb);

    initialized_ = true;
}

void CharacterReferenceContainer::initContainer(
    const fbCharacter::FB_CharacterReferenceContainer* fb)
{
    assert(fb != nullptr);
    refs_.resize(common::numberOf<Character__Model>());
    const auto* v{ fb->ref_values() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        CharacterReference ref{ initCharacterReference(v->Get(i)) };
        const auto pos{ common::toUnderlying(ref.model_) };
        refs_[pos] = move(ref);
    }
    refMinimal_ = initCharacterReference(fb->ref_minimal_values(), false);
    refDefault_ = initCharacterReference(fb->ref_default_values(), false);
    initCharacterReference(fb->sample_of_all_fields(), false);
}

CharacterReference CharacterReferenceContainer::initCharacterReference(
    const fbCharacter::FB_CharacterReference* fb,
    const bool verify)
{
    assert(fb != nullptr);
    CharacterReference ref;

    ref.model_  = toCharacterModel(fb->character_model());
    ref.type_   = toCharacterType(fb->character_type());
    assert((verify ? common::isValidEnum(ref.model_) : true));
    assert((verify ? common::isValidEnum(ref.type_) : true));

    const auto* weaponTypes{ fb->weapon_types() };
    assert(weaponTypes != nullptr);
    assert(weaponTypes->size() <= ref.weaponTypes_.size());
    for (size_t i = 0; i < weaponTypes->size(); ++i) {
        ref.weaponTypes_[i] = toWeaponType(
            static_cast<fbWeapon::FB_WeaponType>(weaponTypes->Get(i))
        );
        assert((verify ? (common::isValidEnum(ref.weaponTypes_[i]) ||
                          common::isValidEnumAux(ref.weaponTypes_[i])) : true));
    }

    ref.attrInitializer_        = AttributeInitializer{ fb->attributes() };

    common::initLanguageBundle(fb->name(), ref.name_);
    common::initLanguageBundle(fb->descrip(), ref.descrip_);

    ref.enteredName_            = move(fb->entered_name()->c_str());

    ref.timeDetect_             = common::Time{ fb->time_detect() };
    ref.xp_                     = common::Experience{ fb->xp() };
    ref.xpReward_               = common::Experience{ fb->xp_reward() };

    ref.rangeLeader_            = common::Range{ fb->range_leader() };
    ref.conMax_                 = common::Constitution{ fb->con_max() };
    ref.conCur_                 = common::Constitution{ fb->con_current() };
    ref.conPerLvl_              = common::Constitution{ fb->con_per_level() };
    ref.mulCritDmg_             = common::Multiplier{ fb->mul_crit_dmg() };
    ref.mulSpeed_               = common::Multiplier{ fb->mul_combat_speed() };
    ref.mulThrow_               = common::Multiplier{ fb->mul_throwing_range() };
    ref.chaHit_                 = common::Chance{ fb->chance_hit() };
    ref.chaHitAR_               = common::Chance{ fb->chance_hit_ar() };
    ref.chaHitSMG_              = common::Chance{ fb->chance_hit_smg() };
    ref.chaHitHMG_              = common::Chance{ fb->chance_hit_hmg() };
    ref.chaHitFT_               = common::Chance{ fb->chance_hit_ft() };
    ref.chaHitBrawl_            = common::Chance{ fb->chance_hit_brawl() };
    ref.chaHitBlunt_            = common::Chance{ fb->chance_hit_blunt() };
    ref.chaHitBladed_           = common::Chance{ fb->chance_hit_bladed() };
    ref.chaHitSAPistol_         = common::Chance{ fb->chance_hit_sapistol() };
    ref.chaHitRevolver_         = common::Chance{ fb->chance_hit_revolver() };
    ref.chaHitPumpSG_           = common::Chance{ fb->chance_hit_pumpsg() };
    ref.chaHitAutoSG_           = common::Chance{ fb->chance_hit_autosg() };
    ref.chaHitSR_               = common::Chance{ fb->chance_hit_sr() };
    ref.chaHitNearbyAllies_     = common::Chance{ fb->chance_hit_nearby_allies() };
    ref.chaCritDmgMultiKill_    = common::Chance{ fb->chance_crit_dmg_multi_kill() };
    ref.chaCritDmg_             = common::Chance{ fb->chance_crit_dmg() };
    ref.chaCritHeal_            = common::Chance{ fb->chance_crit_heal() };
    ref.chaLuckAction_          = common::Chance{ fb->chance_luck_action() };
    ref.chaLuckCritDmg_         = common::Chance{ fb->chance_luck_crit_dmg() };
    ref.chaLuckMegaCritDmg_     = common::Chance{ fb->chance_luck_mega_crit_dmg() };
    ref.chaLuckEvade_           = common::Chance{ fb->chance_luck_evade() };
    ref.chaLuckCritRes_         = common::Chance{ fb->chance_luck_crit_res() };
    ref.chaLuckDblHeal_         = common::Chance{ fb->chance_luck_double_heal() };
    ref.chaLuckDblMoney_        = common::Chance{ fb->chance_luck_double_money() };
    ref.chaLuckDblScrap_        = common::Chance{ fb->chance_luck_double_scrap() };
    ref.bonHeal_                = common::Bonus{ fb->bonus_heal() };
    ref.bonCritHeal_            = common::Bonus{ fb->bonus_crit_heal() };
    ref.bonHealRevive_          = common::Bonus{ fb->bonus_heal_revive() };
    ref.bonRepair_              = common::Bonus{ fb->bonus_repair() };
    ref.bonXP_                  = common::Bonus{ fb->bonus_xp() };
    ref.bonMissionRew_          = common::Bonus{ fb->bonus_mission_reward() };
    ref.bonScrap_               = common::Bonus{ fb->bonus_scrap() };
    ref.bonSellValue_           = common::Bonus{ fb->bonus_sell_value() };
    ref.bonBuyCost_             = common::Bonus{ fb->bonus_buy_cost() };
    ref.bonSneakDmg_            = common::Bonus{ fb->bonus_sneak_dmg() };
    ref.bonNormDmg_             = common::Bonus{ fb->bonus_norm_dmg() };
    ref.bonMeleeDmg_            = common::Bonus{ fb->bonus_melee_dmg() };
    ref.bonRangeDmg_            = common::Bonus{ fb->bonus_range_dmg() };
    ref.bonFireDmg_             = common::Bonus{ fb->bonus_fire_dmg() };
    ref.bonColdDmg_             = common::Bonus{ fb->bonus_cold_dmg() };
    ref.bonEnerDmg_             = common::Bonus{ fb->bonus_energy_dmg() };
    ref.bonExplDmg_             = common::Bonus{ fb->bonus_explosive_dmg() };
    ref.bonAnimalDmg_           = common::Bonus{ fb->bonus_animal_companion_dmg() };
    ref.bonDmgVsRobot_          = common::Bonus{ fb->bonus_dmg_vs_robot() };
    ref.bonDmgVsVehic_          = common::Bonus{ fb->bonus_dmg_vs_vehicle() };
    ref.bonDmgVsSynth_          = common::Bonus{ fb->bonus_dmg_vs_synth() };
    ref.bonDmgVsAnimal_         = common::Bonus{ fb->bonus_dmg_vs_animal() };
    ref.bonDmgVsMutant_         = common::Bonus{ fb->bonus_dmg_vs_mutant() };
    ref.bonNormDmgBossKill_     = common::Bonus{ fb->bonus_norm_dmg_on_boss_kill() };
    ref.bonCONHealedRevive_     = common::Bonus{ fb->bonus_con_healed_on_revive() };
    ref.resStatEff_             = common::Resistance{ fb->res_status_effect() };
    ref.resCritDmg_             = common::Resistance{ fb->res_crit_dmg() };
    ref.resFireDmg_             = common::Resistance{ fb->res_fire_dmg() };
    ref.resColdDmg_             = common::Resistance{ fb->res_cold_dmg() };
    ref.resEnerDmg_             = common::Resistance{ fb->res_energy_dmg() };
    ref.resExplDmg_             = common::Resistance{ fb->res_explosive_dmg() };
    ref.evasion_                = common::Evasion{ fb->evasion() };
    ref.initiat_                = common::Initiative{ fb->initiative() };
    ref.strike_                 = common::Strike{ fb->strike() };

    ref.level_                  = common::Level{ fb->level() };
    ref.armor_                  = common::Armor{ fb->armor() };
    ref.armorPen_               = common::Armor{ fb->armor_penetration() };
    ref.apMax_                  = common::ActionPoint{ fb->ap_max() };
    ref.apCur_                  = common::ActionPoint{ fb->ap_current() };
    ref.movDowned_              = common::NumberMoves{ fb->mov_downed_time() };
    ref.percept_                = common::Perception{ fb->perception() };
    ref.radRes_                 = common::Radiation{ fb->radiation_resistance() };

    ref.initialized_            = true;
    return ref;
}

} // namespace object
} // namespace game
