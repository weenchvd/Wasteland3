
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

    temp.en("Show all items");
    temp.ru("Показать все предметы");
    initLanguageBundleMenu(temp, common_.showAllItems_);

    temp.en("Show items of a certain type");
    temp.ru("Показать предметы определенного типа");
    initLanguageBundleMenu(temp, common_.showItemsOfType_);

    temp.en("Money: $");
    temp.ru("Деньги: $");
    initLanguageBundleMenu(temp, common_.money_);

    temp.en("Inventory (* - new items):");
    temp.ru("Инвентарь (* - новые предметы):");
    initLanguageBundleMenu(temp, common_.inventory_);

    temp.en("Shop:");
    temp.ru("Магазин:");
    initLanguageBundleMenu(temp, common_.shop_);

    temp.en("Item ");
    temp.ru("Предмет ");
    initLanguageBundleMenu(temp, common_.item_);

    temp.en("Item types:");
    temp.ru("Типы предметов:");
    initLanguageBundleMenu(temp, common_.typesOfItems_);

    temp.en("Select a type:");
    temp.ru("Выберите тип:");
    initLanguageBundleMenu(temp, common_.selectType_);
}

} // namespace menu
} // namespace game
