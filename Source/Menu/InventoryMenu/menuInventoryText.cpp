
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuInventoryText.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuInventoryText::base_;
MenuInventoryTextCommon                     MenuInventoryText::common_;
bool                                        MenuInventoryText::initialized_{ false };

///************************************************************************************************

void MenuInventoryText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();

    initialized_ = true;
}

void MenuInventoryText::initCommon()
{
    LanguageBundle temp;

    temp.en(u8"Inventory menu");
    temp.ru(u8"Меню инвентаря");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en(u8"Show money");
    temp.ru(u8"Показать деньги");
    initLanguageBundleMenu(temp, common_.showMoney_);

    temp.en(u8"Show items");
    temp.ru(u8"Показать предметы");
    initLanguageBundleMenu(temp, common_.showItems_);

    temp.en(u8"Show all items");
    temp.ru(u8"Показать все предметы");
    initLanguageBundleMenu(temp, common_.showAllItems_);

    temp.en(u8"Show items of a certain type");
    temp.ru(u8"Показать предметы определенного типа");
    initLanguageBundleMenu(temp, common_.showItemsOfType_);

    temp.en(u8"Enter the item menu");
    temp.ru(u8"Войти в меню предмета");
    initLanguageBundleMenu(temp, common_.enterItem_);

    temp.en(u8"Mark all items as viewed");
    temp.ru(u8"Пометить все предметы как просмотренные");
    initLanguageBundleMenu(temp, common_.markAllAsViewed_);

    temp.en(u8"Money: $");
    temp.ru(u8"Деньги: $");
    initLanguageBundleMenu(temp, common_.money_);

    temp.en(u8"Inventory");
    temp.ru(u8"Инвентарь");
    initLanguageBundleMenu(temp, common_.inventory_);

    temp.en(u8"* - new items");
    temp.ru(u8"* - новые предметы");
    initLanguageBundleMenu(temp, common_.starNewItems_);

    temp.en(u8"Shop:");
    temp.ru(u8"Магазин:");
    initLanguageBundleMenu(temp, common_.shop_);

    temp.en(u8"Item ");
    temp.ru(u8"Предмет ");
    initLanguageBundleMenu(temp, common_.item_);

    temp.en(u8"Item types:");
    temp.ru(u8"Типы предметов:");
    initLanguageBundleMenu(temp, common_.typesOfItems_);

    temp.en(u8"Enter the item number");
    temp.ru(u8"Введите номер предмета");
    initLanguageBundleMenu(temp, common_.enterItemNumber_);

    temp.en(u8"The list of items is outdated. To update the list, use the command: ");
    temp.ru(u8"Список предметов устарел. Чтобы обновить список, используйте команду: ");
    initLanguageBundleMenu(temp, common_.listIsOutdated_);
}

} // namespace menu
} // namespace game
