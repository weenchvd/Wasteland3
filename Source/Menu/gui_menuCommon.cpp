
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"gui_menuCommon.hpp"
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"menuCommonText.hpp"
#include<algorithm>
#include<assert.h>
#include<d3d11.h>
#include<tchar.h>

#undef min
#undef max

namespace game {
namespace menu {

using namespace std;

void guiCommonInitialization(ImGuiWindowFlags& window_flags)
{
    const ImGuiViewport* viewport{ ImGui::GetMainViewport() };
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoSavedSettings;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    window_flags |= ImGuiWindowFlags_NoDocking;
}

///************************************************************************************************

void guiPopupMessage(bool* openPopup,
                     const char* popupTitle,
                     const char* messageText,
                     const char* buttonText)
{
    assert(openPopup != nullptr);
    assert(popupTitle != nullptr);
    assert(messageText != nullptr);
    if (openPopup == nullptr || popupTitle == nullptr || messageText == nullptr) return;

    if (*openPopup) {
        ImGui::OpenPopup(popupTitle);
    }
    *openPopup = false;

    ImVec2 center{ ImGui::GetMainViewport()->GetCenter() };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2{ 0.5f, 0.5f });
    const float textPadding{ 20 };
    const float windowWidth{ ImGui::CalcTextSize(messageText).x + textPadding };
    const float minWindowWidth{ 300 };
    ImVec2 windowSize{ max(windowWidth, minWindowWidth), 0 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

    if (ImGui::BeginPopupModal(popupTitle, nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(messageText);

        if (buttonText == nullptr) {
            buttonText = MenuCommonText::common().close().c_str();
        }
        const float buttonPadding{ 40 };
        ImVec2 buttonSize{ ImGui::CalcTextSize(buttonText).x + buttonPadding, 0 };
        float indent{ ImGui::GetWindowWidth() / 2 - buttonSize.x / 2 };
        ImGui::NewLine();
        ImGui::SameLine(indent);
        if (ImGui::Button(buttonText, buttonSize)) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void guiGetYesNo(bool* open,
                 const char* windowTitle,
                 const char* messageText,
                 YesNo& result)
{
    assert(open != nullptr);
    assert(windowTitle != nullptr);
    assert(messageText != nullptr);
    if (open == nullptr || windowTitle == nullptr || messageText == nullptr) return;

    const auto& comT{ MenuCommonText::common() };

    ImVec2 center{ ImGui::GetMainViewport()->GetCenter() };
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2{ 0.5f, 0.5f });
    const float textPadding{ 20 };
    const float windowWidth{ ImGui::CalcTextSize(messageText).x + textPadding };
    const float minWindowWidth{ 300 };
    ImVec2 windowSize{ max(windowWidth, minWindowWidth), 0 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

    ImGuiWindowFlags window_flags{ ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings };
    if (ImGui::Begin(windowTitle, open, window_flags)) {
        ImGui::Text(messageText);

        const float buttonTextPadding{ 40 };
        const char* buttonTextYes{ comT.yes().c_str() };
        ImVec2 buttonSizeYes{ ImGui::CalcTextSize(buttonTextYes).x + buttonTextPadding, 0 };
        const char* buttonTextNo{ comT.no().c_str() };
        ImVec2 buttonSizeNo{ ImGui::CalcTextSize(buttonTextNo).x + buttonTextPadding, 0 };

        const float buttonPadding{ 10 };
        ImVec2 buttonSize{ max(buttonSizeYes.x, buttonSizeNo.x), 0 };
        float indent{ ImGui::GetWindowWidth() / 2 - buttonSize.x - buttonPadding };
        ImGui::NewLine();
        ImGui::SameLine(indent);
        if (ImGui::Button(buttonTextYes, buttonSize)) {
            result = YesNo::YES;
            *open = false;
        }
        ImGui::SameLine(0, buttonPadding * 2);
        if (ImGui::Button(buttonTextNo, buttonSize)) {
            result = YesNo::NO;
            *open = false;
        }

        ImGui::End();
    }
}

} // namespace menu
} // namespace game
