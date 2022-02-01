
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_TEXT_HPP
#define ATTRIBUTE_TEXT_HPP

#include"attributeTextFB_generated.h"
#include"attributeCommon.hpp"
#include"common.hpp"
#include"locator.hpp"
#include"observerDLL.hpp"
#include<array>

namespace Game {
namespace Object {

class AttributeText {
public:
    using Text              = Game::Common::Text;

    AttributeText() noexcept {}

    AttributeText(const AttributeText&) = delete;
    AttributeText& operator=(const AttributeText&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static const Text& name(Attribute__Type id) noexcept;

    static const Text& descr(Attribute__Type id) noexcept;

private:
    static constexpr int sizeLang_      = Common::toUnderlying(
        Game::Global::PlainText::Language::NUMBER_OF);
    static constexpr int sizeType_      = Common::toUnderlying(Attribute__Type::NUMBER_OF);

    static void setLanguage(Game::Global::PlainText::Language lang);

    static void initLanguage(
        const fbAttribute::FB_LanguageBundle* table,
        Game::Global::PlainText::Language lang
    );

    static void initByType(
        const fbAttribute::FB_AttributeTextType* table,
        std::array<Text, sizeType_>& ar
    );

private:
    static Game::Common::ObserverDLL<void, Game::Global::PlainText::Language>   langObs_;

    static std::array<std::array<Text, sizeType_>, sizeLang_>   name_;
    static std::array<std::array<Text, sizeType_>, sizeLang_>   descr_;

    static std::array<Text, sizeType_>*     ptrName_;
    static std::array<Text, sizeType_>*     ptrDescr_;

    static bool                             initialized_;
};

} // namespace Object
} // namespace Game

#endif // !ATTRIBUTE_TEXT_HPP
