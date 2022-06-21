
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"

namespace game {
namespace object {

using namespace std;

const WeaponModReferenceContainer       WeaponMod::ref_;
const WeaponModText                     WeaponMod::text_;

///************************************************************************************************

WeaponMod::WeaponMod(WeaponMod::Model model) noexcept
    :
    base_{ ref_.weaponModReference(model) }
{
    assert(isInitialized());
    assert(base_.isInitialized());
}

WeaponMod::WeaponMod(const WeaponModReference& ref) noexcept
    :
    base_{ ref }
{
    assert(isInitialized());
    assert(base_.isInitialized());
}

flatbuffers::Offset<fbWeaponMod::FB_WeaponMod> WeaponMod::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    fbWeaponMod::FB_WeaponModBuilder builder{ fbb };
    builder.add_model(WeaponModModelBiMap::toRightType(model()));
    return builder.Finish();
}

unique_ptr<Item> WeaponMod::deserialize(const fbWeaponMod::FB_WeaponMod* fb)
{
    assert(fb != nullptr);
    const auto& f{ global::Locator::getFactory() };
    auto modModel{ WeaponModModelBiMap::toLeftType(fb->model()) };
    auto item{ f.createItem<WeaponMod>(modModel) };
    return item;
}

void WeaponMod::apply(Weapon& weapon) noexcept
{
    weapon.attack().apply(attack());
    weapon.damageMinimumAdd(damageMinimum());
    weapon.damageMaximumAdd(damageMaximum());
    weapon.capacityAmmoAdd(capacityAmmo());
    weapon.multiplierCritDamageAdd(multiplierCritDamage());
    weapon.chanceHitAdd(chanceHit());
    weapon.chanceCritDamageAdd(chanceCritDamage());
    weapon.bonusSneakAttackDamageAdd(bonusSneakAttackDamage());
    weapon.bonusNormalDamageAdd(bonusNormalDamage());
    weapon.bonusMeleeDamageAdd(bonusMeleeDamage());
    weapon.bonusRangedDamageAdd(bonusRangedDamage());
    weapon.armorPenetrationAdd(armorPenetration());
    weapon.actionPointPerAttackAdd(actionPointPerAttack());
    weapon.actionPointPerReloadAdd(actionPointPerReload());
    weapon.shotsPerAttackAdd(shotsPerAttack());
    if (common::isValidEnum(damageType())) weapon.damageType(damageType());
    if (common::isValidEnum(ammoType())) weapon.ammoType(ammoType());
}

const WeaponMod& WeaponMod::weaponModDefault() noexcept
{
    static const WeaponMod def{ ref_.weaponModReferenceDefault() };
    return def;
}

} // namespace object
} // namespace game
