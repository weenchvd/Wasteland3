
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_MAIN_TEXT_HPP
#define MENU_MAIN_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>

namespace game {
namespace menu {

struct MenuMainTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class MenuMainText;

public:
    MenuMainTextCommon() noexcept {}

    const text& menuName() const noexcept;

    const text& exit() const noexcept;

    const text& enterOptions() const noexcept;

    const text& enterSquad() const noexcept;

    const text& enterInventory() const noexcept;

    const text& enterShop() const noexcept;

    const text& enterTrade() const noexcept;

private:
    language_bundle menuName_;
    language_bundle exit_;
    language_bundle enterOpt_;
    language_bundle enterSquad_;
    language_bundle enterInvent_;
    language_bundle enterShop_;
    language_bundle enterTrade_;
};

///************************************************************************************************

class MenuMainText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    MenuMainText() noexcept {}

    MenuMainText(const MenuMainText&) = delete;
    MenuMainText& operator=(const MenuMainText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const MenuMainTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initCommon();

private:
    static common::ObserverDLL<void, language>      langObs_;

    static MenuMainTextCommon                       common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const MenuMainTextCommon::text& MenuMainTextCommon::menuName() const noexcept
{
    return menuName_[MenuMainText::languageIndex()];
}

inline const MenuMainTextCommon::text& MenuMainTextCommon::exit() const noexcept
{
    return exit_[MenuMainText::languageIndex()];
}

inline const MenuMainTextCommon::text& MenuMainTextCommon::enterOptions() const noexcept
{
    return enterOpt_[MenuMainText::languageIndex()];
}

inline const MenuMainTextCommon::text& MenuMainTextCommon::enterSquad() const noexcept
{
    return enterSquad_[MenuMainText::languageIndex()];
}

inline const MenuMainTextCommon::text& MenuMainTextCommon::enterInventory() const noexcept
{
    return enterInvent_[MenuMainText::languageIndex()];
}

inline const MenuMainTextCommon::text& MenuMainTextCommon::enterShop() const noexcept
{
    return enterShop_[MenuMainText::languageIndex()];
}

inline const MenuMainTextCommon::text& MenuMainTextCommon::enterTrade() const noexcept
{
    return enterTrade_[MenuMainText::languageIndex()];
}

///************************************************************************************************

inline void MenuMainText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace menu
} // namespace game

#endif // !MENU_MAIN_TEXT_HPP
