
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_INVENTORY_TEXT_HPP
#define MENU_INVENTORY_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>

namespace game {
namespace menu {

struct MenuInventoryTextCommon {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

    friend class MenuInventoryText;

public:
    MenuInventoryTextCommon() noexcept {}

    const text& menuName() const noexcept;

    const text& showMoney() const noexcept;

    const text& showItems() const noexcept;

    const text& showAllItems() const noexcept;

    const text& showItemsOfType() const noexcept;

    const text& enterItemMenu() const noexcept;

    const text& markAllAsViewed() const noexcept;

    const text& money() const noexcept;

    const text& inventory() const noexcept;

    const text& starNewItems() const noexcept;

    const text& shop() const noexcept;

    const text& item() const noexcept;

    const text& typesOfItems() const noexcept;

    const text& enterItemNumber() const noexcept;

    const text& listIsOutdated() const noexcept;

private:
    language_bundle menuName_;
    language_bundle showMoney_;
    language_bundle showItems_;
    language_bundle showAllItems_;
    language_bundle showItemsOfType_;
    language_bundle enterItem_;
    language_bundle markAllAsViewed_;
    language_bundle money_;
    language_bundle inventory_;
    language_bundle starNewItems_;
    language_bundle shop_;
    language_bundle item_;
    language_bundle typesOfItems_;
    language_bundle enterItemNumber_;
    language_bundle listIsOutdated_;
};

///************************************************************************************************

class MenuInventoryText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    MenuInventoryText() noexcept {}

    MenuInventoryText(const MenuInventoryText&) = delete;
    MenuInventoryText& operator=(const MenuInventoryText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static auto languageIndex() noexcept { return langIndex_; }

    static const MenuInventoryTextCommon& common() noexcept { return common_; }

private:
    static void setLanguage(language lang) noexcept;

    static void initCommon();

private:
    static common::ObserverDLL<void, language>      langObs_;

    static MenuInventoryTextCommon                       common_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::menuName() const noexcept
{
    return menuName_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::showMoney() const noexcept
{
    return showMoney_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::showItems() const noexcept
{
    return showItems_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::showAllItems() const noexcept
{
    return showAllItems_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::showItemsOfType() const noexcept
{
    return showItemsOfType_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::enterItemMenu() const noexcept
{
    return enterItem_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::markAllAsViewed() const noexcept
{
    return markAllAsViewed_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::money() const noexcept
{
    return money_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::inventory() const noexcept
{
    return inventory_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::starNewItems() const noexcept
{
    return starNewItems_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::shop() const noexcept
{
    return shop_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::item() const noexcept
{
    return item_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::typesOfItems() const noexcept
{
    return typesOfItems_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::enterItemNumber() const noexcept
{
    return enterItemNumber_[MenuInventoryText::languageIndex()];
}

inline const MenuInventoryTextCommon::text& MenuInventoryTextCommon::listIsOutdated() const noexcept
{
    return listIsOutdated_[MenuInventoryText::languageIndex()];
}

///************************************************************************************************

inline void MenuInventoryText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace menu
} // namespace game

#endif // !MENU_INVENTORY_TEXT_HPP
