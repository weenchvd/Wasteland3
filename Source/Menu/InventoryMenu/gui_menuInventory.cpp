
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"gui_menuCommon.hpp"
#include"gui_menuInventory.hpp"
#include"gui_menuItem.hpp"
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

    static InventoryIterator    item;
    static Item*                pItem{ nullptr };

    static bool showGuiNotImplemented   { false };
    static bool showGuiRemoveItem       { false };
    static bool showGuiModifyItem       { false };

    guiPopupMessage(&showGuiNotImplemented, u8"##NotImplemented", comT.notImplemented().c_str());
    if (showGuiRemoveItem) {
        bool itemIsSelected{ false };
        if (item.isValid() && pItem == item.getConst()->get()) {
            itemIsSelected = true;
        }
        guiRemoveItem(&showGuiRemoveItem, squad.inventory(), item);
        if (itemIsSelected && !item.isValid()) {
            pItem = nullptr;
        }
    }
    if (showGuiModifyItem) guiMenuItemModify(&showGuiModifyItem, squad, *pItem);

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.menuName().c_str() } + u8"###MenuInventory";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        const ImGuiStyle& style{ ImGui::GetStyle() };
        ImVec2 contentRegionSize{ ImGui::GetWindowContentRegionMax() };
        ImVec2 columnSize{
            contentRegionSize.x / 2.0f - style.ItemSpacing.x,
            contentRegionSize.y - style.ItemSpacing.y - ImGui::GetFrameHeightWithSpacing() * 5.0f
        };

        ostringstream oss;
        oss << text.money() << sign::colon << sign::space << sign::dollar << squad.money() << endl;
        ImGui::AlignTextToFramePadding();
        ImGui::Text(oss.str().c_str());

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
            GuiMenuInventoryVars vars{
                squad.inventory().roster().newItems(),
                item,
                pItem,
                showGuiNotImplemented,
                showGuiRemoveItem,
                showGuiModifyItem
            };
            guiItemList(vars, color::yellowDark, color::yellow, color::turquoise, color::turquoise);

            vars.items_ = squad.inventory().roster().oldItems();
            guiItemList(vars, color::grayDark, color::gray, color::turquoise, color::turquoise);

            ImGui::EndChild();
        }

        ImGui::SameLine();
        guiItemFullDescription(pItem, columnSize, true);

        ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() });
        if (ImGui::Button(comT.exitMenu().c_str())) {
            pItem = nullptr;
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
    for (auto iter{ vars.items_.beg_ }; iter != vars.items_.end_; ++iter) {
        Item* item{ iter.get()->get() };
        ImGui::PushID(item);

        bool popStyleColor{ false };
        if (vars.pItem_ == item) {
            popStyleColor = true;
            ImGui::PushStyleColor(ImGuiCol_Button, colorButtonSelected);
        }
        auto textSize{ ImGui::CalcTextSize(item->name().c_str()) };
        ImVec2 buttonSize{ textSize.x + buttonPaddingX2.x, buttonHeight };
        if (ImGui::Button(item->name().c_str(), buttonSize)) {
            vars.pItem_ = item;
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
            vars.showGuiModifyItem_ = true;
            vars.pItem_ = item.get()->get();
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
}

void guiItemFullDescription(const object::Item* item,
                            const ImVec2& size,
                            bool border,
                            ImGuiWindowFlags flags)
{
    if (ImGui::BeginChild("ItemFullDescription", size, border, flags)) {
        if (item != nullptr) {
            ItemVisitorFullDescription vis;
            item->accept(vis);
            ImGui::PushTextWrapPos();
            ImGui::TextUnformatted(vis.getFullDescription().c_str());
            ImGui::PopTextWrapPos();
        }
        ImGui::EndChild();
    }
}

} // namespace menu
} // namespace game
