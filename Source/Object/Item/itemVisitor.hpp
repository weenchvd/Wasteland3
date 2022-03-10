
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_VISITOR_HPP
#define ITEM_VISITOR_HPP

namespace game {
namespace object {

class Weapon;
class WeaponMod;
class Armor;
class ArmorMod;
class Ammo;
class Junk;

class ItemVisitor {
protected:
    ItemVisitor() noexcept {}

public:
    ItemVisitor(const ItemVisitor&) = delete;
    ItemVisitor& operator=(const ItemVisitor&) = delete;
    ItemVisitor(ItemVisitor&&) = default;
    ItemVisitor& operator=(ItemVisitor&&) = default;

    virtual ~ItemVisitor() noexcept {}

public:
    virtual void visitWeapon(Weapon& weapon) = 0;
    virtual void visitWeaponMod(WeaponMod& weaponMod) = 0;
    virtual void visitArmor(Armor& armor) = 0;
    virtual void visitArmorMod(ArmorMod& armorMod) = 0;
    virtual void visitAmmo(Ammo& ammo) = 0;
    virtual void visitJunk(Junk& junk) = 0;
};

} // namespace object
} // namespace game

#endif // !ITEM_VISITOR_HPP
