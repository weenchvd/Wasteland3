
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_REFERENCE_HPP
#define WEAPON_REFERENCE_HPP

#include"ammo.hpp"
#include"common.hpp"
#include"damage.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include"weaponCommon.hpp"
#include"weaponMod.hpp"
#include"weaponReferenceFB_generated.h"
#include<array>
#include<assert.h>
#include<vector>

namespace game {
namespace object {

struct WeaponReference {
public:
    static constexpr unsigned char nWMSlots_{ 4 }; // number of weapon mod slots

private:
    using text                  = common::Text;
    using weapon_mod_types      = std::array<WeaponMod::Type, nWMSlots_>;
    using language_bundle       = std::array<text, global::PlainText::sizeLang_>;

    friend class WeaponReferenceContainer;

public:
    WeaponReference() noexcept;

    WeaponReference(const WeaponReference&) = delete;
    WeaponReference& operator=(const WeaponReference&) = delete;
    WeaponReference(WeaponReference&&) = default;
    WeaponReference& operator=(WeaponReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

    const text& name() const noexcept;

    const text& descr() const noexcept;

public:
    Weapon__Model           model_;         // weapon model
    Weapon__Type            type_;          // weapon type (kind)
    weapon_mod_types        weaponModTypes_;// list of slot types

    common::Damage          dmgMin_;        // min damage per hit
    common::Damage          dmgMax_;        // max damage per hit
    common::Price           price_;         // price
    common::Range           rangeAttack_;   // attack range
    common::Capacity        capAmmo_;       // ammo capacity
    common::Multiplier      mulCritDmg_;    // critical damage multiplier
    common::Chance          chaHit_;        // base hit chance
    common::Chance          chaCritDmg_;    // base critical damage chance
    common::Level           level_;         // weapon level
    common::Level           levSkill_;      // min level of skill
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

class WeaponReferenceContainer {
private:
    using language      = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

public:
    WeaponReferenceContainer() noexcept {}

    WeaponReferenceContainer(const WeaponReferenceContainer&) = delete;
    WeaponReferenceContainer& operator=(const WeaponReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static bool languageIndex() noexcept { return langIndex_; }

    static const WeaponReference& weaponReference(Weapon__Model id) noexcept;

    static const WeaponReference& weaponReferenceMinimal() noexcept;

private:
    static void setLanguage(language lang);

    static void initContainer(const fbWeapon::FB_WeaponReferenceContainer* container);

    static WeaponReference initWeaponReference(
        const fbWeapon::FB_WeaponReference* reference
    );

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::vector<WeaponReference>             refs_;
    static WeaponReference                          refMinimal_;
    static unsigned char                            langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const WeaponReference::text& WeaponReference::name() const noexcept
{
    return name_[WeaponReferenceContainer::languageIndex()];
}

inline const WeaponReference::text& WeaponReference::descr() const noexcept
{
    return descrip_[WeaponReferenceContainer::languageIndex()];
}

///************************************************************************************************

inline const WeaponReference& WeaponReferenceContainer::weaponReference(Weapon__Model id) noexcept {
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

inline const WeaponReference& WeaponReferenceContainer::weaponReferenceMinimal() noexcept {
    return refMinimal_;
}

inline void WeaponReferenceContainer::setLanguage(WeaponReferenceContainer::language lang)
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !WEAPON_REFERENCE_HPP
