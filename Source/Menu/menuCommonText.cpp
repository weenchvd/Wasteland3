
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuCommonText.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuCommonText::base_;
MenuCommonTextCommon                        MenuCommonText::common_;
bool                                        MenuCommonText::initialized_{ false };

///************************************************************************************************

void MenuCommonText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();

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

    temp.en("Save changes");
    temp.ru("Сохранить изменения");
    initLanguageBundleMenu(temp, common_.saveChanges_);

    temp.en("Cancel changes");
    temp.ru("Отменить изменения");
    initLanguageBundleMenu(temp, common_.cancelChanges_);
}

} // namespace menu
} // namespace game
