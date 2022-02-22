
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_REFERENCE_HPP
#define WEAPON_MOD_REFERENCE_HPP

#include"ammo.hpp"
#include"attribute.hpp"
#include"common.hpp"
#include"damage.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include"skill.hpp"
#include"weaponModCommon.hpp"
#include"weaponModReferenceFB_generated.h"
#include<array>
#include<assert.h>
#include<type_traits>
#include<utility>
#include<vector>

namespace game {
namespace object {

struct WeaponModRequirements {
public:
    using skill_requirement         = std::pair<Skill::Type, common::LevelSkill>;
    using attribute_requirement     = std::pair<Attribute::Type, common::LevelStat>;

public:
    WeaponModRequirements() noexcept;

public:
    std::array<skill_requirement, 2>        skillReq_;
    std::array<attribute_requirement, 2>    attrReq_;
};

///************************************************************************************************

struct WeaponModReference {
public:
    using text                  = common::Text;

private:
    using language_bundle       = std::array<text, global::PlainText::sizeLang_>;

    friend class WeaponModReferenceContainer;

public:
    WeaponModReference() noexcept;

    WeaponModReference(const WeaponModReference&) = delete;
    WeaponModReference& operator=(const WeaponModReference&) = delete;
    WeaponModReference(WeaponModReference&&) = default;
    WeaponModReference& operator=(WeaponModReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

    const text& name() const noexcept;

    const text& descr() const noexcept;

public:
    WeaponMod__Model        model_;         // weapon mod model
    WeaponMod__Type         type_;          // weapon mod type (kind)
    WeaponModRequirements   requirements_;

    common::Damage          dmgMin_;        // min damage per hit
    common::Damage          dmgMax_;        // max damage per hit
    common::Price           price_;         // price
    common::Range           rangeAttack_;   // attack range
    common::Capacity        capAmmo_;       // ammo capacity
    common::Multiplier      mulCritDmg_;    // critical damage multiplier
    common::Chance          chaHit_;        // base hit chance
    common::Chance          chaCritDmg_;    // base critical damage chance
    common::Armor           armorPen_;      // penetration
    common::ActionPoint     apAttack_;      // action points per attack
    common::ActionPoint     apReload_;      // action points per reload
    common::NumberShots     shoPerAttack_;  // number of shots per attack
    Ammo::Type              tyAmmo_;        // ammo type
    Damage::Type            tyDmg_;         // damage type

private:
    language_bundle         name_;          // weapon name
    language_bundle         descrip_;       // description

    bool                    initialized_;
};

///************************************************************************************************

class WeaponModReferenceContainer {
private:
    using language = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

public:
    WeaponModReferenceContainer() noexcept {}

    WeaponModReferenceContainer(const WeaponModReferenceContainer&) = delete;
    WeaponModReferenceContainer& operator=(const WeaponModReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const WeaponModReference& weaponModReference(WeaponMod__Model id) noexcept;

private:
    static void setLanguage(language lang) noexcept;

    static void initContainer(const fbWeaponMod::FB_WeaponModReferenceContainer* container);

    static WeaponModReference initWeaponModReference(
        const fbWeaponMod::FB_WeaponModReference* reference
    );

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::vector<WeaponModReference>          refs_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const WeaponModReference::text& WeaponModReference::name() const noexcept
{
    return name_[WeaponModReferenceContainer::languageIndex()];
}

inline const WeaponModReference::text& WeaponModReference::descr() const noexcept
{
    return descrip_[WeaponModReferenceContainer::languageIndex()];
}

///************************************************************************************************

inline const WeaponModReference& WeaponModReferenceContainer::weaponModReference(
    WeaponMod__Model id
) noexcept {
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

inline void WeaponModReferenceContainer::setLanguage(
    WeaponModReferenceContainer::language lang
) noexcept {
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !WEAPON_MOD_REFERENCE_HPP
