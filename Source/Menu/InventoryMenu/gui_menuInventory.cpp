
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"gui_menuCommon.hpp"
#include"gui_menuInventory.hpp"
#include"imgui.h"
#include"inventory.hpp"
#include"itemVisitorFullDescr.hpp"
#include"itemVisitorType.hpp"
#include"menuCommonText.hpp"
#include"menuInventoryText.hpp"
#include"menuItemText.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void guiMenuInventory(bool* open, object::Squad& squad)
{
    using game::object::InventoryIterator;
    using game::object::Item;

    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };

    auto& roster{ squad.inventory().roster() };

    static InventoryIterator item;
    static const Item* selected{ nullptr };

    static bool showGuiNotImplemented   { false };
    static bool showGuiRemoveItem       { false };
    static bool showGuiModifyItem       { false };

    guiPopupMessage(&showGuiNotImplemented, u8"##NotImplemented", comT.notImplemented().c_str());
    if (showGuiRemoveItem) {
        bool itemIsSelected{ false };
        if (item.isValid() && selected == (*item.getConst()).get()) {
            itemIsSelected = true;
        }
        guiRemoveItem(&showGuiRemoveItem, squad.inventory(), item);
        if (itemIsSelected && !item.isValid()) {
            selected = nullptr;
        }
    }

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.menuName().c_str() } + u8"###MenuInventory";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        const ImGuiStyle& style{ ImGui::GetStyle() };
        ImVec2 contentRegionSize{ ImGui::GetWindowContentRegionMax() };

        ostringstream oss;
        oss << text.money() << sign::colon << sign::space << sign::dollar << squad.money() << endl;
        ImGui::Text(oss.str().c_str());

        ImVec2 columnSize{
            contentRegionSize.x / 2.0f - style.ItemSpacing.x, contentRegionSize.y * 0.7f
        };

        ImGui::NewLine();
        ImVec2 tableSize{ contentRegionSize.x, ImGui::GetFrameHeight() };
        if (ImGui::BeginTable("Titles", 2, ImGuiTableFlags_None, tableSize))
        {
            ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed, columnSize.x);

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            s = string{ text.inventory().c_str() } + sign::space + sign::lp
                + text.colorNewItems().c_str() + sign::rp + sign::colon;
            ImGui::TextUnformatted(s.c_str());

            ImGui::TableNextColumn();
            s = string{ comT.description().c_str() } + sign::colon;
            ImGui::TextUnformatted(s.c_str());

            ImGui::EndTable();
        }

        if (ImGui::BeginChild("ItemList", columnSize, true, ImGuiWindowFlags_AlwaysVerticalScrollbar)) {
            const ImVec4 colorTurquoise { 17.0f / 255.0f, 118.0f / 255.0f, 113.0f / 255.0f, 1.0f };
            const ImVec4 colorYellow    { 195.0f / 255.0f, 151.0f / 255.0f, 0.0f / 255.0f, 1.0f };
            const ImVec4 colorYellowDark{ 125.0f / 255.0f, 97.0f / 255.0f, 0.0f / 255.0f, 1.0f };
            const ImVec4 colorGray      { 150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f, 1.0f };
            const ImVec4 colorGrayDark  { 80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f, 1.0f };

            GuiMenuInventoryVars vars{
                squad.inventory().roster().newItems(),
                item,
                selected,
                showGuiNotImplemented,
                showGuiRemoveItem,
                showGuiModifyItem
            };
            guiItemList(vars, colorYellowDark, colorYellow, colorTurquoise, colorTurquoise);

            vars.items_ = squad.inventory().roster().oldItems();
            guiItemList(vars, colorGrayDark, colorGray, colorTurquoise, colorTurquoise);

            ImGui::EndChild();
        }

        ImGui::SameLine();
        if (ImGui::BeginChild("ItemDescription", columnSize, true)) {
            if (selected != nullptr) {
                ItemVisitorFullDescription vis;
                selected->accept(vis);
                ImGui::PushTextWrapPos();
                ImGui::TextUnformatted(vis.getFullDescription().c_str());
                ImGui::PopTextWrapPos();
            }
            ImGui::EndChild();
        }

        ImGui::NewLine();
        if (ImGui::Button(comT.exitMenu().c_str())) {
            selected = nullptr;
            *open = false;
        }

        ImGui::End();
    }
}

