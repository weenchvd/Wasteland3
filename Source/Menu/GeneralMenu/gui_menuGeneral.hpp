
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_GENERAL_HPP
#define GUI_MENU_GENERAL_HPP

#include"common.hpp"
#include"distribution.hpp"
#include"imgui.h"
#include"specStorage.hpp"
#include"squad.hpp"

namespace game {
namespace menu {

enum class Submenu : char {
    INVENTORY,
    ATTRIBUTES,
    SKILLS
};

struct GuiMenuGeneralVars {
    object::Squad&                      squad_;
    object::Roster::ItemRange           itemRange_;
    object::InventoryIterator&          iItem_;
    object::Item*&                      pItem_;
    object::Character*&                 pChar_;
    int&                                integer_;
    Submenu&                            curSM_;
    Submenu&                            prevSM_;
};

struct GuiWindowUnitColors {
    ImVec4 colSlot_;
    ImVec4 colSlotHovered_;
    ImVec4 colSlotActive_;
    ImVec4 colItemSelected_;
    ImVec4 colSlotCompatible_;
};

struct GuiLevelBarColors {
    ImVec4 notAccepted_;
    ImVec4 accepted_;
    ImVec4 available_;
    ImVec4 availableHighlighted_;
};

///************************************************************************************************

void guiMenuGeneral(bool* open, object::Squad& squad);

///************************************************************************************************

void guiMenuGeneral_Submenu(GuiMenuGeneralVars& vars);

void guiMenuGeneral_SquadMembers(GuiMenuGeneralVars& vars);

void guiWindowUnit(GuiMenuGeneralVars& gVars,
                   const GuiWindowUnitColors& col,
                   const ImVec2& windowSize,
                   bool& showStats,
                   bool& showGuiModifyItem);

//template<class Level, class Point>
//char guiLevelBar(const common::Text& title,
//                 const ImVec2& windowSize,
//                 const GuiLevelBarColors& colors,
//                 const common::SpecStorage<Level>& level,
//                 const common::SpecStorage<Point>& points,
//                 const common::Distribution<Point, Level>& dist);

//void guiLevelBar(const common::Text& title,
//                 const ImVec2& windowSize,
//                 const char minLevel,
//                 const char maxLevel,
//                 char& curLevel);

template<class Level, class Point>
char guiLevelBar(const common::Text& title,
                 const ImVec2& windowSize,
                 const GuiLevelBarColors& colors,
                 const common::SpecStorage<Level>& level,
                 const common::SpecStorage<Point>& points,
                 const common::Distribution<Point, Level>& dist,
                 const bool onSameLine = false,
                 const int barIndent = 0)
{
    constexpr int addIndent{ 20 };
    const auto& style{ ImGui::GetStyle() };
    ImVec2 posTemp{ ImGui::GetCursorScreenPos() };
    int indent{ barIndent };
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted(title.c_str());
    if (onSameLine) {
        ImGui::SameLine();
        if (barIndent <= 0) {
            indent = ImGui::CalcTextSize(title.c_str()).x + addIndent;
        }
    }
    else {
        posTemp = ImGui::GetCursorScreenPos();
    }
    const ImVec2 pos{ posTemp };

    ///********** Set bar and button sizes
    const auto minLevel{ static_cast<char>(level.getMinPossible()) };
    const auto maxLevel{ static_cast<char>(level.getMaxPossible()) };
    const short int nLevels{ maxLevel - minLevel };
    const float barSpacing{ 3.0f };
    ImVec2 barSize{
        windowSize.x - style.ItemSpacing.x - indent, ImGui::GetFrameHeight() * 0.8f
    };
    ImVec2 buttonSize{
        (barSize.x - barSpacing) / nLevels - barSpacing, barSize.y - barSpacing * 2
    };
    if (buttonSize.x < buttonSize.y) {
        buttonSize.x = buttonSize.y;
        barSize.x = (buttonSize.x + barSpacing) * nLevels + barSpacing;
    }

    ///********** Draw the edge of the bar
    const ImVec2 posBar{ pos.x + indent, pos.y };
    const ImVec4 col{ style.Colors[ImGuiCol_Border] };
    const float borderWidth{ 1.0f };
    ImGui::GetWindowDrawList()->AddRect(posBar, ImVec2(posBar.x + barSize.x, posBar.y + barSize.y),
        ImU32{ ImColor{ col } }, 0.0f, ImDrawFlags_None, borderWidth);

    ///********** Draw invisible bar buttons
    ImVec2 posButton{ posBar.x + barSpacing, posBar.y + barSpacing };
    ImGui::SetCursorScreenPos(posButton);
    int buttonPressed{ minLevel };
    int buttonHovered{ minLevel };
    ImGui::PushID(title.c_str());
    for (int i{ minLevel + 1 }; i <= maxLevel; ++i) {
        ImGui::PushID(i);
        if (ImGui::InvisibleButton("", buttonSize)) {
            buttonPressed = i;
        }
        if (ImGui::IsItemHovered()) {
            buttonHovered = i;
        }
        posButton = ImVec2{ posButton.x + buttonSize.x + barSpacing, posButton.y };
        ImGui::SetCursorScreenPos(posButton);
        ImGui::PopID();
    }
    ImGui::PopID();

    ///********** Draw visible bar buttons
    posButton = ImVec2{ posBar.x + barSpacing, posBar.y + barSpacing };
    const auto currentLevel{ static_cast<char>(level.get()) };
    for (int i{ minLevel + 1 }; i <= maxLevel; ++i) {
        ImVec4 colButton{ colors.accepted_ };
        if (i > currentLevel) {
            if (points.get() >= dist.total(static_cast<Level>(i), level.get())) {
                if (i <= buttonHovered) {
                    colButton = colors.availableHighlighted_;
                }
                else {
                    colButton = colors.available_;
                }
            }
            else {
                if (i <= buttonHovered) {
                    colButton = colors.available_;
                }
                else {
                    colButton = colors.notAccepted_;
                }
            }
        }
        ImGui::GetWindowDrawList()->AddRectFilled(posButton,
            ImVec2(posButton.x + buttonSize.x, posButton.y + buttonSize.y),
            ImU32{ ImColor{ colButton } }, 0.0f, ImDrawFlags_None);

        posButton = ImVec2{ posButton.x + buttonSize.x + barSpacing, posButton.y };
        ImGui::SetCursorScreenPos(posButton);
    }

    if (onSameLine) {
        ImGui::SetCursorScreenPos(
            ImVec2{ pos.x, pos.y + ImGui::GetFrameHeight() + style.ItemSpacing.y });
    }
    else {
        ImGui::SetCursorScreenPos(ImVec2{ pos.x, pos.y + barSize.y + style.ItemSpacing.y });
    }
    if (buttonPressed > minLevel &&
        points.get() >= dist.total(static_cast<Level>(buttonPressed), level.get()))
    {
        return buttonPressed - static_cast<char>(level.get());
    }
    return 0;
}

//template<class Level, class Point>
//char guiLevelBar(const common::Text& title,
//                 const ImVec2& windowSize,
//                 const GuiLevelBarColors& colors,
//                 const common::SpecStorage<Level>& level,
//                 const common::SpecStorage<Point>& points,
//                 const common::Distribution<Point, Level>& dist)
//{
//    const auto& style{ ImGui::GetStyle() };
//    ImGui::AlignTextToFramePadding();
//    ImGui::TextUnformatted(title.c_str());
//
//    const auto minLevel{ static_cast<char>(level.getMinPossible()) };
//    const auto maxLevel{ static_cast<char>(level.getMaxPossible()) };
//    const short int nLevels{ maxLevel - minLevel };
//    const float barSpacing{ 3.0f };
//    ImVec2 barSize{
//        windowSize.x - style.ItemSpacing.x, ImGui::GetFrameHeight() * 0.8f
//    };
//    ImVec2 buttonSize{
//        (barSize.x - barSpacing) / nLevels - barSpacing, barSize.y - barSpacing * 2
//    };
//    if (buttonSize.x < barSize.y) {
//        buttonSize.x = barSize.y;
//        barSize.x = (buttonSize.x + barSpacing) * nLevels + barSpacing;
//    }
//
//    ///********** Draw the edge of the bar
//    const ImVec2 pos{ ImGui::GetCursorScreenPos() };
//    const ImVec4 col{ style.Colors[ImGuiCol_Border] };
//    const float borderWidth{ 1.0f };
//    ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + barSize.x, pos.y + barSize.y),
//        ImU32{ ImColor{ col } }, 0.0f, ImDrawFlags_None, borderWidth);
//
//    ///********** Draw invisible bar buttons
//    ImVec2 posButton{ pos.x + barSpacing, pos.y + barSpacing };
//    ImGui::SetCursorScreenPos(posButton);
//    int buttonPressed{ minLevel };
//    int buttonHovered{ minLevel };
//    ImGui::PushID(title.c_str());
//    for (int i{ minLevel + 1 }; i <= maxLevel; ++i) {
//        ImGui::PushID(i);
//        if (ImGui::InvisibleButton("", buttonSize)) {
//            buttonPressed = i;
//        }
//        if (ImGui::IsItemHovered()) {
//            buttonHovered = i;
//        }
//        posButton = ImVec2{ posButton.x + buttonSize.x + barSpacing, posButton.y };
//        ImGui::SetCursorScreenPos(posButton);
//        ImGui::PopID();
//    }
//    ImGui::PopID();
//
//    ///********** Draw visible bar buttons
//    posButton = ImVec2{ pos.x + barSpacing, pos.y + barSpacing };
//    const auto currentLevel{ static_cast<char>(level.get()) };
//    for (int i{ minLevel + 1 }; i <= maxLevel; ++i) {
//        ImVec4 colButton{ colors.accepted_ };
//        if (i > currentLevel) {
//            if (points.get() >= dist.total(static_cast<Level>(i), level.get())) {
//                if (i <= buttonHovered) {
//                    colButton = colors.availableHighlighted_;
//                }
//                else {
//                    colButton = colors.available_;
//                }
//            }
//            else {
//                if (i <= buttonHovered) {
//                    colButton = colors.available_;
//                }
//                else {
//                    colButton = colors.notAccepted_;
//                }
//            }
//        }
//        ImGui::GetWindowDrawList()->AddRectFilled(posButton,
//            ImVec2(posButton.x + buttonSize.x, posButton.y + buttonSize.y),
//            ImU32{ ImColor{ colButton } }, 0.0f, ImDrawFlags_None);
//
//        posButton = ImVec2{ posButton.x + buttonSize.x + barSpacing, posButton.y };
//        ImGui::SetCursorScreenPos(posButton);
//    }
//
//    ImGui::SetCursorScreenPos(ImVec2{ pos.x, pos.y + barSize.y + style.ItemSpacing.y });
//    if (buttonPressed > minLevel &&
//        points.get() >= dist.total(static_cast<Level>(buttonPressed), level.get()))
//    {
//        return buttonPressed - static_cast<char>(level.get());
//    }
//    return 0;
//}

//template<class Level, class Point>
//char guiLevelBar(const common::Text& title,
//                 const ImVec2& windowSize,
//                 const GuiLevelBarColors& colors,
//                 const common::SpecStorage<Level>& level,
//                 const common::SpecStorage<Point>& points,
//                 const common::Distribution<Point, Level>& dist)
//{
//    const auto& style{ ImGui::GetStyle() };
//    ImGui::AlignTextToFramePadding();
//    ImGui::TextUnformatted(title.c_str());
//
//    const auto minLevel{ static_cast<char>(level.getMinPossible()) };
//    const auto maxLevel{ static_cast<char>(level.getMaxPossible()) };
//    const short int nLevels{ maxLevel - minLevel };
//    const float barSpacing{ 3.0f };
//    const ImVec2 barSize{
//        windowSize.x - style.ItemSpacing.x, ImGui::GetFrameHeight() * 0.8f
//    };
//    const ImVec2 buttonSize{
//        (barSize.x - barSpacing) / nLevels - barSpacing, barSize.y - barSpacing * 2
//    };
//
//    const ImVec2 pos{ ImGui::GetCursorScreenPos() };
//    const ImVec4 col{ style.Colors[ImGuiCol_Border] };
//    const float borderWidth{ 1.0f };
//    ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + barSize.x, pos.y + barSize.y),
//        ImU32{ ImColor{ col } }, 0.0f, ImDrawFlags_None, borderWidth);
//
//    ImVec2 posButton{ pos.x + barSpacing, pos.y + barSpacing };
//    ImGui::SetCursorScreenPos(posButton);
//    ImGui::PushStyleColor(ImGuiCol_Button, colors.accepted_);
//    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors.accepted_);
//    ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors.accepted_);
//    const auto currentLevel{ static_cast<char>(level.get()) };
//    int buttonPressed{ minLevel };
//    int buttonHovered{ minLevel };
//    ImGui::PushID(title.c_str());
//    for (int i{ minLevel + 1 }; i <= maxLevel; ++i) {
//        ImGui::PushID(i);
//        ImVec4 colButton{};
//        ImVec4 colButtonHovered{};
//        ImVec4 colButtonActive{};
//        bool setColorButton{ false };
//        if (i > currentLevel) {
//            setColorButton      = true;
//            if (points.get() >= dist.total(static_cast<Level>(i), level.get())) {
//                colButton           = colors.available_;
//                colButtonHovered    = colors.available_;
//                colButtonActive     = colors.available_;
//            }
//            else {
//                colButton           = colors.notAccepted_;
//                colButtonHovered    = colors.notAccepted_;
//                colButtonActive     = colors.notAccepted_;
//            }
//        }
//        if (setColorButton) {
//            ImGui::PushStyleColor(ImGuiCol_Button, colButton);
//            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colButtonHovered);
//            ImGui::PushStyleColor(ImGuiCol_ButtonActive, colButtonActive);
//        }
//        if (ImGui::Button("##Cell", buttonSize)) {
//            buttonPressed = i;
//        }
//        //if (ImGui::IsItemHovered()) {
//        //    buttonHovered = i;
//        //}
//        if (setColorButton) {
//            ImGui::PopStyleColor(3);
//        }
//        posButton = ImVec2{ posButton.x + buttonSize.x + barSpacing, posButton.y };
//        ImGui::SetCursorScreenPos(posButton);
//
//        ImGui::PopID();
//    }
//    ImGui::PopID();
//    ImGui::PopStyleColor(3);
//
//    ImGui::SetCursorScreenPos(ImVec2{ pos.x, pos.y + barSize.y + style.ItemSpacing.y });
//    if (buttonPressed > minLevel &&
//        points.get() >= dist.total(static_cast<Level>(buttonPressed), level.get()))
//    {
//        return buttonPressed - static_cast<char>(level.get());
//    }
//    return 0;
//}

} // namespace menu
} // namespace game

#endif // !GUI_MENU_GENERAL_HPP
