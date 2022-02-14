
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"plainText.hpp"

namespace game {
namespace global {

using namespace std;

PlainText::PlainText(PlainText::Language lang)
    : current_{ lang }
{
    initialize();
}

void PlainText::setLanguage(PlainText::Language lang)
{
    if (current_ == lang) return;
    current_ = lang;
    initialize();
}

const PlainText::text& PlainText::language(PlainText::Language id) const noexcept
{
    if (common::isValidEnum(id)) {
        return lang_[common::toUnderlying(id)];
    }
    return common_[common::toUnderlying(PlainText::General::INVALID_ENUM)];
}

const PlainText::text& PlainText::common(PlainText::General id) const noexcept
{
    if (common::isValidEnum(id)) {
        return common_[common::toUnderlying(id)];
    }
    return common_[common::toUnderlying(PlainText::General::INVALID_ENUM)];
}

void PlainText::initialize()
{
    fill();
    switch (current_) {
    case PlainText::Language::EN:
        initializeEN();
        break;
    case PlainText::Language::RU:
        initializeRU();
        break;
    default:
        initializeEN();
        break;
    }

    lang_[common::toUnderlying(PlainText::Language::EN)]
        = text{ u8"ENGLISH" };
    lang_[common::toUnderlying(PlainText::Language::RU)]
        = text{ u8"РУССКИЙ" };

    common_[common::toUnderlying(PlainText::General::INVALID_ENUM)]
        = invalidEnum;
}

void PlainText::initializeEN()
{
    initCommonEN();
}

void PlainText::initializeRU()
{
    initCommonRU();
}

void PlainText::fill()
{
    fillAll(lang_, getDefault());
    fillAll(common_, getDefault());
}

const PlainText::text& PlainText::getDefault() const noexcept
{
    switch (current_) {
    case PlainText::Language::EN:
        return eng_NoData;
    case PlainText::Language::RU:
        return rus_NoData;
    default:
        return eng_NoData;
    }
}

void PlainText::initCommonEN()
{
    common_[common::toUnderlying(PlainText::General::NO_DATA)]
        = eng_NoData;
}

void PlainText::initCommonRU()
{
    common_[common::toUnderlying(PlainText::General::NO_DATA)]
        = rus_NoData;
}

} // namespace global
} // namespace game
