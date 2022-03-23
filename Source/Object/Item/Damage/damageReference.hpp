
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DAMAGE_REFERENCE_HPP
#define DAMAGE_REFERENCE_HPP

#include"common.hpp"
#include"damageCommon.hpp"
#include"damageReferenceFB_generated.h"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>
#include<type_traits>
#include<utility>
#include<vector>

namespace game {
namespace object {

struct DamageReference {
public:
    using text                  = common::Text;

private:
    using language_bundle       = std::array<text, global::PlainText::sizeLang_>;

    friend class DamageReferenceContainer;

public:
    DamageReference() noexcept;

    DamageReference(const DamageReference&) = delete;
    DamageReference& operator=(const DamageReference&) = delete;
    DamageReference(DamageReference&&) = default;
    DamageReference& operator=(DamageReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

    const text& name() const noexcept;

    const text& descr() const noexcept;

public:
    Damage__Type            type_;          // damage type
    common::Bonus           dmgRobots_;     // damage bonus vs robots
    common::Bonus           dmgVehicles_;   // damage bonus vs vehicles
    common::Bonus           dmgHumans_;     // damage bonus vs humans
    common::Bonus           dmgAnimals_;    // damage bonus vs animals
    common::Bonus           dmgMutants_;    // damage bonus vs mutants

private:
    language_bundle         name_;          // damage name
    language_bundle         descrip_;       // description

    bool                    initialized_;
};

///************************************************************************************************

class DamageReferenceContainer {
private:
    using language = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

public:
    DamageReferenceContainer() noexcept {}

    DamageReferenceContainer(const DamageReferenceContainer&) = delete;
    DamageReferenceContainer& operator=(const DamageReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const DamageReference& damageReference(Damage__Type id) noexcept;

    static const DamageReference& damageReferenceDefault() noexcept { return refDefault_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initContainer(const fbDamage::FB_DamageReferenceContainer* fb);

    static DamageReference initDamageReference(
        const fbDamage::FB_DamageReference* fb,
        const bool assert = true
    );

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::vector<DamageReference>             refs_;
    static DamageReference                          refDefault_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const DamageReference::text& DamageReference::name() const noexcept
{
    return name_[DamageReferenceContainer::languageIndex()];
}

inline const DamageReference::text& DamageReference::descr() const noexcept
{
    return descrip_[DamageReferenceContainer::languageIndex()];
}

///************************************************************************************************

inline const DamageReference& DamageReferenceContainer::damageReference(
    Damage__Type id
) noexcept {
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

inline void DamageReferenceContainer::setLanguage(
    DamageReferenceContainer::language lang
) noexcept {
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !DAMAGE_REFERENCE_HPP
