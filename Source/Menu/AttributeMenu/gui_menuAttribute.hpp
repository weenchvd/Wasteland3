
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_ATTRIBUTE_HPP
#define GUI_MENU_ATTRIBUTE_HPP

#include"common.hpp"
#include"gui_menuGeneral.hpp"
#include"imgui.h"
#include"squad.hpp"

namespace game {
namespace menu {

struct GuiMenuAttributeVars {
    object::Squad&                      squad_;
    object::Roster::ItemRange           itemRange_;
    object::InventoryIterator&          iItem_;
    object::Item*&                      pItem_;
    object::Character*&                 pChar_;
    int&                                integer_;
    const char*&                        descr_;
    bool&                               showStats_;
    bool&                               showGuiExit_;
};

class GuiMenuAttributeState {
public:
    GuiMenuAttributeState(GuiMenuGeneralVars& gVars, GuiMenuAttributeVars& vars) noexcept;

    GuiMenuAttributeState(const GuiMenuAttributeState&) = delete;
    GuiMenuAttributeState& operator=(const GuiMenuAttributeState&) = delete;

    virtual ~GuiMenuAttributeState() noexcept {}

public:
    void changeSubmenu(Submenu previousSM);

    void changeCharacter(object::Character* pCharPrev);

    void exitTheMenu(bool* open, object::Squad& squad);

private:
    object::InventoryIterator&  iItem_;
    object::Item*&              pItem_;
    object::Character*&         pChar_;
    Submenu&                    curSM_;
    const char*&                descr_;
    bool&                       showStats_;
    bool&                       showGuiExit_;
};

///************************************************************************************************

void guiMenuAttribute(bool* open, GuiMenuGeneralVars& gVars);

} // namespace menu
} // namespace game

#endif // !GUI_MENU_ATTRIBUTE_HPP
