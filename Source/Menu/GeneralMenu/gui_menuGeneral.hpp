
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
#include<cmath>

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

template<class Level, class Point>
char guiLevelBar(const common::Text& title,
                 const GuiLevelBarColors& colors,
                 const common::SpecStorage<Level>& level,
                 const common::SpecStorage<Point>& points,
                 const common::Distribution<Point, Level>& dist,
                 bool& isHovered,
                 const int fullWidth,
                 const int horizontalIndent = 0,
                 const int verticalIndent = 0,
                 const int barIndent = 0,
                 const bool onSameLine = false)
{
    const auto& style{ ImGui::GetStyle() };
    const ImVec2 posInit{ ImGui::GetCursorScreenPos() };
    ImVec2 pos{ round(posInit.x + horizontalIndent), round(posInit.y + verticalIndent) };
    ImGui::SetCursorScreenPos(pos);
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted(title.c_str());
    const float minIndent{ 20.0f };
    float indent{ (float)barIndent };
    if (onSameLine) {
        ImGui::SameLine(0.0f, 0.0f);
        if (barIndent <= 0) {
            indent = round(ImGui::CalcTextSize(title.c_str()).x + minIndent);
        }
    }
    else {
        const ImVec2 p{ ImGui::GetCursorScreenPos() };
        pos = ImVec2{ p.x + horizontalIndent, p.y };
    }

    ///********** Set bar and button sizes
    const auto minLevel{ static_cast<char>(level.getMinPossible()) };
    const auto maxLevel{ static_cast<char>(level.getMaxPossible()) };
    const short int nLevels{ maxLevel - minLevel };
    const float barSpacing{ 3.0f };
    ImVec2 buttonSize{
        floor((fullWidth - horizontalIndent * 2 - indent - barSpacing) / nLevels - barSpacing),
        floor(ImGui::GetFrameHeight() * 0.8f - barSpacing * 2)
    };
    if (buttonSize.x < buttonSize.y) {
        buttonSize.x = buttonSize.y;
    }
    ImVec2 barSize{
        (buttonSize.x + barSpacing) * nLevels + barSpacing, buttonSize.y + barSpacing * 2
    };

    ///********** Draw the edge of the bar
    const ImVec2 posBar{
        round(pos.x + (fullWidth - horizontalIndent * 2 - barSize.x)),
        round(pos.y + (ImGui::GetFrameHeight() - barSize.y) / 2)
    };
    const ImVec4 col{ style.Colors[ImGuiCol_Border] };
    const float borderWidth{ 1.0f };
    ImGui::GetWindowDrawList()->AddRect(posBar, ImVec2{ posBar.x + barSize.x, posBar.y + barSize.y },
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

    ///********** Check focus
    ImVec2 buttonSizeAttrFrame{ 0.0f, 0.0f };
    if (onSameLine) {
        buttonSizeAttrFrame =
            ImVec2{ (float)fullWidth, round(ImGui::GetFrameHeight() + verticalIndent * 2) };
    }
    else {
        buttonSizeAttrFrame =
            ImVec2{ (float)fullWidth, round(ImGui::GetFrameHeight() * 2 + verticalIndent * 2) };
    }
    ImGui::SetCursorScreenPos(posInit);
    ImGui::InvisibleButton("AttributeFrame", buttonSizeAttrFrame);
    if (ImGui::IsItemHovered()) {
        ImGui::GetWindowDrawList()->AddRect(posInit,
            ImVec2{ posInit.x + buttonSizeAttrFrame.x, posInit.y + buttonSizeAttrFrame.y },
            ImU32{ ImColor{ color::blue } }, 0.0f, ImDrawFlags_None, 2.0f);
        isHovered = true;
    }
    ImGui::SetCursorScreenPos(ImVec2{ posInit.x, posInit.y + buttonSizeAttrFrame.y });

    if (buttonPressed > minLevel &&
        points.get() >= dist.total(static_cast<Level>(buttonPressed), level.get()))
    {
        return buttonPressed - static_cast<char>(level.get());
    }
    return 0;
}

} // namespace menu
} // namespace game

#endif // !GUI_MENU_GENERAL_HPP
