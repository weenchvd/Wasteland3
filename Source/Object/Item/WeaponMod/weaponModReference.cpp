
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"weaponModPath.hpp"
#include"weaponModReference.hpp"
#include<memory>
#include<stdlib.h>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase               WeaponModReferenceContainer::base_;
vector<WeaponModReference>          WeaponModReferenceContainer::refs_;
WeaponModReference                  WeaponModReferenceContainer::refDefault_;
bool                                WeaponModReferenceContainer::initialized_{ false };

///************************************************************************************************

WeaponModRequirements::WeaponModRequirements()
    :
    skillReq_       {},
    attrReq_        {}
{
    skillReq_.fill(skill_requirement_t{ Skill::Type::INVALID, common::LevelSkill{ 0 } });
    attrReq_.fill(attribute_requirement_t{ Attribute::Type::INVALID, common::LevelStat{ 0 } });
}

///************************************************************************************************

WeaponModReference::WeaponModReference()
    :
    model_          { WeaponMod__Model::INVALID },
    type_           { WeaponMod__Type::INVALID },
    requirements_   {},
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
    if (isInitialized()) return;
    base_.initialize();
    Attack::initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(WEAPON_MOD_REF_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              WEAPON_MOD_REF_FB_BIN_FILE__HASH);
    const fbWeaponMod::FB_WeaponModReferenceContainer* fb{
        fbWeaponMod::GetFB_WeaponModReferenceContainer(buffer.get())
    };

    initContainer(fb);

    initialized_ = true;
}

void WeaponModReferenceContainer::initContainer(
    const fbWeaponMod::FB_WeaponModReferenceContainer* fb)
{
    assert(fb != nullptr);
    refs_.resize(common::numberOf<WeaponMod__Model>());
    const auto* v{ fb->ref_values() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        WeaponModReference ref{ initWeaponModReference(v->Get(i)) };
        const auto pos{ common::toUnderlying(ref.model_) };
        refs_[pos] = move(ref);
    }
    refDefault_ = initWeaponModReference(fb->ref_default_values(), false);
    initWeaponModReference(fb->sample_of_all_fields(), false);
}

WeaponModReference WeaponModReferenceContainer::initWeaponModReference(
    const fbWeaponMod::FB_WeaponModReference* fb,
    const bool verify)
{
    assert(fb != nullptr);
    WeaponModReference ref;

    ref.model_  = toWeaponModModel(fb->weapon_mod_model());
    ref.type_   = toWeaponModType(fb->weapon_mod_type());
    assert((verify ? common::isValidEnum(ref.model_) : true));
    assert((verify ? common::isValidEnum(ref.type_) : true));

    initWeaponModRequirements(fb->weapon_mod_requirements(), ref.requirements_, verify);

    ref.attack_ = Attack::initAttack(fb->attack(), false);

    common::initLanguageBundle(fb->name(), ref.name_);
    common::initLanguageBundle(fb->descrip(), ref.descrip_);

    ref.dmgMin_         = common::Damage        { fb->dmg_min() };
    ref.dmgMax_         = common::Damage        { fb->dmg_max() };
    ref.price_          = common::Price         { fb->price() };
    ref.capAmmo_        = common::Capacity      { fb->capacity_ammo() };
    ref.mulCritDmg_     = common::Multiplier    { fb->multiplier_crit_dmg() };
    ref.chaHit_         = common::Chance        { fb->chance_hit() };
    ref.chaCritDmg_     = common::Chance        { fb->chance_crit_dmg() };
    ref.bonSneakDmg_    = common::Bonus         { fb->bonus_sneak_dmg() };
    ref.bonNormDmg_     = common::Bonus         { fb->bonus_normal_dmg() };
    ref.bonMeleeDmg_    = common::Bonus         { fb->bonus_melee_dmg() };
    ref.bonRangeDmg_    = common::Bonus         { fb->bonus_range_dmg() };
    ref.armorPen_       = common::Armor         { fb->armor_penetration() };
    ref.apAttack_       = common::ActionPoint   { fb->ap_per_attack() };
    ref.apReload_       = common::ActionPoint   { fb->ap_per_reload() };
    ref.shoPerAttack_   = common::NumberShots   { fb->shots_per_attack() };
    ref.tyAmmo_         = toAmmoType(fb->ammo_type());
    ref.tyDmg_          = toDamageType(fb->dmg_type());

    ref.initialized_    = true;
    return ref;
}

void WeaponModReferenceContainer::initWeaponModRequirements(
    const fbWeaponMod::FB_WeaponModRequirements* fb,
    WeaponModRequirements& requirements,
    const bool verify)
{
    assert(fb != nullptr);
    if (fb->skill() != nullptr) {
        const auto* ptr{ fb->skill() };
        assert(ptr->size() <= requirements.skillReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            requirements.skillReq_[i].first     = toSkillType(ptr->Get(i)->type());
            requirements.skillReq_[i].second    = common::LevelSkill{ ptr->Get(i)->level() };
            assert((verify ? common::isValidEnum(requirements.skillReq_[i].first) : true));
        }
    }
    if (fb->attr() != nullptr) {
        const auto* ptr{ fb->attr() };
        assert(ptr->size() <= requirements.attrReq_.size());
        for (size_t i = 0; i < ptr->size(); ++i) {
            requirements.attrReq_[i].first  = toAttributeType(ptr->Get(i)->type());
            requirements.attrReq_[i].second = common::LevelStat{ ptr->Get(i)->level() };
            assert((verify ? common::isValidEnum(requirements.attrReq_[i].first) : true));
        }
    }
}

} // namespace object
} // namespace game
