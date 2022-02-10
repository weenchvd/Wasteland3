
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_REFERENCE_HPP
#define WEAPON_REFERENCE_HPP

#include"ammo.hpp"
#include"common.hpp"
#include"damage.hpp"
//#include"item.hpp"
#include"locator.hpp"
#include"observerDLL.hpp"
#include"weaponCommon.hpp"
#include"weaponMod.hpp"
#include"weaponReferenceFB_generated.h"
#include<array>
#include<vector>

namespace game {
namespace object {

class WeaponReferenceContainer;

struct WeaponReference {
public:
    using text = common::Text;

    static constexpr unsigned int nWMSlots_{ 4 }; // number of weapon mod slots
    using Slot_WeaponModTypes = std::array<WeaponMod::Type, nWMSlots_>;

    static constexpr unsigned char sizeLang_{
        common::toUnderlying(global::PlainText::Language::NUMBER_OF)
    };

    friend class WeaponReferenceContainer;

    WeaponReference() noexcept
        :
        model_          { Weapon__Model::INVALID },
        type_           { Weapon__Type::INVALID },
        weaponModTypes_ { WeaponMod::Type::INVALID,
                          WeaponMod::Type::INVALID,
                          WeaponMod::Type::INVALID,
                          WeaponMod::Type::INVALID },
        name_           {},
        descrip_        {},
        dmgMin_         { 0 },
        dmgMax_         { 0 },
        price_          { 0 },
        rangeAttack_    { 0 },
        capAmmo_        { 0 },
        mulCritDmg_     { 0 },
        chaHit_         { 0 },
        chaCritDmg_     { 0 },
        level_          { 0 },
        levSkill_       { 0 },
        armorPen_       { 0 },
        apAttack_       { 0 },
        apReload_       { 0 },
        shoPerAttack_   { 0 },
        tyAmmo_         { Ammo::Type::INVALID },
        tyDmg_          { Damage::Type::INVALID },
        initialized_    { false }
    {}

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
    Slot_WeaponModTypes     weaponModTypes_;// list of slot types

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
    std::array<text, sizeLang_>     name_;      // weapon name
    std::array<text, sizeLang_>     descrip_;   // description

    bool                    initialized_;
};


class WeaponReferenceContainer {
public:
    using text          = common::Text;
    using language      = global::PlainText::Language;

    static constexpr unsigned char sizeLang_{ common::toUnderlying(language::NUMBER_OF) };

    WeaponReferenceContainer() noexcept {}

    WeaponReferenceContainer(const WeaponReferenceContainer&) = delete;
    WeaponReferenceContainer& operator=(const WeaponReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static bool languageIndex() noexcept { return langIndex_; }

    static const WeaponReference& weaponReference(Weapon__Model id) noexcept {
        return refs_[common::toUnderlying(id)];
    }

    static const WeaponReference& weaponReferenceMinimal() noexcept {
        return refMinimal_;
    }

private:
    static void setLanguage(language lang);

    static void initContainer(const fbWeapon::FB_WeaponReferenceContainer* container);
    static WeaponReference initWeaponReference(
        const fbWeapon::FB_WeaponReference* reference
    );
    static void initLanguageBundle(
        const fbWeapon::FB_LanguageBundle* bundle,
        std::array<text, sizeLang_>& target
    );

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::vector<WeaponReference>             refs_;
    static WeaponReference                          refMinimal_;
    static unsigned char                            langIndex_;
    static bool                                     initialized_;
};

} // namespace object
} // namespace game

#endif // !WEAPON_REFERENCE_HPP
