
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"characterText.hpp"
#include"gui_menuCommon.hpp"
#include"gui_menuGeneral.hpp"
#include"gui_menuInventory.hpp"
#include"gui_menuItem.hpp"
#include"inventory.hpp"
#include"itemCommon.hpp"
#include"itemVisitorFullDescr.hpp"
#include"itemVisitorType.hpp"
#include"menuAttributeText.hpp"
#include"menuCharacterText.hpp"
#include"menuCommon.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuItemText.hpp"
#include"menuSkillText.hpp"
#include"menuSquadText.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void guiMenuInventory(bool* open, GuiMenuGeneralVars& gVars)
{
    using game::object::InventoryIterator;
    using game::object::Item;
    using game::object::Character;

    const auto& comT    { MenuCommonText::common() };
    const auto& text    { MenuInventoryText::common() };
    const auto& charT   { MenuCharacterText::common() };
    const auto& itemT   { MenuItemText::common() };

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

    static bool showGuiRemoveItem       { false };
    static bool showGuiModifyItem       { false };
    static bool showGuiEquipItem        { false };
    static bool showStats               { false };

    object::Squad& squad{ gVars.squad_ };

    GuiMenuInventoryVars vars{
        gVars.squad_,
        gVars.squad_.inventory().roster().oldItems(),
        gVars.iItem_,
        gVars.pItem_,
        gVars.pChar_,
        gVars.integer_,
        showGuiRemoveItem,
        showGuiModifyItem,
        showGuiEquipItem
    };

    if (gVars.curSM_ != gVars.prevSM_) {
        showStats = false;
    }

    ///********** Show GUI
    if (showGuiRemoveItem) {
        bool itemIsSelected{ false };
        if (iItem.isValid() && pItem == iItem.getConst()->get()) {
            itemIsSelected = true;
        }
        guiRemoveItem(&showGuiRemoveItem, squad.inventory(), iItem);
        if (itemIsSelected && !iItem.isValid()) {
            pItem = nullptr;
        }
        return;
    }

    if (showGuiModifyItem) {
        guiMenuItemModify(&showGuiModifyItem, squad, *pItem);
        return;
    }

    if (showGuiEquipItem) {
        auto newMod{ squad.inventory().extract(iItem) };
        unique_ptr<object::Item> oldMod{};
        pChar->unsetWeapon(integer, oldMod);
        pChar->setWeapon(integer, newMod);
        if (oldMod != nullptr) {
            squad.inventory().insert(oldMod);
        }
        showGuiEquipItem = false;
        iItem = InventoryIterator{};
        integer = 0;
    }

    ///********** Windows
    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.menuName().c_str() } + u8"###MenuInventory";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        const ImGuiStyle& style{ ImGui::GetStyle() };
        ImVec2 contentRegionSize{ ImGui::GetWindowContentRegionMax() };
        ImVec2 columnSize{
            contentRegionSize.x / 3.0f - style.ItemSpacing.x,
            contentRegionSize.y - style.ItemSpacing.y - ImGui::GetFrameHeightWithSpacing() * 9.0f
        };

        ///********** Submenus
        guiMenuGeneral_Submenu(gVars);

        ///********** Squad members
        guiMenuGeneral_SquadMembers(gVars);

        ///********** Unit
        ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() });
        const GuiWindowUnitColors uColors{
            colSlot,
            colSlotHovered,
            colSlotActive,
            colItemSelected,
            colSlotCompatible
        };
        guiWindowUnit(gVars, uColors, columnSize, showStats, showGuiModifyItem);

        ///********** Item list
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
        ImGuiWindowFlags flags{ ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse };
        if (ImGui::BeginChild("Inventory", columnSize, false, flags)) {
            ImGui::PopStyleVar();
            ImGui::TextUnformatted(text.inventory().c_str());
            ImGui::SameLine(); helpMarker(text.colorNewItems().c_str());
            ostringstream oss;
            oss << sign::dollar << squad.money();
            ImVec2 textSize{ ImGui::CalcTextSize(oss.str().c_str()) };
            ImGui::SameLine(columnSize.x - textSize.x);
            ImGui::TextUnformatted(oss.str().c_str());

            ImGui::Separator();
            const float buttonTotalPaddingWidth{ style.FramePadding.x * 2 };
            const float windowPosXRight{
                ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x
            };
            static LastItemType lastType{ LastItemType::ALL };
            static LastItemType curType{ LastItemType::ALL };
            const char* buttonText{ nullptr };
            buttonText = comT.all().c_str();
            if (ImGui::Button(buttonText)) {
                curType = LastItemType::ALL;
            }

            buttonText = getItemTypeName(Item::Type::WEAPON).c_str();
            fitButtonInWindowWidth(buttonText, buttonTotalPaddingWidth, windowPosXRight);
            if (ImGui::Button(buttonText)) {
                curType = LastItemType::WEAPON;
            }

            buttonText = getItemTypeName(Item::Type::WEAPON_MOD).c_str();
            fitButtonInWindowWidth(buttonText, buttonTotalPaddingWidth, windowPosXRight);
            if (ImGui::Button(buttonText)) {
                curType = LastItemType::WEAPON_MOD;
            }

            buttonText = getItemTypeName(Item::Type::AMMO).c_str();
            fitButtonInWindowWidth(buttonText, buttonTotalPaddingWidth, windowPosXRight);
            if (ImGui::Button(buttonText)) {
                curType = LastItemType::AMMO;
            }

            ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() / 3 });
            if (ImGui::BeginChild("ItemList", ImVec2{ 0.0f, 0.0f }, false)) {
                if (lastType != curType) {
                    lastType = curType;
                    pItem = nullptr;
                }
                switch (curType) {
                case LastItemType::ALL: {
                    vars.itemRange_ = squad.inventory().roster().newItems();
                    guiItemList(vars, colItemNew, colItemHoveredNew, colItemActive, colItemSelected);

                    vars.itemRange_ = squad.inventory().roster().oldItems();
                    guiItemList(vars, colItem, colItemHovered, colItemActive, colItemSelected);
                    break;
                }
                case LastItemType::WEAPON: {
                    vars.itemRange_ = squad.inventory().roster(Item::Type::WEAPON).oldItems();
                    guiItemList(vars, colItem, colItemHovered, colItemActive, colItemSelected);
                    break;
                }
                case LastItemType::WEAPON_MOD: {
                    vars.itemRange_ = squad.inventory().roster(Item::Type::WEAPON_MOD).oldItems();
                    guiItemList(vars, colItem, colItemHovered, colItemActive, colItemSelected);
                    break;
                }
                case LastItemType::AMMO: {
                    vars.itemRange_ = squad.inventory().roster(Item::Type::AMMO).oldItems();
                    guiItemList(vars, colItem, colItemHovered, colItemActive, colItemSelected);
                    break;
                }
                }
            }
            ImGui::EndChild();
        }
        else {
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();

        ///********** Full item description
        ImGui::SameLine();
        guiItemFullDescription(pItem, columnSize, true);

        ///********** Buttons at the bottom
        ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() });
        if (ImGui::Button(comT.exitMenu().c_str())) {
            squad.inventory().viewedAll();
            pItem = nullptr;
            pChar = nullptr;
            showStats = false;
            *open = false;
        }

        ImVec2 textSizeHide{ ImGui::CalcTextSize(text.hideStats().c_str()) };
        ImVec2 textSizeShow{ ImGui::CalcTextSize(text.showStats().c_str()) };
        float textWidth{ textSizeHide.x > textSizeShow.x ? textSizeHide.x : textSizeShow.x };
        ImVec2 buttonSize{ textWidth + style.FramePadding.x * 2, ImGui::GetFrameHeight() };
        ImGui::SameLine();
        if (showStats) {
            if (ImGui::Button(text.hideStats().c_str(), buttonSize)) {
                showStats = false;
            }
        }
        else {
            if (ImGui::Button(text.showStats().c_str(), buttonSize)) {
                showStats = true;
            }
        }
    }
    ImGui::End();
}

