
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

    temp.en(u8"Actions:");
    temp.ru(u8"Действия:");
    initLanguageBundleMenu(temp, common_.actions_);

    temp.en(u8"Exit the menu");
    temp.ru(u8"Выйти из меню");
    initLanguageBundleMenu(temp, common_.exitMenu_);

    temp.en(u8"Invalid input");
    temp.ru(u8"Недопустимый ввод");
    initLanguageBundleMenu(temp, common_.invalidInput_);

    temp.en(u8"Invalid type");
    temp.ru(u8"Недействительный тип");
    initLanguageBundleMenu(temp, common_.invalidType_);

    temp.en(u8"Invalid number");
    temp.ru(u8"Недействительный номер");
    initLanguageBundleMenu(temp, common_.invalidNumber_);

    temp.en(u8"Unknown action");
    temp.ru(u8"Неизвестное действие");
    initLanguageBundleMenu(temp, common_.unknownAct_);

    temp.en(u8"Enter an action");
    temp.ru(u8"Введите действие");
    initLanguageBundleMenu(temp, common_.enterAct_);

    temp.en(u8"Enter a number");
    temp.ru(u8"Введите номер");
    initLanguageBundleMenu(temp, common_.enterNum_);

    temp.en(u8"Enter the filename (without extension)");
    temp.ru(u8"Введите имя файла (без расширения)");
    initLanguageBundleMenu(temp, common_.enterFilenameNoExt_);

    temp.en(u8"File");
    temp.ru(u8"Файл");
    initLanguageBundleMenu(temp, common_.file_);

    temp.en(u8"Select a type");
    temp.ru(u8"Выберите тип");
    initLanguageBundleMenu(temp, common_.selectType_);

    temp.en(u8"Remove");
    temp.ru(u8"Удалить");
    initLanguageBundleMenu(temp, common_.remove_);

    temp.en(u8"Yes");
    temp.ru(u8"Да");
    initLanguageBundleMenu(temp, common_.yes_);

    temp.en(u8"No");
    temp.ru(u8"Нет");
    initLanguageBundleMenu(temp, common_.no_);

    temp.en(u8"Cancel");
    temp.ru(u8"Отмена");
    initLanguageBundleMenu(temp, common_.cancel_);

    temp.en(u8"Close");
    temp.ru(u8"Закрыть");
    initLanguageBundleMenu(temp, common_.close_);

    temp.en(u8"Description");
    temp.ru(u8"Описание");
    initLanguageBundleMenu(temp, common_.description_);

    temp.en(u8"All");
    temp.ru(u8"Все");
    initLanguageBundleMenu(temp, common_.all_);

    temp.en(u8"> ");
    temp.ru(u8"> ");
    initLanguageBundleMenu(temp, common_.promptSymbol_);

    temp.en(u8"Back");
    temp.ru(u8"Назад");
    initLanguageBundleMenu(temp, common_.back_);

    temp.en(u8"! ");
    temp.ru(u8"! ");
    initLanguageBundleMenu(temp, common_.errorSymbol_);

    temp.en(u8"Feature not implemented yet");
    temp.ru(u8"Функция еще не реализована");
    initLanguageBundleMenu(temp, common_.notImplemented_);

    temp.en(u8"Save changes");
    temp.ru(u8"Сохранить изменения");
    initLanguageBundleMenu(temp, common_.saveChanges_);

    temp.en(u8"Cancel changes");
    temp.ru(u8"Отменить изменения");
    initLanguageBundleMenu(temp, common_.cancelChanges_);

    temp.en(u8"Changes saved");
    temp.ru(u8"Изменения сохранены");
    initLanguageBundleMenu(temp, common_.changesSaved_);

    temp.en(u8"Changes canceled");
    temp.ru(u8"Изменения отменены");
    initLanguageBundleMenu(temp, common_.changesCanceled_);

    temp.en(u8"Action failed");
    temp.ru(u8"Действие не выполнено");
    initLanguageBundleMenu(temp, common_.actionFailed_);

    temp.en(u8"An error has occurred");
    temp.ru(u8"Произошла ошибка");
    initLanguageBundleMenu(temp, common_.errorOccurred_);
}

} // namespace menu
} // namespace game
