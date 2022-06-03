
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCharacterText.hpp"
#include"menuCommon.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuCharacterText::base_;
MenuCharacterTextCommon                     MenuCharacterText::common_;
MenuCharacterTextMain                       MenuCharacterText::main_;
bool                                        MenuCharacterText::initialized_{ false };

///************************************************************************************************

void MenuCharacterText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();
    initMain();

    initialized_ = true;
}

void MenuCharacterText::initCommon()
{
    LanguageBundle temp;

    temp.en("Gear");
    temp.ru("Снаряжение");
    initLanguageBundleMenu(temp, common_.gear_);

    temp.en("empty slot");
    temp.ru("пустой слот");
    initLanguageBundleMenu(temp, common_.emptySlot_);

    temp.en("Weapon");
    temp.ru("Оружие");
    initLanguageBundleMenu(temp, common_.weapon_);
}

void MenuCharacterText::initMain()
{
    LanguageBundle temp;

    temp.en("Character menu");
    temp.ru("Меню персонажа");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en("Show stats");
    temp.ru("Показать статистику");
    initLanguageBundleMenu(temp, main_.showStats_);

    temp.en("Show gear");
    temp.ru("Показать снаряжение");
    initLanguageBundleMenu(temp, main_.showGear_);

    temp.en("Show attributes");
    temp.ru("Показать атрибуты");
    initLanguageBundleMenu(temp, main_.showAttributes_);

    temp.en("Enter the attribute menu");
    temp.ru("Войти в меню атрибутов");
    initLanguageBundleMenu(temp, main_.enterAttrMenu_);

    temp.en("Show skills");
    temp.ru("Показать навыки");
    initLanguageBundleMenu(temp, main_.showSkills_);

    temp.en("Enter the skill menu");
    temp.ru("Войти в меню навыков");
    initLanguageBundleMenu(temp, main_.enterSkillMenu_);
}

} // namespace menu
} // namespace game
