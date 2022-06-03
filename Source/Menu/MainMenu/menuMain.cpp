
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCharacter.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuMain.hpp"
#include"menuMainInit.hpp"
#include"menuMainText.hpp"
#include"menuOptions.hpp"

namespace game {
namespace menu {

using namespace std;

void menuMain(istream& is, ostream& os, object::Squad& squad, object::Inventory& shop)
{
    initializeMenuText();

    Indent ind0{ Indent{} };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, text.exit()) << endl;
        printNumBar(os, ind1, actionMain::MENU_OPTION, text.enterOptions()) << endl;
        printNumBar(os, ind1, actionMain::MENU_SQUAD, text.enterSquad()) << endl;
        printNumBar(os, ind1, actionMain::MENU_INVENTORY, text.enterInventory()) << endl;
        printNumBar(os, ind1, actionMain::MENU_SHOP, text.enterShop()) << endl;
        printNumBar(os, ind1, actionMain::MENU_TRADE, text.enterTrade()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionMain::MENU_OPTION:
            menuOptions(is, os, ind1);
            break;
        case actionMain::MENU_SQUAD:
            menuSquad(is, os, squad, ind1);
            break;
        case actionMain::MENU_INVENTORY:
            menuInventory(is, os, squad, ind1);
            break;
        case actionMain::MENU_SHOP:
            menuShop(is, os, shop, ind1);
            break;
        case actionMain::MENU_TRADE:
            menuTrade(is, os, squad, shop, ind1);
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

void menuTrade(
    istream& is,
    ostream& os,
    object::Squad& squad,
    object::Inventory& shop,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Trade menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionTrade::BUY_ITEM, "Buy items") << endl;
        printNumBar(os, ind1, actionTrade::SELL_ITEM, "Sell items") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionTrade::BUY_ITEM:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionTrade::SELL_ITEM:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
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

void menuShop(istream& is, ostream& os, object::Inventory& shop, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Shop menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionShop::ALL_ITEMS, "Show all items") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionShop::ALL_ITEMS:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
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

void menuSquad(istream& is, ostream& os, object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Squad menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionSquad::SHOW_SQUAD, "Show squad members") << endl;
        printNumBar(os, ind1, actionSquad::MENU_CHARACTER, "Enter the character menu") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionSquad::SHOW_SQUAD:
            showSquad(is, os, squad, ind1);
            break;
        case actionSquad::MENU_CHARACTER: {
            object::Character* c{ pickCharacter(is, os, squad, ind1) };
            if (c != nullptr) {
                menuCharacter(is, os, *c, ind1);
            }
            else {
                os << "!Character not selected" << endl;
            }
            break;
        }
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

///************************************************************************************************

object::Character* pickCharacter(istream& is, ostream& os, object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    const auto& comT{ MenuCommonText::common() };

    os << ind0 << "Select a character:" << endl;
    object::Character* c{ nullptr };

    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        pair.first -= 1;
        if (pair.first >= 0 && pair.first < squad.members().size()) {
            c = static_cast<object::Character*>(squad.members()[pair.first].get());
        }
        else {
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return c;
}

void showSquad(istream& is, ostream& os, const object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };

    os << ind0 << "Squad:" << endl;
    for (int i = 0; i < squad.members().size(); ++i) {
        os << ind1 << "Member " << i + 1 << ": ";
        if (squad.members()[i] != nullptr) {
            auto& c{ *static_cast<object::Character*>(squad.members()[i].get()) };
            os << c.name() << ", Level " << c.level() << " RANGER" << endl;
        }
        else {
            os << "(empty)" << endl;
        }
    }
}

} // namespace menu
} // namespace game
