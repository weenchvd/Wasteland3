
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_SQUAD_TEXT_HPP
#define MENU_SQUAD_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuSquadTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuSquadText;

private:
    MenuSquadTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& squad() const noexcept { return squad_[li()]; }

    const text_t& member() const noexcept { return member_[li()]; }

    const text_t& emptySlot() const noexcept { return emptySlot_[li()]; }

    const text_t& selectCharacter() const noexcept { return selectCharacter_[li()]; }

private:
    language_bundle_t squad_;
    language_bundle_t member_;
    language_bundle_t emptySlot_;
    language_bundle_t selectCharacter_;
};

///************************************************************************************************

struct MenuSquadTextMain {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuSquadText;

private:
    MenuSquadTextMain() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showMembers() const noexcept { return showMembers_[li()]; }

    const text_t& enterCharacter() const noexcept { return enterCharacter_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showMembers_;
    language_bundle_t enterCharacter_;
};

///************************************************************************************************

class MenuSquadText {
private:
    MenuSquadText() noexcept {}

public:
    MenuSquadText(const MenuSquadText&) = delete;
    MenuSquadText& operator=(const MenuSquadText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuSquadTextCommon& common() noexcept { return common_; }

    static const MenuSquadTextMain& main() noexcept { return main_; }

private:
    static void initCommon();

    static void initMain();

private:
    static global::PlainTextBase                    base_;
    static MenuSquadTextCommon                      common_;
    static MenuSquadTextMain                        main_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuSquadTextCommon::language_index_t MenuSquadTextCommon::li() const noexcept
{
    return { MenuSquadText::languageIndex() };
}

inline MenuSquadTextMain::language_index_t MenuSquadTextMain::li() const noexcept
{
    return { MenuSquadText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_SQUAD_TEXT_HPP
