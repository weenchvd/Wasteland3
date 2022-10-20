
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"gui_menuAttribute.hpp"
#include"gui_menuGeneral.hpp"
#include"gui_menuInventory.hpp"
#include"gui_menuSkill.hpp"
#include"inventory.hpp"
#include"item.hpp"
#include"menuAttributeText.hpp"
#include"menuCharacterText.hpp"
#include"menuCommon.hpp"
#include"menuInventoryText.hpp"
#include"menuItemText.hpp"
#include"menuSkillText.hpp"
#include"menuSquadText.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void guiMenuGeneral(bool* open, object::Squad& squad)
{
    static Submenu                      current{ Submenu::INVENTORY };
    static Submenu                      previous{ Submenu::INVENTORY };

    static object::InventoryIterator    iItem{};
    static object::Item*                pItem{ nullptr };
    static object::Character*           pChar{ nullptr };
    static int                          integer{ 0 };

    static bool showGuiMenuInventory    { true };
    static bool showGuiMenuAttribute    { false };
    static bool showGuiMenuSkill        { false };

    switch (current) {
    case Submenu::INVENTORY:
        showGuiMenuInventory    = true;
        showGuiMenuAttribute    = false;
        showGuiMenuSkill        = false;
        break;
    case Submenu::ATTRIBUTES:
        showGuiMenuInventory    = false;
        showGuiMenuAttribute    = true;
        showGuiMenuSkill        = false;
        break;
    case Submenu::SKILLS:
        showGuiMenuInventory    = false;
        showGuiMenuAttribute    = false;
        showGuiMenuSkill        = true;
        break;
    }

    GuiMenuGeneralVars vars{
        squad,
        squad.inventory().roster().oldItems(),
        iItem,
        pItem,
        pChar,
        integer,
        current,
        previous
    };

    if (showGuiMenuInventory)           guiMenuInventory(&showGuiMenuInventory, vars);
    if (showGuiMenuAttribute)           guiMenuAttribute(&showGuiMenuAttribute, vars);
    if (showGuiMenuSkill)               guiMenuSkill(&showGuiMenuSkill, vars);

    if (!(showGuiMenuInventory || showGuiMenuAttribute || showGuiMenuSkill)) {
        current = Submenu::INVENTORY;
        *open = false;
    }
}

///************************************************************************************************

void guiMenuGeneral_Submenu(GuiMenuGeneralVars& vars)
{
    const auto& style{ ImGui::GetStyle() };
    ImGuiTableFlags_ tableSubmenusFlags{ static_cast<ImGuiTableFlags_>(
        ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame
    ) };
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2{ 0.0f, 0.0f });
    if (ImGui::BeginTable("Submenus", 5, tableSubmenusFlags)) {
        bool isActiveSubmenu{ false };
        const ImVec2 buttonSizeSubmenus{
            ImGui::GetWindowContentRegionMax().x / 5,
            ImGui::GetFrameHeight() * 2.0f + style.ItemSpacing.y
        };
        vars.prevSM_ = vars.curSM_;

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        isActiveSubmenu = (vars.curSM_ == Submenu::INVENTORY) ? true : false;
        if (isActiveSubmenu) {
            ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonActive]);
        }
        if (ImGui::Button(MenuInventoryText::common().inventory().c_str(), buttonSizeSubmenus)) {
            vars.curSM_ = Submenu::INVENTORY;
        }
        if (isActiveSubmenu) {
            ImGui::PopStyleColor();
        }

        ImGui::TableNextColumn();
        isActiveSubmenu = (vars.curSM_ == Submenu::ATTRIBUTES) ? true : false;
        if (isActiveSubmenu) {
            ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonActive]);
        }
        if (ImGui::Button(MenuAttributeText::common().attributes().c_str(), buttonSizeSubmenus)) {
            vars.curSM_ = Submenu::ATTRIBUTES;
        }
        if (isActiveSubmenu) {
            ImGui::PopStyleColor();
        }

        ImGui::TableNextColumn();
        isActiveSubmenu = (vars.curSM_ == Submenu::SKILLS) ? true : false;
        if (isActiveSubmenu) {
            ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonActive]);
        }
        if (ImGui::Button(MenuSkillText::common().skills().c_str(), buttonSizeSubmenus)) {
            vars.curSM_ = Submenu::SKILLS;
        }
        if (isActiveSubmenu) {
            ImGui::PopStyleColor();
        }

        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
}

