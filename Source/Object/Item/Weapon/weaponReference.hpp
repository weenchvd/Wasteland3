
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_REFERENCE_HPP
#define WEAPON_REFERENCE_HPP

#include"ammo.hpp"
#include"attack.hpp"
#include"attribute.hpp"
#include"common.hpp"
#include"damage.hpp"
#include"plainTextBase.hpp"
#include"skill.hpp"
#include"weaponCommon.hpp"
#include"weaponMod.hpp"
#include"weaponReferenceFB_generated.h"
#include<array>
#include<assert.h>
#include<utility>
#include<vector>

namespace game {
namespace object {

class WeaponRequirements {
public:
    using skill_requirement_t       = std::pair<Skill::Type, common::LevelSkill>;
    using attribute_requirement_t   = std::pair<Attribute::Type, common::LevelAttribute>;

    static constexpr auto nSkill_   { 2 };
    static constexpr auto nAttr_    { 2 };

    friend class WeaponReferenceContainer;

public:
    WeaponRequirements();

public:
    const std::array<skill_requirement_t, nSkill_>& skillRequirements() const noexcept {
        return skillReq_;
    }

    const std::array<attribute_requirement_t, nAttr_>& attributeRequirements() const noexcept {
        return attrReq_;
    }

private:
    std::array<skill_requirement_t, nSkill_>    skillReq_;
    std::array<attribute_requirement_t, nAttr_> attrReq_;
};

///************************************************************************************************

class WeaponPenalties {
public:
    WeaponPenalties() noexcept;

    bool isPresented() const noexcept;

public:
    common::Multiplier      mulCritDmg_;    // critical damage multiplier
    common::Chance          chaHit_;        // base hit chance
    common::Chance          chaCritDmg_;    // base critical damage chance
    common::Strike          strike_;        // strike rate
};

///************************************************************************************************

class WeaponReference {
public:
    using text_t = common::Text;

    static constexpr auto nWMSlots_{ 4 }; // number of weapon mod slots

    using weapon_mod_types_t = std::array<WeaponMod::Type, nWMSlots_>;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class WeaponReferenceContainer;

public:
    WeaponReference();

    WeaponReference(const WeaponReference&) = delete;
    WeaponReference& operator=(const WeaponReference&) = delete;
    WeaponReference(WeaponReference&&) = default;
    WeaponReference& operator=(WeaponReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

private:
    language_index_t li() const noexcept;

public:
    const text_t& name() const noexcept { return name_[li()]; }

    const text_t& descr() const noexcept { return descrip_[li()]; }

public:
    Weapon__Model           model_;         // weapon model
    Weapon__Type            type_;          // weapon type (kind)
    weapon_mod_types_t      weaponModTypes_;// list of slot types
    WeaponRequirements      requirements_;
    WeaponPenalties         penalties_;
    Attack                  attack_;

    common::Damage          dmgMin_;        // min damage per hit
    common::Damage          dmgMax_;        // max damage per hit
    common::Price           price_;         // price
    common::Capacity        capAmmo_;       // ammo capacity
    common::Multiplier      mulCritDmg_;    // critical damage multiplier
    common::Chance          chaHit_;        // base hit chance
    common::Chance          chaCritDmg_;    // base critical damage chance
    common::Bonus           bonSneakDmg_;   // sneak attack damage bonus
    common::Bonus           bonNormDmg_;    // normal damage bonus
    common::Bonus           bonMeleeDmg_;   // melee damage bonus
    common::Bonus           bonRangeDmg_;   // ranged damage bonus
    common::Level           level_;         // weapon level
    common::Armor           armorPen_;      // penetration
    common::ActionPoint     apAttack_;      // action points per attack
    common::ActionPoint     apReload_;      // action points per reload
    common::NumberShots     shoPerAttack_;  // number of shots per attack
    Ammo::Type              tyAmmo_;        // ammo type
    Damage::Type            tyDmg_;         // damage type

private:
    language_bundle_t       name_;          // weapon name
    language_bundle_t       descrip_;       // description

    bool                    initialized_;
};

///************************************************************************************************

class WeaponReferenceContainer {
private:
    friend class Weapon;

private:
    WeaponReferenceContainer() noexcept {}

public:
    WeaponReferenceContainer(const WeaponReferenceContainer&) = delete;
    WeaponReferenceContainer& operator=(const WeaponReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept {
        return initialized_ && base_.isInitialized() && Attack::isInitialized();
    }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const WeaponReference& weaponReference(Weapon__Model id) noexcept;

    static const WeaponReference& weaponReferenceMinimal() noexcept { return refMinimal_; }

    static const WeaponReference& weaponReferenceDefault() noexcept { return refDefault_; }

private:
    static void initContainer(const fbWeapon::FB_WeaponReferenceContainer* fb);

    static WeaponReference initWeaponReference(
        const fbWeapon::FB_WeaponReference* fb,
        const bool verify = true
    );

    static void initWeaponRequirements(
        const fbWeapon::FB_WeaponRequirements* fb,
        WeaponRequirements& requirements,
        const bool verify
    );

private:
    static global::PlainTextBase                    base_;
    static std::vector<WeaponReference>             refs_;
    static WeaponReference                          refMinimal_;
    static WeaponReference                          refDefault_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline WeaponReference::language_index_t WeaponReference::li() const noexcept
{
    return { WeaponReferenceContainer::languageIndex() };
}

///************************************************************************************************

inline const WeaponReference& WeaponReferenceContainer::weaponReference(
    Weapon__Model id) noexcept
{
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

} // namespace object
} // namespace game

#endif // !WEAPON_REFERENCE_HPP
