
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_OPTIONS_TEXT_HPP
#define MENU_OPTIONS_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuOptionsTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuOptionsText;

private:
    MenuOptionsTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& enterGeneral() const noexcept { return enterGeneral_[li()]; }

    const text_t& questionSaveChanges() const noexcept { return questionSaveChanges_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t enterGeneral_;
    language_bundle_t questionSaveChanges_;
};

///************************************************************************************************

struct MenuOptionsTextGeneral {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuOptionsText;

private:
    MenuOptionsTextGeneral() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& language() const noexcept { return language_[li()]; }

    const text_t& currentLanguage() const noexcept { return currentLanguage_[li()]; }

    const text_t& changeLanguage() const noexcept { return changeLanguage_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t language_;
    language_bundle_t currentLanguage_;
    language_bundle_t changeLanguage_;
};

///************************************************************************************************

struct MenuOptionsTextAux {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuOptionsText;

private:
    MenuOptionsTextAux() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& languages() const noexcept { return languages_[li()]; }

    const text_t& selectLanguage() const noexcept { return selectLanguage_[li()]; }

private:
    language_bundle_t languages_;
    language_bundle_t selectLanguage_;
};

///************************************************************************************************

class MenuOptionsText {
private:
    MenuOptionsText() noexcept {}

public:
    MenuOptionsText(const MenuOptionsText&) = delete;
    MenuOptionsText& operator=(const MenuOptionsText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuOptionsTextCommon& common() noexcept { return common_; }

    static const MenuOptionsTextGeneral& general() noexcept { return general_; }

    static const MenuOptionsTextAux& aux() noexcept { return aux_; }

private:
    static void initCommon();

    static void initGeneral();

    static void initAux();

private:
    static global::PlainTextBase                    base_;
    static MenuOptionsTextCommon                    common_;
    static MenuOptionsTextGeneral                   general_;
    static MenuOptionsTextAux                       aux_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuOptionsTextCommon::language_index_t MenuOptionsTextCommon::li() const noexcept
{
    return { MenuOptionsText::languageIndex() };
}

inline MenuOptionsTextGeneral::language_index_t MenuOptionsTextGeneral::li() const noexcept
{
    return { MenuOptionsText::languageIndex() };
}

inline MenuOptionsTextAux::language_index_t MenuOptionsTextAux::li() const noexcept
{
    return { MenuOptionsText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_OPTIONS_TEXT_HPP
