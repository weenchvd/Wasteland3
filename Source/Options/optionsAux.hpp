
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTIONS_AUX_HPP
#define OPTIONS_AUX_HPP

#include"boost/bimap.hpp"
#include"optionsFB_generated.h"
#include"plainTextBase.hpp"

namespace game {
namespace global {

class OptionLanguageMap {
public:
    using language_pt_t = global::PlainTextBase::Language;
    using language_fb_t = fbOptions::FB_Options_Language;
    using lang_map_t    = boost::bimap<language_pt_t, language_fb_t>;

public:
    OptionLanguageMap() noexcept {}

    OptionLanguageMap(const OptionLanguageMap&) = delete;
    OptionLanguageMap& operator=(const OptionLanguageMap&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static language_pt_t toPTLanguage(language_fb_t lang) noexcept;

    static language_fb_t toFBLanguage(language_pt_t lang) noexcept;

private:
    static void add(language_pt_t langPT, language_fb_t langFB);

private:
    static lang_map_t                               langMap_;
    static bool                                     initialized_;
};

} // namespace global
} // namespace game

#endif // !OPTIONS_AUX_HPP
