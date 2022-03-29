
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SKILL_TEXT_HPP
#define SKILL_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include"skillCommon.hpp"
#include"skillTextFB_generated.h"
#include<array>
#include<assert.h>

namespace game {
namespace object {

class SkillText {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;

    static constexpr auto sizeType_     { common::numberOf<Skill__Type>() };
    static constexpr auto sizeGroup_    { common::numberOf<Skill__Group>() };

    friend class Skill;

private:
    SkillText() noexcept {}

public:
    SkillText(const SkillText&) = delete;
    SkillText& operator=(const SkillText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const text_t& name(Skill__Type id) noexcept;

    static const text_t& descr(Skill__Type id) noexcept;

    static const text_t& group(Skill__Group id) noexcept;

private:
    static void initByType(
        const fbSkill::FB_SkillTextType* fb,
        std::array<language_bundle_t, sizeType_>& ar
    );

    static void initByGroup(
        const fbSkill::FB_SkillTextGroup* fb,
        std::array<language_bundle_t, sizeGroup_>& ar
    );

private:
    static global::PlainTextBase                        base_;
    static std::array<language_bundle_t, sizeType_>     name_;
    static std::array<language_bundle_t, sizeType_>     descr_;
    static std::array<language_bundle_t, sizeGroup_>    group_;
    static bool                                         initialized_;
};

///************************************************************************************************

inline const SkillText::text_t& SkillText::name(Skill__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return name_[common::toUnderlying(id)][languageIndex()];
}

inline const SkillText::text_t& SkillText::descr(Skill__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return descr_[common::toUnderlying(id)][languageIndex()];
}

inline const SkillText::text_t& SkillText::group(Skill__Group id) noexcept
{
    assert(common::isValidEnum(id));
    return group_[common::toUnderlying(id)][languageIndex()];
}

} // namespace object
} // namespace game

#endif // !SKILL_TEXT_HPP
