
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weapon.hpp"
#include<assert.h>
#include<string>

namespace game {
namespace object {

using namespace std;

const WeaponReferenceContainer      Weapon::ref_;
const WeaponText                    Weapon::text_;

///************************************************************************************************

Weapon::Weapon(Weapon::Model model) noexcept
    :
    base_           { ref_.weaponReference(model) },
    dmgMin_         { base_.dmgMin_ },
    dmgMax_         { base_.dmgMax_ },
    rangeAttack_    { base_.rangeAttack_ },
    capAmmo_        { base_.capAmmo_ },
    mulCritDmg_     { base_.mulCritDmg_ },
    chaHit_         { base_.chaHit_ },
    chaCritDmg_     { base_.chaCritDmg_ },
    armorPen_       { base_.armorPen_ },
    apAttack_       { base_.apAttack_ },
    apReload_       { base_.apReload_ },
    shoPerAttack_   { base_.shoPerAttack_ },
    tyAmmo_         { base_.tyAmmo_ },
    tyDmg_          { base_.tyDmg_ },
    slotWeaponMod_  { base_.weaponModTypes_ }
{
    assert(isInitialized());
    assert(base_.isInitialized());
}

void Weapon::apply() noexcept
{
    dmgMin_         = base_.dmgMin_;
    dmgMax_         = base_.dmgMax_;
    rangeAttack_    = base_.rangeAttack_;
    capAmmo_        = base_.capAmmo_;
    mulCritDmg_     = base_.mulCritDmg_;
    chaHit_         = base_.chaHit_;
    chaCritDmg_     = base_.chaCritDmg_;
    armorPen_       = base_.armorPen_;
    apAttack_       = base_.apAttack_;
    apReload_       = base_.apReload_;
    shoPerAttack_   = base_.shoPerAttack_;

    for (unsigned int i = 0; i < slotWeaponMod_.size(); ++i) {
        if (slotWeaponMod_[i]) {
            slotWeaponMod_[i]->apply(*this);
        }
    }

    check();
}

void Weapon::check() noexcept
{
    const WeaponReference& refMin = ref_.weaponReferenceMinimal();
    if (dmgMin_         < refMin.dmgMin_)           dmgMin_         = refMin.dmgMin_;
    if (dmgMax_         < refMin.dmgMax_)           dmgMax_         = refMin.dmgMax_;
    if (rangeAttack_    < refMin.rangeAttack_)      rangeAttack_    = refMin.rangeAttack_;
    if (capAmmo_        < refMin.capAmmo_)          capAmmo_        = refMin.capAmmo_;
    if (mulCritDmg_     < refMin.mulCritDmg_)       mulCritDmg_     = refMin.mulCritDmg_;
    if (chaHit_         < refMin.chaHit_)           chaHit_         = refMin.chaHit_;
    if (chaCritDmg_     < refMin.chaCritDmg_)       chaCritDmg_     = refMin.chaCritDmg_;
    if (armorPen_       < refMin.armorPen_)         armorPen_       = refMin.armorPen_;
    if (apAttack_       < refMin.apAttack_)         apAttack_       = refMin.apAttack_;
    if (apReload_       < refMin.apReload_)         apReload_       = refMin.apReload_;
    if (shoPerAttack_   < refMin.shoPerAttack_)     shoPerAttack_   = refMin.shoPerAttack_;
}

} // namespace object
} // namespace game
