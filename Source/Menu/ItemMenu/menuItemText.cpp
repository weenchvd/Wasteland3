
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
MenuItemTextModify MenuItemText::modify_;

underlying_type_t<MenuItemText::language>   MenuItemText::langIndex_    { 0 };
bool                                        MenuItemText::initialized_  { false };

///************************************************************************************************

void MenuItemText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);

    initCommon();
    initModify();

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

void MenuItemText::initModify()
{
    LanguageBundle temp;

    temp.en("Item modification menu");
    temp.ru("Меню модификации предмета");
    initLanguageBundleMenu(temp, modify_.menuName_);

    temp.en("Item: ");
    temp.ru("Предмет: ");
    initLanguageBundleMenu(temp, modify_.item_);

    temp.en("Modifications: ");
    temp.ru("Модификации: ");
    initLanguageBundleMenu(temp, modify_.mods_);

    temp.en("Install modification");
    temp.ru("Установить модификацию");
    initLanguageBundleMenu(temp, modify_.installMod_);

    temp.en("Remove modification");
    temp.ru("Удалить модификацию");
    initLanguageBundleMenu(temp, modify_.removeMod_);

    temp.en("Enter slot number");
    temp.ru("Введите номер слота");
    initLanguageBundleMenu(temp, modify_.enterSlotNumber_);

    temp.en("Unsuitable modification");
    temp.ru("Неподходящая модификация");
    initLanguageBundleMenu(temp, modify_.unsuitableMod_);
}

} // namespace menu
} // namespace game
