
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ITEM_TEXT_HPP
#define MENU_ITEM_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>

namespace game {
namespace menu {

struct MenuItemTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class MenuItemText;

public:
    MenuItemTextCommon() noexcept {}

    const text& menuName() const noexcept;

    const text& showFullDescription() const noexcept;

    const text& questionDeleteItem() const noexcept;

    const text& equip() const noexcept;

    const text& modify() const noexcept;

private:
    language_bundle menuName_;
    language_bundle showFullDescr_;
    language_bundle questionDelete_;
    language_bundle equip_;
    language_bundle modify_;
};

///************************************************************************************************

class MenuItemText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    MenuItemText() noexcept {}

    MenuItemText(const MenuItemText&) = delete;
    MenuItemText& operator=(const MenuItemText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const MenuItemTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initCommon();

private:
    static common::ObserverDLL<void, language>      langObs_;

    static MenuItemTextCommon                       common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const MenuItemTextCommon::text& MenuItemTextCommon::menuName() const noexcept
{
    return menuName_[MenuItemText::languageIndex()];
}

inline const MenuItemTextCommon::text& MenuItemTextCommon::showFullDescription() const noexcept
{
    return showFullDescr_[MenuItemText::languageIndex()];
}

inline const MenuItemTextCommon::text& MenuItemTextCommon::questionDeleteItem() const noexcept
{
    return questionDelete_[MenuItemText::languageIndex()];
}

inline const MenuItemTextCommon::text& MenuItemTextCommon::equip() const noexcept
{
    return equip_[MenuItemText::languageIndex()];
}

inline const MenuItemTextCommon::text& MenuItemTextCommon::modify() const noexcept
{
    return modify_[MenuItemText::languageIndex()];
}

///************************************************************************************************

inline void MenuItemText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace menu
} // namespace game

#endif // !MENU_ITEM_TEXT_HPP
