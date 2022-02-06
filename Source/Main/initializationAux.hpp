
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef INITIALIZATION_AUX_HPP
#define INITIALIZATION_AUX_HPP

#include"inventory.hpp"
#include"squad.hpp"
#include"unit.hpp"
#include<array>
#include<memory>

namespace init {

void initializeSquad(game::object::Squad& squad);

void initializeInventory(game::object::Inventory& inventory);

void initializeShop(game::object::Inventory& inventory);

void initializeMembers(std::array<std::unique_ptr<game::object::Unit>, game::object::nMembers>& members);

} // namespace init

#endif // !INITIALIZATION_AUX_HPP
