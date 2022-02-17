
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_TEXT_HPP
#define SKILL_TEXT_HPP

#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include"skillCommon.hpp"
#include"skillTextFB_generated.h"
#include<array>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

class SkillText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_     { global::PlainText::sizeLang_ };
    static constexpr auto sizeType_     { common::toUnderlying(Skill__Type::NUMBER_OF) };
    static constexpr auto sizeGroup_    { common::toUnderlying(Skill__Group::NUMBER_OF) };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    SkillText() noexcept {}

    SkillText(const SkillText&) = delete;
    SkillText& operator=(const SkillText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static const text& name(Skill__Type id) noexcept;

    static const text& descr(Skill__Type id) noexcept;

    static const text& group(Skill__Group id) noexcept;

private:
    static void setLanguage(language lang) noexcept;

    static void initByType(
        const fbSkill::FB_SkillTextType* table,
        std::array<language_bundle, sizeType_>& ar
    );

    static void initByGroup(
        const fbSkill::FB_SkillTextGroup* table,
        std::array<language_bundle, sizeGroup_>& ar
    );

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::array<language_bundle, sizeType_>   name_;
    static std::array<language_bundle, sizeType_>   descr_;
    static std::array<language_bundle, sizeGroup_>  group_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const SkillText::text& SkillText::name(Skill__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return name_[common::toUnderlying(id)][langIndex_];
}

inline const SkillText::text& SkillText::descr(Skill__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return descr_[common::toUnderlying(id)][langIndex_];
}

inline const SkillText::text& SkillText::group(Skill__Group id) noexcept
{
    assert(common::isValidEnum(id));
    return group_[common::toUnderlying(id)][langIndex_];
}

inline void SkillText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !SKILL_TEXT_HPP
