
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_INVENTORY_TEXT_HPP
#define MENU_INVENTORY_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuInventoryTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuInventoryText;

private:
    MenuInventoryTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showMoney() const noexcept { return showMoney_[li()]; }

    const text_t& showItems() const noexcept { return showItems_[li()]; }

    const text_t& showAllItems() const noexcept { return showAllItems_[li()]; }

    const text_t& showItemsOfType() const noexcept { return showItemsOfType_[li()]; }

    const text_t& showStats() const noexcept { return showStats_[li()]; }

    const text_t& hideStats() const noexcept { return hideStats_[li()]; }

    const text_t& enterItemMenu() const noexcept { return enterItem_[li()]; }

    const text_t& markAllAsViewed() const noexcept { return markAllAsViewed_[li()]; }

    const text_t& money() const noexcept { return money_[li()]; }

    const text_t& inventory() const noexcept { return inventory_[li()]; }

    const text_t& starNewItems() const noexcept { return starNewItems_[li()]; }

    const text_t& colorNewItems() const noexcept { return colorNewItems_[li()]; }

    const text_t& shop() const noexcept { return shop_[li()]; }

    const text_t& item() const noexcept { return item_[li()]; }

    const text_t& typesOfItems() const noexcept { return typesOfItems_[li()]; }

    const text_t& enterItemNumber() const noexcept { return enterItemNumber_[li()]; }

    const text_t& listIsOutdated() const noexcept { return listIsOutdated_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showMoney_;
    language_bundle_t showItems_;
    language_bundle_t showAllItems_;
    language_bundle_t showItemsOfType_;
    language_bundle_t showStats_;
    language_bundle_t hideStats_;
    language_bundle_t enterItem_;
    language_bundle_t markAllAsViewed_;
    language_bundle_t money_;
    language_bundle_t inventory_;
    language_bundle_t starNewItems_;
    language_bundle_t colorNewItems_;
    language_bundle_t shop_;
    language_bundle_t item_;
    language_bundle_t typesOfItems_;
    language_bundle_t enterItemNumber_;
    language_bundle_t listIsOutdated_;
};

///************************************************************************************************

class MenuInventoryText {
private:
    MenuInventoryText() noexcept {}

public:
    MenuInventoryText(const MenuInventoryText&) = delete;
    MenuInventoryText& operator=(const MenuInventoryText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuInventoryTextCommon& common() noexcept { return common_; }

private:
    static void initCommon();

private:
    static global::PlainTextBase                    base_;
    static MenuInventoryTextCommon                  common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuInventoryTextCommon::language_index_t MenuInventoryTextCommon::li() const noexcept
{
    return { MenuInventoryText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_INVENTORY_TEXT_HPP
