
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommonText.hpp"
#include"menuOption.hpp"
#include"locator.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace game {
namespace menu {

using namespace std;


void menuOption(istream& is, ostream& os, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Option menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionOption::LANGUAGE, "Enter the language menu") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionOption::LANGUAGE:
            menuLanguage(is, os, ind1);
            break;
        case actionCommon::EXIT:
            if (global::Locator::getOption().isModified()) {
                os << ind0 << "Options have been changed. Do you want to save the changes?" << endl;
                switch (getYesNo(is, os, ind1)) {
                case YesNo::YES:
                    global::Locator::getOption().accept();
                    return;
                case YesNo::NO:
                    global::Locator::getOption().reject();
                    return;
                case YesNo::CANCEL:
                default:
                    break;
                }
            }
            else {
                return;
            }
            break;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void menuLanguage(istream& is, ostream& os, const Indent indent)
{
    using global::PlainText;
    using global::Locator;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Language menu" << endl;
        os << ind0 << "Current language: "
            << Locator::getPlainText().language(Locator::getOption().getLanguage()) << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionLanguage::CHANGE_LANGUAGE, "Change language") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionLanguage::CHANGE_LANGUAGE: {
            PlainText::Language lang{ pickLanguage(is, os, ind1) };
            if (lang != PlainText::Language::INVALID) {
                global::Locator::getOption().setLanguage(lang);
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

global::PlainText::Language pickLanguage(istream& is, ostream& os, const Indent indent)
{
    using global::PlainText;
    using global::Locator;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    os << ind0 << "Languages:" << endl;
    for (int i{ common::toUnderlying(common::firstEnum<PlainText::Language>()) };
        i <= common::toUnderlying(common::lastEnum<PlainText::Language>()); ++i)
    {
        os << ind1 << '\'' << i << "\' "
            << Locator::getPlainText().language(static_cast<PlainText::Language>(i)) << endl;
    }

    os << ind0 << "Select a Language:" << endl;
    PlainText::Language t{ PlainText::Language::INVALID };
    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        if (pair.first >= common::toUnderlying(common::firstEnum<PlainText::Language>()) &&
            pair.first <= common::toUnderlying(common::lastEnum<PlainText::Language>()))
        {
            t = static_cast<PlainText::Language>(pair.first);
        }
        else {
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return t;
}

} // namespace menu
} // namespace game
