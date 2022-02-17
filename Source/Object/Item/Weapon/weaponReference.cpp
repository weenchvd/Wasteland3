
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include"weaponPath.hpp"
#include"weaponReference.hpp"
#include<memory>
#include<type_traits>

namespace game {
namespace object {

using namespace std;
using common::Text;
using global::Locator;

common::ObserverDLL<void, WeaponReferenceContainer::language>
    WeaponReferenceContainer::langObs_;

std::vector<WeaponReference>    WeaponReferenceContainer::refs_;
WeaponReference                 WeaponReferenceContainer::refMinimal_;
unsigned char                   WeaponReferenceContainer::langIndex_    { 0 };
bool                            WeaponReferenceContainer::initialized_  { false };

///************************************************************************************************

WeaponRequirements::WeaponRequirements() noexcept
    :
    skillReq_       { skill_requirement{ Skill::Type::INVALID, 0 },
                      skill_requirement{ Skill::Type::INVALID, 0 }, },
    attrReq_        { attribute_requirement{ Attribute::Type::INVALID, 0 },
                      attribute_requirement{ Attribute::Type::INVALID, 0 } }
{}

///************************************************************************************************

WeaponPenalties::WeaponPenalties() noexcept
    :
    mulCritDmg_     { 0 },
    chaHit_         { 0 },
    chaCritDmg_     { 0 },
    strike_         { 0 }
{}

///************************************************************************************************

WeaponReference::WeaponReference() noexcept
    :
    model_          { Weapon__Model::INVALID },
    type_           { Weapon__Type::INVALID },
    weaponModTypes_ { WeaponMod::Type::INVALID,
                      WeaponMod::Type::INVALID,
                      WeaponMod::Type::INVALID,
                      WeaponMod::Type::INVALID },
    requirements_   {},
    penalties_      {},
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
    level_          { 0 },
    armorPen_       { 0 },
    apAttack_       { 0 },
    apReload_       { 0 },
    shoPerAttack_   { 0 },
    tyAmmo_         { Ammo::Type::INVALID },
    tyDmg_          { Damage::Type::INVALID },
    initialized_    { false }
{}

///************************************************************************************************

void WeaponReferenceContainer::initialize()
{
    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(WEAPON_REF_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbWeapon::FB_WeaponReferenceContainer* container{
        fbWeapon::GetFB_WeaponReferenceContainer(buffer.get())
    };

    assert(container != nullptr);
    initContainer(container);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponReferenceContainer::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponReferenceContainer::initContainer(
    const fbWeapon::FB_WeaponReferenceContainer* container)
{
    assert(common::toUnderlying(Weapon__Model::NUMBER_OF) >= 0);
    refs_.resize(common::toUnderlying(Weapon__Model::NUMBER_OF));
    auto v{ container->refs() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        WeaponReference ref{ initWeaponReference(v->Get(i)) };
        auto pos{ common::toUnderlying(ref.model_) };
        refs_[pos] = move(ref);
    }
    refMinimal_ = initWeaponReference(container->ref_minimal());
}

WeaponReference WeaponReferenceContainer::initWeaponReference(
    const fbWeapon::FB_WeaponReference* reference)
{
    assert(reference != nullptr);
    WeaponReference ref;

    ref.model_  = toWeaponModel(reference->weapon_model());
    ref.type_   = toWeaponType(reference->weapon_type());

    auto modTypes{ reference->weapon_mod_types() };
    assert(modTypes != nullptr);
    assert(modTypes->size() <= ref.weaponModTypes_.size());
    for (size_t i = 0; i < modTypes->size(); ++i) {
        ref.weaponModTypes_[i] = toWeaponModType(
            static_cast<fbWeaponMod::FB_WeaponModType>(modTypes->Get(i))
        );
    }

    auto requirements{ reference->weapon_requirements() };
    assert(requirements != nullptr);
    if (requirements->skill() != nullptr) {
        auto ptr{ requirements->skill() };
        assert(ptr->size() <= ref.requirements_.skillReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            ref.requirements_.skillReq_[i].first = toSkillType(ptr->Get(i)->type());
            ref.requirements_.skillReq_[i].second = { ptr->Get(i)->level() };
        }
    }
    if (requirements->attr() != nullptr) {
        auto ptr{ requirements->attr() };
        assert(ptr->size() <= ref.requirements_.attrReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            ref.requirements_.attrReq_[i].first = toAttributeType(ptr->Get(i)->type());
            ref.requirements_.attrReq_[i].second = { ptr->Get(i)->level() };
        }
    }

    auto penalties{ reference->weapon_penalties() };
    assert(penalties != nullptr);
    ref.penalties_.mulCritDmg_  = { penalties->multiplier_crit_dmg() };
    ref.penalties_.chaHit_      = { penalties->chance_hit() };
    ref.penalties_.chaCritDmg_  = { penalties->chance_crit_dmg() };
    ref.penalties_.strike_      = { penalties->strike_rate() };

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
    ref.level_          = { reference->weapon_level() };
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
