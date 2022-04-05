
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"plainText.hpp"

namespace game {
namespace global {

using namespace std;

PlainTextBase                                   PlainText::base_;
array<PlainText::text_t, PlainText::sizeLang_>  PlainText::lang_;
const PlainTextText                             PlainText::text_;
bool                                            PlainText::initialized_{ false };

///************************************************************************************************

void PlainText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();
    text_.initialize();

    initLanguage();

    initialized_ = true;
}

void PlainText::initLanguage()
{
    lang_[common::toUnderlying(language_t::EN)] = text_t{ u8"ENGLISH" };
    lang_[common::toUnderlying(language_t::RU)] = text_t{ u8"РУССКИЙ" };
}

} // namespace global
} // namespace game
