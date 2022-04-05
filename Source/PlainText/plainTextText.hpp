
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAIN_TEXT_TEXT_HPP
#define PLAIN_TEXT_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include"plainTextTextFB_generated.h"
#include<array>

namespace game {
namespace global {

class PlainTextTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class PlainTextText;

private:
    PlainTextTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& price() const noexcept { return price_[li()]; }

private:
    language_bundle_t price_;
};

///************************************************************************************************

class PlainTextText {
private:
    friend class PlainText;

private:
    PlainTextText() noexcept {}

public:
    PlainTextText(const PlainTextText&) = delete;
    PlainTextText& operator=(const PlainTextText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const PlainTextTextCommon& common() noexcept { return common_; }

private:
    static void initCommon(const fbPlainText::FB_PlainTextTextCommon* fb);

private:
    static global::PlainTextBase                    base_;
    static PlainTextTextCommon                      common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline PlainTextTextCommon::language_index_t PlainTextTextCommon::li() const noexcept
{
    return { PlainTextText::languageIndex() };
}

} // namespace global
} // namespace game

#endif // !PLAIN_TEXT_TEXT_HPP
