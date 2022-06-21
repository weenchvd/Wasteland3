
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_HPP
#define AMMO_HPP

#include"ammoCommon.hpp"
#include"ammoFB_generated.h"
#include"ammoReference.hpp"
#include"ammoText.hpp"
#include"common.hpp"
#include"item.hpp"
#include<assert.h>

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

    virtual void accept(ItemVisitor& visitor) const noexcept override {
        visitor.visitAmmo(*this);
    }

    flatbuffers::Offset<fbAmmo::FB_Ammo> serialize(
        flatbuffers::FlatBufferBuilder& fbb) const;

    static std::unique_ptr<Item> deserialize(const fbAmmo::FB_Ammo* fb);

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

    virtual const text& name() const noexcept override {
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
        assert(qty_ >= 0);
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
    AmmoTypeBiMap::initialize();
    ref_.initialize();
    text_.initialize();
}

inline bool Ammo::isInitialized()
{
    return ref_.isInitialized() &&
           text_.isInitialized() &&
           AmmoTypeBiMap::isInitialized();
}

} // namespace object
} // namespace game

#endif // !AMMO_HPP
