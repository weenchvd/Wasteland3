
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTACK_TEXT_HPP
#define ATTACK_TEXT_HPP

#include"attackCommon.hpp"
#include"attackTextFB_generated.h"
#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace object {

class AttackTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class AttackText;

private:
    AttackTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& attackType() const noexcept { return attackType_[li()]; }

    const text_t& attackRange() const noexcept { return attackRange_[li()]; }

    const text_t& rangeOfBounces() const noexcept { return rangeOfBounces_[li()]; }

    const text_t& rangeOfConicalArea() const noexcept { return rangeOfConicalArea_[li()]; }

    const text_t& radiusOfCircularArea() const noexcept { return radiusOfCircularArea_[li()]; }

    const text_t& qtyOfBounces() const noexcept { return qtyOfBounces_[li()]; }

    const text_t& angleOfConicalArea() const noexcept { return angleOfConicalArea_[li()]; }

    const text_t& pointBlank() const noexcept { return pointBlank_[li()]; }

private:
    language_bundle_t attackType_;
    language_bundle_t attackRange_;
    language_bundle_t rangeOfBounces_;
    language_bundle_t rangeOfConicalArea_;
    language_bundle_t radiusOfCircularArea_;
    language_bundle_t qtyOfBounces_;
    language_bundle_t angleOfConicalArea_;
    language_bundle_t pointBlank_;
};

///************************************************************************************************

class AttackText {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;

    static constexpr auto sizeType_{ common::numberOf<Attack__Type>() };

    friend class Attack;

private:
    AttackText() noexcept {}

public:
    AttackText(const AttackText&) = delete;
    AttackText& operator=(const AttackText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const text_t& type(Attack__Type id) noexcept;

    static const AttackTextCommon& common() noexcept { return common_; }

private:
    static void initByType(
        const fbAttack::FB_AttackTextType* fb,
        std::array<language_bundle_t, sizeType_>& ar
    );

    static void initCommon(const fbAttack::FB_AttackTextCommon* fb);

private:
    static global::PlainTextBase                    base_;
    static std::array<language_bundle_t, sizeType_> type_;
    static AttackTextCommon                         common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline AttackTextCommon::language_index_t AttackTextCommon::li() const noexcept
{
    return { AttackText::languageIndex() };
}

///************************************************************************************************

inline const AttackText::text_t& AttackText::type(Attack__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return type_[common::toUnderlying(id)][languageIndex()];
}

} // namespace object
} // namespace game

#endif // !ATTACK_TEXT_HPP
