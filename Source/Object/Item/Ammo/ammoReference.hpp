
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_REFERENCE_HPP
#define AMMO_REFERENCE_HPP

#include"ammoCommon.hpp"
#include"ammoReferenceFB_generated.h"
#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>
#include<type_traits>
#include<vector>

namespace game {
namespace object {

struct AmmoReference {
public:
    using text                  = common::Text;

private:
    using language_bundle       = std::array<text, global::PlainText::sizeLang_>;

    friend class AmmoReferenceContainer;

public:
    AmmoReference() noexcept;

    AmmoReference(const AmmoReference&) = delete;
    AmmoReference& operator=(const AmmoReference&) = delete;
    AmmoReference(AmmoReference&&) = default;
    AmmoReference& operator=(AmmoReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

    const text& name() const noexcept;

    const text& descr() const noexcept;

public:
    Ammo__Type              type_;          // ammo type (kind)
    common::Price           price_;

private:
    language_bundle         name_;          // weapon name
    language_bundle         descrip_;       // description

    bool                    initialized_;
};

///************************************************************************************************

class AmmoReferenceContainer {
private:
    using language = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

public:
    AmmoReferenceContainer() noexcept {}

    AmmoReferenceContainer(const AmmoReferenceContainer&) = delete;
    AmmoReferenceContainer& operator=(const AmmoReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const AmmoReference& ammoReference(Ammo__Type id) noexcept;

private:
    static void setLanguage(language lang) noexcept;

    static void initContainer(const fbAmmo::FB_AmmoReferenceContainer* container);

    static AmmoReference initAmmoReference(
        const fbAmmo::FB_AmmoReference* reference
    );

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::vector<AmmoReference>               refs_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const AmmoReference::text& AmmoReference::name() const noexcept
{
    return name_[AmmoReferenceContainer::languageIndex()];
}

inline const AmmoReference::text& AmmoReference::descr() const noexcept
{
    return descrip_[AmmoReferenceContainer::languageIndex()];
}

///************************************************************************************************

inline const AmmoReference& AmmoReferenceContainer::ammoReference(
    Ammo__Type id
) noexcept {
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

inline void AmmoReferenceContainer::setLanguage(
    AmmoReferenceContainer::language lang
) noexcept {
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !AMMO_REFERENCE_HPP
