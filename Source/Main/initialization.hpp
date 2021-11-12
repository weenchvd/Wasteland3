
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef INITIALIZATION_HPP
#define INITIALIZATION_HPP

#include"inventory.hpp"
#include"squad.hpp"
#include"unit.hpp"
#include<array>
#include<memory>

namespace Init
{
    void initializeSquad(Game::Object::Squad& squad);

    void initializeInventory(Game::Object::Inventory& inventory);

    void initializeShop(Game::Object::Inventory& inventory);

    void initializeMembers(std::array<std::unique_ptr<Game::Object::Unit>, Game::Object::nMembers>& members);

}

#endif // !INITIALIZATION_HPP
