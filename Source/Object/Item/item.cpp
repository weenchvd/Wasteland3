
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"exception.hpp"
#include"item.hpp"
#include"itemFB_generated.h"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<assert.h>

namespace game {
namespace object {

using namespace std;

flatbuffers::Offset<fbItem::FB_Item> Item::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    fbItem::FB_ItemUnion type{ fbItem::FB_ItemUnion::FB_ItemUnion_NONE };
    flatbuffers::Offset<void> offset;

    switch (itemType()) {
    case Item::Type::WEAPON:
        type = fbItem::FB_ItemUnion::FB_ItemUnion_fbWeapon_FB_Weapon;
        offset = static_cast<const Weapon&>(*this).serialize(fbb).Union();
        break;
    case Item::Type::WEAPON_MOD:
        type = fbItem::FB_ItemUnion::FB_ItemUnion_fbWeaponMod_FB_WeaponMod;
        offset = static_cast<const WeaponMod&>(*this).serialize(fbb).Union();
        break;
    case Item::Type::AMMO:
        type = fbItem::FB_ItemUnion::FB_ItemUnion_fbAmmo_FB_Ammo;
        offset = static_cast<const Ammo&>(*this).serialize(fbb).Union();
        break;
    default:
        throw common::SerializationError{ u8"[Item::serialize] Invalid branch" };
    }

    assert(type != fbItem::FB_ItemUnion::FB_ItemUnion_NONE);
    assert(!offset.IsNull());
    fbItem::FB_ItemBuilder builder{ fbb };
    builder.add_item_type(type);
    builder.add_item(offset);
    return builder.Finish();
}

unique_ptr<Item> Item::deserialize(const fbItem::FB_Item* fb)
{
    assert(fb != nullptr);
    switch (fb->item_type()) {
    case fbItem::FB_ItemUnion::FB_ItemUnion_fbWeapon_FB_Weapon: {
        const auto* weapon{ fb->item_as_fbWeapon_FB_Weapon() };
        return Weapon::deserialize(weapon);
    }
    case fbItem::FB_ItemUnion::FB_ItemUnion_fbWeaponMod_FB_WeaponMod: {
        const auto* weaponMod{ fb->item_as_fbWeaponMod_FB_WeaponMod() };
        return WeaponMod::deserialize(weaponMod);
    }
    case fbItem::FB_ItemUnion::FB_ItemUnion_fbAmmo_FB_Ammo: {
        const auto* ammo{ fb->item_as_fbAmmo_FB_Ammo() };
        return Ammo::deserialize(ammo);
    }
    default:
        throw common::SerializationError{ u8"[Item::deserialize] Invalid branch" };
    }
}

///************************************************************************************************

//bool operator==(const Item& lhs, const Item& rhs) noexcept
//{
//    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() == rhs.itemModel()) {
//        return true;
//    }
//    return false;
//}

//bool operator<(const unique_ptr<Item>& lhs, const unique_ptr<Item>& rhs) noexcept
//{
//    if (lhs->itemType() < rhs->itemType()) {
//        return true;
//    }
//    if (lhs->itemType() == rhs->itemType() && lhs->itemModel() < rhs->itemModel()) {
//        return true;
//    }
//    return false;
//}

bool isSameModel(const Item& lhs, const Item& rhs) noexcept
{
    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() == rhs.itemModel()) {
        return true;
    }
    return false;
}

bool isLessByModel(const Item& lhs, const Item& rhs) noexcept
{
    if (lhs.itemType() < rhs.itemType()) {
        return true;
    }
    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() < rhs.itemModel()) {
        return true;
    }
    return false;
}

bool isGreaterByModel(const Item& lhs, const Item& rhs) noexcept
{
    if (lhs.itemType() > rhs.itemType()) {
        return true;
    }
    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() > rhs.itemModel()) {
        return true;
    }
    return false;
}

} // namespace object
} // namespace game
