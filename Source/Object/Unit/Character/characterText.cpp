
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"characterPath.hpp"
#include"characterText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase                       CharacterText::base_;
array<CharacterText::language_bundle_t, CharacterText::sizeType_>
                                            CharacterText::type_;
CharacterTextStats                          CharacterText::stats_;
CharacterTextCommon                         CharacterText::common_;
bool                                        CharacterText::initialized_{ false };

///************************************************************************************************

void CharacterText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(CHARACTER_TEXT_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              CHARACTER_TEXT_FB_BIN_FILE__HASH);
    const fbCharacter::FB_CharacterText* fb{
        fbCharacter::GetFB_CharacterText(buffer.get())
    };

    assert(fb != nullptr);
    initByType(fb->type(), type_);
    initStats(fb->stats());
    initCommon(fb->common());

    initialized_ = true;
}

void CharacterText::initByType(
    const fbCharacter::FB_CharacterTextType* fb,
    array<language_bundle_t, sizeType_>& ar)
{
    assert(sizeType_ > 0);
    assert(fb != nullptr);

    common::initLanguageBundle(
        fb->ranger(),
        ar[common::toUnderlying(Character__Type::RANGER)]
    );
    common::initLanguageBundle(
        fb->companion(),
        ar[common::toUnderlying(Character__Type::COMPANION)]
    );
}

void CharacterText::initStats(const fbCharacter::FB_CharacterTextStats* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->con(), stats_.con_);
    common::initLanguageBundle(fb->con_per_level(), stats_.conPerLevel_);
    common::initLanguageBundle(fb->healing_bonus(), stats_.healingBonus_);
    common::initLanguageBundle(fb->action_points(), stats_.actionPoints_);
    common::initLanguageBundle(fb->hit_chance(), stats_.hitChance_);
    common::initLanguageBundle(fb->crit_chance(), stats_.critChance_);
    common::initLanguageBundle(fb->crit_dmg(), stats_.critDmg_);
    common::initLanguageBundle(fb->penetration(), stats_.penetration_);
    common::initLanguageBundle(fb->sneak_attack_dmg(), stats_.sneakAttackDmg_);
    common::initLanguageBundle(fb->strike_rate(), stats_.strikeRate_);
    common::initLanguageBundle(fb->armor(), stats_.armor_);
    common::initLanguageBundle(fb->evasion(), stats_.evasion_);
    common::initLanguageBundle(fb->crit_resistance(), stats_.critResistance_);
    common::initLanguageBundle(fb->fire_resistance(), stats_.fireResistance_);
    common::initLanguageBundle(fb->cold_resistance(), stats_.coldResistance_);
    common::initLanguageBundle(fb->energy_resistance(), stats_.energyResistance_);
    common::initLanguageBundle(fb->explosive_resistance(), stats_.explosiveResistance_);
    common::initLanguageBundle(fb->status_effect_resistance(), stats_.statusEffectResistance_);
    common::initLanguageBundle(fb->radiation_resistance(), stats_.radiationResistance_);
    common::initLanguageBundle(fb->downed_time(), stats_.downedTime_);
    common::initLanguageBundle(fb->melee_dmg_bonus(), stats_.meleeDmgBonus_);
    common::initLanguageBundle(fb->ranged_dmg_bonus(), stats_.rangedDmgBonus_);
    common::initLanguageBundle(fb->normal_dmg_bonus(), stats_.normalDmgBonus_);
    common::initLanguageBundle(fb->fire_dmg_bonus(), stats_.fireDmgBonus_);
    common::initLanguageBundle(fb->cold_dmg_bonus(), stats_.coldDmgBonus_);
    common::initLanguageBundle(fb->energy_dmg_bonus(), stats_.energyDmgBonus_);
    common::initLanguageBundle(fb->explosive_dmg_bonus(), stats_.explosiveDmgBonus_);
    common::initLanguageBundle(fb->perception(), stats_.perception_);
    common::initLanguageBundle(fb->throwing_range(), stats_.throwingRange_);
    common::initLanguageBundle(fb->initiative(), stats_.initiative_);
    common::initLanguageBundle(fb->detection_time(), stats_.detectionTime_);
    common::initLanguageBundle(fb->combat_speed(), stats_.combatSpeed_);
    common::initLanguageBundle(fb->quick_slots(), stats_.quickSlots_);
    common::initLanguageBundle(fb->leadership_range(), stats_.leadershipRange_);
    common::initLanguageBundle(fb->experience_bonus(), stats_.experienceBonus_);
}

void CharacterText::initCommon(const fbCharacter::FB_CharacterTextCommon* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->level(), common_.level_);
    common::initLanguageBundle(fb->stats(), common_.stats_);
    common::initLanguageBundle(fb->xp(), common_.xp_);
    common::initLanguageBundle(fb->m_meter(), common_.m_meter_);
    common::initLanguageBundle(fb->sec(), common_.sec_);
}

} // namespace object
} // namespace game
