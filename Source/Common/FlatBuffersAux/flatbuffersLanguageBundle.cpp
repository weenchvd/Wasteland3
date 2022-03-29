
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersLanguageBundle.hpp"
#include<assert.h>
#include<type_traits>

namespace game {
namespace common {

using namespace std;

void initLanguageBundle(
    const fbCommon::FB_LanguageBundle* bundle,
    array<common::Text, global::PlainTextBase::sizeLang_>& target
)
{
    using lang = global::PlainTextBase::Language;
    using text = common::Text;
    assert(bundle != nullptr);

    assert(bundle->en() != nullptr);
    target[common::toUnderlying(lang::EN)] = move(text{ bundle->en()->c_str() });
    assert(bundle->ru() != nullptr);
    target[common::toUnderlying(lang::RU)] = move(text{ bundle->ru()->c_str() });
}

} // namespace common
} // namespace game
