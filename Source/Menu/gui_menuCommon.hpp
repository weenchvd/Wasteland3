
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

} // namespace menu
} // namespace game

#endif // !GUI_MENU_COMMON_HPP
