
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include"menuCommon.hpp"
#include"menuItemText.hpp"
#include<assert.h>

namespace game {
namespace menu {

using namespace std;

common::ObserverDLL<void, MenuItemText::language> MenuItemText::langObs_;

MenuItemTextCommon MenuItemText::common_;

underlying_type_t<MenuItemText::language>   MenuItemText::langIndex_    { 0 };
bool                                        MenuItemText::initialized_  { false };

///************************************************************************************************

void MenuItemText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);

    initCommon();

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&MenuItemText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void MenuItemText::initCommon()
{
    LanguageBundle temp;

    temp.en("Item menu");
    temp.ru("Меню предмета");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en("Show full description");
    temp.ru("Показать полное описание");
    initLanguageBundleMenu(temp, common_.showFullDescr_);

    temp.en("Are you sure you want to remove this item?");
    temp.ru("Вы уверены, что хотите удалить этот предмет?");
    initLanguageBundleMenu(temp, common_.questionDelete_);

    temp.en("Equip");
    temp.ru("Экипировать");
    initLanguageBundleMenu(temp, common_.equip_);

    temp.en("Modify");
    temp.ru("Модифицировать");
    initLanguageBundleMenu(temp, common_.modify_);
}

} // namespace menu
} // namespace game