///************************************************************************************************

void guiRemoveItem(bool* open,
                   object::Inventory& inventory,
                   object::InventoryIterator& iItem)
{
    assert(open != nullptr);
    assert(iItem.isValid() == true);

    const auto& text{ MenuItemText::common() };

    YesNo result{ YesNo::INVALID };
    guiGetYesNo(open, u8"##QuestionRemoveItem", text.questionDeleteItem().c_str(), result);
    switch (result) {
    case YesNo::YES: {
        inventory.extract(iItem);
        *open = false;
        break;
    }
    case YesNo::NO:
        *open = false;
        break;
    }
}

void guiItemList(GuiMenuInventoryVars& vars,
                 const ImVec4& colorItem,
                 const ImVec4& colorItemHovered,
                 const ImVec4& colorItemActive,
                 const ImVec4& colorItemSelected)
{
    using game::object::Item;
    using game::object::Roster;

    const auto& comT{ MenuCommonText::common() };

    const ImGuiStyle& style{ ImGui::GetStyle() };
    const float buttonTotalPaddingWidth{ style.FramePadding.x * 2 };
    const float buttonHeight{ ImGui::GetFrameHeight() };
    const float windowPosXRight{ ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x };

    ImGui::PushStyleColor(ImGuiCol_Button, colorItem);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorItemHovered);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorItemActive);
    for (auto iter{ vars.itemRange_.beg_ }; iter != vars.itemRange_.end_; ++iter) {
        Item* pItem{ iter.get()->get() };
        ImGui::PushID(pItem);

        bool setColorButton{ vars.pItem_ == pItem ? true : false };
        if (setColorButton) {
            ImGui::PushStyleColor(ImGuiCol_Button, colorItemSelected);
        }
        auto textSize{ ImGui::CalcTextSize(pItem->name().c_str()) };
        ImVec2 buttonSize{ textSize.x + buttonTotalPaddingWidth, buttonHeight };
        if (ImGui::Button(pItem->name().c_str(), buttonSize)) {
            vars.pItem_ = pItem;
        }
        if (ImGui::BeginPopupContextItem("ContextMenu")) {
            guiContextSensetiveMenuItem(vars, iter);
            if (ImGui::Selectable(comT.remove().c_str())) {
                vars.showGuiRemoveItem_ = true;
                vars.iItem_ = iter;
            }
            ImGui::EndPopup();
        }
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            vars.pItem_ = pItem;
            ImGui::SetDragDropPayload("InventoryItem", &iter, sizeof(iter));
            ImGui::TextUnformatted(pItem->name().c_str());
            ImGui::EndDragDropSource();
        }
        if (setColorButton) {
            ImGui::PopStyleColor();
        }

        auto iterNext{ iter };
        if (++iterNext != vars.itemRange_.end_) {
            fitButtonInWindowWidth(iterNext.getConst()->get()->name().c_str(),
                buttonTotalPaddingWidth, windowPosXRight);
        }

        ImGui::PopID();
    }
    ImGui::PopStyleColor(3);
}

