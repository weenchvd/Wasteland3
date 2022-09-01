
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"itemVisitorExtendedName.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuItem.hpp"
#include"menuItemCommon.hpp"
#include"menuItemText.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"

namespace game {
namespace menu {

using namespace std;

void menuInventory(istream& is, ostream& os, object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& itemT{ MenuItemText::common() };
    const auto& text{ MenuInventoryText::common() };
    pair<object::Roster, bool> pairRoster{ object::Roster{ squad.inventory().roster() }, false};

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionInventory::MONEY, text.showMoney()) << endl;
        printNumBar(os, ind1, actionInventory::SHOW_ITEMS, text.showItems()) << endl;
        printNumBar(os, ind1, actionInventory::MENU_ITEM, text.enterItemMenu()) << endl;
        printNumBar(os, ind1, actionInventory::SHOW_FULL_DESCR, itemT.showFullDescription()) << endl;
        printNumBar(os, ind1, actionInventory::MARK_ALL_AS_VIEWED, text.markAllAsViewed()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionInventory::MONEY:
            os << ind1 << text.money() << sign::colon << sign::space << sign::dollar
                << squad.money() << endl;
            break;
        case actionInventory::SHOW_ITEMS:
            pairRoster = subMenuShowItems(is, os, squad.inventory(), ind1);
            break;
        case actionInventory::MENU_ITEM: {
            pairRoster = subMenuShowItems(is, os, squad.inventory(), ind1);
            if (pairRoster.second == true) {
                auto iter{ pickItem(is, os, pairRoster.first, ind0) };
                if (iter.isValid() == true) {
                    menuItem_Inventory(is, os, squad, iter, ind1);
                    pairRoster.second = false;
                }
            }
            break;
        }
        case actionInventory::SHOW_FULL_DESCR:
            if (pairRoster.second == true) {
                auto iter{ pickItem(is, os, pairRoster.first, ind0) };
                if (iter.isValid() == true) {
                    printFullDescription(is, os, iter, ind1);
                }
            }
            else {
                os << comT.errorSymbol() << text.listIsOutdated();
                printNumBar(os, Indent{ 0 }, actionInventory::SHOW_ITEMS, text.showItems()) << endl;
            }
            break;
        case actionInventory::MARK_ALL_AS_VIEWED:
            squad.inventory().viewedAll();
            pairRoster.second = false;
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

pair<object::Roster, bool> subMenuShowItems(
    istream& is,
    ostream& os,
    object::Inventory& inventory,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };
    pair<object::Roster, bool> ret{ object::Roster{ inventory.roster() }, false };

    os << ind0 << comT.actions() << endl;
    printNumBar(os, ind1, actionShowItems::SHOW_ALL_ITEMS, text.showAllItems()) << endl;
    printNumBar(os, ind1, actionShowItems::SHOW_ITEMS_OF_TYPE, text.showItemsOfType()) << endl;
    os << ind0 << comT.enterAction() << endl;

    switch (getAction(is, os)) {
    case actionShowItems::SHOW_ALL_ITEMS: {
        ret.first = inventory.roster();
        ret.second = true;
        auto title{ text.inventory() + " (" + text.starNewItems() + "):" };
        showItems(is, os, ret.first, title, ind0);
        break;
    }
    case actionShowItems::SHOW_ITEMS_OF_TYPE: {
        object::Item::Type type{ pickItemType(is, os, ind0) };
        if (type != object::Item::Type::__INVALID) {
            ret.first = inventory.roster(type);
            ret.second = true;
            auto title{ text.inventory() + " (" + getItemTypeName(type) + "):" };
            showItems(is, os, ret.first, title, ind0);
        }
        break;
    }
    case actionCommon::INVALID:
        break;
    default:
        os << comT.errorSymbol() << comT.unknownAction() << endl;
        break;
    }
    return ret;
}

///************************************************************************************************

void showItems(
    istream& is,
    ostream& os,
    const object::Roster& roster,
    const common::Text& title,
    const Indent indent)
{
    os << indent << title << endl;
    showRoster(is, os, roster, indent + Indent{});
}

void showRoster(istream& is, ostream& os, const object::Roster& roster, const Indent indent)
{
    Indent ind0{ indent };
    const auto& text{ MenuInventoryText::common() };

    ItemVisitorExtendedName vis;
    int i{ itemNumber::countFrom };
    for (auto iter{ roster.newItems().beg_.getConst()};
        iter != roster.newItems().end_.getConst();
        ++iter)
    {
        (*iter)->accept(vis);
        printNumBar(os, ind0, i++, '*' + vis.getExtendedName()) << endl;
    }
    for (auto iter{ roster.oldItems().beg_.getConst() };
        iter != roster.oldItems().end_.getConst();
        ++iter)
    {
        (*iter)->accept(vis);
        printNumBar(os, ind0, i++, vis.getExtendedName()) << endl;
    }
}

object::Item::Type pickItemType(istream& is, ostream& os, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };

    os << ind0 << text.typesOfItems() << endl;

    for (int i{ common::toUnderlying(common::firstEnum<object::Item::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Item::Type>()); ++i)
    {
        printNumBar(os, ind1, i, getItemTypeName(static_cast<object::Item::Type>(i))) << endl;
    }
    os << ind0 << comT.selectType() << endl;
    object::Item::Type t{ object::Item::Type::__INVALID };
    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        if (pair.first >= common::toUnderlying(common::firstEnum<object::Item::Type>()) &&
            pair.first <= common::toUnderlying(common::lastEnum<object::Item::Type>()))
        {
            t = static_cast<object::Item::Type>(pair.first);
        }
        else {
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return t;
}

object::InventoryIterator pickItem(
    istream& is,
    ostream& os,
    const object::Roster& roster,
    const Indent indent)
{
    Indent ind0{ indent };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuInventoryText::common() };

    os << ind0 << text.enterItemNumber() << endl;

    auto pairNum{ getNumber(is, os) };
    if (pairNum.second == true) {
        if (pairNum.first >= itemNumber::countFrom) {
            int i{ itemNumber::countFrom };
            auto iter{ roster.newItems().beg_ };
            while (i < pairNum.first && iter != roster.newItems().end_) {
                ++i;
                ++iter;
            }
            if (i == pairNum.first && iter != roster.newItems().end_) {
                return iter;
            }

            iter = roster.oldItems().beg_;
            while (i < pairNum.first && iter != roster.oldItems().end_) {
                ++i;
                ++iter;
            }
            if (i == pairNum.first && iter != roster.oldItems().end_) {
                return iter;
            }
        }
        os << comT.errorSymbol() << comT.invalidNumber() << endl;
    }
    return object::InventoryIterator{};
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
