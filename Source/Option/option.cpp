
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"option.hpp"
#include<assert.h>

namespace game {
namespace global {

using namespace std;

OptionLanguage::OptionLanguage() noexcept
    :
    subj_           {},
    curLang_        { language::EN },
    prevLang_       { language::EN }
{}

void OptionLanguage::accept() noexcept
{
    if (isModified() == true) {
        prevLang_ = curLang_;
    }
}

void OptionLanguage::reject() noexcept
{
    if (isModified() == true) {
        curLang_ = prevLang_;
        subj_.notify(curLang_);
    }
}

void OptionLanguage::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    if (curLang_ != lang) {
        curLang_ = lang;
        subj_.notify(curLang_);
    }
}

///************************************************************************************************

bool Options::isModified() const noexcept
{
    return optLang_.isModified();
}

void Options::acceptAll() noexcept
{
    optLang_.accept();
}

void Options::rejectAll() noexcept
{
    optLang_.reject();
}

} // namespace global
} // namespace game
