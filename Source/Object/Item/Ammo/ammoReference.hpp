
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_REFERENCE_HPP
#define AMMO_REFERENCE_HPP

#include"ammoCommon.hpp"
#include"ammoReferenceFB_generated.h"
#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>
#include<assert.h>
#include<vector>

namespace game {
namespace object {

class AmmoReference {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class AmmoReferenceContainer;

public:
    AmmoReference() noexcept;

    AmmoReference(const AmmoReference&) = delete;
    AmmoReference& operator=(const AmmoReference&) = delete;
    AmmoReference(AmmoReference&&) = default;
    AmmoReference& operator=(AmmoReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

private:
    language_index_t li() const noexcept;

public:
    const text_t& name() const noexcept { return name_[li()]; }

    const text_t& descr() const noexcept { return descrip_[li()]; }

public:
    Ammo__Type              type_;          // ammo type (kind)
    common::Price           price_;

private:
    language_bundle_t       name_;          // weapon name
    language_bundle_t       descrip_;       // description

    bool                    initialized_;
};

///************************************************************************************************

class AmmoReferenceContainer {
private:
    friend class Ammo;

private:
    AmmoReferenceContainer() noexcept {}

public:
    AmmoReferenceContainer(const AmmoReferenceContainer&) = delete;
    AmmoReferenceContainer& operator=(const AmmoReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const AmmoReference& ammoReference(Ammo__Type id) noexcept;

private:
    static void initContainer(const fbAmmo::FB_AmmoReferenceContainer* fb);

    static AmmoReference initAmmoReference(const fbAmmo::FB_AmmoReference* fb);

private:
    static global::PlainTextBase                    base_;
    static std::vector<AmmoReference>               refs_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline AmmoReference::language_index_t AmmoReference::li() const noexcept
{
    return { AmmoReferenceContainer::languageIndex() };
}

///************************************************************************************************

inline const AmmoReference& AmmoReferenceContainer::ammoReference(
    Ammo__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

} // namespace object
} // namespace game

#endif // !AMMO_REFERENCE_HPP
