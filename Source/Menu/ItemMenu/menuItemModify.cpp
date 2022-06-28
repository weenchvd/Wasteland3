
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorType.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuInventoryText.hpp"
#include"menuItemCommon.hpp"
#include"menuItemModify.hpp"
#include"menuItemText.hpp"
#include"weapon.hpp"
#include<assert.h>
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void menuItemModify(
    istream& is,
    ostream& os,
    object::Squad& squad,
    object::Item& item,
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
        os << ind0 << text.item() << item.name() << endl;
        showSlotsAndMods(is, os, item, indent);
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionItemModify::SHOW_FULL_DESCR, tCom.showFullDescription()) << endl;
        printNumBar(os, ind1, actionItemModify::INSTALL_MOD, text.installMod()) << endl;
        printNumBar(os, ind1, actionItemModify::REMOVE_MOD, text.removeMod()) << endl;

        int number{ actionItemModify::__NEXT_ACTION_NUMBER };
        switch (contextSensitiveMenuItemModify(is, os, squad, item, number, indent)) {
        case actionItemModify::SHOW_FULL_DESCR:
            printFullDescription(is, os, item, ind1);
            break;
        case actionItemModify::INSTALL_MOD:
            contextSensitiveMenuItemModify_Install(is, os, squad, item, ind1);
            break;
        case actionItemModify::REMOVE_MOD:
            contextSensitiveMenuItemModify_Remove(is, os, squad, item, ind1);
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

int contextSensitiveMenuItemModify(
    istream& is,
    ostream& os,
    object::Squad& squad,
    object::Item& item,
    int nextActionNumber,
    const Indent indent
)
{
    using slot_number_t     = int;
    using action_number_t   = int;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };
    object::ItemVisitorType vis;
    item.accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        const auto& weapon{ static_cast<object::Weapon&>(item) };
        assert(weapon.itemType() == object::Item::Type::WEAPON);

        vector<pair<slot_number_t, action_number_t>> mapping;
        const auto& slots{ weapon.slotMod() };
        for (int i = 0; i < slots.size(); ++i) {
            if (slots[i] != nullptr) {
                mapping.push_back(pair{ i, nextActionNumber++ });
            }
        }

        for (int i = 0; i < mapping.size(); ++i) {
            ostringstream oss;
            oss << text.showFullDescrOfMod() << mapping[i].first + itemCounter::countFrom;
            printNumBar(os, ind1, mapping[i].second, oss.str()) << endl;
        }
        os << ind0 << comT.enterAction() << endl;

        auto action{ getAction(is, os) };
        bool actionFound{ false };
        for (int i = 0; i < mapping.size(); ++i) {
            if (action == mapping[i].second) {
                assert(slots[mapping[i].first].get() != nullptr);
                printFullDescription(is, os, *slots[mapping[i].first].get(), ind1);
                actionFound = true;
                break;
            }
        }
        if (!actionFound) return action;
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

void contextSensitiveMenuItemModify_Install(
    istream& is,
    ostream& os,
    object::Squad& squad,
    object::Item& item,
    const Indent indent
)
{
    Indent ind0{ indent };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };
    const auto& invTCom{ MenuInventoryText::common() };
    object::ItemVisitorType vis;
    item.accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        auto pairSlotNumber{ pickSlotNumber(is, os, squad, item, ind0) };
        if (pairSlotNumber.second == false) break;
        object::Item::Type type{ object::Item::Type::WEAPON_MOD };
        auto roster{ squad.inventory().roster(type) };
        auto title{ invTCom.inventory() + " (" + getItemTypeName(type) + "):" };
        showModsWithTypes(is, os, roster, title, ind0);
        auto iterWeaponMod{ pickItem(is, os, roster, ind0) };
        if (iterWeaponMod.isValid() == false) break;
        auto& weapon{ static_cast<object::Weapon&>(item)};
        const auto* pWeaponMod{ static_cast<object::WeaponMod*>(iterWeaponMod.getConst()->get())};
        if (object::isCompatible(weapon.slotMod().type(pairSlotNumber.first), pWeaponMod->type())) {
            auto newMod{ squad.inventory().extract(iterWeaponMod) };
            unique_ptr<object::Item> oldMod{};
            weapon.unsetMod(pairSlotNumber.first, oldMod);
            weapon.setMod(pairSlotNumber.first, newMod);
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
    object::Item& item,
    const Indent indent)
{
    Indent ind0{ indent };
    object::ItemVisitorType vis;
    item.accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        auto pairSlotNumber{ pickSlotNumber(is, os, squad, item, ind0) };
        if (pairSlotNumber.second == false) break;
        auto& weapon{ static_cast<object::Weapon&>(item) };
        unique_ptr<object::Item> oldMod{};
        weapon.unsetMod(pairSlotNumber.first, oldMod);
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

} // namespace menu
} // namespace game
