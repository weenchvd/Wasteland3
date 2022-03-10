
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include"menuCommonText.hpp"
#include<assert.h>
#include<iostream>
#include<limits>
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

///************************************************************************************************

void printMenuBar(const Indent indent, int number, const common::Text& text)
{
    cout << indent << '\'' << number << "\' " << text << endl;
}

int getAction()
{
    const auto& text{ MenuCommonText::common() };
    cout << text.enterAction() << text.promptSymbol();
    string input;
    getline(cin, input);
    try {
        return stoi(input);
    }
    catch (...) {
        cout << text.errorSymbol() << text.invalidInput() << endl;
        return actionCommon::INVALID;
    }
}

pair<int, bool> getNumber()
{
    const auto& text{ MenuCommonText::common() };
    cout << text.enterNumber() << text.promptSymbol();
    string input;
    getline(cin, input);
    try {
        return { stoi(input), true };
    }
    catch (...) {
        cout << text.errorSymbol() << text.invalidInput() << endl;
        return { numeric_limits<int>::min(), false };
    }
}

YesNo getYesNo(const Indent indent)
{
    Indent ind1{ indent + Indent{} };
    const auto& text{ MenuCommonText::common() };
    cout << indent << text.actions() << endl;
    printMenuBar(ind1, common::toUnderlying(YesNo::CANCEL), text.cancel());
    printMenuBar(ind1, common::toUnderlying(YesNo::YES), text.yes());
    printMenuBar(ind1, common::toUnderlying(YesNo::NO), text.no());
    auto pair{ getNumber() };
    if (pair.second == true) {
        switch (pair.first) {
        case common::toUnderlying(YesNo::CANCEL):
            return YesNo::CANCEL;
        case common::toUnderlying(YesNo::YES):
            return YesNo::YES;
        case common::toUnderlying(YesNo::NO):
            return YesNo::NO;
        default:
            cout << text.errorSymbol() << text.invalidNumber() << endl;
            break;
        }
    }
    return YesNo::INVALID;
}

common::Text statLevel(const common::SpecStorage<common::LevelStat>& level, bool accepted)
{
    common::Text s;
    if (accepted) {
        for (common::LevelStat i{ level.getMinPossible() + 1 }; i <= level.getMaxPossible(); ++i) {
            if (i <= level.getAccepted()) {
                s += '+';
            }
            else {
                s += '-';
            }
        }
    }
    else {
        for (common::LevelStat i{ level.getMinPossible() + 1 }; i <= level.getMaxPossible(); ++i) {
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
    for (unsigned int i{ utf8Size(source) }; i < width; ++i) {
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
