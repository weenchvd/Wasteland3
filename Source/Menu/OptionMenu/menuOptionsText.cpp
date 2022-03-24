
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include"menuCommon.hpp"
#include"menuOptionsText.hpp"
#include<assert.h>

namespace game {
namespace menu {

using namespace std;

common::ObserverDLL<void, MenuOptionsText::language> MenuOptionsText::langObs_;

MenuOptionsTextCommon                           MenuOptionsText::common_;
MenuOptionsTextGeneral                          MenuOptionsText::general_;
MenuOptionsTextAux                              MenuOptionsText::aux_;

underlying_type_t<MenuOptionsText::language>    MenuOptionsText::langIndex_     { 0 };
bool                                            MenuOptionsText::initialized_   { false };

///************************************************************************************************

void MenuOptionsText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);

    initCommon();
    initGeneral();
    initAux();

    assert(Locator::isInitialized());
    setLanguage(Locator::getOptions().optLanguage().getLanguage());
    langObs_.getDelegate().bind<&MenuOptionsText::setLanguage>();
    Locator::getOptions().optLanguage().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void MenuOptionsText::initCommon()
{
    LanguageBundle temp;

    temp.en("Options menu");
    temp.ru("Меню опций");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en("Enter the general options menu");
    temp.ru("Войти в меню общих настроек");
    initLanguageBundleMenu(temp, common_.enterGeneral_);

    temp.en("Options have been changed. Do you want to save the changes?");
    temp.ru("Настройки были изменены. Вы хотите сохранить изменения?");
    initLanguageBundleMenu(temp, common_.questionSaveChanges_);

    temp.en("Options have been changed. Do you want to save the changes?");
    temp.ru("Настройки были изменены. Вы хотите сохранить изменения?");
    initLanguageBundleMenu(temp, common_.questionSaveChanges_);

    temp.en("Save changes");
    temp.ru("Сохранить изменения");
    initLanguageBundleMenu(temp, common_.saveChanges_);

    temp.en("Cancel changes");
    temp.ru("Отменить изменения");
    initLanguageBundleMenu(temp, common_.cancelChanges_);
}

void MenuOptionsText::initGeneral()
{
    LanguageBundle temp;

    temp.en("General options menu");
    temp.ru("Меню общих настроек");
    initLanguageBundleMenu(temp, general_.menuName_);

    temp.en("Current language:");
    temp.ru("Текущий язык:");
    initLanguageBundleMenu(temp, general_.currentLanguage_);

    temp.en("Change language");
    temp.ru("Сменить язык");
    initLanguageBundleMenu(temp, general_.changeLanguage_);
}

void MenuOptionsText::initAux()
{
    LanguageBundle temp;

    temp.en("Languages:");
    temp.ru("Языки:");
    initLanguageBundleMenu(temp, aux_.languages_);

    temp.en("Select a language:");
    temp.ru("Выберите язык:");
    initLanguageBundleMenu(temp, aux_.selectLanguage_);
}

} // namespace menu
} // namespace game
