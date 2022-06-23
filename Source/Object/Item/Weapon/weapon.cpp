
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"exception.hpp"
#include"locator.hpp"
#include"weapon.hpp"
#include<assert.h>
#include<string>
#include<type_traits>
#include<vector>

namespace game {
namespace object {

using namespace std;

const WeaponReferenceContainer      Weapon::ref_;
const WeaponText                    Weapon::text_;

///************************************************************************************************

Weapon::Weapon(Weapon::Model model) noexcept
    :
    base_           { ref_.weaponReference(model) },
    attack_         { base_.attack_ },
    dmgMin_         { base_.dmgMin_ },
    dmgMax_         { base_.dmgMax_ },
    capAmmo_        { base_.capAmmo_ },
    capLoadedAmmo_  { initAmmo_ },
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
    attack_         { base_.attack_ },
    dmgMin_         { base_.dmgMin_ },
    dmgMax_         { base_.dmgMax_ },
    capAmmo_        { base_.capAmmo_ },
    capLoadedAmmo_  { initAmmo_ },
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

flatbuffers::Offset<fbWeapon::FB_Weapon> Weapon::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    vector<flatbuffers::Offset<fbWeaponMod::FB_WeaponMod>> mods;
    for (int i = 0; i < slotWeaponMod_.size(); ++i) {
        if (slotWeaponMod_[i] != nullptr) {
            mods.push_back(slotWeaponMod_[i]->serialize(fbb));
        }
    }
    auto modOffset{ fbb.CreateVector(mods) };

    fbWeapon::FB_WeaponBuilder builder{ fbb };
    builder.add_model(WeaponModelBiMap::toRightType(model()));
    builder.add_mods(modOffset);
    return builder.Finish();
}

unique_ptr<Item> Weapon::deserialize(const fbWeapon::FB_Weapon* fb)
{
    assert(fb != nullptr);
    const auto& f{ global::Locator::getFactory() };
    auto weaponModel{ WeaponModelBiMap::toLeftType(fb->model()) };
    auto item{ f.createItem<Weapon>(weaponModel) };
    auto& weapon{ static_cast<Weapon&>(*item.get()) };
    const auto* mods{ fb->mods() };
    if (mods != nullptr) {
        for (int i = 0; i < mods->size(); ++i) {
            assert(mods->Get(i) != nullptr);
            auto mod{ WeaponMod::deserialize(mods->Get(i)) };
            auto modType{ static_cast<WeaponMod*>(mod.get())->type() };
            auto slotNumber{ weapon.slotMod().slotNumber(modType) };
            if (slotNumber == weapon.slotMod().slotNotFound_ ||
                !weapon.setMod(slotNumber, mod, isCompatible))
            {
                throw common::SerializationError{ u8"[Weapon::deserialize] The mod is not set" };
            }
        }

    }
    return item;
}

void Weapon::apply() noexcept
{
    attack_         = base_.attack_;
    dmgMin_         = base_.dmgMin_;
    dmgMax_         = base_.dmgMax_;
    capAmmo_        = base_.capAmmo_;
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
}

bool Weapon::hasValidValues() const noexcept
{
    const WeaponReference& min{ ref_.weaponReferenceMinimal() };
    if (!attack_.hasValidValues())              return false;
    if (dmgMin_         < min.dmgMin_)          return false;
    if (dmgMax_         < min.dmgMax_)          return false;
    if (capAmmo_        < min.capAmmo_)         return false;
    if (mulCritDmg_     < min.mulCritDmg_)      return false;
    if (chaHit_         < min.chaHit_)          return false;
    if (chaCritDmg_     < min.chaCritDmg_)      return false;
    if (bonSneakDmg_    < min.bonSneakDmg_)     return false;
    if (bonNormDmg_     < min.bonNormDmg_)      return false;
    if (bonMeleeDmg_    < min.bonMeleeDmg_)     return false;
    if (bonRangeDmg_    < min.bonRangeDmg_)     return false;
    if (armorPen_       < min.armorPen_)        return false;
    if (apAttack_       < min.apAttack_)        return false;
    if (apReload_       < min.apReload_)        return false;
    if (shoPerAttack_   < min.shoPerAttack_)    return false;
    return true;
}

void Weapon::reloadAmmo(Ammo& ammo) noexcept
{
    assert(ammo.type() == ammoType());
    if (ammo.type() != ammoType()) return;
    common::Capacity qty{ capacityAmmo() - capLoadedAmmo_ };
    if (ammo.quantity() < common::toUnderlying(qty)) {
        qty = common::Capacity{ ammo.quantity() };
    }
    ammo.quantityAdd(-common::toUnderlying(qty));
    capLoadedAmmo_ = qty;
    assert(common::toUnderlying(capLoadedAmmo_) >= 0);
}

void Weapon::unloadAmmo(Ammo& ammo) noexcept
{
    assert(ammo.type() == ammoType());
    if (ammo.type() != ammoType()) return;
    ammo.quantityAdd(common::toUnderlying(capLoadedAmmo_));
    capLoadedAmmo_ = common::Capacity{ 0 };
}

void Weapon::ammoType(Ammo::Type type) noexcept
{
    assert(common::isValidEnum(type));
    assert(common::toUnderlying(capLoadedAmmo_) == 0);
    if (common::toUnderlying(capLoadedAmmo_) > 0) return;
    tyAmmo_ = type;
}

void Weapon::damageType(Damage::Type type) noexcept
{
    assert(common::isValidEnum(type));
    tyDmg_ = type;
}

bool Weapon::setMod(common::Slot<WeaponMod, nWMSlots_>::slot_number_t slotNumber,
                    unique_ptr<Item>& source,
                    bool (*typeChecker)(WeaponMod::Type, WeaponMod::Type)) noexcept
{
    assert(hasValidValues());
    if (slotWeaponMod_.set(slotNumber, source, typeChecker)) {
        apply();
        if (hasValidValues()) return true;
        slotWeaponMod_.unset(slotNumber, source);
        apply();
        assert(hasValidValues());
    }
    return false;
}

bool Weapon::unsetMod(common::Slot<WeaponMod, nWMSlots_>::slot_number_t slotNumber,
                      unique_ptr<Item>& receiver) noexcept
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
