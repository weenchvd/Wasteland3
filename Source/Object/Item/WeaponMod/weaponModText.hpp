
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_TEXT_HPP
#define WEAPON_MOD_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include"weaponModCommon.hpp"
#include"weaponModTextFB_generated.h"
#include<array>

namespace game {
namespace object {

class WeaponModTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class WeaponModText;

private:
    WeaponModTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& itemType() const noexcept { return itemType_[li()]; }

    const text_t& minDamage() const noexcept { return minDamage_[li()]; }

    const text_t& maxDamage() const noexcept { return maxDamage_[li()]; }

    const text_t& shots() const noexcept { return shoPerAttack_[li()]; }

    const text_t& damageType() const noexcept { return tyDmg_[li()]; }

    const text_t& ap() const noexcept { return ap_[li()]; }

    const text_t& apReload() const noexcept { return apReload_[li()]; }

    const text_t& require() const noexcept { return require_[li()]; }

    const text_t& ammoCapacity() const noexcept { return ammoCap_[li()]; }

    const text_t& ammoType() const noexcept { return ammoType_[li()]; }

    const text_t& range() const noexcept { return range_[li()]; }

    const text_t& hitChance() const noexcept { return hitChance_[li()]; }

    const text_t& critDamage() const noexcept { return critDamage_[li()]; }

    const text_t& critChance() const noexcept { return critChance_[li()]; }

    const text_t& coneAngle() const noexcept { return coneAngle_[li()]; }

    const text_t& bonSneakDamage() const noexcept { return bonSneakDmg_[li()]; }

    const text_t& bonNormDamage() const noexcept { return bonNormDmg_[li()]; }

    const text_t& bonMeleeDamage() const noexcept { return bonMeleeDmg_[li()]; }

    const text_t& bonRangeDamage() const noexcept { return bonRangeDmg_[li()]; }

    const text_t& penetration() const noexcept { return penet_[li()]; }

private:
    language_bundle_t itemType_;
    language_bundle_t minDamage_;
    language_bundle_t maxDamage_;
    language_bundle_t shoPerAttack_;
    language_bundle_t tyDmg_;
    language_bundle_t ap_;
    language_bundle_t apReload_;
    language_bundle_t require_;
    language_bundle_t ammoCap_;
    language_bundle_t ammoType_;
    language_bundle_t range_;
    language_bundle_t hitChance_;
    language_bundle_t critDamage_;
    language_bundle_t critChance_;
    language_bundle_t coneAngle_;
    language_bundle_t bonSneakDmg_;
    language_bundle_t bonNormDmg_;
    language_bundle_t bonMeleeDmg_;
    language_bundle_t bonRangeDmg_;
    language_bundle_t penet_;
};

///************************************************************************************************

class WeaponModText {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;

    static constexpr auto sizeType_{ common::numberOf<WeaponMod__Type>() };

    friend class WeaponMod;

private:
    WeaponModText() noexcept {}

public:
    WeaponModText(const WeaponModText&) = delete;
    WeaponModText& operator=(const WeaponModText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const text_t& type(WeaponMod__Type id) noexcept;

    static const WeaponModTextCommon& common() noexcept { return common_; }

private:
    static void initByType(
        const fbWeaponMod::FB_WeaponModTextType* fb,
        std::array<language_bundle_t, sizeType_>& ar
    );

    static void initCommon(const fbWeaponMod::FB_WeaponModTextCommon* fb);

private:
    static global::PlainTextBase                    base_;
    static std::array<language_bundle_t, sizeType_> type_;
    static WeaponModTextCommon                      common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline WeaponModTextCommon::language_index_t WeaponModTextCommon::li() const noexcept
{
    return { WeaponModText::languageIndex() };
}

///************************************************************************************************

inline const WeaponModText::text_t& WeaponModText::type(WeaponMod__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return type_[common::toUnderlying(id)][WeaponModText::languageIndex()];
}

} // namespace object
} // namespace game

#endif // !WEAPON_MOD_TEXT_HPP
