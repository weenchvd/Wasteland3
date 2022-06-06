
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

    temp.en("Squad");
    temp.ru("Отряд");
    initLanguageBundleMenu(temp, common_.squad_);

    temp.en("Member");
    temp.ru("Член");
    initLanguageBundleMenu(temp, common_.member_);

    temp.en("empty slot");
    temp.ru("пустой слот");
    initLanguageBundleMenu(temp, common_.emptySlot_);

    temp.en("Select a character");
    temp.ru("Выберите персонажа");
    initLanguageBundleMenu(temp, common_.selectCharacter_);
}

void MenuSquadText::initMain()
{
    LanguageBundle temp;

    temp.en("Squad menu");
    temp.ru("Меню отряда");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en("Show squad members");
    temp.ru("Показать членов отряда");
    initLanguageBundleMenu(temp, main_.showMembers_);

    temp.en("Enter the character menu");
    temp.ru("Войти в меню персонажа");
    initLanguageBundleMenu(temp, main_.enterCharacter_);
}

} // namespace menu
} // namespace game
