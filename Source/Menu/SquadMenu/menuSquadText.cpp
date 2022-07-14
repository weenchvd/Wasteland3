
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuSquadText.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuSquadText::base_;
MenuSquadTextCommon                         MenuSquadText::common_;
MenuSquadTextMain                           MenuSquadText::main_;
bool                                        MenuSquadText::initialized_{ false };

///************************************************************************************************

void MenuSquadText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();
    initMain();

    initialized_ = true;
}

void MenuSquadText::initCommon()
{
    LanguageBundle temp;

    temp.en(u8"Squad");
    temp.ru(u8"Отряд");
    initLanguageBundleMenu(temp, common_.squad_);

    temp.en(u8"Member");
    temp.ru(u8"Член");
    initLanguageBundleMenu(temp, common_.member_);

    temp.en(u8"empty slot");
    temp.ru(u8"пустой слот");
    initLanguageBundleMenu(temp, common_.emptySlot_);

    temp.en(u8"Select a character");
    temp.ru(u8"Выберите персонажа");
    initLanguageBundleMenu(temp, common_.selectCharacter_);
}

void MenuSquadText::initMain()
{
    LanguageBundle temp;

    temp.en(u8"Squad menu");
    temp.ru(u8"Меню отряда");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en(u8"Show squad members");
    temp.ru(u8"Показать членов отряда");
    initLanguageBundleMenu(temp, main_.showMembers_);

    temp.en(u8"Enter the character menu");
    temp.ru(u8"Войти в меню персонажа");
    initLanguageBundleMenu(temp, main_.enterCharacter_);
}

} // namespace menu
} // namespace game
