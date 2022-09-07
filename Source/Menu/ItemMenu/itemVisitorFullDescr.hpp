
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

class ItemVisitorWeaponCharacteristics : public object::ItemVisitor {
public:
    using text_t = common::Text;

private:
    static constexpr auto signSpace_    { ' ' };
    static constexpr auto signX_        { 'X' };
    static constexpr auto signPercent_  { '%' };
    static constexpr auto signDollar_   { '$' };
    static constexpr auto separator_    { "----------" };

public:
    ItemVisitorWeaponCharacteristics() noexcept {}

    ItemVisitorWeaponCharacteristics(const ItemVisitorWeaponCharacteristics&) = delete;
    ItemVisitorWeaponCharacteristics& operator=(const ItemVisitorWeaponCharacteristics&) = delete;
    ItemVisitorWeaponCharacteristics(ItemVisitorWeaponCharacteristics&&) = default;
    ItemVisitorWeaponCharacteristics& operator=(ItemVisitorWeaponCharacteristics&&) = default;

    virtual ~ItemVisitorWeaponCharacteristics() noexcept {}

public:
    virtual void visitWeapon(const object::Weapon& weapon) override;

    virtual void visitWeaponMod(const object::WeaponMod& weaponMod) override { reset(); }

    virtual void visitArmor(const object::Armor& armor) override { reset(); }

    virtual void visitArmorMod(const object::ArmorMod& armorMod) override { reset(); }

    virtual void visitAmmo(const object::Ammo& ammo) override { reset(); }

    virtual void visitJunk(const object::Junk& junk) override { reset(); }

public:
    const text_t& name() const noexcept { return name_; }

    const text_t& levelAndType() const noexcept { return levelAndType_; }

    const text_t& description() const noexcept { return descr_; }

    const text_t& installedMods() const noexcept { return installedMods_; }

    const text_t& weaponRequirements() const noexcept { return weaponReq_; }

    const text_t& penalties() const noexcept { return penalties_; }

    const text_t& damageAndDamageType() const noexcept { return dmgAndDmgType_; }

    const text_t& damageDescription() const noexcept { return dmgDescr_; }

    const text_t& attackDescription() const noexcept { return attackDescr_; }

    const text_t& actionPoints() const noexcept { return ap_; }

    const text_t& actionPointsReload() const noexcept { return apReload_; }

    const text_t& ammoCapacity() const noexcept { return ammoCapacity_; }

    const text_t& ammoType() const noexcept { return ammoType_; }

    const text_t& bonusSneakAttackDamage() const noexcept { return bonSneakAttackDmg_; }

    const text_t& bonusNormalDamage() const noexcept { return bonNormalDmg_; }

    const text_t& bonusMeleeDamage() const noexcept { return bonMeleeDmg_; }

    const text_t& bonusRangedDamage() const noexcept { return bonRangedDmg_; }

    const text_t& hitChance() const noexcept { return hitChance_; }

    const text_t& critDamage() const noexcept { return critDamage_; }

    const text_t& critChance() const noexcept { return critChance_; }

    const text_t& penetration() const noexcept { return penetration_; }

    const text_t& price() const noexcept { return price_; }

private:
    void reset() noexcept {
        name_               = text_t{};
        levelAndType_       = text_t{};
        descr_              = text_t{};
        installedMods_      = text_t{};
        weaponReq_          = text_t{};
        penalties_          = text_t{};
        dmgAndDmgType_      = text_t{};
        dmgDescr_           = text_t{};
        attackDescr_        = text_t{};
        ap_                 = text_t{};
        apReload_           = text_t{};
        ammoCapacity_       = text_t{};
        ammoType_           = text_t{};
        bonSneakAttackDmg_  = text_t{};
        bonNormalDmg_       = text_t{};
        bonMeleeDmg_        = text_t{};
        bonRangedDmg_       = text_t{};
        hitChance_          = text_t{};
        critDamage_         = text_t{};
        critChance_         = text_t{};
        penetration_        = text_t{};
        price_              = text_t{};
    }

private:
    text_t name_;
    text_t levelAndType_;
    text_t descr_;
    text_t installedMods_;
    text_t weaponReq_;
    text_t penalties_;
    text_t dmgAndDmgType_;
    text_t dmgDescr_;
    text_t attackDescr_;
    text_t ap_;
    text_t apReload_;
    text_t ammoCapacity_;
    text_t ammoType_;
    text_t bonSneakAttackDmg_;
    text_t bonNormalDmg_;
    text_t bonMeleeDmg_;
    text_t bonRangedDmg_;
    text_t hitChance_;
    text_t critDamage_;
    text_t critChance_;
    text_t penetration_;
    text_t price_;
};

///************************************************************************************************

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
