
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAIN_TEXT_HPP
#define PLAIN_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace global {

class PlainText {
public:
    using text_t            = common::Text;
    using language_t        = global::PlainTextBase::Language;

private:
    static constexpr auto sizeLang_{ global::PlainTextBase::sizeLang_ };

public:
    PlainText() noexcept {}

    PlainText(const PlainText&) = delete;
    PlainText& operator=(const PlainText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static const text_t& language(language_t lang) noexcept;

private:
    static void initLanguage();

private:
    static PlainTextBase                            base_;
    static std::array<text_t, sizeLang_>            lang_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const PlainText::text_t& PlainText::language(language_t lang) noexcept
{
    assert(common::isValidEnum(lang));
    return lang_[common::toUnderlying(lang)];
}

} // namespace global
} // namespace game

#endif // !PLAIN_TEXT_HPP
