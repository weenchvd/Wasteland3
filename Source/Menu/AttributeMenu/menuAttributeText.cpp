
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

    temp.en(u8"Attributes");
    temp.ru(u8"Атрибуты");
    initLanguageBundleMenu(temp, common_.attributes_);

    temp.en(u8"Attributes (accepted)");
    temp.ru(u8"Атрибуты (принято)");
    initLanguageBundleMenu(temp, common_.attributesAccepted_);

    temp.en(u8"Attribute points:");
    temp.ru(u8"Очки атрибутов:");
    initLanguageBundleMenu(temp, common_.attrPoints_);

    temp.en(u8"Attribute points (accepted):");
    temp.ru(u8"Очки атрибутов (принято):");
    initLanguageBundleMenu(temp, common_.attrPointsAccepted_);

    temp.en(u8"Select an attribute:");
    temp.ru(u8"Выберите атрибут:");
    initLanguageBundleMenu(temp, common_.selectAttribute_);

    temp.en(u8"Enter the number of levels:");
    temp.ru(u8"Введите количество уровней:");
    initLanguageBundleMenu(temp, common_.enterNumOfLevels_);

    temp.en(u8"Invalid number of levels");
    temp.ru(u8"Недопустимое количество уровней");
    initLanguageBundleMenu(temp, common_.invalidNumOfLevels_);
}

void MenuAttributeText::initMain()
{
    LanguageBundle temp;

    temp.en(u8"Attribute menu");
    temp.ru(u8"Меню атрибутов");
    initLanguageBundleMenu(temp, main_.menuName_);

    temp.en(u8"Show attributes");
    temp.ru(u8"Показать атрибуты");
    initLanguageBundleMenu(temp, main_.showAttr_);

    temp.en(u8"Show accepted attributes");
    temp.ru(u8"Показать принятые атрибуты");
    initLanguageBundleMenu(temp, main_.showAttrAccepted_);

    temp.en(u8"Modify");
    temp.ru(u8"Модифицировать");
    initLanguageBundleMenu(temp, main_.modify_);

    temp.en(u8"Attributes have been changed. Do you want to save the changes?");
    temp.ru(u8"Атрибуты были изменены. Вы хотите сохранить изменения?");
    initLanguageBundleMenu(temp, main_.questionSaveChanges_);
}

void MenuAttributeText::initModify()
{
    LanguageBundle temp;

    temp.en(u8"Attribute modification menu");
    temp.ru(u8"Меню модификации атрибута");
    initLanguageBundleMenu(temp, modify_.menuName_);

    temp.en(u8"Show attribute description");
    temp.ru(u8"Показать описание атрибута");
    initLanguageBundleMenu(temp, modify_.showDescription_);

    temp.en(u8"Increase level");
    temp.ru(u8"Повысить уровень");
    initLanguageBundleMenu(temp, modify_.increaseLevel_);

    temp.en(u8"Decrease level");
    temp.ru(u8"Понизить уровень");
    initLanguageBundleMenu(temp, modify_.decreaseLevel_);

    temp.en(u8"Attribute:");
    temp.ru(u8"Атрибут:");
    initLanguageBundleMenu(temp, modify_.attribute_);

    temp.en(u8"Attribute (accepted):");
    temp.ru(u8"Атрибут (принято):");
    initLanguageBundleMenu(temp, modify_.attributeAccepted_);
}

} // namespace menu
} // namespace game
