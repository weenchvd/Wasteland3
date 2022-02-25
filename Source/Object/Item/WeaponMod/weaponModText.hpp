
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_TEXT_HPP
#define WEAPON_MOD_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include"weaponModCommon.hpp"
#include"weaponModTextFB_generated.h"
#include<array>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

struct WeaponModTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class WeaponModText;

public:
    WeaponModTextCommon() noexcept {}

    const text& itemType() const noexcept;

    const text& minDamage() const noexcept;

    const text& maxDamage() const noexcept;

    const text& shots() const noexcept;

    const text& damageType() const noexcept;

    const text& ap() const noexcept;

    const text& apReload() const noexcept;

    const text& require() const noexcept;

    const text& ammoCapacity() const noexcept;

    const text& ammoType() const noexcept;

    const text& range() const noexcept;

    const text& hitChance() const noexcept;

    const text& critDamage() const noexcept;

    const text& critChance() const noexcept;

    const text& penetration() const noexcept;

    const text& damageVsRobots() const noexcept;

    const text& damageVsSynths() const noexcept;

    const text& damageVsVehicles() const noexcept;

    const text& damageVsHumans() const noexcept;

    const text& damageVsAnimals() const noexcept;

    const text& damageVsMutants() const noexcept;

private:
    language_bundle itemType_;
    language_bundle minDamage_;
    language_bundle maxDamage_;
    language_bundle shoPerAttack_;
    language_bundle tyDmg_;
    language_bundle ap_;
    language_bundle apReload_;
    language_bundle require_;
    language_bundle ammoCap_;
    language_bundle ammoType_;
    language_bundle range_;
    language_bundle hitChance_;
    language_bundle critDamage_;
    language_bundle critChance_;
    language_bundle penet_;
    language_bundle dmgRobots_;
    language_bundle dmgSynths_;
    language_bundle dmgVehicles_;
    language_bundle dmgHumans_;
    language_bundle dmgAnimals_;
    language_bundle dmgMutants_;
};

///************************************************************************************************

class WeaponModText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_     { global::PlainText::sizeLang_ };
    static constexpr auto sizeType_     { common::numberOf<WeaponMod__Type>() };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    WeaponModText() noexcept {}

    WeaponModText(const WeaponModText&) = delete;
    WeaponModText& operator=(const WeaponModText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const text& type(WeaponMod__Type id) noexcept;

    static const WeaponModTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initByType(
        const fbWeaponMod::FB_WeaponModTextType* table,
        std::array<language_bundle, sizeType_>& ar
    );

    static void initCommon(const fbWeaponMod::FB_WeaponModTextCommon* table);

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::array<language_bundle, sizeType_>   type_;
    static WeaponModTextCommon                      common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const WeaponModTextCommon::text& WeaponModTextCommon::itemType() const noexcept
{
    return itemType_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::minDamage() const noexcept
{
    return minDamage_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::maxDamage() const noexcept
{
    return maxDamage_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::shots() const noexcept
{
    return shoPerAttack_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::damageType() const noexcept
{
    return tyDmg_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::ap() const noexcept
{
    return ap_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::apReload() const noexcept
{
    return apReload_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::require() const noexcept
{
    return require_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::ammoCapacity() const noexcept
{
    return ammoCap_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::ammoType() const noexcept
{
    return ammoType_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::range() const noexcept
{
    return range_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::hitChance() const noexcept
{
    return hitChance_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::critDamage() const noexcept
{
    return critDamage_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::critChance() const noexcept
{
    return critChance_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::penetration() const noexcept
{
    return penet_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::damageVsRobots() const noexcept
{
    return dmgRobots_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::damageVsSynths() const noexcept
{
    return dmgSynths_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::damageVsVehicles() const noexcept
{
    return dmgVehicles_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::damageVsHumans() const noexcept
{
    return dmgHumans_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::damageVsAnimals() const noexcept
{
    return dmgAnimals_[WeaponModText::languageIndex()];
}

inline const WeaponModTextCommon::text& WeaponModTextCommon::damageVsMutants() const noexcept
{
    return dmgMutants_[WeaponModText::languageIndex()];
}

///************************************************************************************************

inline const WeaponModText::text& WeaponModText::type(WeaponMod__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return type_[common::toUnderlying(id)][langIndex_];
}

inline void WeaponModText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !WEAPON_MOD_TEXT_HPP
