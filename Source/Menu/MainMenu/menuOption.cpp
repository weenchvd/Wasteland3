
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuOption.hpp"
#include"locator.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace game {
namespace menu {

using namespace std;


void menuOption(const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Option menu" << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionOption::LANGUAGE << "\' Enter the language menu" << endl;

        switch (getAction()) {
        case actionOption::LANGUAGE:
            menuLanguage(ind1);
            break;
        case actionCommon::EXIT:
            if (global::Locator::getOption().isModified()) {
                cout << ind1 << "Options have been changed. Do you want to save the changes?" << endl;
                switch (getYesNo()) {
                case YesNo::YES:
                    global::Locator::getOption().accept();
                    return;
                case YesNo::NO:
                    global::Locator::getOption().reject();
                    return;
                default:
                    cout << "!Invalid input" << endl;
                    break;
                }
            }
            else {
                return;
            }
            break;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

void menuLanguage(const Indent indent)
{
    using global::PlainText;
    using global::Locator;

    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Language menu" << endl;
        cout << ind1 << "Current language: "
            << Locator::getPlainText().language(Locator::getOption().getLanguage()) << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionLanguage::CHANGE_LANGUAGE << "\' Change language" << endl;

        switch (getAction()) {
        case actionLanguage::CHANGE_LANGUAGE: {
            PlainText::Language lang{ pickLanguage(ind1) };
            if (lang != PlainText::Language::INVALID) {
                global::Locator::getOption().setLanguage(lang);
            }
            else {
                cout << "!Invalid type" << endl;
            }
            break;
        }
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

///------------------------------------------------------------------------------------------------

global::PlainText::Language pickLanguage(const Indent indent)
{
    using global::PlainText;
    using global::Locator;

    Indent ind1 = indent + Indent{};
    cout << ind1 << "Languages:" << endl;
    Indent ind2 = ind1 + Indent{};
    Indent ind3 = ind2 + Indent{};

    for (int i = { common::toUnderlying(common::firstEnum<PlainText::Language>()) };
        i <= common::toUnderlying(common::lastEnum<PlainText::Language>()); ++i)
    {
        cout << ind2 << '\'' << i << "\' "
            << Locator::getPlainText().language(static_cast<PlainText::Language>(i)) << endl;
    }

    cout << ind1 << "Select a Language:" << endl;
    PlainText::Language t{ PlainText::Language::INVALID };
    int n = getPosNumber();
    if (n >= common::toUnderlying(common::firstEnum<PlainText::Language>()) &&
        n <= common::toUnderlying(common::lastEnum<PlainText::Language>()))
    {
        t = static_cast<PlainText::Language>(n);
    }
    return t;
}

} // namespace menu
} // namespace game
