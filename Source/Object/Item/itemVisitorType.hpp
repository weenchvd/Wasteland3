
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_VISITOR_TYPE_HPP
#define ITEM_VISITOR_TYPE_HPP

#include"item.hpp"
#include"itemVisitor.hpp"

namespace game {
namespace object {

class ItemVisitorType : public ItemVisitor {
public:
    ItemVisitorType() noexcept {}

    ItemVisitorType(const ItemVisitorType&) = delete;
    ItemVisitorType& operator=(const ItemVisitorType&) = delete;
    ItemVisitorType(ItemVisitorType&&) = default;
    ItemVisitorType& operator=(ItemVisitorType&&) = default;

    virtual ~ItemVisitorType() noexcept {}

public:
    virtual void visitWeapon(const Weapon& weapon) noexcept override {
        reset();
        type_ = Item::Type::WEAPON;
    }

    virtual void visitWeaponMod(const WeaponMod& weaponMod) noexcept override {
        reset();
        type_ = Item::Type::WEAPON_MOD;
    }

    virtual void visitArmor(const Armor& armor) noexcept override {
        reset();
        // TODO type_ = Item::Type::ARMOR;
    }

    virtual void visitArmorMod(const ArmorMod& armorMod) noexcept override {
        reset();
        // TODO type_ = Item::Type::ARMOR_MOD;
    }

    virtual void visitAmmo(const Ammo& ammo) noexcept override {
        reset();
        type_ = Item::Type::AMMO;
    }

    virtual void visitJunk(const Junk& junk) noexcept override {
        reset();
        // TODO type_ = Item::Type::JUNK;
    }

public:
    Item::Type type()   const noexcept { return type_; }
    bool isWeapon()     const noexcept { return type_ == Item::Type::WEAPON; }
    bool isWeaponMod()  const noexcept { return type_ == Item::Type::WEAPON_MOD; }
    bool isArmor()      const noexcept { return false; }
    bool isArmorMod()   const noexcept { return false; }
    bool isAmmo()       const noexcept { return type_ == Item::Type::AMMO; }
    bool isJunk()       const noexcept { return false; }

private:
    void reset() noexcept {
        *this = ItemVisitorType{};
    }

private:
    Item::Type type_{ Item::Type::INVALID };
};

} // namespace object
} // namespace game

#endif // !ITEM_VISITOR_TYPE_HPP
