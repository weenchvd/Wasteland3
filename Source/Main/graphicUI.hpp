
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GRAPHIC_UI_HPP
#define GRAPHIC_UI_HPP

#include"inventory.hpp"
#include"squad.hpp"
#include<memory>

void graphicUI(
    std::unique_ptr<game::object::Squad>& squad,
    std::unique_ptr<game::object::Inventory>& shop);

#endif // !GRAPHIC_UI_HPP
