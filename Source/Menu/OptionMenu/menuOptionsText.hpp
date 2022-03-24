
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_OPTIONS_TEXT_HPP
#define MENU_OPTIONS_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>

namespace game {
namespace menu {

struct MenuOptionsTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class MenuOptionsText;

public:
    MenuOptionsTextCommon() noexcept {}

    const text& menuName() const noexcept;

    const text& enterGeneral() const noexcept;

    const text& questionSaveChanges() const noexcept;

    const text& saveChanges() const noexcept;

    const text& cancelChanges() const noexcept;

private:
    language_bundle menuName_;
    language_bundle enterGeneral_;
    language_bundle questionSaveChanges_;
    language_bundle saveChanges_;
    language_bundle cancelChanges_;
};

///************************************************************************************************

struct MenuOptionsTextGeneral {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class MenuOptionsText;

public:
    MenuOptionsTextGeneral() noexcept {}

    const text& menuName() const noexcept;

    const text& currentLanguage() const noexcept;

    const text& changeLanguage() const noexcept;

private:
    language_bundle menuName_;
    language_bundle currentLanguage_;
    language_bundle changeLanguage_;
};

///************************************************************************************************

struct MenuOptionsTextAux {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class MenuOptionsText;

public:
    MenuOptionsTextAux() noexcept {}

    const text& languages() const noexcept;

    const text& selectLanguage() const noexcept;

private:
    language_bundle languages_;
    language_bundle selectLanguage_;
};

///************************************************************************************************

class MenuOptionsText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    MenuOptionsText() noexcept {}

    MenuOptionsText(const MenuOptionsText&) = delete;
    MenuOptionsText& operator=(const MenuOptionsText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const MenuOptionsTextCommon& common() noexcept { return common_; }

    static const MenuOptionsTextGeneral& general() noexcept { return general_; }

    static const MenuOptionsTextAux& aux() noexcept { return aux_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initCommon();

    static void initGeneral();

    static void initAux();

private:
    static common::ObserverDLL<void, language>      langObs_;

    static MenuOptionsTextCommon                    common_;
    static MenuOptionsTextGeneral                   general_;
    static MenuOptionsTextAux                       aux_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const MenuOptionsTextCommon::text& MenuOptionsTextCommon::menuName() const noexcept
{
    return menuName_[MenuOptionsText::languageIndex()];
}

inline const MenuOptionsTextCommon::text& MenuOptionsTextCommon::enterGeneral() const noexcept
{
    return enterGeneral_[MenuOptionsText::languageIndex()];
}

inline const MenuOptionsTextCommon::text& MenuOptionsTextCommon::questionSaveChanges() const noexcept
{
    return questionSaveChanges_[MenuOptionsText::languageIndex()];
}

inline const MenuOptionsTextCommon::text& MenuOptionsTextCommon::saveChanges() const noexcept
{
    return saveChanges_[MenuOptionsText::languageIndex()];
}

inline const MenuOptionsTextCommon::text& MenuOptionsTextCommon::cancelChanges() const noexcept
{
    return cancelChanges_[MenuOptionsText::languageIndex()];
}

///************************************************************************************************

inline const MenuOptionsTextGeneral::text& MenuOptionsTextGeneral::menuName() const noexcept
{
    return menuName_[MenuOptionsText::languageIndex()];
}

inline const MenuOptionsTextGeneral::text& MenuOptionsTextGeneral::currentLanguage() const noexcept
{
    return currentLanguage_[MenuOptionsText::languageIndex()];
}

inline const MenuOptionsTextGeneral::text& MenuOptionsTextGeneral::changeLanguage() const noexcept
{
    return changeLanguage_[MenuOptionsText::languageIndex()];
}

///************************************************************************************************

inline const MenuOptionsTextAux::text& MenuOptionsTextAux::languages() const noexcept
{
    return languages_[MenuOptionsText::languageIndex()];
}

inline const MenuOptionsTextAux::text& MenuOptionsTextAux::selectLanguage() const noexcept
{
    return selectLanguage_[MenuOptionsText::languageIndex()];
}

///************************************************************************************************

inline void MenuOptionsText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace menu
} // namespace game

#endif // !MENU_OPTIONS_TEXT_HPP
