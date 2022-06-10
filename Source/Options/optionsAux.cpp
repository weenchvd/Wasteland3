
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

OptionLanguageMap::lang_map_t               OptionLanguageMap::langMap_;
bool                                        OptionLanguageMap::initialized_{ false };

///************************************************************************************************

void OptionLanguageMap::initialize()
{
    if (isInitialized()) return;

    constexpr auto size{ common::numberOf<language_pt_t>() };

    assert(langMap_.empty());

    add(language_pt_t::EN, language_fb_t::FB_Options_Language_EN);
    add(language_pt_t::RU, language_fb_t::FB_Options_Language_RU);
    constexpr auto added{ 2 };

    // to get an compilation error when the number of languages is changed
    // but this function is not changed
    static_assert(size == added, "");
    assert(langMap_.size() == size);

    initialized_ = true;
}

OptionLanguageMap::language_pt_t OptionLanguageMap::toPTLanguage(
    language_fb_t lang) noexcept
{
    assert(isInitialized());
    lang_map_t::right_map::const_iterator iter{ langMap_.right.find(lang) };
    if (iter != langMap_.right.end()) {
        return iter->second;
    }
    return language_pt_t::INVALID;
}

OptionLanguageMap::language_fb_t OptionLanguageMap::toFBLanguage(
    language_pt_t lang) noexcept
{
    assert(isInitialized());
    lang_map_t::left_map::const_iterator iter{ langMap_.left.find(lang) };
    if (iter != langMap_.left.end()) {
        return iter->second;
    }
    return language_fb_t::FB_Options_Language_INVALID;
}

void OptionLanguageMap::add(language_pt_t langPT, language_fb_t langFB)
{
    langMap_.insert(lang_map_t::value_type(langPT, langFB));
}

} // namespace global
} // namespace game
