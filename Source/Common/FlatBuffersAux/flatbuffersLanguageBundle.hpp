
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FLATBUFFERS_LANGUAGE_BUNDLE_HPP
#define FLATBUFFERS_LANGUAGE_BUNDLE_HPP

#include"common.hpp"
#include"languageBundleFB_generated.h"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace common {

// @brief Initialize all languages
void initLanguageBundle(
    const fbCommon::FB_LanguageBundle* bundle,
    std::array<common::Text, global::PlainTextBase::sizeLang_>& target
);

} // namespace common
} // namespace game

#endif // !FLATBUFFERS_LANGUAGE_BUNDLE_HPP
