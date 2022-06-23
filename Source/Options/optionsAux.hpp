
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTIONS_AUX_HPP
#define OPTIONS_AUX_HPP

#include"bidirectionalMap.hpp"
#include"optionsFB_generated.h"
#include"plainTextBase.hpp"

namespace game {
namespace global {

using OptionLanguageBiMap = common::BidirectionalMap<
    global::PlainTextBase::Language, global::PlainTextBase::Language::__INVALID,
    fbOptions::FB_Options_Language, fbOptions::FB_Options_Language::FB_Options_Language_INVALID
>;

} // namespace global
} // namespace game

#endif // !OPTIONS_AUX_HPP
