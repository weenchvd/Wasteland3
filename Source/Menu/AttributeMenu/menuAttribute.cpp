
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuAttribute.hpp"
#include"menuAttributeText.hpp"
#include"menuCommonText.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace game {
namespace menu {

using namespace std;

void menuAttribute(istream& is, ostream& os, object::Character& character, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuAttributeText::main() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << " (" << character.name() << ")" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionAttribute::SHOW_ALL, text.showAttributes()) << endl;
        printNumBar(os, ind1, actionAttribute::SHOW_ALL_ACCEPTED, text.showAttributesAccepted()) << endl;
        printNumBar(os, ind1, actionAttribute::MODIFY, text.modify()) << endl;
        printNumBar(os, ind1, actionAttribute::SAVE_CHANGES, comT.saveChanges()) << endl;
        printNumBar(os, ind1, actionAttribute::CANCEL_CHANGES, comT.cancelChanges()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionAttribute::SHOW_ALL:
            showAllAttributes(is, os, character, ind1);
            break;
        case actionAttribute::SHOW_ALL_ACCEPTED:
            showAllAttributes(is, os, character, ind1, true);
            break;
        case actionAttribute::MODIFY: {
            object::Attribute::Type type{ pickAttribute(is, os, character, ind1) };
            if (type != object::Attribute::Type::__INVALID) {
                menuModifyAttribute(is, os, character, type, ind1);
            }
            break;
        }
        case actionAttribute::SAVE_CHANGES:
            character.attribute().accept();
            break;
        case actionAttribute::CANCEL_CHANGES:
            character.attribute().reject();
            break;
        case actionCommon::EXIT:
            if (character.attribute().isModified()) {
                os << ind0 << text.questionSaveChanges() << endl;
                switch (getYesNo(is, os, ind1)) {
                case YesNo::YES:
                    character.attribute().accept();
                    return;
                case YesNo::NO:
                    character.attribute().reject();
                    return;
                case YesNo::CANCEL:
                default:
                    break;
                }
            }
            else {
                return;
            }
            break;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

void menuModifyAttribute(
    istream& is,
    ostream& os,
    object::Character& character,
    object::Attribute::Type type,
    const Indent indent)
{
    constexpr auto sp{ sign::space };
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuAttributeText::modify() };
    auto nameWidth{ utf8Size(character.attribute().attributeText().name(type)) + attributeSpaces };
    auto width{ utf8Size(text.attributeAccepted()) };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << " (" << character.name() << ")" << endl;
        showAttPoints(is, os, character, ind0);
        os << ind0 << fitInWidth(text.attribute(), width, sp) << sp
            << stringAttribute(character, type, nameWidth, sp, false) << endl;
        os << ind0 << fitInWidth(text.attributeAccepted(), width, sp) << sp
            << stringAttribute(character, type, nameWidth, sp, true) << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionModifyAttribute::SHOW_DESCRIPTION, text.showDescription()) << endl;
        printNumBar(os, ind1, actionModifyAttribute::INCREASE_LEVEL, text.increaseLevel()) << endl;
        printNumBar(os, ind1, actionModifyAttribute::DECREASE_LEVEL, text.decreaseLevel()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionModifyAttribute::SHOW_DESCRIPTION:
            os << ind1 << character.attribute().attributeText().descr(type) << endl;
            break;
        case actionModifyAttribute::INCREASE_LEVEL: {
            changeLevel(is, os, character, type, indent, true);
            break;
        }
        case actionModifyAttribute::DECREASE_LEVEL: {
            changeLevel(is, os, character, type, indent, false);
            break;
        }
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

///************************************************************************************************

void showAllAttributes(
    istream& is,
    ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& text{ MenuAttributeText::common() };

    showAttPoints(is, os, character, ind0, accepted);
    os << ind0 << (accepted ? text.attributesAccepted() : text.attributes()) << sign::colon << endl;

    unsigned int width{ 0 };
    for (int i{ common::toUnderlying(common::firstEnum<object::Attribute::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Attribute::Type>()); ++i)
    {
        auto size{ utf8Size(character.attribute().attributeText().name(
            static_cast<object::Attribute::Type>(i)))
        };
        if (width < size) {
            width = size;
        }
    }
    width += attributeSpaces;

    for (int i{ common::toUnderlying(common::firstEnum<object::Attribute::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Attribute::Type>()); ++i)
    {
        os << ind1 << stringAttribute(character, static_cast<object::Attribute::Type>(i),
            width, sign::space, accepted) << endl;
    }
}

common::Text stringAttribute(
    const object::Character& character,
    object::Attribute::Type type,
    unsigned char width,
    char placeholder,
    bool accepted)
{
    common::Text t{
        fitInWidth(
            character.attribute().attributeText().name(type), width, placeholder)
    };
    t += stringLevel(character.attribute().level(type), accepted);
    return t;
}

void showAttPoints(
    istream& is,
    ostream& os,
    const object::Character& character,
    const Indent indent,
    bool accepted)
{
    const auto& text{ MenuAttributeText::common() };

    os << indent << (accepted ? text.attrPointsAccepted() : text.attrPoints())
        << sign::space << (accepted ? character.attribute().storage().getAccepted() :
            character.attribute().storage().get()) << endl;
}

object::Attribute::Type pickAttribute(
    istream& is,
    ostream& os,
    const object::Character& character,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuAttributeText::common() };

    os << ind0 << text.attributes() << sign::colon << endl;
    for (int i{ common::toUnderlying(common::firstEnum<object::Attribute::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Attribute::Type>()); ++i)
    {
        printNumBar(os, ind1, i, character.attribute().attributeText().name(
            static_cast<object::Attribute::Type>(i))) << endl;
    }
    os << ind0 << text.selectAttribute() << endl;
    object::Attribute::Type t{ object::Attribute::Type::__INVALID };
    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        if (pair.first >= common::toUnderlying(common::firstEnum<object::Attribute::Type>()) &&
            pair.first <= common::toUnderlying(common::lastEnum<object::Attribute::Type>()))
        {
            t = static_cast<object::Attribute::Type>(pair.first);
        }
        else {
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
    }
    return t;
}

void changeLevel(
    istream& is,
    ostream& os,
    object::Character& character,
    object::Attribute::Type type,
    const Indent indent,
    bool increase)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuAttributeText::common() };

    os << ind1 << text.enterNumOfLevels() << endl;

    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        if (pair.first >= 0 &&
            pair.first <= numeric_limits<std::underlying_type_t<common::LevelAttribute>>::max())
        {
            auto success{ character.attribute().addLevel(type, common::LevelAttribute{
                static_cast<std::underlying_type_t<common::LevelAttribute>>(
                    (increase ? pair.first : -pair.first)) })
            };
            if (success) return;
        }
        os << comT.errorSymbol() << text.invalidNumOfLevels() << endl;
    }
}

} // namespace menu
} // namespace game
