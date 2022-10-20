
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef GUI_MENU_COMMON_HPP
#define GUI_MENU_COMMON_HPP

#include"imgui.h"
#include"menuCommon.hpp"

namespace game {
namespace menu {

namespace color {

const ImVec4 green              { 43.0f / 255.0f, 146.0f / 255.0f, 22.0f / 255.0f, 1.0f };
const ImVec4 turquoise          { 17.0f / 255.0f, 118.0f / 255.0f, 113.0f / 255.0f, 1.0f };
const ImVec4 blue               { 66.0f / 255.0f, 173.0f / 255.0f, 250.0f / 255.0f, 1.0f };
const ImVec4 orange             { 255.0f / 255.0f, 153.0f / 255.0f, 0.0f / 255.0f, 1.0f };
const ImVec4 yellow             { 195.0f / 255.0f, 151.0f / 255.0f, 0.0f / 255.0f, 1.0f };
const ImVec4 yellowDark         { 125.0f / 255.0f, 97.0f / 255.0f, 0.0f / 255.0f, 1.0f };
const ImVec4 grey               { 150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f, 1.0f };
const ImVec4 greyDark           { 80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f, 1.0f };
const ImVec4 grey90             { 225.0f / 255.0f, 225.0f / 255.0f, 225.0f / 255.0f, 1.0f };
const ImVec4 grey80             { 200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f };
const ImVec4 grey70             { 175.0f / 255.0f, 175.0f / 255.0f, 175.0f / 255.0f, 1.0f };
const ImVec4 grey60             { 150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f, 1.0f };
const ImVec4 grey50             { 125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f };
const ImVec4 grey40             { 100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f, 1.0f };
const ImVec4 grey30             { 75.0f / 255.0f, 75.0f / 255.0f, 75.0f / 255.0f, 1.0f };
const ImVec4 grey20             { 50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f, 1.0f };

} //namespace color

void guiCommonInitialization(ImGuiWindowFlags& window_flags);

///************************************************************************************************

void guiPopupMessage(bool* openPopup,
                     const char* popupTitle,
                     const char* messageText,
                     const char* buttonText = nullptr);

void guiGetYesNo(bool* open,
                 const char* windowTitle,
                 const char* messageText,
                 YesNo& result);

void guiDescription(const char* description,
                    const ImVec2& size,
                    bool border,
                    ImGuiWindowFlags flags = ImGuiWindowFlags_None);

void helpMarker(const char* description);

void fitButtonInWindowWidth(const char* buttonText);

void fitButtonInWindowWidth(const char* buttonText,
                            const float buttonTotalPaddingWidth,
                            const float windowPosXRight);

} // namespace menu
} // namespace game

#endif // !GUI_MENU_COMMON_HPP
