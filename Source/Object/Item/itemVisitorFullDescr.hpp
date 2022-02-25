
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_VISITOR_FULL_DESCR_HPP
#define ITEM_VISITOR_FULL_DESCR_HPP

#include"common.hpp"
#include"itemVisitor.hpp"
#include"weaponCommon.hpp"
#include"weaponModCommon.hpp"
#include<vector>

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

///************************************************************************************************

class WeaponList {
public:
    using list                  = std::vector<Weapon__Type>;

private:
    static constexpr auto sizeWeaponType_   { common::numberOf<Weapon__Type>() };
    static constexpr auto sizeWeaponModType_{ common::numberOf<WeaponMod__Type>() };

public:
    WeaponList() noexcept {}

    static void initialize() noexcept;

    static bool isInitialized() { return initialized_; }

    static const list& getList(WeaponMod__Type id) noexcept;

private:
    static std::vector<list>        list_;
    static bool                     initialized_;
};

///************************************************************************************************

inline const WeaponList::list& WeaponList::getList(WeaponMod__Type id) noexcept
{
    assert(common::isValidEnum(id));
    initialize();
    return list_[common::toUnderlying(id)];
}

} // namespace object
} // namespace game

#endif // !ITEM_VISITOR_FULL_DESCR_HPP
