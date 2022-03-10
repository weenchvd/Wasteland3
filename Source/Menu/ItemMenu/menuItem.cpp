
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorType.hpp"
#include"itemVisitorFullDescr.hpp"
#include"menuCommonText.hpp"
#include"menuItem.hpp"
#include"menuItemText.hpp"

namespace game {
namespace menu {

using namespace std;

void menuItem_Inventory(
    object::Squad& squad,
    list<unique_ptr<object::Item>>::const_iterator item,
    const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::common() };

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << text.menuName() << endl;
        cout << ind1 << comT.actions() << endl;
        printMenuBar(ind2, actionCommon::EXIT, comT.exitMenu());
        printMenuBar(ind2, actionItem::SHOW_FULL_DESCR, text.showFullDescription());
        printMenuBar(ind2, actionItem::REMOVE, comT.remove());

        switch (contextSensitiveMenuItem_Inventory(squad, item, indent)) {
        case actionItem::SHOW_FULL_DESCR:
            printFullDescription(*item, ind1);
            break;
        case actionItem::REMOVE:
            if (removeItem(squad.inventory(), item, ind1)) return;
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

int contextSensitiveMenuItem_Inventory(
    object::Squad& squad,
    list<unique_ptr<object::Item>>::const_iterator item,
    const Indent indent
)
{
    Indent ind1{ indent + Indent{} };
    Indent ind2{ ind1 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::common() };
    object::ItemVisitorType vis;
    (*item)->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        printMenuBar(ind2, actionItemWeapon::EQUIP, text.equip());
        printMenuBar(ind2, actionItemWeapon::MODIFY, text.modify());

        auto action{ getAction() };
        switch (action) {
        case actionItemWeapon::EQUIP:
            cout << ind1 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionItemWeapon::MODIFY:
            cout << ind1 << comT.notImplemented() << endl;
            // TODO
            break;
        default:
            return action;
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        return getAction();
    }
    return actionCommon::INVALID;
}

///************************************************************************************************

void printFullDescription(const unique_ptr<object::Item>& item, const Indent indent)
{
    Indent ind{ indent + Indent{} + Indent{} };
    ItemVisitorFullDescription vis;
    item->accept(vis);
    auto text{ vis.getFullDescription() };
    for (int i = 0; i < text.size(); ++i) {
        cout << ind;
        while (i < text.size() && text[i] != '\n') {
            cout << text[i++];
        }
        cout << endl;
    }
    if (text.size() > 0) {
        cout << endl;
    }
}

bool removeItem(
    object::Inventory& inventory,
    list<unique_ptr<object::Item>>::const_iterator item,
    const Indent indent)
{
    const auto& text{ MenuItemText::common() };
    cout << indent << text.questionDeleteItem() << endl;
    switch (getYesNo(indent)) {
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
