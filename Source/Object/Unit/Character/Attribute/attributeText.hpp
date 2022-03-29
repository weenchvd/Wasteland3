
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_TEXT_HPP
#define ATTRIBUTE_TEXT_HPP

#include"attributeCommon.hpp"
#include"attributeTextFB_generated.h"
#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>
#include<assert.h>

namespace game {
namespace object {

class AttributeText {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;

    static constexpr auto sizeType_{ common::numberOf<Attribute__Type>() };

    friend class Attribute;

private:
    AttributeText() noexcept {}

public:
    AttributeText(const AttributeText&) = delete;
    AttributeText& operator=(const AttributeText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const text_t& name(Attribute__Type id) noexcept;

    static const text_t& descr(Attribute__Type id) noexcept;

private:
    static void initByType(
        const fbAttribute::FB_AttributeTextType* fb,
        std::array<language_bundle_t, sizeType_>& ar
    );

private:
    static global::PlainTextBase                    base_;
    static std::array<language_bundle_t, sizeType_> name_;
    static std::array<language_bundle_t, sizeType_> descr_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const AttributeText::text_t& AttributeText::name(Attribute__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return name_[common::toUnderlying(id)][languageIndex()];
}

inline const AttributeText::text_t& AttributeText::descr(Attribute__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return descr_[common::toUnderlying(id)][languageIndex()];
}

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_TEXT_HPP
