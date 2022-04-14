
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_TEXT_HPP
#define WEAPON_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include"weaponCommon.hpp"
#include"weaponTextFB_generated.h"
#include<array>

namespace game {
namespace object {

class WeaponTextPenalties {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class WeaponText;

private:
    WeaponTextPenalties() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& critDamage() const noexcept { return critDmg_[li()]; }

    const text_t& hitChance() const noexcept { return hitChance_[li()]; }

    const text_t& critChance() const noexcept { return critChance_[li()]; }

    const text_t& strikeRate() const noexcept { return strikeRate_[li()]; }

private:
    language_bundle_t critDmg_;
    language_bundle_t hitChance_;
    language_bundle_t critChance_;
    language_bundle_t strikeRate_;
};

///************************************************************************************************

class WeaponTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class WeaponText;

private:
    WeaponTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& itemType() const noexcept { return itemType_[li()]; }

    const text_t& level() const noexcept { return level_[li()]; }

    const text_t& damage() const noexcept { return damage_[li()]; }

    const text_t& ap() const noexcept { return ap_[li()]; }

    const text_t& apReload() const noexcept { return apReload_[li()]; }

    const text_t& require() const noexcept { return require_[li()]; }

    const text_t& installedMods() const noexcept { return mods_[li()]; }

    const text_t& ammoCapacity() const noexcept { return ammoCap_[li()]; }

    const text_t& ammoType() const noexcept { return ammoType_[li()]; }

    const text_t& penalty() const noexcept { return penalty_[li()]; }

    const text_t& hitChance() const noexcept { return hitChance_[li()]; }

    const text_t& critDamage() const noexcept { return critDamage_[li()]; }

    const text_t& critChance() const noexcept { return critChance_[li()]; }

    const text_t& bonSneakDamage() const noexcept { return bonSneakDmg_[li()]; }

    const text_t& bonNormDamage() const noexcept { return bonNormDmg_[li()]; }

    const text_t& bonMeleeDamage() const noexcept { return bonMeleeDmg_[li()]; }

    const text_t& bonRangeDamage() const noexcept { return bonRangeDmg_[li()]; }

    const text_t& penetration() const noexcept { return penet_[li()]; }

private:
    language_bundle_t itemType_;
    language_bundle_t level_;
    language_bundle_t damage_;
    language_bundle_t ap_;
    language_bundle_t apReload_;
    language_bundle_t require_;
    language_bundle_t mods_;
    language_bundle_t ammoCap_;
    language_bundle_t ammoType_;
    language_bundle_t penalty_;
    language_bundle_t hitChance_;
    language_bundle_t critDamage_;
    language_bundle_t critChance_;
    language_bundle_t bonSneakDmg_;
    language_bundle_t bonNormDmg_;
    language_bundle_t bonMeleeDmg_;
    language_bundle_t bonRangeDmg_;
    language_bundle_t penet_;
};

///************************************************************************************************

class WeaponText {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;

    static constexpr auto sizeType_{ common::numberOf<Weapon__Type>() };

    friend class Weapon;

private:
    WeaponText() noexcept {}

public:
    WeaponText(const WeaponText&) = delete;
    WeaponText& operator=(const WeaponText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const text_t& type(Weapon__Type id) noexcept;

    static const WeaponTextPenalties& penalties() noexcept { return penalties_; }

    static const WeaponTextCommon& common() noexcept { return common_; }

private:
    static void initByType(
        const fbWeapon::FB_WeaponTextType* fb,
        std::array<language_bundle_t, sizeType_>& ar
    );

    static void initPenalties(const fbWeapon::FB_WeaponTextPenalties* fb);

    static void initCommon(const fbWeapon::FB_WeaponTextCommon* fb);

private:
    static global::PlainTextBase                    base_;
    static std::array<language_bundle_t, sizeType_> type_;
    static WeaponTextPenalties                      penalties_;
    static WeaponTextCommon                         common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline WeaponTextPenalties::language_index_t WeaponTextPenalties::li() const noexcept
{
    return { WeaponText::languageIndex() };
}

inline WeaponTextCommon::language_index_t WeaponTextCommon::li() const noexcept
{
    return { WeaponText::languageIndex() };
}

///************************************************************************************************

inline const WeaponText::text_t& WeaponText::type(Weapon__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return type_[common::toUnderlying(id)][languageIndex()];
}

} // namespace object
} // namespace game

#endif // !WEAPON_TEXT_HPP
