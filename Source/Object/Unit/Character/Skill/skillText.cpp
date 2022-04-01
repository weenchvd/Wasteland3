
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"skillPath.hpp"
#include"skillText.hpp"
#include<assert.h>
#include<memory>
#include<stdlib.h>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase                       SkillText::base_;
array<SkillText::language_bundle_t, SkillText::sizeType_>
                                            SkillText::name_;
array<SkillText::language_bundle_t, SkillText::sizeType_>
                                            SkillText::descr_;
array<SkillText::language_bundle_t, SkillText::sizeGroup_>
                                            SkillText::group_;
bool                                        SkillText::initialized_{ false };

///************************************************************************************************

void SkillText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    if (!common::readBinFlatBuffer(SKILL_TEXT_FB_BIN_FILE__NATIVE_REL_PATH, buffer)) {
        abort();
    }
    const fbSkill::FB_SkillText* fb{
        fbSkill::GetFB_SkillText(buffer.get())
    };

    assert(fb != nullptr);
    initByType(fb->name(), name_);
    initByType(fb->descr(), descr_);
    initByGroup(fb->group(), group_);

    initialized_ = true;
}

void SkillText::initByType(
    const fbSkill::FB_SkillTextType* fb,
    array<language_bundle_t, sizeType_>& ar)
{
    assert(sizeType_ > 0);
    assert(fb != nullptr);

    common::initLanguageBundle(
        fb->automatic_weapons(),
        ar[common::toUnderlying(Skill__Type::AUTOMATIC_WEAPONS)]
    );
    common::initLanguageBundle(
        fb->big_guns(),
        ar[common::toUnderlying(Skill__Type::BIG_GUNS)]
    );
    common::initLanguageBundle(
        fb->brawling(),
        ar[common::toUnderlying(Skill__Type::BRAWLING)]
    );
    common::initLanguageBundle(
        fb->melee_combat(),
        ar[common::toUnderlying(Skill__Type::MELEE_COMBAT)]
    );
    common::initLanguageBundle(
        fb->small_arms(),
        ar[common::toUnderlying(Skill__Type::SMALL_ARMS)]
    );
    common::initLanguageBundle(
        fb->sniper_rifles(),
        ar[common::toUnderlying(Skill__Type::SNIPER_RIFLES)]
    );
    common::initLanguageBundle(
        fb->animal_whisperer(),
        ar[common::toUnderlying(Skill__Type::ANIMAL_WHISPERER)]
    );
    common::initLanguageBundle(
        fb->explosives(),
        ar[common::toUnderlying(Skill__Type::EXPLOSIVES)]
    );
    common::initLanguageBundle(
        fb->first_aid(),
        ar[common::toUnderlying(Skill__Type::FIRST_AID)]
    );
    common::initLanguageBundle(
        fb->sneaky_shit(),
        ar[common::toUnderlying(Skill__Type::SNEAKY_SHIT)]
    );
    common::initLanguageBundle(
        fb->weird_science(),
        ar[common::toUnderlying(Skill__Type::WEIRD_SCIENCE)]
    );
    common::initLanguageBundle(
        fb->armor_modding(),
        ar[common::toUnderlying(Skill__Type::ARMOR_MODDING)]
    );
    common::initLanguageBundle(
        fb->lockpicking(),
        ar[common::toUnderlying(Skill__Type::LOCKPICKING)]
    );
    common::initLanguageBundle(
        fb->nerd_stuff(),
        ar[common::toUnderlying(Skill__Type::NERD_STUFF)]
    );
    common::initLanguageBundle(
        fb->mechanics(),
        ar[common::toUnderlying(Skill__Type::MECHANICS)]
    );
    common::initLanguageBundle(
        fb->survival(),
        ar[common::toUnderlying(Skill__Type::SURVIVAL)]
    );
    common::initLanguageBundle(
        fb->toaster_repair(),
        ar[common::toUnderlying(Skill__Type::TOASTER_REPAIR)]
    );
    common::initLanguageBundle(
        fb->weapon_modding(),
        ar[common::toUnderlying(Skill__Type::WEAPON_MODDING)]
    );
    common::initLanguageBundle(
        fb->barter(),
        ar[common::toUnderlying(Skill__Type::BARTER)]
    );
    common::initLanguageBundle(
        fb->hard_ass(),
        ar[common::toUnderlying(Skill__Type::HARD_ASS)]
    );
    common::initLanguageBundle(
        fb->kiss_ass(),
        ar[common::toUnderlying(Skill__Type::KISS_ASS)]
    );
    common::initLanguageBundle(
        fb->leadership(),
        ar[common::toUnderlying(Skill__Type::LEADERSHIP)]
    );
}

void SkillText::initByGroup(
    const fbSkill::FB_SkillTextGroup* fb,
    array<language_bundle_t, sizeGroup_>& ar)
{
    assert(sizeGroup_ > 0);
    assert(fb != nullptr);

    common::initLanguageBundle(
        fb->combat(),
        ar[common::toUnderlying(Skill__Group::COMBAT)]
    );
    common::initLanguageBundle(
        fb->general(),
        ar[common::toUnderlying(Skill__Group::GENERAL)]
    );
    common::initLanguageBundle(
        fb->exploration(),
        ar[common::toUnderlying(Skill__Group::EXPLORATION)]
    );
    common::initLanguageBundle(
        fb->social(),
        ar[common::toUnderlying(Skill__Group::SOCIAL)]
    );
}

} // namespace object
} // namespace game
