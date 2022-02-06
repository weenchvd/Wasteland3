
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include"option.hpp"
#include<type_traits>

namespace game {
namespace global {

using namespace std;
using global::PlainText;
using global::Locator;

Option::Option() noexcept
    :
    lang_           { Language::EN, false }
{}

bool Option::isModified() const noexcept
{
    return lang_.second;
}

void Option::accept() noexcept
{
    if (lang_.second) {
        Locator::getPlainText().setLanguage(lang_.first);
        langSubj_.notify(lang_.first);
        lang_.second = false;
    }
}

void Option::reject() noexcept
{
    if (lang_.second) {
        lang_ = { Locator::getPlainText().getLanguage(), false };
    }
}

} // namespace global
} // namespace game
