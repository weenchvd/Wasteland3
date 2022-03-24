
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include"skillPath.hpp"
#include"skillText.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, SkillText::language> SkillText::langObs_;

array<SkillText::language_bundle, SkillText::sizeType_>     SkillText::name_;
array<SkillText::language_bundle, SkillText::sizeType_>     SkillText::descr_;
array<SkillText::language_bundle, SkillText::sizeGroup_>    SkillText::group_;

underlying_type_t<SkillText::language>      SkillText::langIndex_   { 0 };
bool                                        SkillText::initialized_ { false };

///************************************************************************************************

void SkillText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);
    assert(sizeType_ > 0);
    assert(sizeGroup_ > 0);
    unique_ptr<char[]> buffer{
        common::getFlatBuffer(SKILL_TEXT_FB_BIN_FILE__NATIVE_REL_PATH)
    };

    const fbSkill::FB_SkillText* table{
        fbSkill::GetFB_SkillText(buffer.get())
    };
    assert(table != nullptr);

    initByType(table->name(), name_);
    initByType(table->descr(), descr_);
    initByGroup(table->group(), group_);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOptions().optLanguage().getLanguage());
    langObs_.getDelegate().bind<&SkillText::setLanguage>();
    Locator::getOptions().optLanguage().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void SkillText::initByType(
    const fbSkill::FB_SkillTextType* table,
    array<language_bundle, sizeType_>& ar)
{
    assert(table != nullptr);

    common::initLanguageBundle(
        table->automatic_weapons(),
        ar[common::toUnderlying(Skill__Type::AUTOMATIC_WEAPONS)]
    );
    common::initLanguageBundle(
        table->big_guns(),
        ar[common::toUnderlying(Skill__Type::BIG_GUNS)]
    );
    common::initLanguageBundle(
        table->brawling(),
        ar[common::toUnderlying(Skill__Type::BRAWLING)]
    );
    common::initLanguageBundle(
        table->melee_combat(),
        ar[common::toUnderlying(Skill__Type::MELEE_COMBAT)]
    );
    common::initLanguageBundle(
        table->small_arms(),
        ar[common::toUnderlying(Skill__Type::SMALL_ARMS)]
    );
    common::initLanguageBundle(
        table->sniper_rifles(),
        ar[common::toUnderlying(Skill__Type::SNIPER_RIFLES)]
    );
    common::initLanguageBundle(
        table->animal_whisperer(),
        ar[common::toUnderlying(Skill__Type::ANIMAL_WHISPERER)]
    );
    common::initLanguageBundle(
        table->explosives(),
        ar[common::toUnderlying(Skill__Type::EXPLOSIVES)]
    );
    common::initLanguageBundle(
        table->first_aid(),
        ar[common::toUnderlying(Skill__Type::FIRST_AID)]
    );
    common::initLanguageBundle(
        table->sneaky_shit(),
        ar[common::toUnderlying(Skill__Type::SNEAKY_SHIT)]
    );
    common::initLanguageBundle(
        table->weird_science(),
        ar[common::toUnderlying(Skill__Type::WEIRD_SCIENCE)]
    );
    common::initLanguageBundle(
        table->armor_modding(),
        ar[common::toUnderlying(Skill__Type::ARMOR_MODDING)]
    );
    common::initLanguageBundle(
        table->lockpicking(),
        ar[common::toUnderlying(Skill__Type::LOCKPICKING)]
    );
    common::initLanguageBundle(
        table->nerd_stuff(),
        ar[common::toUnderlying(Skill__Type::NERD_STUFF)]
    );
    common::initLanguageBundle(
        table->mechanics(),
        ar[common::toUnderlying(Skill__Type::MECHANICS)]
    );
    common::initLanguageBundle(
        table->survival(),
        ar[common::toUnderlying(Skill__Type::SURVIVAL)]
    );
    common::initLanguageBundle(
        table->toaster_repair(),
        ar[common::toUnderlying(Skill__Type::TOASTER_REPAIR)]
    );
    common::initLanguageBundle(
        table->weapon_modding(),
        ar[common::toUnderlying(Skill__Type::WEAPON_MODDING)]
    );
    common::initLanguageBundle(
        table->barter(),
        ar[common::toUnderlying(Skill__Type::BARTER)]
    );
    common::initLanguageBundle(
        table->hard_ass(),
        ar[common::toUnderlying(Skill__Type::HARD_ASS)]
    );
    common::initLanguageBundle(
        table->kiss_ass(),
        ar[common::toUnderlying(Skill__Type::KISS_ASS)]
    );
    common::initLanguageBundle(
        table->leadership(),
        ar[common::toUnderlying(Skill__Type::LEADERSHIP)]
    );
}

void SkillText::initByGroup(
    const fbSkill::FB_SkillTextGroup* table,
    array<language_bundle, sizeGroup_>& ar)
{
    assert(table != nullptr);

    common::initLanguageBundle(
        table->combat(),
        ar[common::toUnderlying(Skill__Group::COMBAT)]
    );
    common::initLanguageBundle(
        table->general(),
        ar[common::toUnderlying(Skill__Group::GENERAL)]
    );
    common::initLanguageBundle(
        table->exploration(),
        ar[common::toUnderlying(Skill__Group::EXPLORATION)]
    );
    common::initLanguageBundle(
        table->social(),
        ar[common::toUnderlying(Skill__Group::SOCIAL)]
    );
}

} // namespace object
} // namespace game
