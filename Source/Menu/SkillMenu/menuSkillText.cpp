
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuSkillText.hpp"
#include"menuCommon.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuSkillText::base_;
MenuSkillTextCommon                         MenuSkillText::common_;
MenuSkillTextMain                           MenuSkillText::main_;
MenuSkillTextModify                         MenuSkillText::modify_;
bool                                        MenuSkillText::initialized_{ false };

///************************************************************************************************

void MenuSkillText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();
    initMain();
    initModify();

    initialized_ = true;
}

void MenuSkillText::initCommon()
{
    LanguageBundle temp;

    temp.en(u8"Skills:");
    temp.ru(u8"Навыки:");
    initLanguageBundleMenu(temp, common_.skills_);

    temp.en(u8"Skills (accepted):");
    temp.ru(u8"Навыки (принято):");
    initLanguageBundleMenu(temp, common_.skillsAccepted_);

    temp.en(u8"Skill points:");
    temp.ru(u8"Очки навыков:");
    initLanguageBundleMenu(temp, common_.skillPoints_);

    temp.en(u8"Skill points (accepted):");
    temp.ru(u8"Очки навыков (принято):");
    initLanguageBundleMenu(temp, common_.skillPointsAccepted_);

    temp.en(u8"Select a skill:");
    temp.ru(u8"Выберите навык:");
    initLanguageBundleMenu(temp, common_.selectSkill_);

    temp.en(u8"Enter the number of levels:");
    temp.ru(u8"Введите количество уровней:");
    initLanguageBundleMenu(temp, common_.enterNumOfLevels_);

    temp.en(u8"Invalid number of levels");
    temp.ru(u8"Недопустимое количество уровней");
    initLanguageBundleMenu(temp, common_.invalidNumOfLevels_);
}

void MenuSkillText::initMain()
{
    LanguageBundle temp;

    temp.en(u8"Skill menu");
    temp.ru(u8"Меню навыков");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en(u8"Show skills");
    temp.ru(u8"Показать навыки");
    initLanguageBundleMenu(temp, main_.showSkills_);

    temp.en(u8"Show accepted skills");
    temp.ru(u8"Показать принятые навыки");
    initLanguageBundleMenu(temp, main_.showSkillsAccepted_);

    temp.en(u8"Modify");
    temp.ru(u8"Модифицировать");
    initLanguageBundleMenu(temp, main_.modify_);

    temp.en(u8"Skills have been changed. Do you want to save the changes?");
    temp.ru(u8"Навыки были изменены. Вы хотите сохранить изменения?");
    initLanguageBundleMenu(temp, main_.questionSaveChanges_);
}

void MenuSkillText::initModify()
{
    LanguageBundle temp;

    temp.en(u8"Skill modification menu");
    temp.ru(u8"Меню модификации навыков");
    initLanguageBundleMenu(temp, modify_.menuName_);

    temp.en(u8"Show skill description");
    temp.ru(u8"Показать описание навыка");
    initLanguageBundleMenu(temp, modify_.showDescription_);

    temp.en(u8"Increase level");
    temp.ru(u8"Повысить уровень");
    initLanguageBundleMenu(temp, modify_.increaseLevel_);

    temp.en(u8"Decrease level");
    temp.ru(u8"Понизить уровень");
    initLanguageBundleMenu(temp, modify_.decreaseLevel_);

    temp.en(u8"Skill:");
    temp.ru(u8"Навык:");
    initLanguageBundleMenu(temp, modify_.skill_);

    temp.en(u8"Skill (accepted):");
    temp.ru(u8"Навык (принято):");
    initLanguageBundleMenu(temp, modify_.skillAccepted_);
}

} // namespace menu
} // namespace game
