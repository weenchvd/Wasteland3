
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"locator.hpp"
#include<assert.h>

namespace game {
namespace object {

using namespace std;

const AmmoReferenceContainer            Ammo::ref_;
const AmmoText                          Ammo::text_;

///************************************************************************************************

Ammo::Ammo(Ammo::Type type, Ammo::ammo_quantity qty) noexcept
    :
    base_   { ref_.ammoReference(type) },
    qty_    { qty }
{
    assert(isInitialized());
    assert(base_.isInitialized());
    assert(qty_ >= 0);
}

flatbuffers::Offset<fbAmmo::FB_Ammo> Ammo::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    fbAmmo::FB_AmmoBuilder builder{ fbb };
    builder.add_type(AmmoTypeBiMap::toRightType(type()));
    builder.add_quantity(quantity());
    return builder.Finish();
}

unique_ptr<Item> Ammo::deserialize(const fbAmmo::FB_Ammo* fb)
{
    assert(fb != nullptr);
    const auto& f{ global::Locator::getFactory() };
    auto ammoType{ AmmoTypeBiMap::toLeftType(fb->type()) };
    Ammo::ammo_quantity quantity{ fb->quantity() };
    auto item{ f.createAmmo(ammoType, quantity) };
    return item;
}

} // namespace object
} // namespace game
