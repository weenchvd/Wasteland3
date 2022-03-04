
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"itemVisitorFullDescr.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"

namespace game {
namespace menu {

using namespace std;

void menuInventory(object::Squad& squad, const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};
    const auto& cText{ MenuCommonText::common() };
    const auto& iText{ MenuInventoryText::common() };

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << iText.menuName() << endl;
        cout << ind1 << cText.actions() << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' " << cText.exitMenu() << endl;
        cout << ind2 << '\'' << actionInventory::MONEY << "\' " << iText.showMoney() << endl;
        cout << ind2 << '\'' << actionInventory::ALL_ITEMS << "\' " << iText.showAllItems() << endl;
        cout << ind2 << '\'' << actionInventory::TYPE_ITEMS << "\' " << iText.showItemsOfType() << endl;

        switch (getAction()) {
        case actionInventory::MONEY:
            cout << ind2 << iText.money() << squad.money() << endl;
            break;
        case actionInventory::ALL_ITEMS:
            showAllItems(squad.inventory(), ind1);
            break;
        case actionInventory::TYPE_ITEMS: {
            object::Item::Type type{ pickItemType(ind1) };
            if (type != object::Item::Type::INVALID) {
                showItemsOfType(squad.inventory(), type, ind1);
            }
            else {
                cout << cText.invalidType() << endl;
            }
            break;
        }
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << cText.errorSymbol() << cText.invalidInput() << endl;
            break;
        default:
            cout << cText.errorSymbol() << cText.unknownAction() << endl;
            break;
        }
    }
}

///************************************************************************************************

void printFullDescription(const unique_ptr<object::Item>& item, const Indent indent)
{
    Indent ind{ indent + Indent{} + Indent{} };
    object::ItemVisitorFullDescription vis;
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

void showItems(
    object::Inventory& inventory,
    const object::Item::Type type,
    const Indent indent,
    const bool squad)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};
    const auto& iText{ MenuInventoryText::common() };

    if (squad) {
        cout << ind1 << iText.inventory() << endl;
    }
    else {
        cout << ind1 << iText.shop() << endl;
    }
    object::Inventory::Roster r;
    if (common::isValidEnum(type)) {
        r = inventory.roster(type);
    }
    else {
        r = inventory.roster();
    }
    int i = 0;
    for (auto iter = r.newItems.beg; iter != r.newItems.end; ++iter) {
        cout << ind2 << iText.item() << ++i << ": " << '*' << (*iter)->name() << endl;
        ///printFullDescription(*iter, ind2);
    }
    for (auto iter = r.oldItems.beg; iter != r.oldItems.end; ++iter) {
        cout << ind2 << iText.item() << ++i << ": " << (*iter)->name() << endl;
        ///printFullDescription(*iter, ind2);
    }
}

void showAllItems(object::Inventory& inventory, const Indent indent, const bool squad)
{
    showItems(inventory, object::Item::Type::INVALID, indent, squad);
}

void showItemsOfType(
    object::Inventory& inventory,
    const object::Item::Type type,
    const Indent indent,
    const bool squad)
{
    showItems(inventory, type, indent, squad);
}

object::Item::Type pickItemType(const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};
    const auto& text{ MenuInventoryText::common() };

    cout << ind1 << text.typesOfItems() << endl;

    for (int i = { common::toUnderlying(common::firstEnum<object::Item::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Item::Type>()); ++i)
    {
        cout << ind2 << '\'' << i << "\' "
            << getItemTypeName(static_cast<object::Item::Type>(i)) << endl;
    }
    cout << ind1 << text.selectType() << endl;
    object::Item::Type t{ object::Item::Type::INVALID };
    int n = getPosNumber();
    if (n >= common::toUnderlying(common::firstEnum<object::Item::Type>()) &&
        n <= common::toUnderlying(common::lastEnum<object::Item::Type>()))
    {
        t = static_cast<object::Item::Type>(n);
    }
    return t;
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