void guiContextSensetiveMenuItem(GuiMenuInventoryVars& vars, object::InventoryIterator& iItem)
{
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::common() };
    object::ItemVisitorType vis;
    (*iItem.getConst())->accept(vis);
    

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        ostringstream oss;
        if (vars.pChar_) {
            for (int i = 0; i < vars.pChar_->slotWeapon().size(); ++i) {
                oss.str("");
                oss << text.equip() << sign::space << sign::lp
                    << comT.slot() << sign::space << i + 1 << sign::rp;
                if (ImGui::Selectable(oss.str().c_str())) {
                    vars.showGuiEquipItem_ = true;
                    vars.iItem_ = iItem;
                    vars.integer_ = i;
                }
            }
        }
        if (ImGui::Selectable(text.modify().c_str())) {
            vars.showGuiModifyItem_ = true;
            vars.pItem_ = iItem.get()->get();
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
}

void guiItemFullDescription(const object::Item* pItem,
                            const ImVec2& size,
                            bool border,
                            ImGuiWindowFlags flags)
{
    if (ImGui::BeginChild("ItemFullDescription", size, border, flags)) {
        if (pItem != nullptr) {
            ItemVisitorFullDescription vis;
            pItem->accept(vis);
            ImGui::PushTextWrapPos();
            ImGui::TextUnformatted(vis.getFullDescription().c_str());
            ImGui::PopTextWrapPos();
        }
    }
    ImGui::EndChild();
}

