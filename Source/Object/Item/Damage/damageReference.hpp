
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DAMAGE_REFERENCE_HPP
#define DAMAGE_REFERENCE_HPP

#include"common.hpp"
#include"damageCommon.hpp"
#include"damageReferenceFB_generated.h"
#include"plainTextBase.hpp"
#include<array>
#include<assert.h>
#include<vector>

namespace game {
namespace object {

class DamageReference {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class DamageReferenceContainer;

public:
    DamageReference() noexcept;

    DamageReference(const DamageReference&) = delete;
    DamageReference& operator=(const DamageReference&) = delete;
    DamageReference(DamageReference&&) = default;
    DamageReference& operator=(DamageReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

private:
    language_index_t li() const noexcept;

public:
    const text_t& name() const noexcept { return name_[li()]; }

    const text_t& descr() const noexcept { return descrip_[li()]; }

public:
    Damage__Type            type_;          // damage type
    common::Bonus           dmgRobots_;     // damage bonus vs robots
    common::Bonus           dmgVehicles_;   // damage bonus vs vehicles
    common::Bonus           dmgHumans_;     // damage bonus vs humans
    common::Bonus           dmgAnimals_;    // damage bonus vs animals
    common::Bonus           dmgMutants_;    // damage bonus vs mutants

private:
    language_bundle_t       name_;          // damage name
    language_bundle_t       descrip_;       // description

    bool                    initialized_;
};

///************************************************************************************************

class DamageReferenceContainer {
private:
    friend class Damage;

private:
    DamageReferenceContainer() noexcept {}

public:
    DamageReferenceContainer(const DamageReferenceContainer&) = delete;
    DamageReferenceContainer& operator=(const DamageReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const DamageReference& damageReference(Damage__Type id) noexcept;

    static const DamageReference& damageReferenceDefault() noexcept { return refDefault_; }

private:
    static void initContainer(const fbDamage::FB_DamageReferenceContainer* fb);

    static DamageReference initDamageReference(
        const fbDamage::FB_DamageReference* fb,
        const bool assert = true
    );

private:
    static global::PlainTextBase                    base_;
    static std::vector<DamageReference>             refs_;
    static DamageReference                          refDefault_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline DamageReference::language_index_t DamageReference::li() const noexcept
{
    return { DamageReferenceContainer::languageIndex() };
}

///************************************************************************************************

inline const DamageReference& DamageReferenceContainer::damageReference(
    Damage__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

} // namespace object
} // namespace game

#endif // !DAMAGE_REFERENCE_HPP
