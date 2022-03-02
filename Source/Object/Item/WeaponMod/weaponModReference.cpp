
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include"weaponModPath.hpp"
#include"weaponModReference.hpp"
#include<memory>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, WeaponModReferenceContainer::language>
                            WeaponModReferenceContainer::langObs_;

vector<WeaponModReference>  WeaponModReferenceContainer::refs_;
WeaponModReference          WeaponModReferenceContainer::refDefault_;


underlying_type_t<WeaponModReferenceContainer::language>
                            WeaponModReferenceContainer::langIndex_     { 0 };
bool                        WeaponModReferenceContainer::initialized_   { false };

///************************************************************************************************

WeaponModRequirements::WeaponModRequirements() noexcept
    :
    skillReq_       {},
    attrReq_        {}
{
    skillReq_.fill(skill_requirement{ Skill::Type::INVALID, 0 });
    attrReq_.fill(attribute_requirement{ Attribute::Type::INVALID, 0 });
}

///************************************************************************************************

WeaponModReference::WeaponModReference() noexcept
    :
    model_          { WeaponMod__Model::INVALID },
    type_           { WeaponMod__Type::INVALID },
    requirements_   {},
    name_           {},
    descrip_        {},
    dmgMin_         { 0 },
    dmgMax_         { 0 },
    price_          { 0 },
    rangeAttack_    { 0 },
    capAmmo_        { 0 },
    mulCritDmg_     { 0 },
    chaHit_         { 0 },
    chaCritDmg_     { 0 },
    armorPen_       { 0 },
    apAttack_       { 0 },
    apReload_       { 0 },
    shoPerAttack_   { 0 },
    tyAmmo_         { Ammo::Type::INVALID },
    tyDmg_          { Damage::Type::INVALID },
    initialized_    { false }
{}

///************************************************************************************************

void WeaponModReferenceContainer::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(WEAPON_MOD_REF_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbWeaponMod::FB_WeaponModReferenceContainer* fb{
        fbWeaponMod::GetFB_WeaponModReferenceContainer(buffer.get())
    };

    initContainer(fb);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponModReferenceContainer::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponModReferenceContainer::initContainer(
    const fbWeaponMod::FB_WeaponModReferenceContainer* fb)
{
    assert(fb != nullptr);
    refs_.resize(common::numberOf<WeaponMod__Model>());
    const auto* v{ fb->refs() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        WeaponModReference ref{ initWeaponModReference(v->Get(i)) };
        const auto pos{ common::toUnderlying(ref.model_) };
        refs_[pos] = move(ref);
    }
    refDefault_ = initWeaponModReference(fb->ref_default(), false);
}

WeaponModReference WeaponModReferenceContainer::initWeaponModReference(
    const fbWeaponMod::FB_WeaponModReference* fb, const bool assert)
{
    assert(fb != nullptr);
    WeaponModReference ref;

    ref.model_  = toWeaponModModel(fb->weapon_mod_model());
    ref.type_   = toWeaponModType(fb->weapon_mod_type());

    initWeaponModRequirements(fb->weapon_mod_requirements(), ref.requirements_);

    common::initLanguageBundle(fb->name(), ref.name_);
    common::initLanguageBundle(fb->descrip(), ref.descrip_);

    ref.dmgMin_         = { fb->dmg_min() };
    ref.dmgMax_         = { fb->dmg_max() };
    ref.price_          = { fb->price() };
    ref.rangeAttack_    = { fb->range_attack() };
    ref.capAmmo_        = { fb->capacity_ammo() };
    ref.mulCritDmg_     = { fb->multiplier_crit_dmg() };
    ref.chaHit_         = { fb->chance_hit() };
    ref.chaCritDmg_     = { fb->chance_crit_dmg() };
    ref.armorPen_       = { fb->armor_penetration() };
    ref.apAttack_       = { fb->ap_per_attack() };
    ref.apReload_       = { fb->ap_per_reload() };
    ref.shoPerAttack_   = { fb->shots_per_attack() };
    ref.tyAmmo_         = toAmmoType(fb->ammo_type());
    ref.tyDmg_          = toDamageType(fb->dmg_type());

    ref.initialized_    = true;

#ifndef NDEBUG
    if (assert == true) {
        assert(common::isValidEnum(ref.model_));
        assert(common::isValidEnum(ref.type_));
    }
#endif

    return ref;
}

void WeaponModReferenceContainer::initWeaponModRequirements(
    const fbWeaponMod::FB_WeaponModRequirements* fb,
    WeaponModRequirements& requirements)
{
    assert(fb != nullptr);
    if (fb->skill() != nullptr) {
        const auto* ptr{ fb->skill() };
        assert(ptr->size() <= requirements.skillReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            requirements.skillReq_[i].first = toSkillType(ptr->Get(i)->type());
            assert(common::isValidEnum(requirements.skillReq_[i].first));
            requirements.skillReq_[i].second = { ptr->Get(i)->level() };
        }
    }
    if (fb->attr() != nullptr) {
        const auto* ptr{ fb->attr() };
        assert(ptr->size() <= requirements.attrReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            requirements.attrReq_[i].first = toAttributeType(ptr->Get(i)->type());
            assert(common::isValidEnum(requirements.attrReq_[i].first));
            requirements.attrReq_[i].second = { ptr->Get(i)->level() };
        }
    }
}

} // namespace object
} // namespace game
