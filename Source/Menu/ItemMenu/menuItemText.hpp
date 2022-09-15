
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ITEM_TEXT_HPP
#define MENU_ITEM_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuItemTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuItemText;

private:
    MenuItemTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showFullDescription() const noexcept { return showFullDescr_[li()]; }

    const text_t& questionDeleteItem() const noexcept { return questionDelete_[li()]; }

    const text_t& equip() const noexcept { return equip_[li()]; }

    const text_t& unequip() const noexcept { return unequip_[li()]; }

    const text_t& modify() const noexcept { return modify_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showFullDescr_;
    language_bundle_t questionDelete_;
    language_bundle_t equip_;
    language_bundle_t unequip_;
    language_bundle_t modify_;
};

///************************************************************************************************

struct MenuItemTextModify {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuItemText;

private:
    MenuItemTextModify() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& item() const noexcept { return item_[li()]; }

    const text_t& mods() const noexcept { return mods_[li()]; }

    const text_t& installMod() const noexcept { return installMod_[li()]; }

    const text_t& removeMod() const noexcept { return removeMod_[li()]; }

    const text_t& enterSlotNumber() const noexcept { return enterSlotNumber_[li()]; }

    const text_t& unsuitableMod() const noexcept { return unsuitableMod_[li()]; }

    const text_t& showFullDescrOfMod() const noexcept { return showFullDescrOfMod_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t item_;
    language_bundle_t mods_;
    language_bundle_t installMod_;
    language_bundle_t removeMod_;
    language_bundle_t enterSlotNumber_;
    language_bundle_t unsuitableMod_;
    language_bundle_t showFullDescrOfMod_;
};

///************************************************************************************************

class MenuItemText {
private:
    MenuItemText() noexcept {}

public:
    MenuItemText(const MenuItemText&) = delete;
    MenuItemText& operator=(const MenuItemText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuItemTextCommon& common() noexcept { return common_; }

    static const MenuItemTextModify& modify() noexcept { return modify_; }

private:
    static void initCommon();

    static void initModify();

private:
    static global::PlainTextBase                    base_;
    static MenuItemTextCommon                       common_;
    static MenuItemTextModify                       modify_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuItemTextCommon::language_index_t MenuItemTextCommon::li() const noexcept
{
    return { MenuItemText::languageIndex() };
}

inline MenuItemTextModify::language_index_t MenuItemTextModify::li() const noexcept
{
    return { MenuItemText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_ITEM_TEXT_HPP
