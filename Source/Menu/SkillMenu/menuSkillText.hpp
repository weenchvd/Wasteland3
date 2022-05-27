
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_SKILL_TEXT_HPP
#define MENU_SKILL_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuSkillTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuSkillText;

private:
    MenuSkillTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& skills() const noexcept { return skills_[li()]; }

    const text_t& skillsAccepted() const noexcept { return skillsAccepted_[li()]; }

    const text_t& skillPoints() const noexcept { return skillPoints_[li()]; }

    const text_t& skillPointsAccepted() const noexcept { return skillPointsAccepted_[li()]; }

    const text_t& selectSkill() const noexcept { return selectSkill_[li()]; }

    const text_t& enterNumOfLevels() const noexcept { return enterNumOfLevels_[li()]; }

    const text_t& invalidNumOfLevels() const noexcept { return invalidNumOfLevels_[li()]; }

private:
    language_bundle_t skills_;
    language_bundle_t skillsAccepted_;
    language_bundle_t skillPoints_;
    language_bundle_t skillPointsAccepted_;
    language_bundle_t selectSkill_;
    language_bundle_t enterNumOfLevels_;
    language_bundle_t invalidNumOfLevels_;
};

///************************************************************************************************

struct MenuSkillTextMain {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuSkillText;

private:
    MenuSkillTextMain() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showSkills() const noexcept { return showSkills_[li()]; }

    const text_t& showSkillsAccepted() const noexcept { return showSkillsAccepted_[li()]; }

    const text_t& modify() const noexcept { return modify_[li()]; }

    const text_t& questionSaveChanges() const noexcept { return questionSaveChanges_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showSkills_;
    language_bundle_t showSkillsAccepted_;
    language_bundle_t modify_;
    language_bundle_t questionSaveChanges_;
};

///************************************************************************************************

struct MenuSkillTextModify {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuSkillText;

private:
    MenuSkillTextModify() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showDescription() const noexcept { return showDescription_[li()]; }

    const text_t& increaseLevel() const noexcept { return increaseLevel_[li()]; }

    const text_t& decreaseLevel() const noexcept { return decreaseLevel_[li()]; }

    const text_t& skill() const noexcept { return skill_[li()]; }

    const text_t& skillAccepted() const noexcept { return skillAccepted_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showDescription_;
    language_bundle_t increaseLevel_;
    language_bundle_t decreaseLevel_;
    language_bundle_t skill_;
    language_bundle_t skillAccepted_;
};

///************************************************************************************************

class MenuSkillText {
private:
    MenuSkillText() noexcept {}

public:
    MenuSkillText(const MenuSkillText&) = delete;
    MenuSkillText& operator=(const MenuSkillText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuSkillTextCommon& common() noexcept { return common_; }

    static const MenuSkillTextMain& main() noexcept { return main_; }

    static const MenuSkillTextModify& modify() noexcept { return modify_; }

private:
    static void initCommon();

    static void initMain();

    static void initModify();

private:
    static global::PlainTextBase                    base_;
    static MenuSkillTextCommon                      common_;
    static MenuSkillTextMain                        main_;
    static MenuSkillTextModify                      modify_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuSkillTextCommon::language_index_t MenuSkillTextCommon::li() const noexcept
{
    return { MenuSkillText::languageIndex() };
}

inline MenuSkillTextMain::language_index_t MenuSkillTextMain::li() const noexcept
{
    return { MenuSkillText::languageIndex() };
}

inline MenuSkillTextModify::language_index_t MenuSkillTextModify::li() const noexcept
{
    return { MenuSkillText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_SKILL_TEXT_HPP
