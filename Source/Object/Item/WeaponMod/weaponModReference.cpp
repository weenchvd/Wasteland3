
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

underlying_type_t<WeaponModReferenceContainer::language>
                            WeaponModReferenceContainer::langIndex_     { 0 };
bool                        WeaponModReferenceContainer::initialized_   { false };

///************************************************************************************************

WeaponModRequirements::WeaponModRequirements() noexcept
    :
    skillReq_       { skill_requirement{ Skill::Type::INVALID, 0 },
                      skill_requirement{ Skill::Type::INVALID, 0 }, },
    attrReq_        { attribute_requirement{ Attribute::Type::INVALID, 0 },
                      attribute_requirement{ Attribute::Type::INVALID, 0 } }
{}

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
    const fbWeaponMod::FB_WeaponModReferenceContainer* container{
        fbWeaponMod::GetFB_WeaponModReferenceContainer(buffer.get())
    };

    initContainer(container);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponModReferenceContainer::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponModReferenceContainer::initContainer(
    const fbWeaponMod::FB_WeaponModReferenceContainer* container)
{
    assert(container != nullptr);
    refs_.resize(common::numberOf<WeaponMod__Model>());
    auto v{ container->refs() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        WeaponModReference ref{ initWeaponModReference(v->Get(i)) };
        auto pos{ common::toUnderlying(ref.model_) };
        refs_[pos] = move(ref);
    }
}

WeaponModReference WeaponModReferenceContainer::initWeaponModReference(
    const fbWeaponMod::FB_WeaponModReference* reference)
{
    assert(reference != nullptr);
    WeaponModReference ref;

    ref.model_  = toWeaponModModel(reference->weapon_mod_model());
    assert(common::isValidEnum(ref.model_));
    ref.type_   = toWeaponModType(reference->weapon_mod_type());
    assert(common::isValidEnum(ref.type_));

    auto requirements{ reference->weapon_mod_requirements() };
    assert(requirements != nullptr);
    if (requirements->skill() != nullptr) {
        auto ptr{ requirements->skill() };
        assert(ptr->size() <= ref.requirements_.skillReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            ref.requirements_.skillReq_[i].first = toSkillType(ptr->Get(i)->type());
            assert(common::isValidEnum(ref.requirements_.skillReq_[i].first));
            ref.requirements_.skillReq_[i].second = { ptr->Get(i)->level() };
        }
    }
    if (requirements->attr() != nullptr) {
        auto ptr{ requirements->attr() };
        assert(ptr->size() <= ref.requirements_.attrReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            ref.requirements_.attrReq_[i].first = toAttributeType(ptr->Get(i)->type());
            assert(common::isValidEnum(ref.requirements_.attrReq_[i].first));
            ref.requirements_.attrReq_[i].second = { ptr->Get(i)->level() };
        }
    }

    common::initLanguageBundle(reference->name(), ref.name_);
    common::initLanguageBundle(reference->descrip(), ref.descrip_);

    ref.dmgMin_         = { reference->dmg_min() };
    ref.dmgMax_         = { reference->dmg_max() };
    ref.price_          = { reference->price() };
    ref.rangeAttack_    = { reference->range_attack() };
    ref.capAmmo_        = { reference->capacity_ammo() };
    ref.mulCritDmg_     = { reference->multiplier_crit_dmg() };
    ref.chaHit_         = { reference->chance_hit() };
    ref.chaCritDmg_     = { reference->chance_crit_dmg() };
    ref.armorPen_       = { reference->armor_penetration() };
    ref.apAttack_       = { reference->ap_per_attack() };
    ref.apReload_       = { reference->ap_per_reload() };
    ref.shoPerAttack_   = { reference->shots_per_attack() };
    ref.tyAmmo_         = toAmmoType(reference->ammo_type());
    ref.tyDmg_          = toDamageType(reference->dmg_type());

    ref.initialized_    = true;

    return ref;
}

} // namespace object
} // namespace game
