
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuAttribute.hpp"
#include<limits>
#include<sstream>
#include<string>

namespace game {
namespace menu {

using namespace std;


void menuAttribute(object::Character& character, const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};

    while (true)
    {
        cout << endl << endl;
        cout << ind1 << "Attribute menu (" << character.name() << ")" << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionAttribute::SHOW_ALL << "\' Show attributes" << endl;
        cout << ind2 << '\'' << actionAttribute::SHOW_ALL_ACCEPTED << "\' Show attributes (accepted)" << endl;
        cout << ind2 << '\'' << actionAttribute::MODIFY << "\' Modify attribute" << endl;

        switch (getAction()) {
        case actionAttribute::SHOW_ALL:
            showAllAttributes(character, ind1);
            break;
        case actionAttribute::SHOW_ALL_ACCEPTED:
            showAllAttributes(character, ind1, true);
            break;
        case actionAttribute::MODIFY: {
            object::Attribute::Type type{ pickAttribute(character, ind1) };
            if (type != object::Attribute::Type::INVALID) {
                menuModifyAttribute(character, type, ind1);
            }
            else {
                cout << "!Invalid type" << endl;
            }
            break;
        }
        case actionCommon::EXIT:
            if (character.attribute().isModified()) {
                cout << ind1 << "Attributes have been changed. Do you want to save the changes?" << endl;
                switch (getYesNo()) {
                case YesNo::YES:
                    character.attribute().accept();
                    return;
                case YesNo::NO:
                    character.attribute().reject();
                    return;
                default:
                    cout << "!Invalid input" << endl;
                    break;
                }
            }
            else {
                return;
            }
            break;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

void menuModifyAttribute(
    object::Character& character,
    object::Attribute::Type type,
    const Indent indent)
{
    Indent ind1 = indent + Indent{};
    Indent ind2 = ind1 + Indent{};
    auto width{ utf8Size(character.attribute().attributeText().name(type)) + 2 };

    while (true)
    {
        cout << endl << endl;
        showAttPoints(character, ind1);
        cout << ind1 << "Attribute: " << stringAttribute(character, type, width, space) << endl;
        cout << ind2 << character.attribute().attributeText().descr(type) << endl;
        cout << ind1 << "Actions:" << endl;
        cout << ind2 << '\'' << actionCommon::EXIT << "\' Exit the menu" << endl;
        cout << ind2 << '\'' << actionModifyAttribute::SHOW_ACCEPTED << "\' Show the accepted level" << endl;
        cout << ind2 << '\'' << actionModifyAttribute::INCREASE_LEVEL << "\' Increase level" << endl;
        cout << ind2 << '\'' << actionModifyAttribute::DECREASE_LEVEL << "\' Decrease level" << endl;

        switch (getAction()) {
        case actionModifyAttribute::SHOW_ACCEPTED:
            cout << ind2 << "Attribute (accepted): "
                << stringAttribute(character, type, width, space, true) << endl;
            break;
        case actionModifyAttribute::INCREASE_LEVEL: {
            int n = getPosNumber();
            if (n >= 0 && n <= numeric_limits<common::LevelStat>::max()) {
                character.attribute().addLevel(type, n);
            }
            break;
        }
        case actionModifyAttribute::DECREASE_LEVEL: {
            int n = getPosNumber();
            if (n >= 0 && n <= numeric_limits<common::LevelStat>::max()) {
                character.attribute().addLevel(type, -n);
            }
            break;
        }
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            cout << "!Invalid action" << endl;
            break;
        default:
            cout << "!Unknown action" << endl;
            break;
        }
    }
}

///------------------------------------------------------------------------------------------------

void showAllAttributes(
    const object::Character& character,
    const Indent indent,
    bool accepted)
{
    Indent ind1 = indent + Indent{};
    showAttPoints(character, ind1, accepted);
    cout << ind1 << "Attributes";
    if (accepted) {
        cout << " (accepted)";
    }
    cout << ":" << endl;
    Indent ind2 = ind1 + Indent{};

    cout << ind2 << stringAttribute(character, object::Attribute::Type::COORDINATION,
        attrWidth, space, accepted) << endl;
    cout << ind2 << stringAttribute(character, object::Attribute::Type::LUCK,
        attrWidth, space, accepted) << endl;
    cout << ind2 << stringAttribute(character, object::Attribute::Type::AWARENESS,
        attrWidth, space, accepted) << endl;
    cout << ind2 << stringAttribute(character, object::Attribute::Type::STRENGTH,
        attrWidth, space, accepted) << endl;
    cout << ind2 << stringAttribute(character, object::Attribute::Type::SPEED,
        attrWidth, space, accepted) << endl;
    cout << ind2 << stringAttribute(character, object::Attribute::Type::INTELLIGENCE,
        attrWidth, space, accepted) << endl;
    cout << ind2 << stringAttribute(character, object::Attribute::Type::CHARISMA,
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
    t += statLevel(character.attribute().level(type), accepted);
    return t;
}

void showAttPoints(
    const object::Character& character,
    const Indent indent,
    bool accepted)
{
    cout << indent << "Attribute points";
    if (accepted) {
        cout << " (accepted): " << static_cast<int>(
            character.attribute().storage().getAccepted()) << endl;
    }
    else {
        cout << ": " << static_cast<int>(
            character.attribute().storage().get()) << endl;
    }
}

object::Attribute::Type pickAttribute(
    const object::Character& character,
    const Indent indent)
{
    Indent ind1 = indent + Indent{};
    cout << ind1 << "Attributes:" << endl;
    Indent ind2 = ind1 + Indent{};

    for (int i = { common::toUnderlying(common::firstEnum<object::Attribute::Type>()) };
        i <= common::toUnderlying(common::lastEnum<object::Attribute::Type>()); ++i)
    {
        cout << ind2 << '\'' << i << "\' "
            << character.attribute().attributeText().name(
                static_cast<object::Attribute::Type>(i)) << endl;
    }
    cout << ind1 << "Select an attribute:" << endl;
    object::Attribute::Type t{ object::Attribute::Type::INVALID };
    int n = getPosNumber();
    if (n >= common::toUnderlying(common::firstEnum<object::Attribute::Type>()) &&
        n <= common::toUnderlying(common::lastEnum<object::Attribute::Type>()))
    {
        t = static_cast<object::Attribute::Type>(n);
    }
    return t;
}

} // namespace menu
} // namespace game
