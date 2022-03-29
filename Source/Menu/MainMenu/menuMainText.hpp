
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_MAIN_TEXT_HPP
#define MENU_MAIN_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuMainTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuMainText;

private:
    MenuMainTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& exit() const noexcept { return exit_[li()]; }

    const text_t& enterOptions() const noexcept { return enterOpt_[li()]; }

    const text_t& enterSquad() const noexcept { return enterSquad_[li()]; }

    const text_t& enterInventory() const noexcept { return enterInvent_[li()]; }

    const text_t& enterShop() const noexcept { return enterShop_[li()]; }

    const text_t& enterTrade() const noexcept { return enterTrade_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t exit_;
    language_bundle_t enterOpt_;
    language_bundle_t enterSquad_;
    language_bundle_t enterInvent_;
    language_bundle_t enterShop_;
    language_bundle_t enterTrade_;
};

///************************************************************************************************

class MenuMainText {
private:
    MenuMainText() noexcept {}

public:
    MenuMainText(const MenuMainText&) = delete;
    MenuMainText& operator=(const MenuMainText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuMainTextCommon& common() noexcept { return common_; }

private:
    static void initCommon();

private:
    static global::PlainTextBase                    base_;
    static MenuMainTextCommon                       common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuMainTextCommon::language_index_t MenuMainTextCommon::li() const noexcept
{
    return { MenuMainText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_MAIN_TEXT_HPP
