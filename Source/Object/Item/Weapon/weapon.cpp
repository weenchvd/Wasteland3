
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weapon.hpp"
#include<assert.h>
#include<string>
#include<type_traits>

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
    capLoadedAmmo_  { initAmmo_ },
    angleCone_      { base_.angleCone_ },
    mulCritDmg_     { base_.mulCritDmg_ },
    chaHit_         { base_.chaHit_ },
    chaCritDmg_     { base_.chaCritDmg_ },
    bonSneakDmg_    { base_.bonSneakDmg_ },
    bonNormDmg_     { base_.bonNormDmg_ },
    bonMeleeDmg_    { base_.bonMeleeDmg_ },
    bonRangeDmg_    { base_.bonRangeDmg_ },
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

Weapon::Weapon(const WeaponReference& ref) noexcept
    :
    base_           { ref },
    dmgMin_         { base_.dmgMin_ },
    dmgMax_         { base_.dmgMax_ },
    rangeAttack_    { base_.rangeAttack_ },
    capAmmo_        { base_.capAmmo_ },
    capLoadedAmmo_  { initAmmo_ },
    angleCone_      { base_.angleCone_ },
    mulCritDmg_     { base_.mulCritDmg_ },
    chaHit_         { base_.chaHit_ },
    chaCritDmg_     { base_.chaCritDmg_ },
    bonSneakDmg_    { base_.bonSneakDmg_ },
    bonNormDmg_     { base_.bonNormDmg_ },
    bonMeleeDmg_    { base_.bonMeleeDmg_ },
    bonRangeDmg_    { base_.bonRangeDmg_ },
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
    angleCone_      = base_.angleCone_;
    mulCritDmg_     = base_.mulCritDmg_;
    chaHit_         = base_.chaHit_;
    chaCritDmg_     = base_.chaCritDmg_;
    bonSneakDmg_    = base_.bonSneakDmg_;
    bonNormDmg_     = base_.bonNormDmg_;
    bonMeleeDmg_    = base_.bonMeleeDmg_;
    bonRangeDmg_    = base_.bonRangeDmg_;
    armorPen_       = base_.armorPen_;
    apAttack_       = base_.apAttack_;
    apReload_       = base_.apReload_;
    shoPerAttack_   = base_.shoPerAttack_;
    tyAmmo_         = base_.tyAmmo_;
    tyDmg_          = base_.tyDmg_;

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
    /// TODO if (angleCone_      < refMin.angleCone_)        angleCone_      = refMin.angleCone_;
    if (mulCritDmg_     < refMin.mulCritDmg_)       mulCritDmg_     = refMin.mulCritDmg_;
    if (chaHit_         < refMin.chaHit_)           chaHit_         = refMin.chaHit_;
    if (chaCritDmg_     < refMin.chaCritDmg_)       chaCritDmg_     = refMin.chaCritDmg_;
    if (bonSneakDmg_    < refMin.bonSneakDmg_)      bonSneakDmg_    = refMin.bonSneakDmg_;
    if (bonNormDmg_     < refMin.bonNormDmg_)       bonNormDmg_     = refMin.bonNormDmg_;
    if (bonMeleeDmg_    < refMin.bonMeleeDmg_)      bonMeleeDmg_    = refMin.bonMeleeDmg_;
    if (bonRangeDmg_    < refMin.bonRangeDmg_)      bonRangeDmg_    = refMin.bonRangeDmg_;
    if (armorPen_       < refMin.armorPen_)         armorPen_       = refMin.armorPen_;
    if (apAttack_       < refMin.apAttack_)         apAttack_       = refMin.apAttack_;
    if (apReload_       < refMin.apReload_)         apReload_       = refMin.apReload_;
    if (shoPerAttack_   < refMin.shoPerAttack_)     shoPerAttack_   = refMin.shoPerAttack_;
}

void Weapon::reloadAmmo(Ammo& ammo) noexcept
{
    assert(ammo.type() == ammoType());
    if (ammo.type() != ammoType()) return;
    common::Capacity qty{ capacityAmmo() - capLoadedAmmo_ };
    if (ammo.quantity() < qty) {
        qty = ammo.quantity();
    }
    ammo.quantityAdd(-qty);
    capLoadedAmmo_ = qty;
    assert(capLoadedAmmo_ >= 0);
}

void Weapon::unloadAmmo(Ammo& ammo) noexcept
{
    assert(ammo.type() == ammoType());
    if (ammo.type() != ammoType()) return;
    ammo.quantityAdd(capLoadedAmmo_);
    capLoadedAmmo_ = 0;
}

void Weapon::ammoType(Ammo::Type type) noexcept
{
    assert(common::isValidEnum(type));
    assert(capLoadedAmmo_ == 0);
    if (capLoadedAmmo_ > 0) return;
    tyAmmo_ = type;
}

void Weapon::damageType(Damage::Type type) noexcept
{
    assert(common::isValidEnum(type));
    tyDmg_ = type;
}

bool Weapon::setMod(
    unsigned int slotNumber,
    unique_ptr<Item>& source,
    bool (*typeChecker)(WeaponMod::Type, WeaponMod::Type)
) noexcept
{
    if (slotWeaponMod_.set(slotNumber, source, typeChecker)) {
        this->apply();
        return true;
    }
    return false;
}

bool Weapon::unsetMod(unsigned int slotNumber, unique_ptr<Item>& receiver) noexcept
{
    if (slotWeaponMod_.unset(slotNumber, receiver)) {
        this->apply();
        return true;
    }
    return false;
}

const Weapon& Weapon::weaponDefault() noexcept
{
    static const Weapon def{ ref_.weaponReferenceDefault() };
    return def;
}

} // namespace object
} // namespace game
