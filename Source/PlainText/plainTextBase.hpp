
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAIN_TEXT_BASE_HPP
#define PLAIN_TEXT_BASE_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainTextCommon.hpp"
#include<type_traits>

namespace game {
namespace global {

class PlainTextBase {
public:
    using Language              = PlainText__Language;
    using language_index_t      = std::underlying_type_t<Language>;

    static constexpr auto sizeLang_{ common::numberOf<PlainTextBase::Language>() };

public:
    PlainTextBase() noexcept {}

    PlainTextBase(const PlainTextBase&) = delete;
    PlainTextBase& operator=(const PlainTextBase&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

private:
    static void setLanguage(Language lang) noexcept;

private:
    static common::ObserverDLL<void, Language>      langObs_;
    static language_index_t                         langIndex_;
    static bool                                     initialized_;
};

} // namespace global
} // namespace game

#endif // !PLAIN_TEXT_BASE_HPP