///************************************************************************************************

void guiRemoveItem(bool* open,
                   object::Inventory& inventory,
                   object::InventoryIterator& item)
{
    assert(open != nullptr);
    assert(item.isValid() == true);

    const auto& text{ MenuItemText::common() };

    YesNo result{ YesNo::INVALID };
    guiGetYesNo(open, u8"##QuestionRemoveItem", text.questionDeleteItem().c_str(), result);
    switch (result) {
    case YesNo::YES: {
        inventory.extract(item);
        *open = false;
        break;
    }
    case YesNo::NO:
        *open = false;
        break;
    }
}

void guiItemList(GuiMenuInventoryVars& vars,
                 const ImVec4& colorButton,
                 const ImVec4& colorButtonHovered,
                 const ImVec4& colorButtonActive,
                 const ImVec4& colorButtonSelected)
{
    using game::object::Item;
    using game::object::Roster;

    const auto& comT{ MenuCommonText::common() };

    const ImGuiStyle& style{ ImGui::GetStyle() };
    const ImVec2 buttonPaddingX2{ style.FramePadding.x * 2, style.FramePadding.y * 2 };
    const auto buttonHeight{ ImGui::GetFrameHeight() };
    const auto windowVisibleX{ ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x };

    ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorButtonHovered);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorButtonActive);
    for (auto iter{ vars.items_.beg_ }; iter != vars.items_.end_; ++iter)
    {
        const Item* item{ iter.getConst()->get() };
        ImGui::PushID(item);

        static bool popStyleColor{ false };
        if (vars.selected_ == item) {
            popStyleColor = true;
            ImGui::PushStyleColor(ImGuiCol_Button, colorButtonSelected);
        }
        auto textSize{ ImGui::CalcTextSize(item->name().c_str()) };
        ImVec2 buttonSize{ textSize.x + buttonPaddingX2.x, buttonHeight };
        if (ImGui::Button(item->name().c_str(), buttonSize)) {
            vars.selected_ = item;
        }
        if (ImGui::BeginPopupContextItem("ContextMenu")) {
            if (ImGui::Selectable(comT.remove().c_str())) {
                vars.showGuiRemoveItem_ = true;
                vars.item_ = iter;
            }
            guiContextSensetiveMenuItem(vars, iter);
            ImGui::EndPopup();
        }
        if (popStyleColor) {
            popStyleColor = false;
            ImGui::PopStyleColor();
        }

        auto iterNext{ iter };
        if (++iterNext != vars.items_.end_) {
            const auto textSize{
                ImGui::CalcTextSize(iterNext.getConst()->get()->name().c_str())
            };
            const auto buttonWidth{ textSize.x + buttonPaddingX2.x };
            const auto buttonEndPosX{
                ImGui::GetItemRectMax().x + style.ItemSpacing.x + buttonWidth
            };
            if (buttonEndPosX < windowVisibleX) {
                ImGui::SameLine();
            }
        }

        ImGui::PopID();
    }
    ImGui::PopStyleColor(3);
}

void guiContextSensetiveMenuItem(GuiMenuInventoryVars& vars, object::InventoryIterator& item)
{
    const auto& text{ MenuItemText::common() };
    object::ItemVisitorType vis;
    (*item.getConst())->accept(vis);
    

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        if (ImGui::Selectable(text.equip().c_str())) {
            vars.showGuiNotImplemented_ = true;
        }
        if (ImGui::Selectable(text.modify().c_str())) {
            vars.showGuiNotImplemented_ = true;
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
}

} // namespace menu
} // namespace game
