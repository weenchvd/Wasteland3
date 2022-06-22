
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

ostream& printNumBar(ostream& os, const Indent indent, int number, const common::Text& text)
{
    os << indent << '\'' << number << "\' " << text;
    return os;
}

ostream& verticalIndent(ostream& os)
{
    os << endl << endl;
    return os;
}

ostringstream& clearStream(ostringstream& oss)
{
    oss.str("");
    oss.clear();
    return oss;
}

int getAction(istream& is, ostream& os)
{
    const auto& text{ MenuCommonText::common() };
    os << text.promptSymbol();
    string input;
    getline(is, input);
    try {
        return stoi(input);
    }
    catch (...) {
        os << text.errorSymbol() << text.invalidInput() << endl;
        return actionCommon::INVALID;
    }
}

pair<int, bool> getNumber(istream& is, ostream& os)
{
    const auto& text{ MenuCommonText::common() };
    os << text.promptSymbol();
    string input;
    getline(is, input);
    try {
        return { stoi(input), true };
    }
    catch (...) {
        os << text.errorSymbol() << text.invalidInput() << endl;
        return { numeric_limits<int>::min(), false };
    }
}

pair<string, bool> getFileStem(
    istream& is,
    ostream& os,
    const Indent indent)
{
    regex r{ ".+" };
    return getFileStem(is, os, r, indent);
}

pair<string, bool> getFileStem(
    istream& is,
    ostream& os,
    const std::regex& r,
    const Indent indent)
{
    const auto& text{ MenuCommonText::common() };
    os << indent << text.enterFilenameNoExt() << endl;
    os << text.promptSymbol();
    string input;
    getline(is, input);
    smatch mr;
    if (regex_match(input, mr, r) && input.size() > 0) {
        return { input, true };
    }
    os << text.errorSymbol() << text.invalidInput() << endl;
    return { string{}, false };
}

YesNo getYesNo(istream& is, ostream& os, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& text{ MenuCommonText::common() };
    os << ind0 << text.actions() << endl;
    printNumBar(os, ind1, common::toUnderlying(YesNo::CANCEL), text.cancel()) << endl;
    printNumBar(os, ind1, common::toUnderlying(YesNo::YES), text.yes()) << endl;
    printNumBar(os, ind1, common::toUnderlying(YesNo::NO), text.no()) << endl;
    os << ind0 << text.enterAction() << endl;
    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        switch (pair.first) {
        case common::toUnderlying(YesNo::CANCEL):
            return YesNo::CANCEL;
        case common::toUnderlying(YesNo::YES):
            return YesNo::YES;
        case common::toUnderlying(YesNo::NO):
            return YesNo::NO;
        default:
            os << text.errorSymbol() << text.invalidNumber() << endl;
            break;
        }
    }
    return YesNo::INVALID;
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

common::Text fitInWidth(
    const common::Text& left,
    unsigned char width,
    char placeholder)
{
    common::Text t{ left };
    for (unsigned int i{ utf8Size(left) }; i < width; ++i) {
        t += placeholder;
    }
    return t;
}

common::Text fitInWidth(
    const common::Text& left,
    const common::Text& right,
    unsigned char width,
    char placeholder)
{
    common::Text t;
    auto minSize{ left.size() + right.size() + 1 };
    t.reserve(width > minSize ? width : minSize);
    t = left;
    t += sign::space;
    auto nPlaceholders{
        static_cast<int>(width) - static_cast<int>(utf8Size(t)) - static_cast<int>(utf8Size(right))
    };
    for (int i = 0; i < nPlaceholders - 1; ++i) {
        t += placeholder;
    }
    if (nPlaceholders > 0) {
        t += sign::space;
    }
    t += right;
    return t;
}

///************************************************************************************************

size_t LanguageBundle::size() const noexcept
{
    size_t size{ 0 };
    for (int i = 0; i < bundle_.size(); ++i) {
        if (bundle_[i].size() > 0) ++size;
    }
    return size;
}

void initLanguageBundleMenu(
    LanguageBundle& bundle,
    std::array<common::Text, global::PlainTextBase::sizeLang_>& target)
{
    using lang = global::PlainTextBase::Language;
    assert(bundle.size() == target.size());

    for (size_t i{ common::toUnderlying(common::firstEnum<lang>()) };
        i <= common::toUnderlying(common::lastEnum<lang>());
        ++i)
    {
        target[i] = move(bundle[i]);
    }
}

} // namespace menu
} // namespace game
