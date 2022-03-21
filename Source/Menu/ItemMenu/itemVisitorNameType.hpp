
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_VISITOR_NAME_TYPE_HPP
#define ITEM_VISITOR_NAME_TYPE_HPP

#include"common.hpp"
#include"itemVisitor.hpp"

namespace game {
namespace menu {

class ItemVisitorNameType : public object::ItemVisitor {
public:
    using text = common::Text;

public:
    ItemVisitorNameType() noexcept {}

    ItemVisitorNameType(const ItemVisitorNameType&) = delete;
    ItemVisitorNameType& operator=(const ItemVisitorNameType&) = delete;
    ItemVisitorNameType(ItemVisitorNameType&&) = default;
    ItemVisitorNameType& operator=(ItemVisitorNameType&&) = default;

    virtual ~ItemVisitorNameType() noexcept {}

public:
    virtual void visitWeapon(object::Weapon& weapon) noexcept override;

    virtual void visitWeaponMod(object::WeaponMod& weaponMod) noexcept override;

    virtual void visitArmor(object::Armor& armor) noexcept override;

    virtual void visitArmorMod(object::ArmorMod& armorMod) noexcept override;

    virtual void visitAmmo(object::Ammo& ammo) noexcept override;

    virtual void visitJunk(object::Junk& junk) noexcept override;

public:
    text getNameType() noexcept { return text_; }

private:
    void reset() noexcept {
        text_ = text{};
    }

private:
    text text_;          // name with type
};

} // namespace menu
} // namespace game

#endif // !ITEM_VISITOR_NAME_TYPE_HPP
