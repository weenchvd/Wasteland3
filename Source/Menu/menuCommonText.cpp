
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include"menuCommon.hpp"
#include"menuCommonText.hpp"
#include<assert.h>

namespace game {
namespace menu {

using namespace std;

common::ObserverDLL<void, MenuCommonText::language> MenuCommonText::langObs_;

MenuCommonTextCommon MenuCommonText::common_;

underlying_type_t<MenuCommonText::language> MenuCommonText::langIndex_  { 0 };
bool                                        MenuCommonText::initialized_{ false };

///************************************************************************************************

void MenuCommonText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);

    initCommon();

    assert(Locator::isInitialized());
    setLanguage(Locator::getOptions().optLanguage().getLanguage());
    langObs_.getDelegate().bind<&MenuCommonText::setLanguage>();
    Locator::getOptions().optLanguage().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void MenuCommonText::initCommon()
{
    LanguageBundle temp;


    temp.en("Actions:");
    temp.ru("Действия:");
    initLanguageBundleMenu(temp, common_.actions_);

    temp.en("Exit the menu");
    temp.ru("Выйти из меню");
    initLanguageBundleMenu(temp, common_.exitMenu_);

    temp.en("Invalid input");
    temp.ru("Недопустимый ввод");
    initLanguageBundleMenu(temp, common_.invalidInput_);

    temp.en("Invalid type");
    temp.ru("Недействительный тип");
    initLanguageBundleMenu(temp, common_.invalidType_);

    temp.en("Invalid number");
    temp.ru("Недействительный номер");
    initLanguageBundleMenu(temp, common_.invalidNumber_);

    temp.en("Unknown action");
    temp.ru("Неизвестное действие");
    initLanguageBundleMenu(temp, common_.unknownAct_);

    temp.en("Enter an action");
    temp.ru("Введите действие");
    initLanguageBundleMenu(temp, common_.enterAct_);

    temp.en("Enter a number");
    temp.ru("Введите номер");
    initLanguageBundleMenu(temp, common_.enterNum_);

    temp.en("Select a type");
    temp.ru("Выберите тип");
    initLanguageBundleMenu(temp, common_.selectType_);

    temp.en("Remove");
    temp.ru("Удалить");
    initLanguageBundleMenu(temp, common_.remove_);

    temp.en("Yes");
    temp.ru("Да");
    initLanguageBundleMenu(temp, common_.yes_);

    temp.en("No");
    temp.ru("Нет");
    initLanguageBundleMenu(temp, common_.no_);

    temp.en("Cancel");
    temp.ru("Отмена");
    initLanguageBundleMenu(temp, common_.cancel_);

    temp.en("> ");
    temp.ru("> ");
    initLanguageBundleMenu(temp, common_.promptSymbol_);

    temp.en("! ");
    temp.ru("! ");
    initLanguageBundleMenu(temp, common_.errorSymbol_);

    temp.en("Feature not implemented yet");
    temp.ru("Функция еще не реализована");
    initLanguageBundleMenu(temp, common_.notImplemented_);
}

} // namespace menu
} // namespace game
