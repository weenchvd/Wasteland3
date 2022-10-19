
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"gui_menuAttribute.hpp"
#include"gui_menuCommon.hpp"
#include"menuAttributeText.hpp"
#include"menuCommon.hpp"
#include"menuCommonText.hpp"
#include"menuInventoryText.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

GuiMenuAttributeState::GuiMenuAttributeState(
    GuiMenuGeneralVars& gVars, GuiMenuAttributeVars& vars) noexcept
    :
    iItem_      { vars.iItem_ },
    pItem_      { vars.pItem_ },
    pChar_      { vars.pChar_ },
    curSM_      { gVars.curSM_ },
    descr_      { vars.descr_ },
    showStats_  { vars.showStats_ },
    showGuiExit_{ vars.showGuiExit_ }
{}

void GuiMenuAttributeState::changeSubmenu(Submenu previousSM)
{
    static bool showGuiQuestionConfirmChanges{ false };
    static Submenu nextSM{ Submenu::INVENTORY };
    if (previousSM != curSM_) {
        if (pChar_ != nullptr && pChar_->attribute().isModified()) {
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
            MenuAttributeText::common().questionConfirmChanges().c_str(), result);
        switch (result) {
        case YesNo::YES:
            showGuiQuestionConfirmChanges = false;
            pChar_->attribute().accept();
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

void GuiMenuAttributeState::changeCharacter(object::Character* pCharPrev)
{
    static bool showGuiQuestionConfirmChanges{ false };
    static object::Character* pCharNext{ nullptr };
    if (pCharPrev != pChar_ ) {
        if (pCharPrev != nullptr && pCharPrev->attribute().isModified()) {
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
            MenuAttributeText::common().questionConfirmChanges().c_str(), result);
        switch (result) {
        case YesNo::YES:
            showGuiQuestionConfirmChanges = false;
            pCharPrev->attribute().accept();
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

void GuiMenuAttributeState::exitTheMenu(bool* open, object::Squad& squad)
{
    static bool showGuiQuestionConfirmChanges{ false };
    if (pChar_ != nullptr && pChar_->attribute().isModified()) {
        showGuiQuestionConfirmChanges = true;
    }
    if (showGuiQuestionConfirmChanges) {
        YesNo result{ YesNo::INVALID };
        guiGetYesNo(&showGuiQuestionConfirmChanges, u8"##QuestionConfirmChanges",
            MenuAttributeText::common().questionConfirmChanges().c_str(), result);
        switch (result) {
        case YesNo::YES:
            showGuiQuestionConfirmChanges = false;
            pChar_->attribute().accept();
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

void guiMenuAttribute(bool* open, GuiMenuGeneralVars& gVars)
{
    using game::object::InventoryIterator;
    using game::object::Item;
    using game::object::Character;
    using game::object::Attribute;

    const auto& comT    { MenuCommonText::common() };
    const auto& invenT  { MenuInventoryText::common() };
    const auto& text    { MenuAttributeText::common() };
    const auto& tMain   { MenuAttributeText::main() };

    const ImVec4 colItemNew         { color::yellowDark };
    const ImVec4 colItemHoveredNew  { color::yellow };
    const ImVec4 colItem            { color::greyDark };
    const ImVec4 colItemHovered     { color::grey };
    const ImVec4 colItemActive      { color::turquoise };
    const ImVec4 colItemSelected    { color::turquoise };
    const ImVec4 colSlot            { color::greyDark };
    const ImVec4 colSlotHovered     { color::grey };
    const ImVec4 colSlotActive      { color::turquoise };
    const ImVec4 colSlotSelected    { color::turquoise };
    const ImVec4 colSlotCompatible  { color::green };

    static InventoryIterator&       iItem{ gVars.iItem_ };
    static Item*&                   pItem{ gVars.pItem_ };
    static Character*&              pChar{ gVars.pChar_ };
    static int&                     integer{ gVars.integer_ };
    static const char*              pDescr{ nullptr };

    static bool showStats                       { false };
    static bool showGuiExit                     { false };
    static bool showGuiQuestionUndoChanges      { false };

    object::Squad& squad{ gVars.squad_ };

    GuiMenuAttributeVars vars{
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
    static GuiMenuAttributeState state{ gVars, vars };

    ///********** Windows
    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ tMain.menuName().c_str() } + u8"###MenuAttribute";
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
        const GuiWindowUnitColors uColors{};
        bool dummyShowGuiModifyItem{ false };
        guiWindowUnit(gVars, uColors, columnSize, showStats, dummyShowGuiModifyItem);

        ///********** Attribute list
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
        ImGuiWindowFlags flags{ ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse };
        if (ImGui::BeginChild("Attribute", columnSize, false, flags)) {
            ImGui::PopStyleVar();

            ImGui::TextUnformatted(text.attributes().c_str());
            ostringstream oss;
            oss << text.attrPoints() << sign::colon << sign::space
                << (pChar != nullptr ? static_cast<int>(pChar->attribute().storage().get()) : 0);
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

            if (ImGui::BeginChild("AttributeBars", ImVec2{ 0.0f, 0.0f }, false)) {
                if (pChar) {
                    GuiLevelBarColors colors{
                        color::grey20, color::blue, color::grey40, color::grey90
                    };
                    const Character* c{ pChar };
                    int maxTextWidth{ 0 };
                    for (int i{ common::toUnderlying(common::firstEnum<Attribute::Type>()) };
                        i <= common::toUnderlying(common::lastEnum<Attribute::Type>()); ++i)
                    {
                        Attribute::Type attrType{ static_cast<Attribute::Type>(i) };
                        ImVec2 textSize{
                            ImGui::CalcTextSize(c->attribute().attributeText().name(attrType).c_str())
                        };
                        if (maxTextWidth < textSize.x) {
                            maxTextWidth = textSize.x;
                        }
                    }
                    const int barIndent{ maxTextWidth + 100 };
                    for (int i{ common::toUnderlying(common::firstEnum<Attribute::Type>()) };
                        i <= common::toUnderlying(common::lastEnum<Attribute::Type>()); ++i)
                    {
                        bool isHovered{ false };
                        Attribute::Type attrType{ static_cast<Attribute::Type>(i) };
                        char levelShift{ guiLevelBar<Attribute::level_t, Attribute::point_t>(
                            c->attribute().attributeText().name(attrType),
                            colors,
                            c->attribute().level(attrType),
                            c->attribute().storage(),
                            c->attribute().pointDistibution(),
                            isHovered,
                            ImGui::GetWindowContentRegionMax().x, 5, 8, barIndent, true)
                        };
                        if (levelShift > 0) {
                            pChar->attribute().addLevel(attrType,
                                static_cast<Attribute::level_t>(levelShift));
                        }
                        if (isHovered) {
                            oss.str("");
                            oss << c->attribute().attributeText().name(attrType) << endl
                                << c->attribute().attributeText().descr(attrType);
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

        ///********** Attribute description
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
            if (pChar != nullptr && pChar->attribute().isModified()) {
                showGuiQuestionUndoChanges = true;
            }
        }

        if (showGuiQuestionUndoChanges) {
            YesNo result{ YesNo::INVALID };
            guiGetYesNo(&showGuiQuestionUndoChanges, u8"##QuestionUndoChanges",
                text.questionUndoChanges().c_str(), result);
            if (result == YesNo::YES) {
                pChar->attribute().reject();
            }
        }
    }
    ImGui::End();
}

} // namespace menu
} // namespace game
