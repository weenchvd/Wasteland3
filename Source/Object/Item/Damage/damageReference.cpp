
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"damagePath.hpp"
#include"damageReference.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include<memory>
#include<stdlib.h>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase               DamageReferenceContainer::base_;
vector<DamageReference>             DamageReferenceContainer::refs_;
DamageReference                     DamageReferenceContainer::refDefault_;
bool                                DamageReferenceContainer::initialized_{ false };

///************************************************************************************************

DamageReference::DamageReference() noexcept
    :
    type_           { Damage__Type::INVALID },
    name_           {},
    descrip_        {},
    dmgRobots_      { 0 },
    dmgVehicles_    { 0 },
    dmgHumans_      { 0 },
    dmgAnimals_     { 0 },
    dmgMutants_     { 0 },
    initialized_    { false }
{}

///************************************************************************************************

void DamageReferenceContainer::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(DAMAGE_REF_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              DAMAGE_REF_FB_BIN_FILE__HASH);
    const fbDamage::FB_DamageReferenceContainer* fb{
        fbDamage::GetFB_DamageReferenceContainer(buffer.get())
    };

    initContainer(fb);

    initialized_ = true;
}

void DamageReferenceContainer::initContainer(
    const fbDamage::FB_DamageReferenceContainer* fb)
{
    assert(fb != nullptr);
    refs_.resize(common::numberOf<Damage__Type>());
    const auto* v{ fb->refs() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        DamageReference ref{ initDamageReference(v->Get(i)) };
        const auto pos{ common::toUnderlying(ref.type_) };
        refs_[pos] = move(ref);
    }
    refDefault_ = initDamageReference(fb->ref_default(), false);
}

DamageReference DamageReferenceContainer::initDamageReference(
    const fbDamage::FB_DamageReference* fb, const bool verify)
{
    assert(fb != nullptr);
    DamageReference ref;

    ref.type_           = toDamageType(fb->dmg_type());
    assert((verify ? common::isValidEnum(ref.type_) : true));

    common::initLanguageBundle(fb->name(), ref.name_);
    common::initLanguageBundle(fb->descrip(), ref.descrip_);

    ref.dmgRobots_      = { fb->damage_vs_robots() };
    ref.dmgVehicles_    = { fb->damage_vs_vehicles() };
    ref.dmgHumans_      = { fb->damage_vs_humans() };
    ref.dmgAnimals_     = { fb->damage_vs_animals() };
    ref.dmgMutants_     = { fb->damage_vs_mutants() };

    ref.initialized_    = true;
    return ref;
}

} // namespace object
} // namespace game
