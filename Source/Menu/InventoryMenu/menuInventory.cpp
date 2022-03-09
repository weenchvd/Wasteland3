
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuItem.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"

namespace game {
namespace menu {

using namespace std;

void menuInventory(object::Squad& squad, const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << text.menuName() << endl;
        cout << ind1 << comT.actions() << endl;
        printMenuBar(ind2, actionCommon::EXIT, comT.exitMenu());
        printMenuBar(ind2, actionInventory::MONEY, text.showMoney());
        printMenuBar(ind2, actionInventory::SHOW_ITEMS, text.showItems());
        printMenuBar(ind2, actionInventory::MENU_ITEM, text.enterItemMenu());

        switch (getAction()) {
        case actionInventory::MONEY:
            cout << ind2 << text.money() << squad.money() << endl;
            break;
        case actionInventory::SHOW_ITEMS:
            subMenuShowItems(squad.inventory(), ind1);
            break;
        case actionInventory::MENU_ITEM: {
            auto roster{ subMenuShowItems(squad.inventory(), ind1) };
            if (roster.second == true) {
                auto iter{ pickItem(roster.first, ind1) };
                if (iter.second == true) {
                    menuItem(squad, iter.first, ind1);
                }
            }
            break;
        }
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

pair<object::Roster, bool> subMenuShowItems(object::Inventory& inventory, const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };
    pair<object::Roster, bool> ret{ object::Roster{ inventory.roster() }, false };

    cout << ind1 << comT.actions() << endl;
    printMenuBar(ind2, actionShowItems::SHOW_ALL_ITEMS, text.showAllItems());
    printMenuBar(ind2, actionShowItems::SHOW_ITEMS_OF_TYPE, text.showItemsOfType());

    switch (getAction()) {
    case actionShowItems::SHOW_ALL_ITEMS:
        ret.first = inventory.roster();
        ret.second = true;
        showItems(ret.first, text.inventory(), ind1);
        break;
    case actionShowItems::SHOW_ITEMS_OF_TYPE: {
        object::Item::Type type{ pickItemType(ind1) };
        if (type != object::Item::Type::INVALID) {
            ret.first = inventory.roster(type);
            ret.second = true;
            showItems(ret.first, text.inventory(), ind1);
        }
        break;
    }
    case actionCommon::INVALID:
        break;
    default:
        cout << comT.errorSymbol() << comT.unknownAction() << endl;
        break;
    }
    return ret;
}

///************************************************************************************************

void showItems(object::Roster& roster, const common::Text& title, const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    cout << ind1 << title << endl;
    showRoster(roster, ind1);
}

void showRoster(object::Roster& roster, const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    const auto& text{ MenuInventoryText::common() };

    int i{ itemNumber::countFrom };
    for (auto iter{ roster.newItems().beg_ }; iter != roster.newItems().end_; ++iter) {
        cout << ind1 << text.item() << i++ << ": " << '*' << (*iter)->name() << endl;
    }
    for (auto iter{ roster.oldItems().beg_ }; iter != roster.oldItems().end_; ++iter) {
        cout << ind1 << text.item() << i++ << ": " << (*iter)->name() << endl;
    }
}

object::Item::Type pickItemType(const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };

    cout << ind1 << text.typesOfItems() << endl;

    for (int i{ common::toUnderlying(common::firstEnum<object::Item::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Item::Type>()); ++i)
    {
        cout << ind2 << '\'' << i << "\' "
            << getItemTypeName(static_cast<object::Item::Type>(i)) << endl;
    }
    cout << ind1 << comT.selectType() << endl;
    object::Item::Type t{ object::Item::Type::INVALID };
    auto pair{ getNumber() };
    if (pair.second == true) {
        if (pair.first >= common::toUnderlying(common::firstEnum<object::Item::Type>()) &&
            pair.first <= common::toUnderlying(common::lastEnum<object::Item::Type>()))
        {
            t = static_cast<object::Item::Type>(pair.first);
        }
        else {
            cout << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return t;
}

pair<list<unique_ptr<object::Item>>::const_iterator, bool> pickItem(
    object::Roster& roster,
    const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };

    cout << ind1 << text.enterItemNumber() << endl;

    auto pair{ getNumber() };
    if (pair.second == true) {
        if (pair.first >= itemNumber::countFrom) {
            int i{ itemNumber::countFrom };
            auto iter = roster.newItems().beg_;
            while (i < pair.first && iter != roster.newItems().end_) {
                ++i;
                ++iter;
            }
            if (i == pair.first && iter != roster.newItems().end_) {
                return { iter, true };
            }

            iter = roster.oldItems().beg_;
            while (i < pair.first && iter != roster.oldItems().end_) {
                ++i;
                ++iter;
            }
            if (i == pair.first && iter != roster.oldItems().end_) {
                return { iter, true };
            }
        }
        else {
            cout << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return { list<unique_ptr<object::Item>>::const_iterator{}, false };
}

const common::Text& getItemTypeName(const object::Item::Type type)
{
    switch (type) {
    case object::Item::Type::WEAPON:
        return object::Weapon::weaponText().common().itemType();
    case object::Item::Type::WEAPON_MOD:
        return object::WeaponMod::weaponModText().common().itemType();
    case object::Item::Type::AMMO:
        return object::Ammo::ammoText().common().itemType();
    default: {
        static const common::Text def{ "???" };
        return def;
    }
    }
}

} // namespace menu
} // namespace game
