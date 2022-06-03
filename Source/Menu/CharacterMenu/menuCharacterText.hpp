
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_CHARACTER_TEXT_HPP
#define MENU_CHARACTER_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuCharacterTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuCharacterText;

private:
    MenuCharacterTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& gear() const noexcept { return gear_[li()]; }

    const text_t& emptySlot() const noexcept { return emptySlot_[li()]; }

    const text_t& weapon() const noexcept { return weapon_[li()]; }

private:
    language_bundle_t gear_;
    language_bundle_t emptySlot_;
    language_bundle_t weapon_;
};

///************************************************************************************************

struct MenuCharacterTextMain {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuCharacterText;

private:
    MenuCharacterTextMain() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showStats() const noexcept { return showStats_[li()]; }

    const text_t& showGear() const noexcept { return showGear_[li()]; }

    const text_t& showAttributes() const noexcept { return showAttributes_[li()]; }

    const text_t& enterAttrMenu() const noexcept { return enterAttrMenu_[li()]; }

    const text_t& showSkills() const noexcept { return showSkills_[li()]; }

    const text_t& enterSkillMenu() const noexcept { return enterSkillMenu_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showStats_;
    language_bundle_t showGear_;
    language_bundle_t showAttributes_;
    language_bundle_t enterAttrMenu_;
    language_bundle_t showSkills_;
    language_bundle_t enterSkillMenu_;
};

///************************************************************************************************

class MenuCharacterText {
private:
    MenuCharacterText() noexcept {}

public:
    MenuCharacterText(const MenuCharacterText&) = delete;
    MenuCharacterText& operator=(const MenuCharacterText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuCharacterTextCommon& common() noexcept { return common_; }

    static const MenuCharacterTextMain& main() noexcept { return main_; }

private:
    static void initCommon();

    static void initMain();

private:
    static global::PlainTextBase                    base_;
    static MenuCharacterTextCommon                  common_;
    static MenuCharacterTextMain                    main_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuCharacterTextCommon::language_index_t MenuCharacterTextCommon::li() const noexcept
{
    return { MenuCharacterText::languageIndex() };
}

inline MenuCharacterTextMain::language_index_t MenuCharacterTextMain::li() const noexcept
{
    return { MenuCharacterText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_CHARACTER_TEXT_HPP
