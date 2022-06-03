
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_COMMON_HPP
#define MENU_COMMON_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include"specStorage.hpp"
#include<array>
#include<iostream>
#include<limits>
#include<sstream>
#include<utility>

namespace game {
namespace menu {

namespace sign {

constexpr auto space    { ' ' };
constexpr auto dot      { '.' };
constexpr auto colon    { ':' };
constexpr auto slash    { '/' };
constexpr auto lp       { '(' };
constexpr auto rp       { ')' };
constexpr auto percent  { '%' };
constexpr auto dollar   { '$' };
constexpr auto sharp    { '#' };
constexpr auto x        { 'X' };

constexpr auto separator10  { "----------" };
constexpr auto separator20  { "--------------------" };
constexpr auto separator30  { "------------------------------" };

} // namespace sign

class Indent {
public:
    Indent()
        : indent_{ 2 } {}

    Indent(unsigned int indent)
        : indent_{ indent } {}

    unsigned int get() const {
        return indent_;
    }

private:
    unsigned int indent_;
};

Indent operator+(const Indent& left, const Indent& right);

std::ostream& operator<<(std::ostream& os, const Indent& indent);

///************************************************************************************************

std::ostream& printNumBar(std::ostream& os, const Indent indent, int number, const common::Text& text);

std::ostream& verticalIndent(std::ostream& os);

std::ostringstream& clearStream(std::ostringstream& oss);

int getAction(std::istream& is, std::ostream& os);

std::pair<int, bool> getNumber(std::istream& is, std::ostream& os);

enum class YesNo {
    INVALID = -1,
    CANCEL,
    YES,
    NO
};

YesNo getYesNo(std::istream& is, std::ostream& os, const Indent indent);

namespace actionCommon {

enum ActionCommon {
    INVALID = std::numeric_limits<int>::min(),
    EXIT = 0,
    __NEXT_ACTION_NUMBER
};

} // namespace actionCommon

template<class LevelType>
common::Text stringLevel(const common::SpecStorage<LevelType>& level, bool accepted)
{
    common::Text s;
    LevelType lvl{ accepted ? level.getAccepted() : level.get() };
    for (LevelType i{ level.getMinPossible() + LevelType{ 1 } };
        i <= level.getMaxPossible();
        i += LevelType{ 1 })
    {
        s += (i <= lvl) ? '+' : '-';
    }
    return s;
}

unsigned int utf8Size(const std::string& s);

common::Text fitInWidth(
    const common::Text& left,
    unsigned char width,
    char placeholder
);

common::Text fitInWidth(
    const common::Text& left,
    const common::Text& rigth,
    unsigned char width,
    char placeholder
);

///************************************************************************************************

class LanguageBundle {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_t        = global::PlainTextBase::Language;

public:
    LanguageBundle() noexcept {}

    LanguageBundle(const LanguageBundle&) = delete;
    LanguageBundle& operator=(const LanguageBundle&) = delete;

    size_t size() const noexcept;

    text_t& operator[](size_t index) noexcept {
        return bundle_[index];
    }

    void en(text_t t) {
        bundle_[common::toUnderlying(language_t::EN)] = std::move(t);
    }

    void ru(text_t t) {
        bundle_[common::toUnderlying(language_t::RU)] = std::move(t);
    }

private:
    language_bundle_t bundle_;
};

void initLanguageBundleMenu(
    LanguageBundle& bundle,
    std::array<common::Text, global::PlainTextBase::sizeLang_>& target
);

} // namespace menu
} // namespace game

#endif // !MENU_COMMON_HPP
