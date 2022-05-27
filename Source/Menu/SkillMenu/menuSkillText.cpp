
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

    temp.en("Skills:");
    temp.ru("Навыки:");
    initLanguageBundleMenu(temp, common_.skills_);

    temp.en("Skills (accepted):");
    temp.ru("Навыки (принято):");
    initLanguageBundleMenu(temp, common_.skillsAccepted_);

    temp.en("Skill points:");
    temp.ru("Очки навыков:");
    initLanguageBundleMenu(temp, common_.skillPoints_);

    temp.en("Skill points (accepted):");
    temp.ru("Очки навыков (принято):");
    initLanguageBundleMenu(temp, common_.skillPointsAccepted_);

    temp.en("Select a skill:");
    temp.ru("Выберите навык:");
    initLanguageBundleMenu(temp, common_.selectSkill_);

    temp.en("Enter the number of levels:");
    temp.ru("Введите количество уровней:");
    initLanguageBundleMenu(temp, common_.enterNumOfLevels_);

    temp.en("Invalid number of levels");
    temp.ru("Недопустимое количество уровней");
    initLanguageBundleMenu(temp, common_.invalidNumOfLevels_);
}

void MenuSkillText::initMain()
{
    LanguageBundle temp;

    temp.en("Skill menu");
    temp.ru("Меню навыков");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en("Show skills");
    temp.ru("Показать навыки");
    initLanguageBundleMenu(temp, main_.showSkills_);

    temp.en("Show accepted skills");
    temp.ru("Показать принятые навыки");
    initLanguageBundleMenu(temp, main_.showSkillsAccepted_);

    temp.en("Modify");
    temp.ru("Модифицировать");
    initLanguageBundleMenu(temp, main_.modify_);

    temp.en("Skills have been changed. Do you want to save the changes?");
    temp.ru("Навыки были изменены. Вы хотите сохранить изменения?");
    initLanguageBundleMenu(temp, main_.questionSaveChanges_);
}

void MenuSkillText::initModify()
{
    LanguageBundle temp;

    temp.en("Skill modification menu");
    temp.ru("Меню модификации навыков");
    initLanguageBundleMenu(temp, modify_.menuName_);

    temp.en("Show skill description");
    temp.ru("Показать описание навыка");
    initLanguageBundleMenu(temp, modify_.showDescription_);

    temp.en("Increase level");
    temp.ru("Повысить уровень");
    initLanguageBundleMenu(temp, modify_.increaseLevel_);

    temp.en("Decrease level");
    temp.ru("Понизить уровень");
    initLanguageBundleMenu(temp, modify_.decreaseLevel_);

    temp.en("Skill:");
    temp.ru("Навык:");
    initLanguageBundleMenu(temp, modify_.skill_);

    temp.en("Skill (accepted):");
    temp.ru("Навык (принято):");
    initLanguageBundleMenu(temp, modify_.skillAccepted_);
}

} // namespace menu
} // namespace game
