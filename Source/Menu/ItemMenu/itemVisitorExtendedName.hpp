
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_VISITOR_EXTENDED_NAME_HPP
#define ITEM_VISITOR_EXTENDED_NAME_HPP

#include"common.hpp"
#include"itemVisitor.hpp"

namespace game {
namespace menu {

class ItemVisitorExtendedName : public object::ItemVisitor {
public:
    using text_t = common::Text;

public:
    ItemVisitorExtendedName() noexcept {}

    ItemVisitorExtendedName(const ItemVisitorExtendedName&) = delete;
    ItemVisitorExtendedName& operator=(const ItemVisitorExtendedName&) = delete;
    ItemVisitorExtendedName(ItemVisitorExtendedName&&) = default;
    ItemVisitorExtendedName& operator=(ItemVisitorExtendedName&&) = default;

    virtual ~ItemVisitorExtendedName() noexcept {}

public:
    virtual void visitWeapon(object::Weapon& weapon) override;

    virtual void visitWeaponMod(object::WeaponMod& weaponMod) override;

    virtual void visitArmor(object::Armor& armor) override;

    virtual void visitArmorMod(object::ArmorMod& armorMod) override;

    virtual void visitAmmo(object::Ammo& ammo) override;

    virtual void visitJunk(object::Junk& junk) override;

public:
    const text_t& getExtendedName() const noexcept { return text_; }

private:
    void reset() noexcept {
        text_ = text_t{};
    }

private:
    text_t text_;          // extended name
};

} // namespace menu
} // namespace game

#endif // !ITEM_VISITOR_EXTENDED_NAME_HPP
