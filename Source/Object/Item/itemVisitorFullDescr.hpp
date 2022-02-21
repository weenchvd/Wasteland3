
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_VISITOR_FULL_DESCR_HPP
#define ITEM_VISITOR_FULL_DESCR_HPP

#include"common.hpp"
#include"itemVisitor.hpp"

namespace game {
namespace object {

class ItemVisitorFullDescription : public ItemVisitor {
public:
    using text = common::Text;

public:
    ItemVisitorFullDescription() noexcept {}

    virtual ~ItemVisitorFullDescription() noexcept {}

    virtual void visitWeapon(Weapon& weapon) noexcept override;

    virtual void visitWeaponMod(WeaponMod& weaponMod) noexcept override;

    virtual void visitArmor(Armor& armor) noexcept override;

    virtual void visitArmorMod(ArmorMod& armorMod) noexcept override;

    virtual void visitAmmo(Ammo& ammo) noexcept override;

    virtual void visitJunk(Junk& junk) noexcept override;

    text getFullDescription() noexcept {
        return text_;
    }

private:
    void reset() noexcept {
        text_ = text{};
    }

private:
    text text_;          // full description
};

} // namespace object
} // namespace game

#endif // !ITEM_VISITOR_FULL_DESCR_HPP
