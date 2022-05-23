
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuAttribute.hpp"
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

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Attribute menu (" << character.name() << ")" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionAttribute::SHOW_ALL, "Show attributes") << endl;
        printNumBar(os, ind1, actionAttribute::SHOW_ALL_ACCEPTED, "Show attributes (accepted)") << endl;
        printNumBar(os, ind1, actionAttribute::MODIFY, "Modify attribute") << endl;
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
            if (type != object::Attribute::Type::INVALID) {
                menuModifyAttribute(is, os, character, type, ind1);
            }
            break;
        }
        case actionCommon::EXIT:
            if (character.attribute().isModified()) {
                os << ind0 << "Attributes have been changed. Do you want to save the changes?" << endl;
                switch (getYesNo(is, os, ind0)) {
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
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    auto width{ utf8Size(character.attribute().attributeText().name(type)) + 2 };

    while (true)
    {
        verticalIndent(os);
        showAttPoints(is, os, character, ind0);
        os << ind0 << "Attribute: " << stringAttribute(character, type, width, space) << endl;
        os << ind1 << character.attribute().attributeText().descr(type) << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionModifyAttribute::SHOW_ACCEPTED, "Show the accepted level") << endl;
        printNumBar(os, ind1, actionModifyAttribute::INCREASE_LEVEL, "Increase level") << endl;
        printNumBar(os, ind1, actionModifyAttribute::DECREASE_LEVEL, "Decrease level") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionModifyAttribute::SHOW_ACCEPTED:
            os << ind1 << "Attribute (accepted): "
                << stringAttribute(character, type, width, space, true) << endl;
            break;
        case actionModifyAttribute::INCREASE_LEVEL: {
            auto pair{ getNumber(is, os) };
            if (pair.second == true) {
                if (pair.first >= 0 &&
                    pair.first <= numeric_limits<std::underlying_type_t<common::LevelAttribute>>::max()) {
                    // TODO ^^^ check or set range
                    character.attribute().addLevel(type, common::LevelAttribute{
                        static_cast<std::underlying_type_t<common::LevelAttribute>>(pair.first) });
                }
                else {
                    // TODO os << message
                }
            }
            break;
        }
        case actionModifyAttribute::DECREASE_LEVEL: {
            auto pair{ getNumber(is, os) };
            if (pair.second == true) {
                if (pair.first >= 0 &&
                    pair.first <= numeric_limits<std::underlying_type_t<common::LevelAttribute>>::max()) {
                    // TODO ^^^ check or set range
                    character.attribute().addLevel(type, common::LevelAttribute{
                        static_cast<std::underlying_type_t<common::LevelAttribute>>(-pair.first) });
                }
                else {
                    // TODO os << message
                }
            }
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

    showAttPoints(is, os, character, ind0, accepted);
    os << ind0 << "Attributes";
    if (accepted) {
        os << " (accepted)";
    }
    os << ":" << endl;

    os << ind1 << stringAttribute(character, object::Attribute::Type::COORDINATION,
        attrWidth, space, accepted) << endl;
    os << ind1 << stringAttribute(character, object::Attribute::Type::LUCK,
        attrWidth, space, accepted) << endl;
    os << ind1 << stringAttribute(character, object::Attribute::Type::AWARENESS,
        attrWidth, space, accepted) << endl;
    os << ind1 << stringAttribute(character, object::Attribute::Type::STRENGTH,
        attrWidth, space, accepted) << endl;
    os << ind1 << stringAttribute(character, object::Attribute::Type::SPEED,
        attrWidth, space, accepted) << endl;
    os << ind1 << stringAttribute(character, object::Attribute::Type::INTELLIGENCE,
        attrWidth, space, accepted) << endl;
    os << ind1 << stringAttribute(character, object::Attribute::Type::CHARISMA,
        attrWidth, space, accepted) << endl;
}

common::Text stringAttribute(
    const object::Character& character,
    object::Attribute::Type type,
    unsigned char width,
    char placeholder,
    bool accepted)
{
    common::Text t{
        fillWithPlaseholders(
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
    os << indent << "Attribute points";
    if (accepted) {
        os << " (accepted): " << static_cast<int>(
            character.attribute().storage().getAccepted()) << endl;
    }
    else {
        os << ": " << static_cast<int>(
            character.attribute().storage().get()) << endl;
    }
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

    os << ind0 << "Attributes:" << endl;
    for (int i{ common::toUnderlying(common::firstEnum<object::Attribute::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Attribute::Type>()); ++i)
    {
        os << ind1 << '\'' << i << "\' "
            << character.attribute().attributeText().name(
                static_cast<object::Attribute::Type>(i)) << endl;
    }
    os << ind0 << "Select an attribute:" << endl;
    object::Attribute::Type t{ object::Attribute::Type::INVALID };
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

} // namespace menu
} // namespace game