void guiMenuGeneral_SquadMembers(GuiMenuGeneralVars& vars)
{
    const auto& style{ ImGui::GetStyle() };
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted(MenuSquadText::common().squad().c_str());

    ImGuiTableFlags_ tableSquadMembersFlags{ static_cast<ImGuiTableFlags_>(
        ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame
    ) };
    int squadSize{ 0 };
    for (int i = 0; i < vars.squad_.members().size(); ++i) {
        if (vars.squad_.members()[i] != nullptr) {
            ++squadSize;
        }
    }
    const ImVec2 buttonSizeSquadMembers{
        150.0f, ImGui::GetFrameHeight() * 2.0f + style.ItemSpacing.y
    };
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2{ 0.0f, 0.0f });
    if (ImGui::BeginTable("SquadMembers", squadSize, tableSquadMembersFlags,
        ImVec2{ buttonSizeSquadMembers.x * squadSize, 0.0f }))
    {
        ImGui::TableNextRow();
        for (int i = 0; i < vars.squad_.members().size(); ++i) {
            if (vars.squad_.members()[i] != nullptr) {
                auto& member{ vars.squad_.members()[i] };
                ImGui::TableNextColumn();
                bool setColorButton{ vars.pChar_ == member.get() ? true : false };
                if (setColorButton) {
                    ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonActive]);
                }
                if (ImGui::Button(member->name().c_str(), buttonSizeSquadMembers)) {
                    if (vars.pChar_) {
                        bool selectedItemBelongsToSelectedCharacter{ false };
                        for (int i = 0; i < vars.pChar_->slotWeapon().size(); ++i) {
                            if (vars.pChar_->slotWeapon()[i].get() == vars.pItem_) {
                                selectedItemBelongsToSelectedCharacter = true;
                                break;
                            }
                        }
                        if (selectedItemBelongsToSelectedCharacter &&
                            vars.pChar_ != member.get())
                        {
                            vars.pItem_ = nullptr;
                        }
                    }
                    vars.pChar_ = static_cast<object::Character*>(member.get());
                }
                if (setColorButton) {
                    ImGui::PopStyleColor();
                }
            }
        }

        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
}

