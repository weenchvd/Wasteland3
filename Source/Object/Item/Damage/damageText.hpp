
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DAMAGE_TEXT_HPP
#define DAMAGE_TEXT_HPP

#include"common.hpp"
#include"damageCommon.hpp"
#include"damageTextFB_generated.h"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace object {

class DamageTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class DamageText;

private:
    DamageTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& damageVsRobots() const noexcept { return dmgRobots_[li()]; }

    const text_t& damageVsVehicles() const noexcept { return dmgVehicles_[li()]; }

    const text_t& damageVsHumans() const noexcept { return dmgHumans_[li()]; }

    const text_t& damageVsAnimals() const noexcept { return dmgAnimals_[li()]; }

    const text_t& damageVsMutants() const noexcept { return dmgMutants_[li()]; }

private:
    language_bundle_t dmgRobots_;
    language_bundle_t dmgVehicles_;
    language_bundle_t dmgHumans_;
    language_bundle_t dmgAnimals_;
    language_bundle_t dmgMutants_;
};

///************************************************************************************************

class DamageText {
private:
    friend class Damage;

private:
    DamageText() noexcept {}

public:
    DamageText(const DamageText&) = delete;
    DamageText& operator=(const DamageText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const DamageTextCommon& common() noexcept { return common_; }

private:
    static void initCommon(const fbDamage::FB_DamageTextCommon* fb);

private:
    static global::PlainTextBase                    base_;
    static DamageTextCommon                         common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline DamageTextCommon::language_index_t DamageTextCommon::li() const noexcept
{
    return { DamageText::languageIndex() };
}

} // namespace object
} // namespace game

#endif // !DAMAGE_TEXT_HPP
