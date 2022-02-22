
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_HPP
#define WEAPON_MOD_HPP

#include"common.hpp"
#include"item.hpp"
#include"weaponModCommon.hpp"
#include"weaponModReference.hpp"
#include"weaponModText.hpp"
#include<type_traits>
#include<vector>

namespace game {
namespace global {

class Factory;

} // namespace global

namespace object {

class Weapon;

class WeaponMod : public Item {
public:
    using Model         = WeaponMod__Model;
    using Type          = WeaponMod__Type;
    using text          = common::Text;

private:
    friend global::Factory;

protected:
    explicit WeaponMod(WeaponMod::Model model) noexcept;

public:
    WeaponMod(const WeaponMod&) = delete;
    WeaponMod& operator=(const WeaponMod&) = delete;

    virtual ~WeaponMod() noexcept {}

    static void initialize();

    static bool isInitialized();

    virtual void accept(ItemVisitor& visitor) noexcept override {
        visitor.visitWeaponMod(*this);
    }

    void apply(Weapon& weapon) noexcept;

/// weapon mod parameters
public:
    const WeaponModReference& weaponModReference() noexcept {
        return base_;
    }

    virtual Item::Type itemType() const noexcept override {
        return Item::Type::WEAPONMOD;
    }

    virtual Item::Model itemModel() const noexcept override {
        return static_cast<Item::Model>(base_.model_);
    }

    WeaponMod::Model model() const noexcept {
        return base_.model_;
    }

    WeaponMod::Type type() const noexcept {
        return base_.type_;
    }

    const WeaponModRequirements& requirements() const noexcept {
        return base_.requirements_;
    }

    const text& name() const noexcept {
        return base_.name();
    }

    const text& description() const noexcept {
        return base_.descr();
    }

public:
    static const WeaponModReference& weaponModReference(WeaponMod::Model id) noexcept {
        return ref_.weaponModReference(id);
    }

    static const WeaponModText& weaponModText() noexcept {
        return text_;
    }

private:
    const WeaponModReference&  base_;           // reference, sample, template

    static const WeaponModReferenceContainer    ref_;
    static const WeaponModText                  text_;
};

///************************************************************************************************

inline void WeaponMod::initialize()
{
    ref_.initialize();
    text_.initialize();
}

inline bool WeaponMod::isInitialized()
{
    return ref_.isInitialized()
        && text_.isInitialized();
}

} // namespace object
} // namespace game

#endif // !WEAPON_MOD_HPP
