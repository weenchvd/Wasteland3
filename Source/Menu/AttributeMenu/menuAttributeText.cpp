
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuAttributeText.hpp"
#include"menuCommon.hpp"

namespace game {
namespace menu {

using namespace std;

global::PlainTextBase                       MenuAttributeText::base_;
MenuAttributeTextCommon                     MenuAttributeText::common_;
MenuAttributeTextMain                       MenuAttributeText::main_;
MenuAttributeTextModify                     MenuAttributeText::modify_;
bool                                        MenuAttributeText::initialized_{ false };

///************************************************************************************************

void MenuAttributeText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    initCommon();
    initMain();
    initModify();

    initialized_ = true;
}

void MenuAttributeText::initCommon()
{
    LanguageBundle temp;

    temp.en("Attributes:");
    temp.ru("Атрибуты:");
    initLanguageBundleMenu(temp, common_.attributes_);

    temp.en("Attributes (accepted):");
    temp.ru("Атрибуты (принято):");
    initLanguageBundleMenu(temp, common_.attributesAccepted_);

    temp.en("Attribute points:");
    temp.ru("Очки атрибутов:");
    initLanguageBundleMenu(temp, common_.attrPoints_);

    temp.en("Attribute points (accepted):");
    temp.ru("Очки атрибутов (принято):");
    initLanguageBundleMenu(temp, common_.attrPointsAccepted_);

    temp.en("Select an attribute:");
    temp.ru("Выберите атрибут:");
    initLanguageBundleMenu(temp, common_.selectAttribute_);

    temp.en("Enter the number of levels:");
    temp.ru("Введите количество уровней:");
    initLanguageBundleMenu(temp, common_.enterNumOfLevels_);

    temp.en("Invalid number of levels");
    temp.ru("Недопустимое количество уровней");
    initLanguageBundleMenu(temp, common_.invalidNumOfLevels_);
}

void MenuAttributeText::initMain()
{
    LanguageBundle temp;

    temp.en("Attribute menu");
    temp.ru("Меню атрибутов");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en("Show attributes");
    temp.ru("Показать атрибуты");
    initLanguageBundleMenu(temp, main_.showAttr_);

    temp.en("Show accepted attributes");
    temp.ru("Показать принятые атрибуты");
    initLanguageBundleMenu(temp, main_.showAttrAccepted_);

    temp.en("Modify");
    temp.ru("Модифицировать");
    initLanguageBundleMenu(temp, main_.modify_);

    temp.en("Attributes have been changed. Do you want to save the changes?");
    temp.ru("Атрибуты были изменены. Вы хотите сохранить изменения?");
    initLanguageBundleMenu(temp, main_.questionSaveChanges_);
}

void MenuAttributeText::initModify()
{
    LanguageBundle temp;

    temp.en("Attribute modification menu");
    temp.ru("Меню модификации атрибута");
    initLanguageBundleMenu(temp, modify_.menuName_);

    temp.en("Show attribute description");
    temp.ru("Показать описание атрибута");
    initLanguageBundleMenu(temp, modify_.showDescription_);

    temp.en("Increase level");
    temp.ru("Повысить уровень");
    initLanguageBundleMenu(temp, modify_.increaseLevel_);

    temp.en("Decrease level");
    temp.ru("Понизить уровень");
    initLanguageBundleMenu(temp, modify_.decreaseLevel_);

    temp.en("Attribute:");
    temp.ru("Атрибут:");
    initLanguageBundleMenu(temp, modify_.attribute_);

    temp.en("Attribute (accepted):");
    temp.ru("Атрибут (принято):");
    initLanguageBundleMenu(temp, modify_.attributeAccepted_);
}

} // namespace menu
} // namespace game
