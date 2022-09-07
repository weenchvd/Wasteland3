
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

namespace game {
namespace menu {

using namespace std;

void guiMenuItemModify(bool* open, object::Squad& squad, object::Item& item)
{
    using game::object::InventoryIterator;
    using game::object::Item;
    using game::object::Weapon;
    using game::object::WeaponMod;

    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };
    const auto& wmodT{ WeaponMod::weaponModText() };

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
        ImGui::PushStyleColor(ImGuiCol_Button, color::grayDark);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color::gray);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, color::turquoise);

        object::ItemVisitorType vis;
        item.accept(vis);

        switch (vis.type()) {
        case object::Item::Type::WEAPON: {
            Weapon& weapon{ static_cast<Weapon&>(item) };
            auto& slots{ weapon.slotMod() };
            ItemVisitorWeaponCharacteristics visWeaponChar;
            weapon.accept(visWeaponChar);

            if (ImGui::BeginChild("WeaponModification", columnSize, true)) {
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

                    bool popStyleColor{ false };
                    if (selected) {
                        if (selected == slot.get()) {
                            popStyleColor = true;
                            ImGui::PushStyleColor(ImGuiCol_Button, color::turquoise);
                        }
                        else if (object::isCompatible(weapon.slotMod().type(i),
                            static_cast<const WeaponMod*>(selected)->type()))
                        {
                            popStyleColor = true;
                            ImGui::PushStyleColor(ImGuiCol_Button, color::green);
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
                    if (popStyleColor) {
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
                ImGui::NewLine();
                ImGui::TextUnformatted(visWeaponChar.damageAndDamageType().c_str());
                const auto& dmgDescr{ visWeaponChar.damageDescription() };
                if (dmgDescr.size() > 0) {
                    ImGui::TextUnformatted(dmgDescr.c_str());
                }
                ImGui::TextUnformatted(visWeaponChar.attackDescription().c_str());
                ImGui::TextUnformatted(visWeaponChar.actionPoints().c_str());
                ImGui::TextUnformatted(visWeaponChar.actionPointsReload().c_str());
                const auto& ammoCap{ visWeaponChar.ammoCapacity() };
                if (ammoCap.size() > 0) {
                    ImGui::TextUnformatted(ammoCap.c_str());
                }
                const auto& ammoType{ visWeaponChar.ammoType() };
                if (ammoType.size() > 0) {
                    ImGui::TextUnformatted(ammoType.c_str());
                }
                const auto& bonSneakAtt{ visWeaponChar.bonusSneakAttackDamage() };
                if (bonSneakAtt.size() > 0) {
                    ImGui::TextUnformatted(bonSneakAtt.c_str());
                }
                const auto& bonNormalDmg{ visWeaponChar.bonusNormalDamage() };
                if (bonNormalDmg.size() > 0) {
                    ImGui::TextUnformatted(bonNormalDmg.c_str());
                }
                const auto& bonMeleeDmg{ visWeaponChar.bonusMeleeDamage() };
                if (bonMeleeDmg.size() > 0) {
                    ImGui::TextUnformatted(bonMeleeDmg.c_str());
                }
                const auto& bonRangedDmg{ visWeaponChar.bonusRangedDamage() };
                if (bonRangedDmg.size() > 0) {
                    ImGui::TextUnformatted(bonRangedDmg.c_str());
                }
                ImGui::TextUnformatted(visWeaponChar.hitChance().c_str());
                ImGui::TextUnformatted(visWeaponChar.critDamage().c_str());
                ImGui::TextUnformatted(visWeaponChar.critChance().c_str());
                ImGui::TextUnformatted(visWeaponChar.penetration().c_str());

                ImGui::EndChild();
            }

            ImGui::SameLine();
            if (ImGui::BeginChild("WeaponMods", columnSize, true)) {
                squad.inventory().viewedAll();
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

                    bool popStyleColor{ false };
                    if (selected == mod) {
                        popStyleColor = true;
                        ImGui::PushStyleColor(ImGuiCol_Button, color::turquoise);
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
                    if (popStyleColor) {
                        popStyleColor = false;
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

                ImGui::EndChild();
            }

            ImGui::SameLine();
            guiItemFullDescription(selected, columnSize, true);

            break;
        }
        default:
            assert(true);
            break;
        }
        ImGui::PopStyleColor(3);

        ImGui::Dummy(ImVec2{ 0, ImGui::GetFrameHeight() });
        if (ImGui::Button(comT.exitMenu().c_str())) {
            selected = nullptr;
            *open = false;
        }

        ImGui::End();
    }
}

///************************************************************************************************

} // namespace menu
} // namespace game
