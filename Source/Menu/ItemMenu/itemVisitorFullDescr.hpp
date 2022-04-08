
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
namespace menu {

class ItemVisitorFullDescription : public object::ItemVisitor {
public:
    using text_t = common::Text;

private:
    static constexpr auto signSpace_    { ' ' };
    static constexpr auto signX_        { 'X' };
    static constexpr auto signPercent_  { '%' };
    static constexpr auto signDollar_   { '$' };
    static constexpr auto separator_    { "----------" };

public:
    ItemVisitorFullDescription() noexcept {}

    ItemVisitorFullDescription(const ItemVisitorFullDescription&) = delete;
    ItemVisitorFullDescription& operator=(const ItemVisitorFullDescription&) = delete;
    ItemVisitorFullDescription(ItemVisitorFullDescription&&) = default;
    ItemVisitorFullDescription& operator=(ItemVisitorFullDescription&&) = default;

    virtual ~ItemVisitorFullDescription() noexcept {}

public:
    virtual void visitWeapon(const object::Weapon& weapon) override;

    virtual void visitWeaponMod(const object::WeaponMod& weaponMod) override;

    virtual void visitArmor(const object::Armor& armor) override;

    virtual void visitArmorMod(const object::ArmorMod& armorMod) override;

    virtual void visitAmmo(const object::Ammo& ammo) override;

    virtual void visitJunk(const object::Junk& junk) override;

public:
    const text_t& getFullDescription() const noexcept { return text_; }

private:
    void reset() noexcept {
        text_ = text_t{};
    }

private:
    text_t text_;          // full description
};

///************************************************************************************************

class WeaponList {
public:
    using list_t = std::vector<object::Weapon__Type>;

private:
    static constexpr auto sizeWeaponType_   { common::numberOf<object::Weapon__Type>() };
    static constexpr auto sizeWeaponModType_{ common::numberOf<object::WeaponMod__Type>() };

public:
    WeaponList() noexcept {}

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static const list_t& getList(object::WeaponMod__Type id);

private:
    static std::vector<list_t>      list_;
    static bool                     initialized_;
};

///************************************************************************************************

inline const WeaponList::list_t& WeaponList::getList(object::WeaponMod__Type id)
{
    assert(common::isValidEnum(id));
    initialize();
    return list_[common::toUnderlying(id)];
}

} // namespace menu
} // namespace game

#endif // !ITEM_VISITOR_FULL_DESCR_HPP
