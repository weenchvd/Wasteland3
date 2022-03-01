
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_HPP
#define AMMO_HPP

#include"ammoCommon.hpp"
#include"ammoReference.hpp"
#include"ammoText.hpp"
#include"common.hpp"
#include"item.hpp"

namespace game {
namespace global {

class Factory;

} // namespace global

namespace object {

class Ammo : public Item {
public:
    using Type              = Ammo__Type;
    using text              = common::Text;
    using ammo_quantity     = short int;

private:
    friend global::Factory;

private:
    explicit Ammo(Ammo::Type type, ammo_quantity qty) noexcept;

public:
    Ammo(const Ammo&) = delete;
    Ammo& operator=(const Ammo&) = delete;

    virtual ~Ammo() noexcept {}

    static void initialize();

    static bool isInitialized();

    virtual void accept(ItemVisitor& visitor) noexcept override {
        visitor.visitAmmo(*this);
    }

public:
    virtual Item::Type itemType() const noexcept override {
        return Item::Type::AMMO;
    }

    virtual Item::Model itemModel() const noexcept override {
        return static_cast<Item::Model>(base_.type_);
    }

    Ammo::Type type() const noexcept {
        return base_.type_;
    }

    const text& name() const noexcept {
        return base_.name();
    }

    const text& description() const noexcept {
        return base_.descr();
    }

    common::Price price() const noexcept {
        return base_.price_;
    }

    ammo_quantity quantity() const noexcept {
        return qty_;
    }

    void quantityAdd(ammo_quantity shift) noexcept {
        qty_ += shift;
    }

public:
    static const AmmoReferenceContainer& ammoReferenceContainer() noexcept {
        return ref_;
    }

    static const AmmoText& ammoText() noexcept {
        return text_;
    }

private:
    const AmmoReference&    base_;

    ammo_quantity           qty_;           // quantity of ammo

    static const AmmoReferenceContainer         ref_;
    static const AmmoText                       text_;
};

///************************************************************************************************

inline void Ammo::initialize()
{
    ref_.initialize();
    text_.initialize();
}

inline bool Ammo::isInitialized()
{
    return ref_.isInitialized()
        && text_.isInitialized();
}

} // namespace object
} // namespace game

#endif // !AMMO_HPP
