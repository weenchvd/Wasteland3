
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTION_HPP
#define OPTION_HPP

#include"observerDLL.hpp"
#include"plainText.hpp"

namespace game {
namespace global {

class OptionLanguage {
public:
    using language = global::PlainText::Language;

    friend class Options;

protected:
    OptionLanguage() noexcept;

public:
    OptionLanguage(const OptionLanguage&) = delete;
    OptionLanguage& operator=(const OptionLanguage&) = delete;

    bool isModified() const noexcept { return curLang_ != prevLang_; }

    void accept() noexcept;

    void reject() noexcept;

public:
    language getLanguage() const noexcept { return curLang_; }

    void setLanguage(language lang) noexcept;

    const common::SubjectDLL<void, language>& languageSubject() const noexcept { return subj_; }

    common::SubjectDLL<void, language>& languageSubject() noexcept { return subj_; }

private:
    common::SubjectDLL<void, language>      subj_;
    language                                curLang_;
    language                                prevLang_;
};

///************************************************************************************************

class Options {
public:
    friend class Factory;

protected:
    Options() noexcept {}

public:
    Options(const Options&) = delete;
    Options& operator=(const Options&) = delete;

    bool isModified() const noexcept;

    void acceptAll() noexcept;

    void rejectAll() noexcept;

public:
    const OptionLanguage& optLanguage() const noexcept {
        return optLang_;
    }
    OptionLanguage& optLanguage() noexcept {
        return optLang_;
    }

private:
    OptionLanguage                  optLang_;
};

} // namespace global
} // namespace game

#endif // !OPTION_HPP
