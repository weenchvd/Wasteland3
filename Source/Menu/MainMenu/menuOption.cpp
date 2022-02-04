
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuOption.hpp"
#include"locator.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace Game {
namespace Menu {

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
        cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << ActionOption::LANGUAGE << "\' Enter the language menu" << endl;

        switch (getAction()) {
        case ActionOption::LANGUAGE:
            menuLanguage(ind1);
            break;
        case ActionCommon::EXIT:
            if (Game::Global::Locator::getOption().isModified()) {
                cout << ind1 << "Options have been changed. Do you want to save the changes?" << endl;
                switch (getYesNo()) {
                case YesNo::YES:
                    Game::Global::Locator::getOption().accept();
                    return;
                case YesNo::NO:
                    Game::Global::Locator::getOption().reject();
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
        case ActionCommon::INVALID:
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
    using Game::Global::PlainText;
    using Game::Global::Locator;

    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Language menu" << endl;
        cout << ind1 << "Current language: "
            << Locator::getPlainText().language(Locator::getOption().getLanguage()) << endl;
        cout << ind2 << '\'' << ActionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << ActionLanguage::CHANGE_LANGUAGE << "\' Change language" << endl;

        switch (getAction()) {
        case ActionLanguage::CHANGE_LANGUAGE: {
            PlainText::Language lang{ pickLanguage(ind1) };
            if (lang != PlainText::Language::INVALID) {
                Game::Global::Locator::getOption().setLanguage(lang);
            }
            else {
                cout << "!Invalid type" << endl;
            }
            break;
        }
        case ActionCommon::EXIT:
            return;
        case ActionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

///------------------------------------------------------------------------------------------------

Game::Global::PlainText::Language pickLanguage(const Indent indent)
{
    using Game::Global::PlainText;
    using Game::Global::Locator;

    Indent ind1 = indent + Indent{};
    cout << ind1 << "Languages:" << endl;
    Indent ind2 = ind1 + Indent{};
    Indent ind3 = ind2 + Indent{};

    for (int i = static_cast<int>(PlainText::Language::INVALID) + 1;
        i < static_cast<int>(PlainText::Language::NUMBER_OF);
        ++i)
    {
        cout << ind2 << '\'' << i << "\' "
            << Locator::getPlainText().language(static_cast<PlainText::Language>(i)) << endl;
    }

    cout << ind1 << "Select a Language:" << endl;
    PlainText::Language t{ PlainText::Language::INVALID };
    int n = getPosNumber();
    if (n > static_cast<int>(PlainText::Language::INVALID) &&
        n < static_cast<int>(PlainText::Language::NUMBER_OF)) {
        t = static_cast<PlainText::Language>(n);
    }
    return t;
}

} // namespace Menu
} // namespace Game
