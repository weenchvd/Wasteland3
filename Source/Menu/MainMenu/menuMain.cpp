
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
#include"menuSquad.hpp"

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
        printNumBar(os, ind1, actionTrade::SHOW_ALL_ITEMS, "Show all items") << endl;
        printNumBar(os, ind1, actionTrade::BUY_ITEM, "Buy items") << endl;
        printNumBar(os, ind1, actionTrade::SELL_ITEM, "Sell items") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionTrade::SHOW_ALL_ITEMS:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
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

} // namespace menu
} // namespace game
