
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuCommonText.hpp"
#include<assert.h>
#include<iostream>
#include<string>
#include<type_traits>

namespace game {
namespace menu {

using namespace std;


Indent operator+(const Indent& left, const Indent& right) {
    return Indent{ left.get() + right.get() };
}

ostream& operator<<(ostream& os, const Indent& indent) {
    for (unsigned int i = 0; i < indent.get(); ++i) {
        os.put(' ');
    }
    return os;
}

int getAction()
{
    cout << MenuCommonText::common().enterAction() << MenuCommonText::common().promptSymbol();
    string input;
    getline(cin, input);
    try {
        return stoi(input);
    }
    catch (...) {
        return actionCommon::INVALID;
    }
}

int getPosNumber()
{
    cout << MenuCommonText::common().enterNumber() << MenuCommonText::common().promptSymbol();
    string input;
    getline(cin, input);
    int n;
    try {
        n = stoi(input);
    }
    catch (...) {
        return -1;
    }
    if (n < 0) {
        return -1;
    }
    return n;
}

YesNo getYesNo(const Indent indent)
{
    Indent ind1 = indent + Indent{};
    const auto& text{ MenuCommonText::common() };
    cout << indent << text.actions() << endl;
    cout << ind1 << "'1' " << text.yes() << endl;
    cout << ind1 << "'0' " << text.no() << endl;
    cout << text.enterAction() << text.promptSymbol();
    string input;
    getline(cin, input);
    if (input.size() != sizeof('1')) {
        return YesNo::INVALID;
    }
    char ch = toupper(input[0]);
    if (ch == '1') {
        return YesNo::YES;
    }
    else if (ch == '0') {
        return YesNo::NO;
    }
    else {
        return YesNo::INVALID;
    }
}

common::Text statLevel(const common::SpecStorage<common::LevelStat>& level, bool accepted)
{
    common::Text s;
    if (accepted) {
        for (common::LevelStat i = level.getMinPossible() + 1; i <= level.getMaxPossible(); ++i) {
            if (i <= level.getAccepted()) {
                s += '+';
            }
            else {
                s += '-';
            }
        }
    }
    else {
        for (common::LevelStat i = level.getMinPossible() + 1; i <= level.getMaxPossible(); ++i) {
            if (i <= level.get()) {
                s += '+';
            }
            else {
                s += '-';
            }
        }
    }
    return s;
}

unsigned int utf8Size(const std::string& s)
{
    unsigned int size{ 0 };
    for (auto& ch : s) {
        if ((ch & 0xC0) != 0x80) {
            ++size;
        }
    }
    return size;
}

common::Text fillWithPlaseholders(
    const common::Text& source,
    unsigned char width,
    char placeholder)
{
    common::Text t{ source };
    for (int i = utf8Size(source); i < width; ++i) {
        t += placeholder;
    }
    return t;
}

///************************************************************************************************

void initLanguageBundleMenu(
    LanguageBundle& bundle,
    std::array<common::Text, global::PlainText::sizeLang_>& target)
{
    using lang = global::PlainText::Language;
    using text = common::Text;
    assert(bundle.size() == target.size());

    target[common::toUnderlying(lang::EN)] = move(bundle.en());
    target[common::toUnderlying(lang::RU)] = move(bundle.ru());
}


} // namespace menu
} // namespace game
