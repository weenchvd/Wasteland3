
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

    temp.en(u8"Gear");
    temp.ru(u8"Снаряжение");
    initLanguageBundleMenu(temp, common_.gear_);

    temp.en(u8"empty slot");
    temp.ru(u8"пустой слот");
    initLanguageBundleMenu(temp, common_.emptySlot_);

    temp.en(u8"Weapon");
    temp.ru(u8"Оружие");
    initLanguageBundleMenu(temp, common_.weapon_);

    temp.en(u8"Select a weapon slot");
    temp.ru(u8"Выберите слот для оружия");
    initLanguageBundleMenu(temp, common_.selectWeaponSlot_);
}

void MenuCharacterText::initMain()
{
    LanguageBundle temp;

    temp.en(u8"Character menu");
    temp.ru(u8"Меню персонажа");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en(u8"Show stats");
    temp.ru(u8"Показать статистику");
    initLanguageBundleMenu(temp, main_.showStats_);

    temp.en(u8"Show gear");
    temp.ru(u8"Показать снаряжение");
    initLanguageBundleMenu(temp, main_.showGear_);

    temp.en(u8"Show attributes");
    temp.ru(u8"Показать атрибуты");
    initLanguageBundleMenu(temp, main_.showAttributes_);

    temp.en(u8"Enter the attribute menu");
    temp.ru(u8"Войти в меню атрибутов");
    initLanguageBundleMenu(temp, main_.enterAttrMenu_);

    temp.en(u8"Show skills");
    temp.ru(u8"Показать навыки");
    initLanguageBundleMenu(temp, main_.showSkills_);

    temp.en(u8"Enter the skill menu");
    temp.ru(u8"Войти в меню навыков");
    initLanguageBundleMenu(temp, main_.enterSkillMenu_);
}

} // namespace menu
} // namespace game
