
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommonText.hpp"
#include"menuOptions.hpp"
#include"menuOptionsText.hpp"
#include"locator.hpp"
#include"plainText.hpp"

namespace game {
namespace menu {

using namespace std;

void menuOptions(istream& is, ostream& os, const Indent indent)
{
    using global::PlainText;
    using global::Locator;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuOptionsText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionOptions::GENERAL_OPTIONS, text.enterGeneral()) << endl;
        printNumBar(os, ind1, actionOptions::SAVE_CHANGES, text.saveChanges()) << endl;
        printNumBar(os, ind1, actionOptions::CANCEL_CHANGES, text.cancelChanges()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionOptions::GENERAL_OPTIONS:
            menuGeneralOptions(is, os, ind1);
            break;
        case actionOptions::SAVE_CHANGES:
            Locator::getOptions().acceptAll();
            break;
        case actionOptions::CANCEL_CHANGES:
            Locator::getOptions().rejectAll();
            break;
        case actionCommon::EXIT:
            if (Locator::getOptions().isModified()) {
                os << ind0 << text.questionSaveChanges() << endl;
                switch (getYesNo(is, os, ind1)) {
                case YesNo::YES:
                    Locator::getOptions().acceptAll();
                    return;
                case YesNo::NO:
                    Locator::getOptions().rejectAll();
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

void menuGeneralOptions(istream& is, ostream& os, const Indent indent)
{
    using global::PlainText;
    using global::PlainTextBase;
    using global::Locator;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto sp{ ' ' };
    const auto& comT{ MenuCommonText::common() };
    const auto& tCom{ MenuOptionsText::common() };
    const auto& text{ MenuOptionsText::general() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << text.currentLanguage() << sp
            << PlainText::language(Locator::getOptions().optLanguage().getLanguage()) << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionGeneralOptions::CHANGE_LANGUAGE, text.changeLanguage()) << endl;
        printNumBar(os, ind1, actionGeneralOptions::SAVE_CHANGES, tCom.saveChanges()) << endl;
        printNumBar(os, ind1, actionGeneralOptions::CANCEL_CHANGES, tCom.cancelChanges()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionGeneralOptions::CHANGE_LANGUAGE: {
            PlainTextBase::Language lang{ pickLanguage(is, os, ind1) };
            if (lang != PlainTextBase::Language::__INVALID) {
                Locator::getOptions().optLanguage().setLanguage(lang);
            }
            break;
        }
        case actionGeneralOptions::SAVE_CHANGES:
            Locator::getOptions().acceptAll();
            break;
        case actionGeneralOptions::CANCEL_CHANGES:
            Locator::getOptions().rejectAll();
            break;
        case actionCommon::EXIT:
            if (Locator::getOptions().isModified()) {
                os << ind0 << tCom.questionSaveChanges() << endl;
                switch (getYesNo(is, os, ind1)) {
                case YesNo::YES:
                    Locator::getOptions().acceptAll();
                    return;
                case YesNo::NO:
                    Locator::getOptions().rejectAll();
                    return;
                case YesNo::CANCEL:
                default:
                    break;
                }
            }
            else {
                return;
            }
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

///************************************************************************************************

global::PlainTextBase::Language pickLanguage(istream& is, ostream& os, const Indent indent)
{
    using global::PlainText;
    using global::PlainTextBase;
    using global::Locator;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuOptionsText::aux() };

    os << ind0 << text.languages() << endl;
    for (int i{ common::toUnderlying(common::firstEnum<PlainTextBase::Language>()) };
        i <= common::toUnderlying(common::lastEnum<PlainTextBase::Language>()); ++i)
    {
        printNumBar(os, ind1, i,
            PlainText::language(static_cast<PlainTextBase::Language>(i))
        ) << endl;
    }

    os << ind0 << text.selectLanguage() << endl;
    PlainTextBase::Language t{ PlainTextBase::Language::__INVALID };
    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        if (pair.first >= common::toUnderlying(common::firstEnum<PlainTextBase::Language>()) &&
            pair.first <= common::toUnderlying(common::lastEnum<PlainTextBase::Language>()))
        {
            t = static_cast<PlainTextBase::Language>(pair.first);
        }
        else {
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return t;
}

} // namespace menu
} // namespace game
