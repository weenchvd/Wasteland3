
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

    const text_t& saveGame() const noexcept { return saveGame_[li()]; }

    const text_t& loadGame() const noexcept { return loadGame_[li()]; }

    const text_t& gameSaved() const noexcept { return gameSaved_[li()]; }

    const text_t& gameNotSaved() const noexcept { return gameNotSaved_[li()]; }

    const text_t& gameLoaded() const noexcept { return gameLoaded_[li()]; }

    const text_t& gameNotLoaded() const noexcept { return gameNotLoaded_[li()]; }

    const text_t& fileList() const noexcept { return fileList_[li()]; }

    const text_t& fileNotSelected() const noexcept { return fileNotSelected_[li()]; }

    const text_t& filenameNotSpec() const noexcept { return filenameNotSpec_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t exit_;
    language_bundle_t enterOpt_;
    language_bundle_t enterSquad_;
    language_bundle_t enterInvent_;
    language_bundle_t enterShop_;
    language_bundle_t enterTrade_;
    language_bundle_t saveGame_;
    language_bundle_t loadGame_;
    language_bundle_t gameSaved_;
    language_bundle_t gameNotSaved_;
    language_bundle_t gameLoaded_;
    language_bundle_t gameNotLoaded_;
    language_bundle_t fileList_;
    language_bundle_t fileNotSelected_;
    language_bundle_t filenameNotSpec_;
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
