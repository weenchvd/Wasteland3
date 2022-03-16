
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
    istream& is,
    ostream& os,
    object::Squad& squad,
    list<unique_ptr<object::Item>>::iterator iterator,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& tCom{ MenuItemText::common() };
    const auto& text{ MenuItemText::modify() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << text.item() << (*iterator)->name() << endl;
        showMods(is, os, iterator, indent);
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionItemModify::SHOW_FULL_DESCR, tCom.showFullDescription()) << endl;
        printNumBar(os, ind1, actionItemModify::INSTALL_MOD, text.installMod()) << endl;
        printNumBar(os, ind1, actionItemModify::REMOVE_MOD, text.removeMod()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionItemModify::SHOW_FULL_DESCR:
            printFullDescription(is, os, *iterator, ind1);
            break;
        case actionItemModify::INSTALL_MOD:
            contextSensitiveMenuItemModify_Install(is, os, squad, iterator, ind1);
            break;
        case actionItemModify::REMOVE_MOD:
            contextSensitiveMenuItemModify_Remove(is, os, squad, iterator, ind1);
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void contextSensitiveMenuItemModify_Install(
    istream& is,
    ostream& os,
    object::Squad& squad,
    list<unique_ptr<object::Item>>::iterator iterator,
    const Indent indent
)
{
    Indent ind0{ indent };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };
    const auto& invTCom{ MenuInventoryText::common() };
    object::ItemVisitorType vis;
    (*iterator)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        auto pairSlotNumber{ pickSlotNumber(is, os, squad, iterator, ind0) };
        if (pairSlotNumber.second == false) break;
        object::Item::Type type{ object::Item::Type::WEAPON_MOD };
        auto roster{ squad.inventory().roster(type) };
        auto title{ invTCom.inventory() + " (" + getItemTypeName(type) + "):" };
        showItems(is, os, roster, title, ind0);
        auto pairIter{ pickItem(is, os, roster, ind0) };
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
            os << comT.errorSymbol() << text.unsuitableMod() << endl;
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
}

void contextSensitiveMenuItemModify_Remove(
    std::istream& is,
    std::ostream& os,
    object::Squad& squad,
    std::list<std::unique_ptr<object::Item>>::iterator iterator,
    const Indent indent)
{
    Indent ind0{ indent };
    object::ItemVisitorType vis;
    (*iterator)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        auto pairSlotNumber{ pickSlotNumber(is, os, squad, iterator, ind0) };
        if (pairSlotNumber.second == false) break;
        auto* weapon{ static_cast<object::Weapon*>(iterator->get()) };
        unique_ptr<object::Item> oldMod{};
        weapon->unsetMod(pairSlotNumber.first, oldMod);
        if (oldMod != nullptr) {
            squad.inventory().insert(oldMod);
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
    istream& is,
    ostream& os,
    list<unique_ptr<object::Item>>::const_iterator iterator,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };

    os << ind0 << text.mods() << endl;

    int i{ itemModNumber::countFrom };
    object::ItemVisitorType vis;
    (*iterator)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        const auto* weapon{ static_cast<object::Weapon*>(iterator->get()) };
        for (int j = 0; j < weapon->slotMod().sizeRaw(); ++j) {
            if (weapon->slotMod().type(j) != object::WeaponMod::Type::INVALID) {
                printNumBar(os, ind1, i++,
                    object::WeaponMod::weaponModText().type(weapon->slotMod().type(j))
                );
                os << ": ";
                if (weapon->slotMod()[j] != nullptr) {
                    os << weapon->slotMod()[j]->name();
                }
                os << endl;
            }
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
}

pair<int, bool> pickSlotNumber(
    istream& is,
    ostream& os,
    object::Squad& squad,
    list<unique_ptr<object::Item>>::iterator iterator,
    const Indent indent)
{
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };

    os << indent << text.enterSlotNumber() << endl;

    int i{ itemModNumber::countFrom };
    object::ItemVisitorType vis;
    (*iterator)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        const auto* weapon{ static_cast<object::Weapon*>(iterator->get()) };
        auto pair{ getNumber(is, os) };
        if (pair.second == true) {
            for (int j = 0; j < weapon->slotMod().sizeRaw(); ++j) {
                if (weapon->slotMod().type(j) != object::WeaponMod::Type::INVALID) {
                    if (pair.first == i) {
                        return { j, true };
                    }
                    ++i;
                }
            }
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
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
