
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

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

void WeaponMod::apply(Weapon& weapon) noexcept
{
    weapon.damageMinimumAdd(damageMinimum());
    weapon.damageMaximumAdd(damageMaximum());
    ///weapon.rangeAttackAdd(rangeAttack());
    weapon.capacityAmmoAdd(capacityAmmo());
    ///weapon.angleConeAdd(angleCone());
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
