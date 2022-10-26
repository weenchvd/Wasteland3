
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"gui_menuCommon.hpp"
#include"gui_menuSkill.hpp"
#include"menuCommon.hpp"
#include"menuCommonText.hpp"
#include"menuInventoryText.hpp"
#include"menuSkillText.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

GuiMenuSkillState::GuiMenuSkillState(
    GuiMenuGeneralVars& gVars, GuiMenuSkillVars& vars) noexcept
    :
    iItem_      { vars.iItem_ },
    pItem_      { vars.pItem_ },
    pChar_      { vars.pChar_ },
    curSM_      { gVars.curSM_ },
    descr_      { vars.descr_ },
    showStats_  { vars.showStats_ },
    showGuiExit_{ vars.showGuiExit_ }
{}

void GuiMenuSkillState::changeSubmenu(Submenu previousSM)
{
    static bool showGuiQuestionConfirmChanges{ false };
    static Submenu nextSM{ Submenu::INVENTORY };
    if (previousSM != curSM_) {
        if (pChar_ != nullptr && pChar_->skill().isModified()) {
            showGuiQuestionConfirmChanges = true;
            nextSM = curSM_;
            curSM_ = previousSM;
        }
        else {
            showStats_ = false;
            descr_ = nullptr;
        }
    }
    if (showGuiQuestionConfirmChanges) {
        YesNo result{ YesNo::INVALID };
        guiGetYesNo(&showGuiQuestionConfirmChanges, u8"##QuestionConfirmChanges",
            MenuSkillText::common().questionConfirmChanges().c_str(), result);
        switch (result) {
        case YesNo::YES:
            showGuiQuestionConfirmChanges = false;
            pChar_->skill().accept();
            curSM_ = nextSM;
            showStats_ = false;
            descr_ = nullptr;
            break;
        case YesNo::NO:
            showGuiQuestionConfirmChanges = false;
            break;
        case YesNo::INVALID:
            break;
        }
    }
}

void GuiMenuSkillState::changeCharacter(object::Character* pCharPrev)
{
    static bool showGuiQuestionConfirmChanges{ false };
    static object::Character* pCharNext{ nullptr };
    if (pCharPrev != pChar_ ) {
        if (pCharPrev != nullptr && pCharPrev->skill().isModified()) {
            showGuiQuestionConfirmChanges = true;
            pCharNext = pChar_;
            pChar_ = pCharPrev;
        }
        else {
            descr_ = nullptr;
        }
    }
    if (showGuiQuestionConfirmChanges) {
        YesNo result{ YesNo::INVALID };
        guiGetYesNo(&showGuiQuestionConfirmChanges, u8"##QuestionConfirmChanges",
            MenuSkillText::common().questionConfirmChanges().c_str(), result);
        switch (result) {
        case YesNo::YES:
            showGuiQuestionConfirmChanges = false;
            pCharPrev->skill().accept();
            pChar_ = pCharNext;
            descr_ = nullptr;
            break;
        case YesNo::NO:
            showGuiQuestionConfirmChanges = false;
            break;
        case YesNo::INVALID:
            break;
        }
    }
}

void GuiMenuSkillState::exitTheMenu(bool* open, object::Squad& squad)
{
    static bool showGuiQuestionConfirmChanges{ false };
    if (pChar_ != nullptr && pChar_->skill().isModified()) {
        showGuiQuestionConfirmChanges = true;
    }
    if (showGuiQuestionConfirmChanges) {
        YesNo result{ YesNo::INVALID };
        guiGetYesNo(&showGuiQuestionConfirmChanges, u8"##QuestionConfirmChanges",
            MenuSkillText::common().questionConfirmChanges().c_str(), result);
        switch (result) {
        case YesNo::YES:
            showGuiQuestionConfirmChanges = false;
            pChar_->skill().accept();
            break;
        case YesNo::NO:
            showGuiQuestionConfirmChanges = false;
            showGuiExit_ = false;
            return;
        case YesNo::INVALID:
            return;
        }
    }
    squad.inventory().viewedAll();
    pItem_ = nullptr;
    pChar_ = nullptr;
    descr_ = nullptr;
    showStats_ = false;
    showGuiExit_ = false;
    *open = false;
}

///************************************************************************************************

