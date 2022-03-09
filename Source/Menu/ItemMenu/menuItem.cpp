
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorFullDescr.hpp"
#include"menuCommonText.hpp"
#include"menuItem.hpp"
#include"menuItemText.hpp"

namespace game {
namespace menu {

using namespace std;

void menuItem(
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

        switch (getAction()) {
        case actionItem::SHOW_FULL_DESCR:
            printFullDescription(*item, ind1);
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

} // namespace menu
} // namespace game
