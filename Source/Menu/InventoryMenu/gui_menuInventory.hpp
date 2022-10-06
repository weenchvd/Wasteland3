
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_INVENTORY_HPP
#define GUI_MENU_INVENTORY_HPP

#include"common.hpp"
#include"gui_menuGeneral.hpp"
#include"imgui.h"
#include"squad.hpp"

namespace game {
namespace menu {

enum class LastItemType : char {
    ALL,
    WEAPON,
    WEAPON_MOD,
    AMMO
};

struct GuiMenuInventoryVars {
    object::Squad&                      squad_;
    object::Roster::ItemRange           itemRange_;
    object::InventoryIterator&          iItem_;
    object::Item*&                      pItem_;
    object::Character*&                 pChar_;
    int&                                integer_;
    bool&                               showGuiRemoveItem_;
    bool&                               showGuiModifyItem_;
    bool&                               showGuiEquipItem_;
};

///************************************************************************************************

void guiMenuInventory(bool* open, GuiMenuGeneralVars& gVars);

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

void guiShowStats(object::Character& ch,
                  const char ph,
                  const float tw);

void guiPrintText(const common::Text& left,
                  const common::Text& right,
                  const char placeholder,
                  const float totalWidth);

} // namespace menu
} // namespace game

#endif // !GUI_MENU_INVENTORY_HPP
