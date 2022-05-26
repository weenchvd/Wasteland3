
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorType.hpp"
#include"menuCommonText.hpp"
#include"menuItem.hpp"
#include"menuItemCommon.hpp"
#include"menuItemModify.hpp"
#include"menuItemText.hpp"
#include<assert.h>

namespace game {
namespace menu {

using namespace std;

void menuItem_Inventory(
    istream& is,
    ostream& os,
    object::Squad& squad,
    object::InventoryIterator& iterItem,
    const Indent indent)
{
    assert(iterItem.isValid() == true);
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::common() };

    squad.inventory().viewed(iterItem);

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionItem::SHOW_FULL_DESCR, text.showFullDescription()) << endl;
        printNumBar(os, ind1, actionItem::REMOVE, comT.remove()) << endl;

        switch (contextSensitiveMenuItem_Inventory(is, os, squad, iterItem, indent)) {
        case actionItem::SHOW_FULL_DESCR:
            printFullDescription(is, os, iterItem, ind1);
            break;
        case actionItem::REMOVE:
            if (removeItem(is, os, squad.inventory(), iterItem, ind1)) return;
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
    object::InventoryIterator& iterItem,
    const Indent indent
)
{
    assert(iterItem.isValid() == true);
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::common() };
    object::ItemVisitorType vis;
    (*iterItem.getConst())->accept(vis);

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
            menuItemModify(is, os, squad, iterItem, ind1);
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

} // namespace menu
} // namespace game