void guiWindowUnit(GuiMenuGeneralVars& gVars,
                   const GuiWindowUnitColors& col,
                   const ImVec2& windowSize,
                   bool& showStats,
                   bool& showGuiModifyItem)
{
    if (ImGui::BeginChild("Unit", windowSize, true)) {
        object::Character*& pChar{ gVars.pChar_ };
        if (pChar != nullptr) {
            object::Item*& pItem{ gVars.pItem_ };
            int& integer{ gVars.integer_ };
            object::Squad& squad{ gVars.squad_ };
            const ImGuiStyle& style{ ImGui::GetStyle() };
            ImGui::PushStyleColor(ImGuiCol_Button, col.colSlot_);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, col.colSlotHovered_);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, col.colSlotActive_);

            ImGui::TextUnformatted(pChar->name().c_str());
            ostringstream oss;
            oss << object::CharacterText::common().level() << sign::space << pChar->level()
                << sign::space << pChar->characterText().type(pChar->type());
            ImGui::TextUnformatted(oss.str().c_str());
            ImGui::NewLine();
            if (showStats) {
                for (int i = 0; i < pChar->slotWeapon().size(); ++i) {
                    if (pChar->slotWeapon()[i].get() == pItem) {
                        pItem = nullptr;
                        break;
                    }
                }
                int totalWidth =
                    windowSize.x - style.WindowPadding.x * 2.0f - style.ScrollbarSize;
                guiShowStats(*pChar, sign::dot, totalWidth);
            }
            else if (gVars.curSM_ == Submenu::INVENTORY) {
                ImVec2 buttonSize{
                    windowSize.x - style.ItemSpacing.x * 2.0f, ImGui::GetFrameHeight()
                };
                ostringstream oss;
                for (int i = 0; i < pChar->slotWeapon().size(); ++i) {
                    auto& slot{ pChar->slotWeapon()[i] };
                    ImGui::PushID(i);
                    oss.str("");
                    oss << MenuCharacterText::common().weapon() << sign::space << i + 1;
                    ImGui::TextUnformatted(oss.str().c_str());
                    bool setColorButton{ false };
                    if (pItem) {
                        if (pItem == slot.get()) {
                            setColorButton = true;
                            ImGui::PushStyleColor(ImGuiCol_Button, col.colItemSelected_);
                        }
                        else if (object::isCompatible(object::Item::Type::WEAPON, pItem->itemType())) {
                            setColorButton = true;
                            ImGui::PushStyleColor(ImGuiCol_Button, col.colSlotCompatible_);
                        }
                    }
                    if (slot != nullptr) {
                        if (ImGui::Button(slot->name().c_str(), buttonSize)) {
                            pItem = slot.get();
                        }
                        if (ImGui::BeginPopupContextItem("ContextMenu")) {
                            if (ImGui::Selectable(MenuItemText::common().unequip().c_str())) {
                                unique_ptr<object::Item> oldMod{};
                                pChar->unsetWeapon(i, oldMod);
                                if (oldMod != nullptr) {
                                    squad.inventory().insert(oldMod);
                                }
                            }
                            if (ImGui::Selectable(MenuItemText::common().modify().c_str())) {
                                showGuiModifyItem = true;
                                pItem = slot.get();
                            }
                            ImGui::EndPopup();
                        }
                        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                            pItem = slot.get();
                            integer = i;
                            ImGui::SetDragDropPayload("EquippedItem",
                                &integer, sizeof(integer));
                            ImGui::TextUnformatted(slot->name().c_str());
                            ImGui::EndDragDropSource();
                        }
                    }
                    else {
                        ImGui::Button("##EmptySlot", buttonSize);
                    }
                    if (ImGui::BeginDragDropTarget()) {
                        const ImGuiPayload* payload{
                            ImGui::AcceptDragDropPayload("EquippedItem")
                        };
                        if (payload) {
                            assert(payload->DataSize == sizeof(integer));
                            int index{ *static_cast<int*>(payload->Data) };
                            assert(index >= 0 && index < pChar->slotWeapon().size());
                            unique_ptr<object::Item> weapon1{};
                            unique_ptr<object::Item> weapon2{};
                            pChar->unsetWeapon(i, weapon1);
                            pChar->unsetWeapon(index, weapon2);
                            pChar->setWeapon(i, weapon2);
                            pChar->setWeapon(index, weapon1);
                        }
                        ImGui::EndDragDropTarget();
                    }
                    if (ImGui::BeginDragDropTarget()) {
                        const ImGuiPayload* payload{
                            ImGui::AcceptDragDropPayload("InventoryItem")
                        };
                        if (payload) {
                            assert(payload->DataSize == sizeof(object::InventoryIterator));
                            object::InventoryIterator iter{
                                *static_cast<object::InventoryIterator*>(payload->Data)
                            };
                            assert(iter.isValid());
                            if (object::isCompatible(object::Item::Type::WEAPON,
                                iter.get()->get()->itemType()))
                            {
                                auto newWeapon{ squad.inventory().extract(iter) };
                                unique_ptr<object::Item> oldWeapon{};
                                pChar->unsetWeapon(i, oldWeapon);
                                pChar->setWeapon(i, newWeapon);
                                if (oldWeapon != nullptr) {
                                    squad.inventory().insert(oldWeapon);
                                }
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }
                    if (setColorButton) {
                        ImGui::PopStyleColor();
                    }
                    ImGui::PopID();
                }
            }
            ImGui::PopStyleColor(3);
        }
    }
    ImGui::EndChild();
}

} // namespace menu
} // namespace game
