
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_SKILL_HPP
#define GUI_MENU_SKILL_HPP

#include"common.hpp"
#include"gui_menuGeneral.hpp"
#include"imgui.h"
#include"squad.hpp"

namespace game {
namespace menu {

struct GuiMenuSkillVars {
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

class GuiMenuSkillState {
public:
    GuiMenuSkillState(GuiMenuGeneralVars& gVars, GuiMenuSkillVars& vars) noexcept;

    GuiMenuSkillState(const GuiMenuSkillState&) = delete;
    GuiMenuSkillState& operator=(const GuiMenuSkillState&) = delete;

    virtual ~GuiMenuSkillState() noexcept {}

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

void guiMenuSkill(bool* open, GuiMenuGeneralVars& gVars);

} // namespace menu
} // namespace game

#endif // !GUI_MENU_SKILL_HPP
