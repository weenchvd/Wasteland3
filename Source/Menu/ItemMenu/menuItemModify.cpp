
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorType.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuItem.hpp"
#include"menuItemModify.hpp"
#include"menuItemText.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"

namespace game {
namespace menu {

using namespace std;

void menuItemModify(
    object::Squad& squad,
    list<unique_ptr<object::Item>>::iterator iterator,
    const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& tCom{ MenuItemText::common() };
    const auto& text{ MenuItemText::modify() };

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << text.menuName() << endl;
        cout << ind1 << text.item() << (*iterator)->name() << endl;
        showMods(iterator, indent);
        cout << ind1 << comT.actions() << endl;
        printMenuBar(ind2, actionCommon::EXIT, comT.exitMenu());
        printMenuBar(ind2, actionItemModify::SHOW_FULL_DESCR, tCom.showFullDescription());
        printMenuBar(ind2, actionItemModify::INSTALL_MOD, text.installMod());
        printMenuBar(ind2, actionItemModify::REMOVE_MOD, text.removeMod());

        switch (getAction()) {
        case actionItemModify::SHOW_FULL_DESCR:
            printFullDescription(*iterator, ind1);
            break;
        case actionItemModify::INSTALL_MOD:
            contextSensitiveMenuItemModify_Install(squad, iterator, ind1);
            break;
        case actionItemModify::REMOVE_MOD:
            cout << ind1 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            cout << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void contextSensitiveMenuItemModify_Install(
    object::Squad& squad,
    list<unique_ptr<object::Item>>::iterator iterator,
    const Indent indent
)
{
    Indent ind1{ indent + Indent{} };
    //Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };
    const auto& invTCom{ MenuInventoryText::common() };
    object::ItemVisitorType vis;
    (*iterator)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        auto pairSlotNumber{ pickSlotNumber(squad, iterator, ind1) };
        if (pairSlotNumber.second == false) break;
        object::Item::Type type{ object::Item::Type::WEAPON_MOD };
        auto roster{ squad.inventory().roster(type) };
        auto title{ invTCom.inventory() + " (" + getItemTypeName(type) + "):" };
        showItems(roster, title, ind1);
        auto pairIter{ pickItem(roster, ind1) };
        if (pairIter.second == false) break;
        auto* weapon{ static_cast<object::Weapon*>(iterator->get()) };
        const auto* weaponMod{ static_cast<object::WeaponMod*>(pairIter.first->get()) };
        if (object::isCompatible(weapon->slotMod().type(pairSlotNumber.first), weaponMod->type())) {
            auto newMod{ squad.inventory().extract(pairIter.first) };
            unique_ptr<object::Item> oldMod{};
            weapon->unsetMod(pairSlotNumber.first, oldMod);
            weapon->setMod(pairSlotNumber.first, newMod, object::isCompatible);
            if (oldMod != nullptr) {
                squad.inventory().insert(oldMod);
            }
        }
        else {
            cout << comT.errorSymbol() << text.unsuitableMod() << endl;
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
}

///************************************************************************************************

void showMods(
    list<unique_ptr<object::Item>>::const_iterator iterator,
    const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };

    cout << ind1 << text.mods() << endl;

    int i{ itemModNumber::countFrom };
    object::ItemVisitorType vis;
    (*iterator)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        const auto* weapon{ static_cast<object::Weapon*>(iterator->get()) };
        for (int j = 0; j < weapon->slotMod().sizeRaw(); ++j) {
            if (weapon->slotMod().type(j) != object::WeaponMod::Type::INVALID) {
                auto t{ object::WeaponMod::weaponModText().type(weapon->slotMod().type(j)) + ": "};
                if (weapon->slotMod()[j] != nullptr) {
                    t += weapon->slotMod()[j]->name();
                }
                printMenuBar(ind2, i++, t);
            }
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
    cout << ind1 << comT.enterAction() << endl;
}

pair<int, bool> pickSlotNumber(
    object::Squad& squad,
    list<unique_ptr<object::Item>>::iterator iterator,
    const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };

    cout << ind1 << text.enterSlotNumber() << endl;

    int i{ itemModNumber::countFrom };
    object::ItemVisitorType vis;
    (*iterator)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        const auto* weapon{ static_cast<object::Weapon*>(iterator->get()) };
        auto pair{ getNumber() };
        if (pair.second == true) {
            for (int j = 0; j < weapon->slotMod().sizeRaw(); ++j) {
                if (weapon->slotMod().type(j) != object::WeaponMod::Type::INVALID) {
                    if (pair.first == i) {
                        return { j, true };
                    }
                    ++i;
                }
            }
            cout << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
    return { numeric_limits<int>::min(), false };
}

} // namespace menu
} // namespace game
