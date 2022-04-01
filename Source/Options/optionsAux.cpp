
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"optionsAux.hpp"
#include<assert.h>

namespace game {
namespace global {

using namespace std;

vector<OptionLanguageMap::language_pt_t>    OptionLanguageMap::langPT_;
vector<OptionLanguageMap::language_fb_t>    OptionLanguageMap::langFB_;
bool                                        OptionLanguageMap::initialized_{ false };

///************************************************************************************************

void OptionLanguageMap::initialize()
{
    if (isInitialized()) return;

    constexpr auto size{ common::numberOf<language_pt_t>() };
    langPT_.reserve(size);
    langFB_.reserve(size);

    assert(langPT_.empty());
    assert(langFB_.empty());

    add(language_pt_t::EN, language_fb_t::FB_Options_Language_EN);
    add(language_pt_t::RU, language_fb_t::FB_Options_Language_RU);
    constexpr auto added{ 2 };

    // to get an compilation error when the number of languages is changed
    // but this function is not changed
    static_assert(size == added, "");
    assert(langPT_.size() == size);
    assert(langPT_.size() == langFB_.size());

    initialized_ = true;
}

OptionLanguageMap::language_pt_t OptionLanguageMap::toPTLanguage(
    language_fb_t lang) noexcept
{
    assert(isInitialized());
    for (size_t i = 0; i < langFB_.size(); ++i) {
        if (langFB_[i] == lang) return langPT_[i];
    }
    return language_pt_t::INVALID;
}

OptionLanguageMap::language_fb_t OptionLanguageMap::toFBLanguage(
    language_pt_t lang) noexcept
{
    assert(isInitialized());
    for (size_t i = 0; i < langPT_.size(); ++i) {
        if (langPT_[i] == lang) return langFB_[i];
    }
    return language_fb_t::FB_Options_Language_INVALID;
}

void OptionLanguageMap::add(language_pt_t langPT, language_fb_t langFB)
{
    langPT_.push_back(langPT);
    langFB_.push_back(langFB);
}

} // namespace global
} // namespace game
