
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
    weapon.damageMinimumAdd(base_.dmgMin_);
    weapon.damageMaximumAdd(base_.dmgMax_);
    weapon.rangeAttackAdd(base_.rangeAttack_);
    weapon.capacityAmmoAdd(base_.capAmmo_);
    weapon.multiplierCritDamageAdd(base_.mulCritDmg_);
    weapon.chanceHitAdd(base_.chaHit_);
    weapon.chanceCritDamageAdd(base_.chaCritDmg_);
    weapon.armorPenetrationAdd(base_.armorPen_);
    weapon.actionPointPerAttackAdd(base_.apAttack_);
    weapon.actionPointPerReloadAdd(base_.apReload_);
    weapon.shotsPerAttackAdd(base_.shoPerAttack_);
    if (common::isValidEnum(base_.tyAmmo_)) weapon.ammoType(base_.tyAmmo_);
    if (common::isValidEnum(base_.tyDmg_)) weapon.damageType(base_.tyDmg_);
}

const WeaponMod& WeaponMod::weaponModDefault() noexcept
{
    static const WeaponMod def{ ref_.weaponModReferenceDefault() };
    return def;
}

} // namespace object
} // namespace game
