
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include"observerDLL.hpp"
#include"optionsFB_generated.h"
#include"plainTextBase.hpp"

namespace game {
namespace global {

class OptionLanguage {
public:
    using language_t = global::PlainTextBase::Language;

    friend class Options;

private:
    OptionLanguage() noexcept;

public:
    OptionLanguage(const OptionLanguage&) = delete;
    OptionLanguage& operator=(const OptionLanguage&) = delete;

    bool isModified() const noexcept { return curLang_ != prevLang_; }

    bool accept() noexcept;

    void reject() noexcept;

public:
    language_t getLanguage() const noexcept { return curLang_; }

    void setLanguage(language_t lang) noexcept;

    const common::SubjectDLL<void, language_t>& languageSubject() const noexcept { return subj_; }

    common::SubjectDLL<void, language_t>& languageSubject() noexcept { return subj_; }

private:
    common::SubjectDLL<void, language_t>    subj_;
    language_t                              curLang_;
    language_t                              prevLang_;
};

///************************************************************************************************

class Options {
private:
    static constexpr char* optionsJSONFileName_ { u8"config.json" };
    static constexpr char* optionsBinFileName_  { u8"config" };

    friend class Factory;

private:
    Options();

public:
    Options(const Options&) = delete;
    Options& operator=(const Options&) = delete;

    static void initialize();

    bool isModified() const noexcept;

    void acceptAll() noexcept;

    void rejectAll() noexcept;

    bool saveOptionsToFiles();

    bool loadOptionsFromFiles();

private:
    bool saveOptionsToJSON();

    bool saveOptionsToBin();

    flatbuffers::FlatBufferBuilder saveOptions();

    bool loadOptionsFromJSON();

    bool loadOptionsFromBin();

    bool loadOptions(const fbOptions::FB_Options* fb);

public:
    const OptionLanguage& optLanguage() const noexcept { return optLang_; }

    OptionLanguage& optLanguage() noexcept { return optLang_; }

private:
    OptionLanguage                  optLang_;
};

} // namespace global
} // namespace game

#endif // !OPTIONS_HPP
