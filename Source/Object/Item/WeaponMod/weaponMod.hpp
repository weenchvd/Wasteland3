
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_HPP
#define WEAPON_MOD_HPP

#include"common.hpp"
#include"item.hpp"
#include"weaponModCommon.hpp"
#include"weaponModFB_generated.h"
#include"weaponModReference.hpp"
#include"weaponModText.hpp"
#include<type_traits>
#include<vector>

namespace game {
namespace global {

class Factory;

} // namespace global

namespace object {

class Weapon;

class WeaponMod : public Item {
public:
    using Model = WeaponMod__Model;
    using Type  = WeaponMod__Type;

private:
    friend global::Factory;

private:
    explicit WeaponMod(WeaponMod::Model model) noexcept;

    explicit WeaponMod(const WeaponModReference& ref) noexcept;

public:
    WeaponMod(const WeaponMod&) = delete;
    WeaponMod& operator=(const WeaponMod&) = delete;

    virtual ~WeaponMod() noexcept {}

    static void initialize();

    static bool isInitialized();

    virtual void accept(ItemVisitor& visitor) const noexcept override {
        visitor.visitWeaponMod(*this);
    }

    void apply(Weapon& weapon) noexcept;

///********** unchangeable weapon mod parameters (from reference)
public:
    virtual Item::Type itemType() const noexcept override {
        return Item::Type::WEAPON_MOD;
    }

    virtual Item::Model itemModel() const noexcept override {
        return static_cast<Item::Model>(base_.model_);
    }

    WeaponMod::Model model() const noexcept {
        return base_.model_;
    }

    WeaponMod::Type type() const noexcept {
        return base_.type_;
    }

    const WeaponModRequirements& requirements() const noexcept {
        return base_.requirements_;
    }

    const Attack& attack() const noexcept {
        return base_.attack_;
    }

    virtual const common::Text& name() const noexcept override {
        return base_.name();
    }

    const common::Text& description() const noexcept {
        return base_.descr();
    }

    common::Damage damageMinimum() const noexcept {
        return base_.dmgMin_;
    }

    common::Damage damageMaximum() const noexcept {
        return base_.dmgMax_;
    }

    common::Price price() const noexcept {
        return base_.price_;
    }

    common::Capacity capacityAmmo() const noexcept {
        return base_.capAmmo_;
    }

    common::Multiplier multiplierCritDamage() const noexcept {
        return base_.mulCritDmg_;
    }

    common::Chance chanceHit() const noexcept {
        return base_.chaHit_;
    }

    common::Chance chanceCritDamage() const noexcept {
        return base_.chaCritDmg_;
    }

    common::Bonus bonusSneakAttackDamage() const noexcept {
        return base_.bonSneakDmg_;
    }

    common::Bonus bonusNormalDamage() const noexcept {
        return base_.bonNormDmg_;
    }

    common::Bonus bonusMeleeDamage() const noexcept {
        return base_.bonMeleeDmg_;
    }

    common::Bonus bonusRangedDamage() const noexcept {
        return base_.bonRangeDmg_;
    }

    common::Armor armorPenetration() const noexcept {
        return base_.armorPen_;
    }

    common::ActionPoint actionPointPerAttack() const noexcept {
        return base_.apAttack_;
    }

    common::ActionPoint actionPointPerReload() const noexcept {
        return base_.apReload_;
    }

    common::NumberShots shotsPerAttack() const noexcept {
        return base_.shoPerAttack_;
    }

    Ammo::Type ammoType() const noexcept {
        return base_.tyAmmo_;
    }

    Damage::Type damageType() const noexcept {
        return base_.tyDmg_;
    }

public:
    static const WeaponMod& weaponModDefault() noexcept;

    static const WeaponModReferenceContainer& weaponModReferenceContainer() noexcept {
        return ref_;
    }

    static const WeaponModText& weaponModText() noexcept {
        return text_;
    }

///********** serialization
public:
    flatbuffers::Offset<fbWeaponMod::FB_WeaponMod> serialize(
        flatbuffers::FlatBufferBuilder& fbb) const;

    static std::unique_ptr<Item> deserialize(const fbWeaponMod::FB_WeaponMod* fb);

private:
    const WeaponModReference&  base_;           // reference, sample, template

    static const WeaponModReferenceContainer    ref_;
    static const WeaponModText                  text_;
};

///************************************************************************************************

inline void WeaponMod::initialize()
{
    WeaponModModelBiMap::initialize();
    ref_.initialize();
    text_.initialize();
}

inline bool WeaponMod::isInitialized()
{
    return ref_.isInitialized() &&
           text_.isInitialized() &&
           WeaponModModelBiMap::isInitialized();
}

} // namespace object
} // namespace game

#endif // !WEAPON_MOD_HPP
