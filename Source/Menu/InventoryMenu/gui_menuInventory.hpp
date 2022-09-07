
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_INVENTORY_HPP
#define GUI_MENU_INVENTORY_HPP

#include"imgui.h"
#include"squad.hpp"

namespace game {
namespace menu {

struct GuiMenuInventoryVars {
    object::Roster::ItemRange           items_;
    object::InventoryIterator&          item_;
    object::Item*&                      pItem_;
    bool&                               showGuiNotImplemented_;
    bool&                               showGuiRemoveItem_;
    bool&                               showGuiModifyItem_;
};

///************************************************************************************************

void guiMenuInventory(bool* open, object::Squad& squad);

///************************************************************************************************

void guiRemoveItem(bool* open,
                   object::Inventory& inventory,
                   object::InventoryIterator& item);

void guiItemList(GuiMenuInventoryVars& vars,
                 const ImVec4& colorButton,
                 const ImVec4& colorButtonHovered,
                 const ImVec4& colorButtonActive,
                 const ImVec4& colorButtonSelected);

void guiContextSensetiveMenuItem(GuiMenuInventoryVars& vars, object::InventoryIterator& item);

void guiItemFullDescription(const object::Item* item,
                            const ImVec2& size,
                            bool border,
                            ImGuiWindowFlags flags = ImGuiWindowFlags_None);

} // namespace menu
} // namespace game

#endif // !GUI_MENU_INVENTORY_HPP
