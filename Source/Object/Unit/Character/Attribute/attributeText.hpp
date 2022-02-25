
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_TEXT_HPP
#define ATTRIBUTE_TEXT_HPP

#include"attributeCommon.hpp"
#include"attributeTextFB_generated.h"
#include"common.hpp"
#include"observerDLL.hpp"
#include"plainText.hpp"
#include<array>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

class AttributeText {
public:
    using text              = common::Text;

private:
    using language          = global::PlainText::Language;

    static constexpr auto sizeLang_{ global::PlainText::sizeLang_ };
    static constexpr auto sizeType_{ common::numberOf<Attribute__Type>() };

    using language_bundle   = std::array<text, sizeLang_>;

public:
    AttributeText() noexcept {}

    AttributeText(const AttributeText&) = delete;
    AttributeText& operator=(const AttributeText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static const text& name(Attribute__Type id) noexcept;

    static const text& descr(Attribute__Type id) noexcept;

private:
    static void setLanguage(language lang) noexcept;

    static void initByType(
        const fbAttribute::FB_AttributeTextType* table,
        std::array<language_bundle, sizeType_>& ar
    );

private:
    static common::ObserverDLL<void, language>      langObs_;

    static std::array<language_bundle, sizeType_>   name_;
    static std::array<language_bundle, sizeType_>   descr_;

    static std::underlying_type_t<language>         langIndex_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline const AttributeText::text& AttributeText::name(Attribute__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return name_[common::toUnderlying(id)][langIndex_];
}

inline const AttributeText::text& AttributeText::descr(Attribute__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return descr_[common::toUnderlying(id)][langIndex_];
}

inline void AttributeText::setLanguage(language lang) noexcept
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_TEXT_HPP
