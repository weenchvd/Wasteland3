
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DAMAGE_TEXT_HPP
#define DAMAGE_TEXT_HPP

#include"common.hpp"
#include"damageCommon.hpp"
#include"damageTextFB_generated.h"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

struct DamageTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class DamageText;

public:
    DamageTextCommon() noexcept {}

    const text& damageVsRobots() const noexcept;

    const text& damageVsVehicles() const noexcept;

    const text& damageVsHumans() const noexcept;

    const text& damageVsAnimals() const noexcept;

    const text& damageVsMutants() const noexcept;

private:
    language_bundle dmgRobots_;
    language_bundle dmgVehicles_;
    language_bundle dmgHumans_;
    language_bundle dmgAnimals_;
    language_bundle dmgMutants_;
};

///************************************************************************************************

class DamageText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    DamageText() noexcept {}

    DamageText(const DamageText&) = delete;
    DamageText& operator=(const DamageText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const DamageTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initCommon(const fbDamage::FB_DamageTextCommon* fb);

private:
    static common::ObserverDLL<void, language>      langObs_;

    static DamageTextCommon                         common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************
inline const DamageTextCommon::text& DamageTextCommon::damageVsRobots() const noexcept
{
    return dmgRobots_[DamageText::languageIndex()];
}

inline const DamageTextCommon::text& DamageTextCommon::damageVsVehicles() const noexcept
{
    return dmgVehicles_[DamageText::languageIndex()];
}

inline const DamageTextCommon::text& DamageTextCommon::damageVsHumans() const noexcept
{
    return dmgHumans_[DamageText::languageIndex()];
}

inline const DamageTextCommon::text& DamageTextCommon::damageVsAnimals() const noexcept
{
    return dmgAnimals_[DamageText::languageIndex()];
}

inline const DamageTextCommon::text& DamageTextCommon::damageVsMutants() const noexcept
{
    return dmgMutants_[DamageText::languageIndex()];
}

///************************************************************************************************

inline void DamageText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !DAMAGE_TEXT_HPP
