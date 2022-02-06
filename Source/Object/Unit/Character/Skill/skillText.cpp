
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"skillPath.hpp"
#include"skillText.hpp"
#include<assert.h>
#include<memory>
#include<type_traits>

namespace game {
namespace object {

using namespace std;
using common::Text;
using global::PlainText;
using global::Locator;

common::ObserverDLL<void, PlainText::Language>
    SkillText::langObs_;

std::array<
    std::array<Text, SkillText::sizeType_>,
    SkillText::sizeLang_
>
    SkillText::name_;

std::array<
    std::array<Text, SkillText::sizeType_>,
    SkillText::sizeLang_
>
    SkillText::descr_;

std::array<
    std::array<Text, SkillText::sizeGroup_>,
    SkillText::sizeLang_
>
    SkillText::group_;

std::array<Text, SkillText::sizeType_>*     SkillText::ptrName_ { nullptr };
std::array<Text, SkillText::sizeType_>*     SkillText::ptrDescr_{ nullptr };
std::array<Text, SkillText::sizeGroup_>*    SkillText::ptrGroup_{ nullptr };

bool SkillText::initialized_{ false };


void SkillText::setLanguage(PlainText::Language lang)
{
    assert(common::isValidEnum(lang));
    ptrName_    = { &name_[common::toUnderlying(lang)] };
    ptrDescr_   = { &descr_[common::toUnderlying(lang)] };
    ptrGroup_   = { &group_[common::toUnderlying(lang)] };
}

const Text& SkillText::name(Skill__Type id) noexcept
{
    assert(common::isValidEnum(id));
    assert(ptrName_ != nullptr);
    return (*ptrName_)[common::toUnderlying(id)];
}

const Text& SkillText::descr(Skill__Type id) noexcept
{
    assert(common::isValidEnum(id));
    assert(ptrDescr_ != nullptr);
    return (*ptrDescr_)[common::toUnderlying(id)];
}

const Text& SkillText::group(Skill__Group id) noexcept
{
    assert(common::isValidEnum(id));
    assert(ptrGroup_ != nullptr);
    return (*ptrGroup_)[common::toUnderlying(id)];
}

void SkillText::initialize()
{
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

    initLanguage(table->en(), PlainText::Language::EN);
    initLanguage(table->ru(), PlainText::Language::RU);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&SkillText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void SkillText::initLanguage(
    const fbSkill::FB_LanguageBundle* table,
    PlainText::Language lang)
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    initByType(table->name(), name_[common::toUnderlying(lang)]);
    initByType(table->descr(), descr_[common::toUnderlying(lang)]);
    initByGroup(table->group(), group_[common::toUnderlying(lang)]);
}

void SkillText::initByType(
    const fbSkill::FB_SkillTextType* table,
    std::array<Text, sizeType_>& ar)
{
    ar[common::toUnderlying(Skill__Type::AUTOMATIC_WEAPONS)] =
        move(Text{ table->automatic_weapons()->c_str() });
    ar[common::toUnderlying(Skill__Type::BIG_GUNS)] =
        move(Text{ table->big_guns()->c_str() });
    ar[common::toUnderlying(Skill__Type::BRAWLING)] =
        move(Text{ table->brawling()->c_str() });
    ar[common::toUnderlying(Skill__Type::MELEE_COMBAT)] =
        move(Text{ table->melee_combat()->c_str() });
    ar[common::toUnderlying(Skill__Type::SMALL_ARMS)] =
        move(Text{ table->small_arms()->c_str() });
    ar[common::toUnderlying(Skill__Type::SNIPER_RIFLES)] =
        move(Text{ table->sniper_rifles()->c_str() });
    ar[common::toUnderlying(Skill__Type::ANIMAL_WHISPERER)] =
        move(Text{ table->animal_whisperer()->c_str() });
    ar[common::toUnderlying(Skill__Type::EXPLOSIVES)] =
        move(Text{ table->explosives()->c_str() });
    ar[common::toUnderlying(Skill__Type::FIRST_AID)] =
        move(Text{ table->first_aid()->c_str() });
    ar[common::toUnderlying(Skill__Type::SNEAKY_SHIT)] =
        move(Text{ table->sneaky_shit()->c_str() });
    ar[common::toUnderlying(Skill__Type::WEIRD_SCIENCE)] =
        move(Text{ table->weird_science()->c_str() });
    ar[common::toUnderlying(Skill__Type::ARMOR_MODDING)] =
        move(Text{ table->armor_modding()->c_str() });
    ar[common::toUnderlying(Skill__Type::LOCKPICKING)] =
        move(Text{ table->lockpicking()->c_str() });
    ar[common::toUnderlying(Skill__Type::NERD_STUFF)] =
        move(Text{ table->nerd_stuff()->c_str() });
    ar[common::toUnderlying(Skill__Type::MECHANICS)] =
        move(Text{ table->mechanics()->c_str() });
    ar[common::toUnderlying(Skill__Type::SURVIVAL)] =
        move(Text{ table->survival()->c_str() });
    ar[common::toUnderlying(Skill__Type::TOASTER_REPAIR)] =
        move(Text{ table->toaster_repair()->c_str() });
    ar[common::toUnderlying(Skill__Type::WEAPON_MODDING)] =
        move(Text{ table->weapon_modding()->c_str() });
    ar[common::toUnderlying(Skill__Type::BARTER)] =
        move(Text{ table->barter()->c_str() });
    ar[common::toUnderlying(Skill__Type::HARD_ASS)] =
        move(Text{ table->hard_ass()->c_str() });
    ar[common::toUnderlying(Skill__Type::KISS_ASS)] =
        move(Text{ table->kiss_ass()->c_str() });
    ar[common::toUnderlying(Skill__Type::LEADERSHIP)] =
        move(Text{ table->leadership()->c_str() });
}

void SkillText::initByGroup(
    const fbSkill::FB_SkillTextGroup* table,
    std::array<Text, sizeGroup_>& ar)
{
    ar[common::toUnderlying(Skill__Group::COMBAT)] =
        move(Text{ table->combat()->c_str() });
    ar[common::toUnderlying(Skill__Group::GENERAL)] =
        move(Text{ table->general()->c_str() });
    ar[common::toUnderlying(Skill__Group::EXPLORATION)] =
        move(Text{ table->exploration()->c_str() });
    ar[common::toUnderlying(Skill__Group::SOCIAL)] =
        move(Text{ table->social()->c_str() });
}

} // namespace object
} // namespace game
