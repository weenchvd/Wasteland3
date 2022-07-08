
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_MAIN_HPP
#define GUI_MENU_MAIN_HPP

#include"inventory.hpp"
#include"squad.hpp"
#include<memory>

namespace game {
namespace menu {

void guiMenuMain(
    std::unique_ptr<game::object::Squad>& squad,
    std::unique_ptr<game::object::Inventory>& shop,
    bool* open);

} // namespace menu
} // namespace game

#endif // !GUI_MENU_MAIN_HPP
