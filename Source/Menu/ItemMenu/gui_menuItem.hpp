
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_ITEM_HPP
#define GUI_MENU_ITEM_HPP

#include"squad.hpp"

namespace game {
namespace menu {

void guiMenuItemModify(bool* open, object::Squad& squad, object::Item& item);

///************************************************************************************************

} // namespace menu
} // namespace game

#endif // !GUI_MENU_ITEM_HPP