// @param "ph" - placeholder;
// @param "tw" - total width;
void guiShowStats(object::Character& ch,
                  const char ph,
                  const float tw)
{
    const auto& tCom{ object::CharacterText::common() };
    const auto& tSta{ object::CharacterText::stats() };

    constexpr auto sp{ sign::space };
    constexpr auto pc{ sign::percent };
    constexpr auto x { sign::x };

    ImGui::TextUnformatted(tCom.stats().c_str());
    ostringstream oss;
    clearStream(oss) << ch.constitutionCurrent() << sign::slash << ch.constitutionMaximum();
    guiPrintText(tSta.con(), oss.str(), ph, tw);
    clearStream(oss) << ch.experience();
    guiPrintText(tCom.xp(), oss.str(), ph, tw);
    clearStream(oss) << ch.constitutionPerLevel();
    guiPrintText(tSta.conPerLevel(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusHealing() << pc;
    guiPrintText(tSta.healingBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.actionPointMaximum();
    guiPrintText(tSta.actionPoints(), oss.str(), ph, tw);
    clearStream(oss) << ch.chanceHit() << pc;
    guiPrintText(tSta.hitChance(), oss.str(), ph, tw);
    clearStream(oss) << ch.chanceCritDamage() << pc;
    guiPrintText(tSta.critChance(), oss.str(), ph, tw);
    clearStream(oss) << ch.multiplierCritDamage() << x;
    guiPrintText(tSta.critDmg(), oss.str(), ph, tw);
    clearStream(oss) << ch.armorPenetration();
    guiPrintText(tSta.penetration(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusSneakAttackDamage() << pc;
    guiPrintText(tSta.sneakAttackDmg(), oss.str(), ph, tw);
    clearStream(oss) << ch.strikeRate() << pc;
    guiPrintText(tSta.strikeRate(), oss.str(), ph, tw);
    clearStream(oss) << ch.armor();
    guiPrintText(tSta.armor(), oss.str(), ph, tw);
    clearStream(oss) << ch.evasion() << pc;
    guiPrintText(tSta.evasion(), oss.str(), ph, tw);
    clearStream(oss) << ch.resistanceCritDamage() << pc;
    guiPrintText(tSta.critResistance(), oss.str(), ph, tw);
    clearStream(oss) << ch.resistanceFireDamage() << pc;
    guiPrintText(tSta.fireResistance(), oss.str(), ph, tw);
    clearStream(oss) << ch.resistanceColdDamage() << pc;
    guiPrintText(tSta.coldResistance(), oss.str(), ph, tw);
    clearStream(oss) << ch.resistanceEnergyDamage() << pc;
    guiPrintText(tSta.energyResistance(), oss.str(), ph, tw);
    clearStream(oss) << ch.resistanceExplosiveDamage() << pc;
    guiPrintText(tSta.explosiveResistance(), oss.str(), ph, tw);
    clearStream(oss) << ch.resistanceStatusEffect() << pc;
    guiPrintText(tSta.statusEffectResistance(), oss.str(), ph, tw);
    clearStream(oss) << tCom.level() << sp << ch.radiationResistance();
    guiPrintText(tSta.radiationResistance(), oss.str(), ph, tw);
    clearStream(oss) << ch.downedTime();
    guiPrintText(tSta.downedTime(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusMeleeDamage() << pc;
    guiPrintText(tSta.meleeDmgBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusRangedDamage() << pc;
    guiPrintText(tSta.rangedDmgBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusNormalDamage() << pc;
    guiPrintText(tSta.normalDmgBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusFireDamage() << pc;
    guiPrintText(tSta.fireDmgBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusColdDamage() << pc;
    guiPrintText(tSta.coldDmgBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusEnergyDamage() << pc;
    guiPrintText(tSta.energyDmgBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.bonusExplosiveDamage() << pc;
    guiPrintText(tSta.explosiveDmgBonus(), oss.str(), ph, tw);
    clearStream(oss) << ch.perception();
    guiPrintText(tSta.perception(), oss.str(), ph, tw);
    clearStream(oss) << ch.multiplierThrowingRange() << x;
    guiPrintText(tSta.throwingRange(), oss.str(), ph, tw);
    clearStream(oss) << ch.initiative() << pc;
    guiPrintText(tSta.initiative(), oss.str(), ph, tw);
    clearStream(oss) << ch.timeDetection() << sp << tCom.sec();
    guiPrintText(tSta.detectionTime(), oss.str(), ph, tw);
    clearStream(oss) << ch.multiplierCombatSpeed() << x;
    guiPrintText(tSta.combatSpeed(), oss.str(), ph, tw);
    //clearStream(oss) << ch.();
    //guiPrintText(tSta.quickSlots(), oss.str(), ph, tw);
    clearStream(oss) << ch.rangeLeadership() << sp << tCom.m_meter();
    guiPrintText(tSta.leadershipRange(), oss.str(), ph, tw);
}

void guiPrintText(const common::Text& left,
                  const common::Text& right,
                  const char placeholder,
                  const float totalWidth)
{
    float textWidthLeft { ImGui::CalcTextSize(left.c_str()).x };
    float textWidthRight{ ImGui::CalcTextSize(right.c_str()).x };
    float textWidthPlaceholder{ totalWidth - textWidthLeft - textWidthRight };
    common::Text phText{ sign::space };
    phText += sign::space;
    while (ImGui::CalcTextSize(phText.c_str()).x < textWidthPlaceholder) {
        phText += placeholder;
    }
    swap(phText[1], phText[phText.size() - 1]);
    common::Text fullText{ left + phText + right };
    ImGui::TextUnformatted(fullText.c_str());
}

} // namespace menu
} // namespace game
