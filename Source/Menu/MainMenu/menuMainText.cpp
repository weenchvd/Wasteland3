
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

    temp.en(u8"Main menu");
    temp.ru(u8"Главное меню");
    initLanguageBundleMenu(temp, common_.menuName_);

    temp.en(u8"Exit the game");
    temp.ru(u8"Выйти из игры");
    initLanguageBundleMenu(temp, common_.exit_);

    temp.en(u8"Enter the option menu");
    temp.ru(u8"Войти в меню опций");
    initLanguageBundleMenu(temp, common_.enterOpt_);

    temp.en(u8"Enter the squad menu");
    temp.ru(u8"Войти в меню отряда");
    initLanguageBundleMenu(temp, common_.enterSquad_);

    temp.en(u8"Enter the inventory menu");
    temp.ru(u8"Войти в меню инвентаря");
    initLanguageBundleMenu(temp, common_.enterInvent_);

    temp.en(u8"Enter the shop menu");
    temp.ru(u8"Войти в меню магазина");
    initLanguageBundleMenu(temp, common_.enterShop_);

    temp.en(u8"Enter the trade menu");
    temp.ru(u8"Войти в меню торговли");
    initLanguageBundleMenu(temp, common_.enterTrade_);

    temp.en(u8"Save the game");
    temp.ru(u8"Сохранить игру");
    initLanguageBundleMenu(temp, common_.saveGame_);

    temp.en(u8"Load the game");
    temp.ru(u8"Загрузить игру");
    initLanguageBundleMenu(temp, common_.loadGame_);

    temp.en(u8"Game saved");
    temp.ru(u8"Игра сохранена");
    initLanguageBundleMenu(temp, common_.gameSaved_);

    temp.en(u8"Game not saved");
    temp.ru(u8"Игра не сохранена");
    initLanguageBundleMenu(temp, common_.gameNotSaved_);

    temp.en(u8"Game loaded");
    temp.ru(u8"Игра загружена");
    initLanguageBundleMenu(temp, common_.gameLoaded_);

    temp.en(u8"Game not loaded");
    temp.ru(u8"Игра не загружена");
    initLanguageBundleMenu(temp, common_.gameNotLoaded_);

    temp.en(u8"List of files");
    temp.ru(u8"Список файлов");
    initLanguageBundleMenu(temp, common_.fileList_);

    temp.en(u8"File not selected");
    temp.ru(u8"Файл не выбран");
    initLanguageBundleMenu(temp, common_.fileNotSelected_);

    temp.en(u8"File name not specified");
    temp.ru(u8"Имя файла не указано");
    initLanguageBundleMenu(temp, common_.filenameNotSpec_);
}

} // namespace menu
} // namespace game
