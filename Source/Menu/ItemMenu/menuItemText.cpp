
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
