
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"locator.hpp"
#include"plainTextBase.hpp"
#include<assert.h>

namespace game {
namespace global {

using namespace std;

common::ObserverDLL<void, PlainTextBase::Language>  PlainTextBase::langObs_;
PlainTextBase::language_index_t                     PlainTextBase::langIndex_   { 0 };
bool                                                PlainTextBase::initialized_ { false };

///************************************************************************************************

void PlainTextBase::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);
    assert(Locator::isInitialized());
    setLanguage(Locator::getOptions().optLanguage().getLanguage());
    langObs_.getDelegate().bind<&PlainTextBase::setLanguage>();
    Locator::getOptions().optLanguage().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void PlainTextBase::setLanguage(Language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace global
} // namespace game
