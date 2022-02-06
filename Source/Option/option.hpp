
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTION_HPP
#define OPTION_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<assert.h>
#include<memory>
#include<utility>

namespace game {
namespace global {

class Factory;

class Option {
public:
    using Language      = global::PlainText::Language;

    friend Factory;

protected:
    Option() noexcept;

public:
    Option(const Option&) = delete;
    Option& operator=(const Option&) = delete;

    bool isModified() const noexcept;

    void accept() noexcept;

    void reject() noexcept;

public:
    global::PlainText::Language getLanguage() const noexcept;

    void setLanguage(global::PlainText::Language lang) noexcept;

    const common::SubjectDLL<void, Language>& languageSubject() const noexcept;

    common::SubjectDLL<void, Language>& languageSubject() noexcept;

private:
    std::pair<Language, bool>                   lang_;
    common::SubjectDLL<void, Language>    langSubj_;
};

///------------------------------------------------------------------------------------------------

inline global::PlainText::Language Option::getLanguage() const noexcept
{
    return lang_.first;
}

inline void Option::setLanguage(global::PlainText::Language lang) noexcept
{
    assert(common::isValidEnum(lang));
    lang_ = { lang, true };
}

inline const common::SubjectDLL<void, global::PlainText::Language>&
    Option::languageSubject() const noexcept
{
    return langSubj_;
}

inline common::SubjectDLL<void, global::PlainText::Language>&
    Option::languageSubject() noexcept
{
    return langSubj_;
}

} // namespace global
} // namespace game

#endif // !OPTION_HPP
