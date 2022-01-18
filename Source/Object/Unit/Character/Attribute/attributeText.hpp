
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_TEXT_HPP
#define ATTRIBUTE_TEXT_HPP

#include"attribute-text_generated.h"
#include"attributeCommon.hpp"
#include"common.hpp"
#include"locator.hpp"
#include<array>

namespace Game
{
    namespace Object
    {
        class AttributeText {
        public:
            using Text              = Game::Common::Text;

            AttributeText();

            AttributeText(const AttributeText&) = delete;
            AttributeText& operator=(const AttributeText&) = delete;
            AttributeText(AttributeText&&) = default;
            AttributeText& operator=(AttributeText&&) = default;

            bool isInitialized() const { return initialized_; }

            const Text& name(Attribute__Type id) const noexcept;

            const Text& descr(Attribute__Type id) const noexcept;

        private:
            static constexpr int sizeLang_      = Common::toUnderlying(
                Game::Global::PlainText::Language::NUMBER_OF);
            static constexpr int sizeType_      = Common::toUnderlying(Attribute__Type::NUMBER_OF);

            void initLanguage(
                const fbAttribute::FB_LanguageBundle* table,
                Game::Global::PlainText::Language lang
            );
            void initByType(
                const fbAttribute::FB_AttributeTextType* table,
                std::array<Text, sizeType_>& ar
                );

        private:
            std::array<std::array<Text, sizeType_>, sizeLang_>  name_;
            std::array<std::array<Text, sizeType_>, sizeLang_>  descr_;

            std::array<Text, sizeType_>*    ptrName_;       // rem
            std::array<Text, sizeType_>*    ptrDescr_;

            bool                            initialized_;
        };

    }
}

#endif // !ATTRIBUTE_TEXT_HPP
