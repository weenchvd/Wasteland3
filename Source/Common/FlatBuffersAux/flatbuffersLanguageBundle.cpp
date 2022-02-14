
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersLanguageBundle.hpp"
#include<type_traits>

namespace game {
namespace common {

using namespace std;

void initLanguageBundle(
    const fbCommon::FB_LanguageBundle* bundle,
    array<common::Text, global::PlainText::sizeLang_>& target
)
{
    using lang = global::PlainText::Language;
    using text = common::Text;
    target[common::toUnderlying(lang::EN)] = move(text{ bundle->en()->c_str() });
    target[common::toUnderlying(lang::RU)] = move(text{ bundle->ru()->c_str() });
}

} // namespace common
} // namespace game