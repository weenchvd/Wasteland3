
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_REFERENCE_HPP
#define WEAPON_MOD_REFERENCE_HPP

#include"ammo.hpp"
#include"attack.hpp"
#include"attribute.hpp"
#include"common.hpp"
#include"damage.hpp"
#include"plainTextBase.hpp"
#include"skill.hpp"
#include"weaponModCommon.hpp"
#include"weaponModReferenceFB_generated.h"
#include<array>
#include<assert.h>
#include<utility>
#include<vector>

namespace game {
namespace object {

class WeaponModRequirements {
public:
    using skill_requirement_t       = std::pair<Skill::Type, common::LevelSkill>;
    using attribute_requirement_t   = std::pair<Attribute::Type, common::LevelAttribute>;

    static constexpr auto nSkill_   { 2 };
    static constexpr auto nAttr_    { 2 };

    friend class WeaponModReferenceContainer;

public:
    WeaponModRequirements();

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

class WeaponModReference {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class WeaponModReferenceContainer;

public:
    WeaponModReference();

    WeaponModReference(const WeaponModReference&) = delete;
    WeaponModReference& operator=(const WeaponModReference&) = delete;
    WeaponModReference(WeaponModReference&&) = default;
    WeaponModReference& operator=(WeaponModReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

private:
    language_index_t li() const noexcept;

public:
    const text_t& name() const noexcept { return name_[li()]; }

    const text_t& descr() const noexcept { return descrip_[li()]; }

public:
    WeaponMod__Model        model_;         // weapon mod model
    WeaponMod__Type         type_;          // weapon mod type (kind)
    WeaponModRequirements   requirements_;
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

class WeaponModReferenceContainer {
private:
    friend class WeaponMod;

private:
    WeaponModReferenceContainer() noexcept {}

public:
    WeaponModReferenceContainer(const WeaponModReferenceContainer&) = delete;
    WeaponModReferenceContainer& operator=(const WeaponModReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept {
        return initialized_ && base_.isInitialized() && Attack::isInitialized();
    }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const WeaponModReference& weaponModReference(WeaponMod__Model id) noexcept;

    static const WeaponModReference& weaponModReferenceDefault() noexcept { return refDefault_; }

private:
    static void initContainer(const fbWeaponMod::FB_WeaponModReferenceContainer* fb);

    static WeaponModReference initWeaponModReference(
        const fbWeaponMod::FB_WeaponModReference* fb,
        const bool verify = true
    );

    static void initWeaponModRequirements(
        const fbWeaponMod::FB_WeaponModRequirements* fb,
        WeaponModRequirements& requirements,
        const bool verify
    );

private:
    static global::PlainTextBase                    base_;
    static std::vector<WeaponModReference>          refs_;
    static WeaponModReference                       refDefault_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline WeaponModReference::language_index_t WeaponModReference::li() const noexcept
{
    return { WeaponModReferenceContainer::languageIndex() };
}

///************************************************************************************************

inline const WeaponModReference& WeaponModReferenceContainer::weaponModReference(
    WeaponMod__Model id) noexcept
{
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

} // namespace object
} // namespace game

#endif // !WEAPON_MOD_REFERENCE_HPP
