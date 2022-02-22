
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_TEXT_HPP
#define WEAPON_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include"weaponCommon.hpp"
#include"weaponTextFB_generated.h"
#include<array>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

struct WeaponTextPenalties {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class WeaponText;

public:
    WeaponTextPenalties() noexcept {}

    const text& critDamage() const noexcept;

    const text& hitChance() const noexcept;

    const text& critChance() const noexcept;

    const text& strikeRate() const noexcept;

private:
    language_bundle critDmg_;
    language_bundle hitChance_;
    language_bundle critChance_;
    language_bundle strikeRate_;
};

///************************************************************************************************

struct WeaponTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class WeaponText;

public:
    WeaponTextCommon() noexcept {}

    const text& damage() const noexcept;

    const text& level() const noexcept;

    const text& ap() const noexcept;

    const text& apReload() const noexcept;

    const text& require() const noexcept;

    const text& installedMods() const noexcept;

    const text& ammoCapacity() const noexcept;

    const text& ammoType() const noexcept;

    const text& range() const noexcept;

    const text& penalty() const noexcept;

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
    language_bundle damage_;
    language_bundle level_;
    language_bundle ap_;
    language_bundle apReload_;
    language_bundle require_;
    language_bundle mods_;
    language_bundle ammoCap_;
    language_bundle ammoType_;
    language_bundle range_;
    language_bundle penalty_;
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

class WeaponText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_     { global::PlainText::sizeLang_ };
    static constexpr auto sizeType_     { common::toUnderlying(Weapon__Type::NUMBER_OF) };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    WeaponText() noexcept {}

    WeaponText(const WeaponText&) = delete;
    WeaponText& operator=(const WeaponText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const text& type(Weapon__Type id) noexcept;

    static const WeaponTextPenalties& penalties() noexcept { return penalties_; }

    static const WeaponTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initByType(
        const fbWeapon::FB_WeaponTextType* table,
        std::array<language_bundle, sizeType_>& ar
    );

    static void initPenalties(const fbWeapon::FB_WeaponTextPenalties* table);

    static void initCommon(const fbWeapon::FB_WeaponTextCommon* table);

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::array<language_bundle, sizeType_>   type_;
    static WeaponTextPenalties                      penalties_;
    static WeaponTextCommon                         common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const WeaponTextCommon::text& WeaponTextCommon::damage() const noexcept
{
    return damage_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::level() const noexcept
{
    return level_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::ap() const noexcept
{
    return ap_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::apReload() const noexcept
{
    return apReload_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::require() const noexcept
{
    return require_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::installedMods() const noexcept
{
    return mods_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::ammoCapacity() const noexcept
{
    return ammoCap_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::ammoType() const noexcept
{
    return ammoType_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::range() const noexcept
{
    return range_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::penalty() const noexcept
{
    return penalty_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::hitChance() const noexcept
{
    return hitChance_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::critDamage() const noexcept
{
    return critDamage_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::critChance() const noexcept
{
    return critChance_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::penetration() const noexcept
{
    return penet_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::damageVsRobots() const noexcept
{
    return dmgRobots_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::damageVsSynths() const noexcept
{
    return dmgSynths_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::damageVsVehicles() const noexcept
{
    return dmgVehicles_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::damageVsHumans() const noexcept
{
    return dmgHumans_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::damageVsAnimals() const noexcept
{
    return dmgAnimals_[WeaponText::languageIndex()];
}

inline const WeaponTextCommon::text& WeaponTextCommon::damageVsMutants() const noexcept
{
    return dmgMutants_[WeaponText::languageIndex()];
}

///************************************************************************************************

inline const WeaponTextPenalties::text& WeaponTextPenalties::critDamage() const noexcept
{
    return critDmg_[WeaponText::languageIndex()];
}

inline const WeaponTextPenalties::text& WeaponTextPenalties::hitChance() const noexcept
{
    return hitChance_[WeaponText::languageIndex()];
}

inline const WeaponTextPenalties::text& WeaponTextPenalties::critChance() const noexcept
{
    return critChance_[WeaponText::languageIndex()];
}

inline const WeaponTextPenalties::text& WeaponTextPenalties::strikeRate() const noexcept
{
    return strikeRate_[WeaponText::languageIndex()];
}

///************************************************************************************************

inline const WeaponText::text& WeaponText::type(Weapon__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return type_[common::toUnderlying(id)][langIndex_];
}

inline void WeaponText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !WEAPON_TEXT_HPP
