
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ITEM_COMMON_HPP
#define MENU_ITEM_COMMON_HPP

#include"attack.hpp"
#include"common.hpp"
#include"damage.hpp"
#include"menuCommon.hpp"

namespace game {
namespace menu {

common::Text getDamageDescription(
    const Indent indent,
    const object::Damage::Type type
);

common::Text getAttackDescription(
    const Indent indent,
    const object::Attack& attack
);

} // namespace menu
} // namespace game

#endif // !MENU_ITEM_COMMON_HPP
