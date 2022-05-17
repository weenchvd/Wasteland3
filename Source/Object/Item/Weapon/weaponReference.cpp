
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"weaponPath.hpp"
#include"weaponReference.hpp"
#include<memory>
#include<stdlib.h>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase               WeaponReferenceContainer::base_;
vector<WeaponReference>             WeaponReferenceContainer::refs_;
WeaponReference                     WeaponReferenceContainer::refMinimal_;
WeaponReference                     WeaponReferenceContainer::refDefault_;
bool                                WeaponReferenceContainer::initialized_{ false };

///************************************************************************************************

WeaponRequirements::WeaponRequirements()
    :
    skillReq_       {},
    attrReq_        {}
{
    skillReq_.fill(skill_requirement_t{ Skill::Type::INVALID, 0 });
    attrReq_.fill(attribute_requirement_t{ Attribute::Type::INVALID, 0 });
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
    return  mulCritDmg_ != def.mulCritDmg_ ||
            chaHit_     != def.chaHit_ ||
            chaCritDmg_ != def.chaCritDmg_ ||
            strike_     != def.strike_;
}

///************************************************************************************************

WeaponReference::WeaponReference()
    :
    model_          { Weapon__Model::INVALID },
    type_           { Weapon__Type::INVALID },
    weaponModTypes_ {},
    requirements_   {},
    penalties_      {},
    attack_         {},
    name_           {},
    descrip_        {},
    dmgMin_         { 0 },
    dmgMax_         { 0 },
    price_          { 0 },
    capAmmo_        { 0 },
    mulCritDmg_     { 0 },
    chaHit_         { 0 },
    chaCritDmg_     { 0 },
    bonSneakDmg_    { 0 },
    bonNormDmg_     { 0 },
    bonMeleeDmg_    { 0 },
    bonRangeDmg_    { 0 },
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
    if (isInitialized()) return;
    base_.initialize();
    Attack::initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(WEAPON_REF_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              WEAPON_REF_FB_BIN_FILE__HASH);
    const fbWeapon::FB_WeaponReferenceContainer* fb{
        fbWeapon::GetFB_WeaponReferenceContainer(buffer.get())
    };

    initContainer(fb);

    initialized_ = true;
}

void WeaponReferenceContainer::initContainer(
    const fbWeapon::FB_WeaponReferenceContainer* fb)
{
    assert(fb != nullptr);
    refs_.resize(common::numberOf<Weapon__Model>());
    const auto* v{ fb->ref_values() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        WeaponReference ref{ initWeaponReference(v->Get(i)) };
        const auto pos{ common::toUnderlying(ref.model_) };
        refs_[pos] = move(ref);
    }
    refMinimal_ = initWeaponReference(fb->ref_minimal_values(), false);
    refDefault_ = initWeaponReference(fb->ref_default_values(), false);
    initWeaponReference(fb->sample_of_all_fields(), false);
}

WeaponReference WeaponReferenceContainer::initWeaponReference(
    const fbWeapon::FB_WeaponReference* fb,
    const bool verify)
{
    assert(fb != nullptr);
    WeaponReference ref;

    ref.model_  = toWeaponModel(fb->weapon_model());
    ref.type_   = toWeaponType(fb->weapon_type());
    assert((verify ? common::isValidEnum(ref.model_) : true));
    assert((verify ? common::isValidEnum(ref.type_) : true));

    const auto* modTypes{ fb->weapon_mod_types() };
    assert(modTypes != nullptr);
    assert(modTypes->size() <= ref.weaponModTypes_.size());
    for (size_t i = 0; i < modTypes->size(); ++i) {
        ref.weaponModTypes_[i] = toWeaponModType(
            static_cast<fbWeaponMod::FB_WeaponModType>(modTypes->Get(i))
        );
        assert((verify ? common::isValidEnum(ref.weaponModTypes_[i]) : true));
    }

    initWeaponRequirements(fb->weapon_requirements(), ref.requirements_, verify);

    const auto* penalties{ fb->weapon_penalties() };
    assert(penalties != nullptr);
    ref.penalties_.mulCritDmg_  = { penalties->multiplier_crit_dmg() };
    ref.penalties_.chaHit_      = { penalties->chance_hit() };
    ref.penalties_.chaCritDmg_  = { penalties->chance_crit_dmg() };
    ref.penalties_.strike_      = { penalties->strike_rate() };

    ref.attack_ = Attack::initAttack(fb->attack(), verify);

    common::initLanguageBundle(fb->name(), ref.name_);
    common::initLanguageBundle(fb->descrip(), ref.descrip_);

    ref.dmgMin_         = { fb->dmg_min() };
    ref.dmgMax_         = { fb->dmg_max() };
    ref.price_          = { fb->price() };
    ref.capAmmo_        = { fb->capacity_ammo() };
    ref.mulCritDmg_     = { fb->multiplier_crit_dmg() };
    ref.chaHit_         = { fb->chance_hit() };
    ref.chaCritDmg_     = { fb->chance_crit_dmg() };
    ref.bonSneakDmg_    = { fb->bonus_sneak_dmg() };
    ref.bonNormDmg_     = { fb->bonus_normal_dmg() };
    ref.bonMeleeDmg_    = { fb->bonus_melee_dmg() };
    ref.bonRangeDmg_    = { fb->bonus_range_dmg() };
    ref.level_          = { fb->weapon_level() };
    ref.armorPen_       = { fb->armor_penetration() };
    ref.apAttack_       = { fb->ap_per_attack() };
    ref.apReload_       = { fb->ap_per_reload() };
    ref.shoPerAttack_   = { fb->shots_per_attack() };
    ref.tyAmmo_         = toAmmoType(fb->ammo_type());
    ref.tyDmg_          = toDamageType(fb->dmg_type());
    assert((verify ? common::isValidEnum(ref.tyAmmo_) : true));
    assert((verify ? common::isValidEnum(ref.tyDmg_) : true));

    ref.initialized_    = true;
    return ref;
}

void WeaponReferenceContainer::initWeaponRequirements(
    const fbWeapon::FB_WeaponRequirements* fb,
    WeaponRequirements& requirements,
    const bool verify)
{
    assert(fb != nullptr);
    if (fb->skill() != nullptr) {
        const auto* ptr{ fb->skill() };
        assert(ptr->size() <= requirements.skillReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            requirements.skillReq_[i].first     = toSkillType(ptr->Get(i)->type());
            requirements.skillReq_[i].second    = { ptr->Get(i)->level() };
            assert((verify ? common::isValidEnum(requirements.skillReq_[i].first) : true));
        }
    }
    if (fb->attr() != nullptr) {
        const auto* ptr{ fb->attr() };
        assert(ptr->size() <= requirements.attrReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            requirements.attrReq_[i].first  = toAttributeType(ptr->Get(i)->type());
            requirements.attrReq_[i].second = { ptr->Get(i)->level() };
            assert((verify ? common::isValidEnum(requirements.attrReq_[i].first) : true));
        }
    }
}

} // namespace object
} // namespace game
