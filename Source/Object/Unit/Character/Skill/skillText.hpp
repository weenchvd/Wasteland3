
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_TEXT_HPP
#define SKILL_TEXT_HPP

#include"common.hpp"
#include"locator.hpp"
#include"observerDLL.hpp"
#include"skillCommon.hpp"
#include"skillTextFB_generated.h"
#include<array>

namespace game {
namespace object {

class SkillText {
public:
    using Text              = common::Text;

    SkillText() noexcept {}

    SkillText(const SkillText&) = delete;
    SkillText& operator=(const SkillText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static const Text& name(Skill__Type id) noexcept;

    static const Text& descr(Skill__Type id) noexcept;

    static const Text& group(Skill__Group id) noexcept;

private:
    static constexpr int sizeLang_      = common::toUnderlying(
        global::PlainText::Language::NUMBER_OF);
    static constexpr int sizeType_      = common::toUnderlying(Skill__Type::NUMBER_OF);
    static constexpr int sizeGroup_     = common::toUnderlying(Skill__Group::NUMBER_OF);

    static void setLanguage(global::PlainText::Language lang);

    static void initLanguage(
        const fbSkill::FB_LanguageBundle* table,
        global::PlainText::Language lang
    );

    static void initByType(
        const fbSkill::FB_SkillTextType* table,
        std::array<Text, sizeType_>& ar
    );

    static void initByGroup(
        const fbSkill::FB_SkillTextGroup* table,
        std::array<Text, sizeGroup_>& ar
    );

private:
    static common::ObserverDLL<void, global::PlainText::Language>   langObs_;

    static std::array<std::array<Text, sizeType_>, sizeLang_>   name_;
    static std::array<std::array<Text, sizeType_>, sizeLang_>   descr_;
    static std::array<std::array<Text, sizeGroup_>, sizeLang_>  group_;

    static std::array<Text, sizeType_>*     ptrName_;
    static std::array<Text, sizeType_>*     ptrDescr_;
    static std::array<Text, sizeGroup_>*    ptrGroup_;

    static bool                             initialized_;
};

} // namespace object
} // namespace game

#endif // !SKILL_TEXT_HPP
