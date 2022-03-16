
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorType.hpp"
#include"itemVisitorFullDescr.hpp"
#include"menuCommonText.hpp"
#include"menuItem.hpp"
#include"menuItemModify.hpp"
#include"menuItemText.hpp"

namespace game {
namespace menu {

using namespace std;

void menuItem_Inventory(
    istream& is,
    ostream& os,
    object::Squad& squad,
    list<unique_ptr<object::Item>>::const_iterator item,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::common() };

    item = squad.inventory().viewed(item);

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionItem::SHOW_FULL_DESCR, text.showFullDescription()) << endl;
        printNumBar(os, ind1, actionItem::REMOVE, comT.remove()) << endl;

        switch (contextSensitiveMenuItem_Inventory(is, os, squad, item, indent)) {
        case actionItem::SHOW_FULL_DESCR:
            printFullDescription(is, os, *item, ind1);
            break;
        case actionItem::REMOVE:
            if (removeItem(is, os, squad.inventory(), item, ind1)) return;
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

int contextSensitiveMenuItem_Inventory(
    istream& is,
    ostream& os,
    object::Squad& squad,
    list<unique_ptr<object::Item>>::const_iterator item,
    const Indent indent
)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::common() };
    object::ItemVisitorType vis;
    (*item)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        printNumBar(os, ind1, actionItemWeapon::EQUIP, text.equip()) << endl;
        printNumBar(os, ind1, actionItemWeapon::MODIFY, text.modify()) << endl;
        os << ind0 << comT.enterAction() << endl;

        auto action{ getAction(is, os) };
        switch (action) {
        case actionItemWeapon::EQUIP:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionItemWeapon::MODIFY: {
            auto pair{ squad.inventory().getIterator(item) };
            if (pair.second == true) {
                menuItemModify(is, os, squad, pair.first, ind1);
            }
            break;
        }
        default:
            return action;
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        os << ind0 << comT.enterAction() << endl;
        return getAction(is, os);
    }
    return actionCommon::INVALID;
}

///************************************************************************************************

void printFullDescription(
    istream& is,
    ostream& os,
    const unique_ptr<object::Item>& item,
    const Indent indent)
{
    ItemVisitorFullDescription vis;
    item->accept(vis);
    auto text{ vis.getFullDescription() };
    for (int i = 0; i < text.size(); ++i) {
        os << indent;
        while (i < text.size() && text[i] != '\n') {
            os << text[i++];
        }
        os << endl;
    }
    if (text.size() > 0) {
        os << endl;
    }
}

bool removeItem(
    istream& is,
    ostream& os,
    object::Inventory& inventory,
    list<unique_ptr<object::Item>>::const_iterator item,
    const Indent indent)
{
    const auto& text{ MenuItemText::common() };
    os << indent << text.questionDeleteItem() << endl;
    switch (getYesNo(is, os, indent)) {
    case YesNo::YES:
        inventory.extract(item);
        return true;
    case YesNo::NO:
    case YesNo::CANCEL:
    default:
        return false;
    }
}

} // namespace menu
} // namespace game
