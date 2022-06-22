
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"optionsAux.hpp"
#include<assert.h>

namespace game {
namespace common {

global::OptionLanguageBiMap::map_t  global::OptionLanguageBiMap::map_;
bool                                global::OptionLanguageBiMap::initialized_{ false };

///************************************************************************************************

void global::OptionLanguageBiMap::init()
{
    using left_t    = global::PlainTextBase::Language;
    using right_t   = fbOptions::FB_Options_Language;

    assert(map_.empty());

    add(left_t::INVALID, right_t::FB_Options_Language_INVALID);

    add(left_t::EN, right_t::FB_Options_Language_EN);
    add(left_t::RU, right_t::FB_Options_Language_RU);
    constexpr auto added{ 3 };

    constexpr auto size{ common::numberOf<left_t>() + 1 }; // '+ 1' is INVALID type
    // to get an compilation error when the number of languages is changed
    // but this function is not changed
    static_assert(size == added, "");
    assert(map_.size() == size);
}

} // namespace common
} // namespace game
