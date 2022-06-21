
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
#include"weaponFB_generated.h"
#include"weaponMod.hpp"
#include"weaponReference.hpp"
#include"weaponText.hpp"

namespace game {
namespace global {

class Factory;

} // namespace global

namespace object {

class Weapon : public Item {
public:
    using Model = Weapon__Model;
    using Type  = Weapon__Type;

private:
    friend global::Factory;

    static constexpr auto nWMSlots_{ WeaponReference::nWMSlots_ }; // number of weapon mod slots
    static constexpr auto initAmmo_{ 0 };

private:
    explicit Weapon(Weapon::Model model) noexcept;

    explicit Weapon(const WeaponReference& ref) noexcept;

public:
    Weapon(const Weapon&) = delete;
    Weapon& operator=(const Weapon&) = delete;

    virtual ~Weapon() noexcept {}

    static void initialize();

    static bool isInitialized();

    virtual void accept(ItemVisitor& visitor) const noexcept override {
        visitor.visitWeapon(*this);
    }

    flatbuffers::Offset<fbWeapon::FB_Weapon> serialize(
        flatbuffers::FlatBufferBuilder& fbb) const;

    static std::unique_ptr<Item> deserialize(const fbWeapon::FB_Weapon* fb);

    void apply() noexcept;

private:
    bool hasValidValues() const noexcept;

///********** unchangeable weapon parameters (from reference)
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

    const WeaponRequirements& requirements() const noexcept {
        return base_.requirements_;
    }

    const WeaponPenalties& penalties() const noexcept {
        return base_.penalties_;
    }

    virtual const common::Text& name() const noexcept override {
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

///********** changeable weapon parameters
public:
    const Attack& attack() const noexcept {
        return attack_;
    }
    Attack& attack() noexcept {
        return attack_;
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

    common::Capacity capacityAmmo() const noexcept {
        return capAmmo_;
    }
    void capacityAmmoAdd(common::Capacity shift) noexcept {
        capAmmo_ += shift;
    }
    void reloadAmmo(Ammo& ammo) noexcept;
    void unloadAmmo(Ammo& ammo) noexcept;

    common::Multiplier multiplierCritDamage() const noexcept {
        return mulCritDmg_;
    }
    void multiplierCritDamageAdd(common::Multiplier shift) noexcept {
        mulCritDmg_ += shift;
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

    common::Bonus bonusSneakAttackDamage() const noexcept {
        return bonSneakDmg_;
    }
    void bonusSneakAttackDamageAdd(common::Bonus shift) noexcept {
        bonSneakDmg_ += shift;
    }

    common::Bonus bonusNormalDamage() const noexcept {
        return bonNormDmg_;
    }
    void bonusNormalDamageAdd(common::Bonus shift) noexcept {
        bonNormDmg_ += shift;
    }

    common::Bonus bonusMeleeDamage() const noexcept {
        return bonMeleeDmg_;
    }
    void bonusMeleeDamageAdd(common::Bonus shift) noexcept {
        bonMeleeDmg_ += shift;
    }

    common::Bonus bonusRangedDamage() const noexcept {
        return bonRangeDmg_;
    }
    void bonusRangedDamageAdd(common::Bonus shift) noexcept {
        bonRangeDmg_ += shift;
    }

    common::Armor armorPenetration() const noexcept {
        return armorPen_;
    }
    void armorPenetrationAdd(common::Armor shift) noexcept {
        armorPen_ += shift;
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

    common::NumberShots shotsPerAttack() const noexcept {
        return shoPerAttack_;
    }
    void shotsPerAttackAdd(common::NumberShots shift) noexcept {
        shoPerAttack_ += shift;
    }

    Ammo::Type ammoType() const noexcept {
        return tyAmmo_;
    }
    void ammoType(Ammo::Type type) noexcept;

    Damage::Type damageType() const noexcept {
        return tyDmg_;
    }
    void damageType(Damage::Type type) noexcept;

public:
    const common::Slot<WeaponMod, nWMSlots_>& slotMod() const noexcept {
        return slotWeaponMod_;
    }

    bool setMod(
        unsigned int slotNumber,
        std::unique_ptr<Item>& source,
        bool (*typeChecker)(WeaponMod::Type, WeaponMod::Type)
    ) noexcept;

    bool unsetMod(unsigned int slotNumber, std::unique_ptr<Item>& receiver) noexcept;

    static const Weapon& weaponDefault() noexcept;

    static const WeaponReferenceContainer& weaponReferenceContainer() noexcept {
        return ref_;
    }

    static const WeaponText& weaponText() noexcept {
        return text_;
    }

private:
    const WeaponReference&      base_;          // reference, sample, template

    Attack                      attack_;
    common::Damage              dmgMin_;        // min damage per hit
    common::Damage              dmgMax_;        // max damage per hit
    common::Capacity            capAmmo_;       // ammo capacity
    common::Capacity            capLoadedAmmo_; // loaded ammo
    common::Multiplier          mulCritDmg_;    // crit damage multiplier
    common::Chance              chaHit_;        // base hit chance
    common::Chance              chaCritDmg_;    // base critical damage chance
    common::Bonus               bonSneakDmg_;   // sneak attack damage bonus
    common::Bonus               bonNormDmg_;    // normal damage bonus
    common::Bonus               bonMeleeDmg_;   // melee damage bonus
    common::Bonus               bonRangeDmg_;   // ranged damage bonus
    common::Armor               armorPen_;      // penetration
    common::ActionPoint         apAttack_;      // action points per attack
    common::ActionPoint         apReload_;      // action points per reload
    common::NumberShots         shoPerAttack_;  // number of shots per attack
    Ammo::Type                  tyAmmo_;        // ammo type
    Damage::Type                tyDmg_;         // damage type

    common::Slot<WeaponMod, nWMSlots_>      slotWeaponMod_; // weapon mod slots

    static const WeaponReferenceContainer   ref_;           // references
    static const WeaponText                 text_;
};

///************************************************************************************************

inline void Weapon::initialize()
{
    WeaponModelBiMap::initialize();
    ref_.initialize();
    text_.initialize();
}

inline bool Weapon::isInitialized()
{
    return ref_.isInitialized() &&
           text_.isInitialized() &&
           WeaponModelBiMap::isInitialized();
}

} // namespace object
} // namespace game

#endif // !WEAPON_HPP