void guiMenuSkill(bool* open, GuiMenuGeneralVars& gVars)
{
    using game::object::InventoryIterator;
    using game::object::Item;
    using game::object::Character;
    using game::object::Skill;

    const auto& comT    { MenuCommonText::common() };
    const auto& invenT  { MenuInventoryText::common() };
    const auto& text    { MenuSkillText::common() };
    const auto& tMain   { MenuSkillText::main() };

    static InventoryIterator&       iItem{ gVars.iItem_ };
    static Item*&                   pItem{ gVars.pItem_ };
    static Character*&              pChar{ gVars.pChar_ };
    static int&                     integer{ gVars.integer_ };
    static const char*              pDescr{ nullptr };

    static bool showStats                       { false };
    static bool showGuiExit                     { false };
    static bool showGuiQuestionUndoChanges      { false };

    object::Squad& squad{ gVars.squad_ };

    GuiMenuSkillVars vars{
        squad,
        squad.inventory().roster().oldItems(),
        iItem,
        pItem,
        pChar,
        integer,
        pDescr,
        showStats,
        showGuiExit
    };

    static common::Text description{};
    static GuiMenuSkillState state{ gVars, vars };

    if (showGuiQuestionUndoChanges) {
        YesNo result{ YesNo::INVALID };
        guiGetYesNo(&showGuiQuestionUndoChanges, u8"##QuestionUndoChanges",
            text.questionUndoChanges().c_str(), result);
        if (result == YesNo::YES) {
            pChar->skill().reject();
        }
        return;
    }

    ///********** Windows
    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ tMain.menuName().c_str() } + u8"###MenuSkill";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        const ImGuiStyle& style{ ImGui::GetStyle() };
        ImVec2 contentRegionSize{ ImGui::GetWindowContentRegionMax() };
        ImVec2 columnSize{
            contentRegionSize.x / 3.0f - style.ItemSpacing.x,
            contentRegionSize.y - style.ItemSpacing.y - ImGui::GetFrameHeightWithSpacing() * 9.0f
        };

        ///********** Submenus
        Submenu prevSM{ gVars.curSM_ };
        guiMenuGeneral_Submenu(gVars);
        state.changeSubmenu(prevSM);

        ///********** Squad members
        Character* pCharPrev{ pChar };
        guiMenuGeneral_SquadMembers(gVars);
        state.changeCharacter(pCharPrev);

        ///********** Unit
        ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() });
        const GuiWindowUnitColors dummyColors{};
        bool dummyShowGuiModifyItem{ false };
        guiWindowUnit(gVars, dummyColors, columnSize, showStats, dummyShowGuiModifyItem);

        ///********** Skill list
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
        ImGuiWindowFlags flags{ ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse };
        if (ImGui::BeginChild("Skill", columnSize, false, flags)) {
            ImGui::PopStyleVar();

            ImGui::TextUnformatted(text.skills().c_str());
            ostringstream oss;
            oss << text.skillPoints() << sign::colon << sign::space
                << (pChar != nullptr ? static_cast<int>(pChar->skill().storage().get()) : 0);
            ImVec2 textSize{ ImGui::CalcTextSize(oss.str().c_str()) };
            ImGui::SameLine(columnSize.x - textSize.x);
            ImGui::TextUnformatted(oss.str().c_str());
            ImVec2 pos{ ImGui::GetCursorScreenPos() };
            ImGui::SetCursorScreenPos(
                ImVec2{ pos.x, pos.y + (int)(ImGui::GetFrameHeight() * 0.2f) });

            ImGui::Separator();
            pos = ImGui::GetCursorScreenPos();
            ImGui::SetCursorScreenPos(
                ImVec2{ pos.x, pos.y + (int)(ImGui::GetFrameHeight() * 0.2f) });

            if (ImGui::BeginChild("SkillBars", ImVec2{ 0.0f, 0.0f }, false)) {
                if (pChar) {
                    GuiLevelBarColors colors{
                        color::grey20, color::orange, color::grey40, color::grey90
                    };
                    const Character* c{ pChar };
                    int maxTextWidth{ 0 };
                    for (int i{ common::toUnderlying(common::firstEnum<Skill::Type>()) };
                        i <= common::toUnderlying(common::lastEnum<Skill::Type>()); ++i)
                    {
                        Skill::Type skillType{ static_cast<Skill::Type>(i) };
                        ImVec2 textSize{
                            ImGui::CalcTextSize(c->skill().skillText().name(skillType).c_str())
                        };
                        if (maxTextWidth < textSize.x) {
                            maxTextWidth = textSize.x;
                        }
                    }
                    for (int i{ common::toUnderlying(common::firstEnum<Skill::Type>()) };
                        i <= common::toUnderlying(common::lastEnum<Skill::Type>()); ++i)
                    {
                        bool isHovered{ false };
                        Skill::Type skillType{ static_cast<Skill::Type>(i) };
                        char levelShift{ guiLevelBar<Skill::level_t, Skill::point_t>(
                            c->skill().skillText().name(skillType),
                            colors,
                            c->skill().level(skillType),
                            c->skill().storage(),
                            c->skill().pointDistibution(),
                            isHovered,
                            ImGui::GetWindowContentRegionMax().x, 5, 8, 0, false)
                        };
                        if (levelShift > 0) {
                            pChar->skill().addLevel(skillType,
                                static_cast<Skill::level_t>(levelShift));
                        }
                        if (isHovered) {
                            oss.str("");
                            oss << c->skill().skillText().name(skillType) << endl
                                << sign::separator30 << endl
                                << c->skill().skillText().descr(skillType);
                            description = oss.str();
                            pDescr = description.c_str();
                        }
                    }
                }
            }
            ImGui::EndChild();
        }
        else {
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();

        ///********** Skill description
        ImGui::SameLine();
        guiDescription(pDescr, columnSize, true);

        ///********** Buttons at the bottom
        ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() });
        if (ImGui::Button(comT.exitMenu().c_str())) {
            showGuiExit = true;
        }
        if (showGuiExit) {
            state.exitTheMenu(open, squad);
        }

        ImVec2 textSizeHide{ ImGui::CalcTextSize(invenT.hideStats().c_str()) };
        ImVec2 textSizeShow{ ImGui::CalcTextSize(invenT.showStats().c_str()) };
        float textWidth{ textSizeHide.x > textSizeShow.x ? textSizeHide.x : textSizeShow.x };
        ImVec2 buttonSize{ textWidth + style.FramePadding.x * 2, ImGui::GetFrameHeight() };
        ImGui::SameLine();
        if (showStats) {
            if (ImGui::Button(invenT.hideStats().c_str(), buttonSize)) {
                showStats = false;
            }
        }
        else {
            if (ImGui::Button(invenT.showStats().c_str(), buttonSize)) {
                showStats = true;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button(text.undoChanges().c_str())) {
            if (pChar != nullptr && pChar->skill().isModified()) {
                showGuiQuestionUndoChanges = true;
            }
        }
    }
    ImGui::End();
}

} // namespace menu
} // namespace game
