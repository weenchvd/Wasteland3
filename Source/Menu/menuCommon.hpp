
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_COMMON_HPP
#define MENU_COMMON_HPP

#include"common.hpp"
#include"plainText.hpp"
#include"specStorage.hpp"
#include<array>
#include<iostream>
#include<utility>

namespace game {
namespace menu {

constexpr char space{ ' ' };

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

inline double secondTime(common::Time time) {
    return static_cast<double>(time) / 1000;
}

inline double multiplier(common::Multiplier mult) {
    return static_cast<double>(mult) / 100;
}

inline double percentChance(common::Chance chance) {
    return static_cast<double>(chance) / 10;
}

inline double percentBonus(common::Bonus bonus) {
    return static_cast<double>(bonus) / 10;
}

inline double percentEvasion(common::Evasion evasion) {
    return static_cast<double>(evasion) / 10;
}

inline double percentResistance(common::Resistance res) {
    return static_cast<double>(res) / 10;
}

inline double percentInitiative(common::Initiative init) {
    return static_cast<double>(init) / 10;
}

inline double percentStrike(common::Strike strike) {
    return static_cast<double>(strike) / 10;
}

inline int integer(char ch) {
    return static_cast<int>(ch);
}

///************************************************************************************************

void printMenuBar(const Indent indent, int number, const common::Text& text);

int getAction();

std::pair<int, bool> getNumber();

enum class YesNo {
    INVALID = -1,
    CANCEL,
    YES,
    NO
};

YesNo getYesNo(const Indent indent);

namespace actionCommon {

enum ActionCommon {
    INVALID = -1,
    EXIT,
    NEXT
};

} // namespace actionCommon

common::Text statLevel(
    const common::SpecStorage<common::LevelStat>& level,
    bool accepted = false
);

unsigned int utf8Size(const std::string& s);

common::Text fillWithPlaseholders(
    const common::Text& source,
    unsigned char width,
    char placeholder
);

///************************************************************************************************

class LanguageBundle {
public:
    using text              = common::Text;
    
private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ 2 };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    LanguageBundle() noexcept {}

    LanguageBundle(const LanguageBundle&) = delete;
    LanguageBundle& operator=(const LanguageBundle&) = delete;

    size_t size() const noexcept { return bundle_.size(); }

    void en(text t) {
        bundle_[common::toUnderlying(language::EN)] = std::move(t);
    }
    text& en() {
        return bundle_[common::toUnderlying(language::EN)];
    }

    void ru(text t) {
        bundle_[common::toUnderlying(language::RU)] = std::move(t);
    }
    text& ru() {
        return bundle_[common::toUnderlying(language::RU)];
    }

private:
    language_bundle bundle_;
};

void initLanguageBundleMenu(
    LanguageBundle& bundle,
    std::array<common::Text, global::PlainText::sizeLang_>& target
);

} // namespace menu
} // namespace game

#endif // !MENU_COMMON_HPP
