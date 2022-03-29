
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuMainText.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuMainText::base_;
MenuMainTextCommon                          MenuMainText::common_;
bool                                        MenuMainText::initialized_{ false };

///************************************************************************************************

void MenuMainText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();

    initialized_ = true;
}

void MenuMainText::initCommon()
{
    LanguageBundle temp;

    temp.en("Main menu");
    temp.ru("Главное меню");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en("Exit the game");
    temp.ru("Выйти из игры");
    initLanguageBundleMenu(temp, common_.exit_);

    temp.en("Enter the option menu");
    temp.ru("Войти в меню опций");
    initLanguageBundleMenu(temp, common_.enterOpt_);

    temp.en("Enter the squad menu");
    temp.ru("Войти в меню отряда");
    initLanguageBundleMenu(temp, common_.enterSquad_);

    temp.en("Enter the inventory menu");
    temp.ru("Войти в меню инвентаря");
    initLanguageBundleMenu(temp, common_.enterInvent_);

    temp.en("Enter the shop menu");
    temp.ru("Войти в меню магазина");
    initLanguageBundleMenu(temp, common_.enterShop_);

    temp.en("Enter the trade menu");
    temp.ru("Войти в меню торговли");
    initLanguageBundleMenu(temp, common_.enterTrade_);
}

} // namespace menu
} // namespace game
