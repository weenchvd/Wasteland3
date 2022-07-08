
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"gui_menuCommon.hpp"
#include"gui_menuOptions.hpp"
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"menuCommon.hpp"
#include"menuCommonText.hpp"
#include"menuOptionsText.hpp"
#include"locator.hpp"
#include"plainText.hpp"
#include<d3d11.h>
#include<string>
#include<tchar.h>

namespace game {
namespace menu {

using namespace std;

void guiMenuOptions(bool* open)
{
    using global::PlainText;
    using global::PlainTextBase;
    using global::Locator;
    using common::toUnderlying;

    const auto& comT{ MenuCommonText::common() };
    const auto& tCom{ MenuOptionsText::common() };
    const auto& tGen{ MenuOptionsText::general() };

    static bool showGuiChangesSaved         { false };
    static bool showGuiChangesCanceled      { false };
    static bool showGuiQuestionSaveChanges  { false };

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ tCom.menuName().c_str() } + u8"###MenuOptions";
    ImGui::Begin(s.c_str(), nullptr, window_flags);

    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
    s = string{ tGen.menuName().c_str() } + u8"###MenuGeneralOptions";
    if (ImGui::CollapsingHeader(s.c_str())) {
        ImGui::Indent();

        // Language option
        auto curLang{ Locator::getOptions().optLanguage().getLanguage() };
        const char* comboPreviewValue{ PlainText::language(curLang).c_str() };

        if (ImGui::BeginCombo(tGen.language().c_str(), comboPreviewValue)) {
            for (int i{ toUnderlying(common::firstEnum<PlainTextBase::Language>()) };
                i <= toUnderlying(common::lastEnum<PlainTextBase::Language>()); ++i)
            {
                const auto lang{ static_cast<PlainTextBase::Language>(i) };
                const bool isSelected{ curLang == lang ? true : false };
                const char* label{ PlainText::language(lang).c_str() };
                if (ImGui::Selectable(label, isSelected)) {
                    Locator::getOptions().optLanguage().setLanguage(lang);
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        ImGui::Unindent();
    }
    ImGui::PopItemWidth();

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button(comT.saveChanges().c_str())) {
        Locator::getOptions().acceptAll();
        showGuiChangesSaved = true;
    }
    if (ImGui::Button(comT.cancelChanges().c_str())) {
        Locator::getOptions().rejectAll();
        showGuiChangesCanceled = true;
    }
    ImGui::NewLine();
    if (ImGui::Button(comT.exitMenu().c_str())) {
        if (Locator::getOptions().isModified()) {
            showGuiQuestionSaveChanges = true;
        }
        else {
            *open = false;
        }
    }

    guiPopupMessage(&showGuiChangesSaved, u8"##ChangesSaved", comT.changesSaved().c_str());
    guiPopupMessage(&showGuiChangesCanceled, u8"##ChangesCanceled", comT.changesCanceled().c_str());

    if (showGuiQuestionSaveChanges) {
        YesNo result{ YesNo::INVALID };
        guiGetYesNo(&showGuiQuestionSaveChanges, u8"##QuestionSaveChanges",
            tCom.questionSaveChanges().c_str(), result);
        switch (result) {
        case YesNo::YES:
            Locator::getOptions().acceptAll();
            *open = false;
            break;
        case YesNo::NO:
            Locator::getOptions().rejectAll();
            *open = false;
            break;
        }
    }

    ImGui::End();
}

///************************************************************************************************



} // namespace menu
} // namespace game
