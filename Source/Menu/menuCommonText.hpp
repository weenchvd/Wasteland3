
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_COMMON_TEXT_HPP
#define MENU_COMMON_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>

namespace game {
namespace menu {

struct MenuCommonTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class MenuCommonText;

public:
    MenuCommonTextCommon() noexcept {}

    const text& actions() const noexcept;

    const text& exitMenu() const noexcept;

    const text& invalidInput() const noexcept;

    const text& invalidType() const noexcept;

    const text& unknownAction() const noexcept;

    const text& enterAction() const noexcept;

    const text& enterNumber() const noexcept;

    const text& yes() const noexcept;

    const text& no() const noexcept;

    const text& promptSymbol() const noexcept;

    const text& errorSymbol() const noexcept;

private:
    language_bundle actions_;
    language_bundle exitMenu_;
    language_bundle invalidInput_;
    language_bundle invalidType_;
    language_bundle unknownAct_;
    language_bundle enterAct_;
    language_bundle enterNum_;
    language_bundle yes_;
    language_bundle no_;
    language_bundle promptSymbol_;
    language_bundle errorSymbol_;
};

///************************************************************************************************

class MenuCommonText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    MenuCommonText() noexcept {}

    MenuCommonText(const MenuCommonText&) = delete;
    MenuCommonText& operator=(const MenuCommonText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const MenuCommonTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initCommon();

private:
    static common::ObserverDLL<void, language>      langObs_;

    static MenuCommonTextCommon                     common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::actions() const noexcept
{
    return actions_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::exitMenu() const noexcept
{
    return exitMenu_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::invalidInput() const noexcept
{
    return invalidInput_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::invalidType() const noexcept
{
    return invalidType_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::unknownAction() const noexcept
{
    return unknownAct_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::enterAction() const noexcept
{
    return enterAct_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::enterNumber() const noexcept
{
    return enterNum_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::yes() const noexcept
{
    return yes_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::no() const noexcept
{
    return no_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::promptSymbol() const noexcept
{
    return promptSymbol_[MenuCommonText::languageIndex()];
}

inline const MenuCommonTextCommon::text& MenuCommonTextCommon::errorSymbol() const noexcept
{
    return errorSymbol_[MenuCommonText::languageIndex()];
}

///************************************************************************************************

inline void MenuCommonText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace menu
} // namespace game

#endif // !MENU_COMMON_TEXT_HPP
