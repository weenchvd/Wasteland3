
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
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
}

} // namespace object
} // namespace game
