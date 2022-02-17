
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include"ammo.hpp"
#include"common.hpp"
#include"damage.hpp"
#include"item.hpp"
#include"slot.hpp"
#include"weaponCommon.hpp"
#include"weaponMod.hpp"
#include"weaponReference.hpp"

namespace game {
namespace global {

class Factory;

} // namespace global

namespace object {

class Weapon : public Item {
public:
    using Model         = Weapon__Model;
    using Type          = Weapon__Type;

private:
    friend global::Factory;

    static constexpr auto nWMSlots_{ WeaponReference::nWMSlots_ };

protected:
    explicit Weapon(Weapon::Model model) noexcept;

public:
    Weapon(const Weapon&) = delete;
    Weapon& operator=(const Weapon&) = delete;

    virtual ~Weapon() noexcept {}

    static void initialize();

    static bool isInitialized();

    virtual void accept(ItemVisitor& visitor) noexcept override {
        visitor.visitWeapon(*this);
    }

    void apply() noexcept;

private:
    void check() noexcept;

/// weapon parameters
public:
    virtual Item::Type itemType() const noexcept override {
        return Item::Type::WEAPON;
    }

    virtual Item::Model itemModel() const noexcept override {
        return static_cast<Item::Model>(base_.model_);
    }

    Weapon::Model model() const noexcept {
        return base_.model_;
    }

    Weapon::Type type() const noexcept {
        return base_.type_;
    }

    const common::Text& name() const noexcept {
        return base_.name();
    }

    const common::Text& description() const noexcept {
        return base_.descr();
    }

    common::Price price() const noexcept {
        return base_.price_;
    }

    common::Level level() const noexcept {
        return base_.level_;
    }

    //common::Level levelSkill() const noexcept {
    //    return base_.levSkill_;
    //}

    common::Multiplier multiplierCritDamage() const noexcept {
        return mulCritDmg_;
    }

    void multiplierCritDamageAdd(common::Multiplier shift) noexcept {
        mulCritDmg_ += shift;
    }

    common::Damage damageMinimum() const noexcept {
        return dmgMin_;
    }

    void damageMinimumAdd(common::Damage shift) noexcept {
        dmgMin_ += shift;
    }

    common::Damage damageMaximum() const noexcept {
        return dmgMax_;
    }

    void damageMaximumAdd(common::Damage shift) noexcept {
        dmgMax_ += shift;
    }

    common::Chance chanceHit() const noexcept {
        return chaHit_;
    }

    void chanceHitAdd(common::Chance shift) noexcept {
        chaHit_ += shift;
    }

    common::Chance chanceCritDamage() const noexcept {
        return chaCritDmg_;
    }

    void chanceCritDamageAdd(common::Chance shift) noexcept {
        chaCritDmg_ += shift;
    }

    common::Armor armorPenetration() const noexcept {
        return armorPen_;
    }

    void armorPenetrationAdd(common::Armor shift) noexcept {
        armorPen_ += shift;
    }

    common::Range rangeAttack() const noexcept {
        return rangeAttack_;
    }

    void rangeAttackAdd(common::Range shift) noexcept {
        rangeAttack_ += shift;
    }

    common::NumberShots shotsPerAttack() const noexcept {
        return shoPerAttack_;
    }

    void shotsPerAttackAdd(common::NumberShots shift) noexcept {
        shoPerAttack_ += shift;
    }

    common::ActionPoint actionPointPerAttack() const noexcept {
        return apAttack_;
    }

    void actionPointPerAttackAdd(common::ActionPoint shift) noexcept {
        apAttack_ += shift;
    }

    common::ActionPoint actionPointPerReload() const noexcept {
        return apReload_;
    }

    void actionPointPerReloadAdd(common::ActionPoint shift) noexcept {
        apReload_ += shift;
    }

    common::Capacity capacityAmmo() const noexcept {
        return capAmmo_;
    }

    void capacityAmmoAdd(common::Capacity shift) noexcept {
        capAmmo_ += shift;
    }

    Ammo::Type ammoType() const noexcept {
        return tyAmmo_;
    }

    void ammoType(Ammo::Type type) noexcept {
        tyAmmo_ = type;
    }

    Damage::Type damageType() const noexcept {
        return tyDmg_;
    }

    void damageType(Damage::Type type) noexcept {
        tyDmg_ = type;
    }

/// slots
public:
    const common::Slot<WeaponMod, nWMSlots_>& slotMod() const noexcept {
        return slotWeaponMod_;
    }

    common::Slot<WeaponMod, nWMSlots_>& slotMod() noexcept {
        return slotWeaponMod_;
    }

private:
    const WeaponReference&      base_;          // reference, sample, template

    common::Damage              dmgMin_;        // min damage per hit
    common::Damage              dmgMax_;        // max damage per hit
    common::Range               rangeAttack_;   // attack range
    common::Capacity            capAmmo_;       // ammo capacity
    common::Multiplier          mulCritDmg_;    // crit damage multiplier
    common::Chance              chaHit_;        // base hit chance
    common::Chance              chaCritDmg_;    // base critical damage chance
    common::Armor               armorPen_;      // penetration
    common::ActionPoint         apAttack_;      // action points per attack
    common::ActionPoint         apReload_;      // action points per reload
    common::NumberShots         shoPerAttack_;  // number of shots per attack
    Ammo::Type                  tyAmmo_;        // ammo type
    Damage::Type                tyDmg_;         // damage type

    common::Slot<WeaponMod, nWMSlots_>      slotWeaponMod_; // weapon mod slots

    static const WeaponReferenceContainer   ref_;           // references
};

///************************************************************************************************

inline void Weapon::initialize()
{
    ref_.initialize();
}

inline bool Weapon::isInitialized()
{
    return ref_.isInitialized();
}

} // namespace object
} // namespace game

#endif // !WEAPON_HPP
