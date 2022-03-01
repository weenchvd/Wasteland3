
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_TEXT_HPP
#define AMMO_TEXT_HPP

#include"ammoCommon.hpp"
#include"ammoTextFB_generated.h"
#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

struct AmmoTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class AmmoText;

public:
    AmmoTextCommon() noexcept {}

    const text& itemType() const noexcept;

    const text& quantity() const noexcept;

private:
    language_bundle itemType_;
    language_bundle qty_;
};

///************************************************************************************************

class AmmoText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_     { global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    AmmoText() noexcept {}

    AmmoText(const AmmoText&) = delete;
    AmmoText& operator=(const AmmoText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const AmmoTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initCommon(const fbAmmo::FB_AmmoTextCommon* fb);

private:
    static common::ObserverDLL<void, language>      langObs_;

    static AmmoTextCommon                           common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const AmmoTextCommon::text& AmmoTextCommon::itemType() const noexcept
{
    return itemType_[AmmoText::languageIndex()];
}

inline const AmmoTextCommon::text& AmmoTextCommon::quantity() const noexcept
{
    return qty_[AmmoText::languageIndex()];
}

///************************************************************************************************

inline void AmmoText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !AMMO_TEXT_HPP
