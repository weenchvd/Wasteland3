
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
#include<type_traits>
#include<vector>

namespace Game {
namespace Global {

class Factory; // TODO delete?

} // namespace Global

namespace Object {

class Weapon;

class WeaponMod : public Item {
public:
    using Model         = WeaponMod__Model;
    using Type          = WeaponMod__Type;

    friend Game::Global::Factory;

protected:
    explicit WeaponMod(WeaponMod::Model model) noexcept;

public:
    WeaponMod(const WeaponMod&) = delete;
    WeaponMod& operator=(const WeaponMod&) = delete;

    virtual ~WeaponMod() noexcept {}

    static void initializeReference() {
        if (ref_.size() == 0) initRef();
    }

    virtual void accept(ItemVisitor& visitor) noexcept override {
        visitor.visitWeaponMod(*this);
    }

    void apply(Weapon& weapon);

/// weapon mod parameters
public:
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

    Common::Text name() const noexcept {
        return base_.name_;
    }

private:
    static void initRef();

    static void add(WeaponModReference ref) {
        ref_[static_cast<std::underlying_type_t<WeaponMod::Model>>(ref.model_)] = std::move(ref);
    }

private:
    const WeaponModReference&  base_;           // reference, sample, template

    static std::vector<WeaponModReference>  ref_;           // references
};

} // namespace Object
} // namespace Game

#endif // !WEAPON_MOD_HPP
