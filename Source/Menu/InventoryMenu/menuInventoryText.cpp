
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include"menuCommon.hpp"
#include"menuInventoryText.hpp"
#include<assert.h>

namespace game {
namespace menu {

using namespace std;

common::ObserverDLL<void, MenuInventoryText::language> MenuInventoryText::langObs_;

MenuInventoryTextCommon MenuInventoryText::common_;

underlying_type_t<MenuInventoryText::language>  MenuInventoryText::langIndex_   { 0 };
bool                                            MenuInventoryText::initialized_ { false };

///************************************************************************************************

void MenuInventoryText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);

    initCommon();

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&MenuInventoryText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void MenuInventoryText::initCommon()
{
    LanguageBundle temp;

    temp.en("Inventory menu");
    temp.ru("Меню инвентаря");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en("Show money");
    temp.ru("Показать деньги");
    initLanguageBundleMenu(temp, common_.showMoney_);

    temp.en("Show items");
    temp.ru("Показать предметы");
    initLanguageBundleMenu(temp, common_.showItems_);

    temp.en("Show all items");
    temp.ru("Показать все предметы");
    initLanguageBundleMenu(temp, common_.showAllItems_);

    temp.en("Show items of a certain type");
    temp.ru("Показать предметы определенного типа");
    initLanguageBundleMenu(temp, common_.showItemsOfType_);

    temp.en("Enter the item menu");
    temp.ru("Войти в меню предмета");
    initLanguageBundleMenu(temp, common_.enterItem_);

    temp.en("Mark all items as viewed");
    temp.ru("Пометить все предметы как просмотренные");
    initLanguageBundleMenu(temp, common_.markAllAsViewed_);

    temp.en("Money: $");
    temp.ru("Деньги: $");
    initLanguageBundleMenu(temp, common_.money_);

    temp.en("Inventory");
    temp.ru("Инвентарь");
    initLanguageBundleMenu(temp, common_.inventory_);

    temp.en("* - new items");
    temp.ru("* - новые предметы");
    initLanguageBundleMenu(temp, common_.starNewItems_);

    temp.en("Shop:");
    temp.ru("Магазин:");
    initLanguageBundleMenu(temp, common_.shop_);

    temp.en("Item ");
    temp.ru("Предмет ");
    initLanguageBundleMenu(temp, common_.item_);

    temp.en("Item types:");
    temp.ru("Типы предметов:");
    initLanguageBundleMenu(temp, common_.typesOfItems_);

    temp.en("Enter the item number");
    temp.ru("Введите номер предмета");
    initLanguageBundleMenu(temp, common_.enterItemNumber_);

    temp.en("The list of items is outdated. To update the list, use the command: ");
    temp.ru("Список предметов устарел. Чтобы обновить список, используйте команду: ");
    initLanguageBundleMenu(temp, common_.listIsOutdated_);
}

} // namespace menu
} // namespace game
