
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"gui_menuCommon.hpp"
#include"gui_menuInventory.hpp"
#include"gui_menuItem.hpp"
#include"imgui.h"
#include"inventory.hpp"
#include"itemVisitorFullDescr.hpp"
#include"itemVisitorType.hpp"
#include"menuCommonText.hpp"
#include"menuItemText.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void guiMenuItemModify(bool* open, object::Squad& squad, object::Item& item)
{
    using game::object::InventoryIterator;
    using game::object::Item;
    using game::object::Weapon;
    using game::object::WeaponMod;

    const auto& comT    { MenuCommonText::common() };
    const auto& text    { MenuItemText::modify() };
    const auto& wmodT   { WeaponMod::weaponModText() };

    const ImVec4 colItem            { color::greyDark };
    const ImVec4 colItemHovered     { color::grey };
    const ImVec4 colItemActive      { color::turquoise };
    const ImVec4 colItemSelected    { color::turquoise };
    const ImVec4 colSlot            { color::greyDark };
    const ImVec4 colSlotHovered     { color::grey };
    const ImVec4 colSlotActive      { color::turquoise };
    const ImVec4 colSlotSelected    { color::turquoise };
    const ImVec4 colSlotCompatible  { color::green };

    static const Item* selected{ nullptr };

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.menuName().c_str() } + u8"###MenuItemModify";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        const ImGuiStyle& style{ ImGui::GetStyle() };
        ImVec2 contentRegionSize{ ImGui::GetWindowContentRegionMax() };
        ImVec2 columnSize{
            contentRegionSize.x / 3.0f - style.ItemSpacing.x,
            contentRegionSize.y - style.ItemSpacing.y - ImGui::GetFrameHeightWithSpacing() * 3.0f
        };

        object::ItemVisitorType vis;
        item.accept(vis);

        switch (vis.type()) {
        case object::Item::Type::WEAPON: {
            Weapon& weapon{ static_cast<Weapon&>(item) };
            auto& slots{ weapon.slotMod() };
            ItemVisitorWeaponCharacteristics visWeaponChar;
            weapon.accept(visWeaponChar);

            ///********** Weapon window
            if (ImGui::BeginChild("WeaponModification", columnSize, true)) {
                ImGui::PushStyleColor(ImGuiCol_Button, colSlot);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colSlotHovered);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, colSlotActive);
                ImVec2 buttonSize{
                    columnSize.x - style.ItemSpacing.x * 2.0f,
                    0.0f
                };
                ImGui::TextUnformatted(visWeaponChar.name().c_str());
                ImGui::TextUnformatted(visWeaponChar.levelAndType().c_str());
                ImGui::NewLine();

                for (int i = 0; i < slots.size(); ++i) {
                    auto& slot{ slots[i] };
                    ImGui::PushID(slot.get());
                    ImGui::TextUnformatted(wmodT.type(slots.type(i)).c_str());

                    bool setColorButton{ false };
                    if (selected) {
                        if (selected == slot.get()) {
                            setColorButton = true;
                            ImGui::PushStyleColor(ImGuiCol_Button, colSlotSelected);
                        }
                        else if (object::isCompatible(weapon.slotMod().type(i),
                            static_cast<const WeaponMod*>(selected)->type()))
                        {
                            setColorButton = true;
                            ImGui::PushStyleColor(ImGuiCol_Button, colSlotCompatible);
                        }
                    }
                    if (slot != nullptr) {
                        if (ImGui::Button(slot->name().c_str(), buttonSize)) {
                            selected = static_cast<Item*>(slot.get());
                        }
                        if (ImGui::BeginPopupContextItem("ContextMenu")) {
                            if (ImGui::Selectable(text.removeMod().c_str())) {
                                unique_ptr<object::Item> oldMod{};
                                weapon.unsetMod(i, oldMod);
                                if (oldMod != nullptr) {
                                    squad.inventory().insert(oldMod);
                                }
                            }
                            ImGui::EndPopup();
                        }
                    }
                    else {
                        ImGui::Button("##EmptySlot", buttonSize);
                    }
                    if (setColorButton) {
                        ImGui::PopStyleColor();
                    }
                    if (ImGui::BeginDragDropTarget()) {
                        if (const ImGuiPayload * payload{ ImGui::AcceptDragDropPayload("WeaponMod") }) {
                            assert(payload->DataSize == sizeof(InventoryIterator));
                            InventoryIterator iter{ *static_cast<InventoryIterator*>(payload->Data) };
                            assert(iter.isValid());
                            if (object::isCompatible(weapon.slotMod().type(i),
                                static_cast<object::WeaponMod*>(iter.get()->get())->type()))
                            {
                                auto newMod{ squad.inventory().extract(iter) };
                                unique_ptr<object::Item> oldMod{};
                                weapon.unsetMod(i, oldMod);
                                weapon.setMod(i, newMod);
                                if (oldMod != nullptr) {
                                    squad.inventory().insert(oldMod);
                                }
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }
                    ImGui::PopID();
                }

                ostringstream oss;
                oss << visWeaponChar.damageAndDamageType() << endl;
                const auto& dmgDescr{ visWeaponChar.damageDescription() };
                if (dmgDescr.size() > 0) {
                    oss << dmgDescr;
                }
                oss << visWeaponChar.attackDescription()
                    << visWeaponChar.actionPoints() << endl
                    << visWeaponChar.actionPointsReload() << endl;
                const auto& ammoCap{ visWeaponChar.ammoCapacity() };
                if (ammoCap.size() > 0) {
                    oss << ammoCap << endl;
                }
                const auto& ammoType{ visWeaponChar.ammoType() };
                if (ammoType.size() > 0) {
                    oss << ammoType << endl;
                }
                const auto& bonSneakAtt{ visWeaponChar.bonusSneakAttackDamage() };
                if (bonSneakAtt.size() > 0) {
                    oss << bonSneakAtt << endl;
                }
                const auto& bonNormalDmg{ visWeaponChar.bonusNormalDamage() };
                if (bonNormalDmg.size() > 0) {
                    oss << bonNormalDmg << endl;
                }
                const auto& bonMeleeDmg{ visWeaponChar.bonusMeleeDamage() };
                if (bonMeleeDmg.size() > 0) {
                    oss << bonMeleeDmg << endl;
                }
                const auto& bonRangedDmg{ visWeaponChar.bonusRangedDamage() };
                if (bonRangedDmg.size() > 0) {
                    oss << bonRangedDmg << endl;
                }
                oss << visWeaponChar.hitChance() << endl
                    << visWeaponChar.critDamage() << endl
                    << visWeaponChar.critChance() << endl
                    << visWeaponChar.penetration();

                ImGui::NewLine();
                ImGui::TextUnformatted(oss.str().c_str());

                ImGui::PopStyleColor(3);
            }
            ImGui::EndChild();

            ///********** Weapon mods window
            ImGui::SameLine();
            if (ImGui::BeginChild("WeaponMods", columnSize, true)) {
                squad.inventory().viewedAll();
                ImGui::PushStyleColor(ImGuiCol_Button, colItem);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colItemHovered);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, colItemActive);
                object::Roster weaponMods{ squad.inventory().roster(Item::Type::WEAPON_MOD) };
                for (auto iter{ weaponMods.oldItems().beg_};
                    iter != weaponMods.oldItems().end_;
                    ++iter)
                {
                    const ImVec2 buttonPaddingX2{ style.FramePadding.x * 2, style.FramePadding.y * 2 };
                    const auto buttonHeight{ ImGui::GetFrameHeight() };
                    const auto windowVisibleX{
                        ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x
                    };

                    Item* mod{ iter.get()->get() };
                    ImGui::PushID(mod);

                    bool setColorButton{ selected == mod ? true : false };
                    if (setColorButton) {
                        ImGui::PushStyleColor(ImGuiCol_Button, colItemSelected);
                    }
                    auto textSize{ ImGui::CalcTextSize(mod->name().c_str()) };
                    ImVec2 buttonSize{ textSize.x + buttonPaddingX2.x, buttonHeight };
                    if (ImGui::Button(mod->name().c_str(), buttonSize)) {
                        selected = mod;
                    }
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        selected = mod;
                        ImGui::SetDragDropPayload("WeaponMod", &iter, sizeof(iter));
                        ImGui::TextUnformatted(mod->name().c_str());
                        ImGui::EndDragDropSource();
                    }
                    if (setColorButton) {
                        ImGui::PopStyleColor();
                    }

                    auto iterNext{ iter };
                    if (++iterNext != weaponMods.oldItems().end_) {
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
            ImGui::EndChild();

            ///********** Description window
            ImGui::SameLine();
            guiItemFullDescription(selected, columnSize, true);

            break;
        }
        default:
            assert(true);
            break;
        }

        ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() });
        if (ImGui::Button(comT.exitMenu().c_str())) {
            selected = nullptr;
            *open = false;
        }
    }
    ImGui::End();
}

///************************************************************************************************

} // namespace menu
} // namespace game
