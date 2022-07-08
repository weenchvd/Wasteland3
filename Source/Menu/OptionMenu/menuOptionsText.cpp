
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuOptionsText.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuOptionsText::base_;
MenuOptionsTextCommon                       MenuOptionsText::common_;
MenuOptionsTextGeneral                      MenuOptionsText::general_;
MenuOptionsTextAux                          MenuOptionsText::aux_;
bool                                        MenuOptionsText::initialized_{ false };

///************************************************************************************************

void MenuOptionsText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();
    initGeneral();
    initAux();

    initialized_ = true;
}

void MenuOptionsText::initCommon()
{
    LanguageBundle temp;

    temp.en(u8"Options menu");
    temp.ru(u8"Меню опций");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en(u8"Enter the general options menu");
    temp.ru(u8"Войти в меню общих настроек");
    initLanguageBundleMenu(temp, common_.enterGeneral_);

    temp.en(u8"Options have been changed. Do you want to save the changes?");
    temp.ru(u8"Настройки были изменены. Вы хотите сохранить изменения?");
    initLanguageBundleMenu(temp, common_.questionSaveChanges_);
}

void MenuOptionsText::initGeneral()
{
    LanguageBundle temp;

    temp.en(u8"General options menu");
    temp.ru(u8"Меню общих настроек");
    initLanguageBundleMenu(temp, general_.menuName_);

    temp.en(u8"Language");
    temp.ru(u8"Язык");
    initLanguageBundleMenu(temp, general_.language_);

    temp.en(u8"Current language:");
    temp.ru(u8"Текущий язык:");
    initLanguageBundleMenu(temp, general_.currentLanguage_);

    temp.en(u8"Change language");
    temp.ru(u8"Сменить язык");
    initLanguageBundleMenu(temp, general_.changeLanguage_);
}

void MenuOptionsText::initAux()
{
    LanguageBundle temp;

    temp.en(u8"Languages:");
    temp.ru(u8"Языки:");
    initLanguageBundleMenu(temp, aux_.languages_);

    temp.en(u8"Select a language:");
    temp.ru(u8"Выберите язык:");
    initLanguageBundleMenu(temp, aux_.selectLanguage_);
}

} // namespace menu
} // namespace game
