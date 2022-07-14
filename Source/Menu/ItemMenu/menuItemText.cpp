
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuItemText.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuItemText::base_;
MenuItemTextCommon                          MenuItemText::common_;
MenuItemTextModify                          MenuItemText::modify_;
bool                                        MenuItemText::initialized_{ false };

///************************************************************************************************

void MenuItemText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();
    initModify();

    initialized_ = true;
}

void MenuItemText::initCommon()
{
    LanguageBundle temp;

    temp.en(u8"Item menu");
    temp.ru(u8"Меню предмета");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en(u8"Show full description");
    temp.ru(u8"Показать полное описание");
    initLanguageBundleMenu(temp, common_.showFullDescr_);

    temp.en(u8"Are you sure you want to remove this item?");
    temp.ru(u8"Вы уверены, что хотите удалить этот предмет?");
    initLanguageBundleMenu(temp, common_.questionDelete_);

    temp.en(u8"Equip");
    temp.ru(u8"Экипировать");
    initLanguageBundleMenu(temp, common_.equip_);

    temp.en(u8"Modify");
    temp.ru(u8"Модифицировать");
    initLanguageBundleMenu(temp, common_.modify_);
}

void MenuItemText::initModify()
{
    LanguageBundle temp;

    temp.en(u8"Item modification menu");
    temp.ru(u8"Меню модификации предмета");
    initLanguageBundleMenu(temp, modify_.menuName_);

    temp.en(u8"Item: ");
    temp.ru(u8"Предмет: ");
    initLanguageBundleMenu(temp, modify_.item_);

    temp.en(u8"Modifications: ");
    temp.ru(u8"Модификации: ");
    initLanguageBundleMenu(temp, modify_.mods_);

    temp.en(u8"Install modification");
    temp.ru(u8"Установить модификацию");
    initLanguageBundleMenu(temp, modify_.installMod_);

    temp.en(u8"Remove modification");
    temp.ru(u8"Удалить модификацию");
    initLanguageBundleMenu(temp, modify_.removeMod_);

    temp.en(u8"Enter slot number");
    temp.ru(u8"Введите номер слота");
    initLanguageBundleMenu(temp, modify_.enterSlotNumber_);

    temp.en(u8"Unsuitable modification");
    temp.ru(u8"Неподходящая модификация");
    initLanguageBundleMenu(temp, modify_.unsuitableMod_);

    temp.en(u8"Show full description of modification #");
    temp.ru(u8"Показать полное описание модификации #");
    initLanguageBundleMenu(temp, modify_.showFullDescrOfMod_);
}

} // namespace menu
} // namespace game
