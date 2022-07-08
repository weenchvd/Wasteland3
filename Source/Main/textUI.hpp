
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TEXT_UI_HPP
#define TEXT_UI_HPP

#include"inventory.hpp"
#include"squad.hpp"
#include<memory>

void textUI(
    std::unique_ptr<game::object::Squad>& squad,
    std::unique_ptr<game::object::Inventory>& shop);

#endif // !TEXT_UI_HPP
