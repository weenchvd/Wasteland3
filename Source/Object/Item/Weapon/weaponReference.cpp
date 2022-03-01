
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

common::ObserverDLL<void, WeaponReferenceContainer::language>
                            WeaponReferenceContainer::langObs_;

vector<WeaponReference>     WeaponReferenceContainer::refs_;
WeaponReference             WeaponReferenceContainer::refMinimal_;
WeaponReference             WeaponReferenceContainer::refDefault_;

underlying_type_t<WeaponReferenceContainer::language>
                            WeaponReferenceContainer::langIndex_    { 0 };
bool                        WeaponReferenceContainer::initialized_  { false };

///************************************************************************************************

WeaponRequirements::WeaponRequirements() noexcept
    :
    skillReq_       {},
    attrReq_        {}
{
    skillReq_.fill(skill_requirement{ Skill::Type::INVALID, 0 });
    attrReq_.fill(attribute_requirement{ Attribute::Type::INVALID, 0 });
}

///************************************************************************************************

WeaponPenalties::WeaponPenalties() noexcept
    :
    mulCritDmg_     { 0 },
    chaHit_         { 0 },
    chaCritDmg_     { 0 },
    strike_         { 0 }
{}

bool WeaponPenalties::isPresented() const noexcept
{
    assert(WeaponReferenceContainer::weaponReferenceDefault().isInitialized());
    const WeaponPenalties& def{ WeaponReferenceContainer::weaponReferenceDefault().penalties_ };
    if (mulCritDmg_ != def.mulCritDmg_) return true;
    if (chaHit_     != def.chaHit_)     return true;
    if (chaCritDmg_ != def.chaCritDmg_) return true;
    if (strike_     != def.strike_)     return true;
    return false;
}

///************************************************************************************************

WeaponReference::WeaponReference() noexcept
    :
    model_          { Weapon__Model::INVALID },
    type_           { Weapon__Type::INVALID },
    weaponModTypes_ {},
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
{
    weaponModTypes_.fill(WeaponMod::Type::INVALID);
}

///************************************************************************************************

void WeaponReferenceContainer::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(WEAPON_REF_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbWeapon::FB_WeaponReferenceContainer* fb{
        fbWeapon::GetFB_WeaponReferenceContainer(buffer.get())
    };

    initContainer(fb);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponReferenceContainer::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void WeaponReferenceContainer::initContainer(
    const fbWeapon::FB_WeaponReferenceContainer* fb)
{
    assert(fb != nullptr);
    refs_.resize(common::numberOf<Weapon__Model>());
    const auto* v{ fb->refs() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        WeaponReference ref{ initWeaponReference(v->Get(i)) };
        const auto pos{ common::toUnderlying(ref.model_) };
        refs_[pos] = move(ref);
    }
    refMinimal_ = initWeaponReference(fb->ref_minimal(), false);
    refDefault_ = initWeaponReference(fb->ref_default(), false);
}

WeaponReference WeaponReferenceContainer::initWeaponReference(
    const fbWeapon::FB_WeaponReference* fb, const bool assert)
{
    assert(fb != nullptr);
    WeaponReference ref;

    ref.model_  = toWeaponModel(fb->weapon_model());
    ref.type_   = toWeaponType(fb->weapon_type());

    const auto* modTypes{ fb->weapon_mod_types() };
    assert(modTypes != nullptr);
    assert(modTypes->size() <= ref.weaponModTypes_.size());
    for (size_t i = 0; i < modTypes->size(); ++i) {
        ref.weaponModTypes_[i] = toWeaponModType(
            static_cast<fbWeaponMod::FB_WeaponModType>(modTypes->Get(i))
        );
        assert(common::isValidEnum(ref.weaponModTypes_[i]));
    }

    initWeaponRequirements(fb->weapon_requirements(), ref.requirements_);

    const auto* penalties{ fb->weapon_penalties() };
    assert(penalties != nullptr);
    ref.penalties_.mulCritDmg_  = { penalties->multiplier_crit_dmg() };
    ref.penalties_.chaHit_      = { penalties->chance_hit() };
    ref.penalties_.chaCritDmg_  = { penalties->chance_crit_dmg() };
    ref.penalties_.strike_      = { penalties->strike_rate() };

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
    ref.level_          = { fb->weapon_level() };
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
        assert(common::isValidEnum(ref.tyAmmo_));
        assert(common::isValidEnum(ref.tyDmg_));
    }
#endif

    return ref;
}

void WeaponReferenceContainer::initWeaponRequirements(
    const fbWeapon::FB_WeaponRequirements* fb,
    WeaponRequirements& requirements)
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
