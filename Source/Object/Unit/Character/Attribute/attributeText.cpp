
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attributePath.hpp"
#include"attributeText.hpp"
#include"flatbuffersAux.hpp"
#include<assert.h>
#include<memory>
#include<type_traits>

namespace Game
{
    namespace Object
    {
        using namespace std;
        using Game::Common::Text;

        Common::ObserverEnum<Game::Global::PlainText::Language>
            AttributeText::langObs_{ AttributeText::changeLanguage };

        std::array<
            std::array<Text, AttributeText::sizeType_>,
            AttributeText::sizeLang_
        >
            AttributeText::name_;

        std::array<
            std::array<Text, AttributeText::sizeType_>,
            AttributeText::sizeLang_
        >
            AttributeText::descr_;

        std::array<Text, AttributeText::sizeType_>* AttributeText::ptrName_ { nullptr };
        std::array<Text, AttributeText::sizeType_>* AttributeText::ptrDescr_{ nullptr };

        bool AttributeText::initialized_{ false };


        void AttributeText::changeLanguage(Game::Global::PlainText::Language lang)
        {
            ptrName_    = { &name_[Common::toUnderlying(lang)] };
            ptrDescr_   = { &descr_[Common::toUnderlying(lang)] };
        }

        const Text& AttributeText::name(Attribute__Type id) noexcept
        {
            assert(Common::isValidEnum(id));
            assert(ptrName_ != nullptr);
            return (*ptrName_)[Common::toUnderlying(id)];
        }

        const Text& AttributeText::descr(Attribute__Type id) noexcept
        {
            assert(Common::isValidEnum(id));
            assert(ptrName_ != nullptr);
            return (*ptrDescr_)[Common::toUnderlying(id)];
        }

        void AttributeText::initialize()
        {
            if (isInitialized()) return;

            assert(sizeLang_ > 0);
            assert(sizeType_ > 0);
            unique_ptr<char[]> buffer{
                Common::getFlatBuffer(ATTRIBUTE_TEXT_FB_FILENAME_WITH_NATIVE_RELATIVE_PATH)
            };

            const fbAttribute::FB_AttributeText* table{
                fbAttribute::GetFB_AttributeText(buffer.get())
            };
            assert(table != nullptr);

            initLanguage(table->en(), Game::Global::PlainText::Language::EN);
            initLanguage(table->ru(), Game::Global::PlainText::Language::RU);

            assert(Game::Global::Locator::isInitialized());
            changeLanguage(Game::Global::Locator::getOption().getLanguage());
            Game::Global::Locator::getOption().languageSubject().addObserver(&langObs_);

            initialized_ = true;
        }

        void AttributeText::initLanguage(
            const fbAttribute::FB_LanguageBundle* table,
            Game::Global::PlainText::Language lang)
        {
            assert(Common::isValidEnum(lang));
            assert(Common::toUnderlying(lang) >= 0 && Common::toUnderlying(lang) < sizeLang_);
            initByType(table->name(), name_[Common::toUnderlying(lang)]);
            initByType(table->descr(), descr_[Common::toUnderlying(lang)]);
        }

        void AttributeText::initByType(
            const fbAttribute::FB_AttributeTextType* table,
            std::array<Text, sizeType_>& ar)
        {
            ar[Common::toUnderlying(Attribute__Type::COORDINATION)] =
                move(Text{ table->coordination()->c_str() });
            ar[Common::toUnderlying(Attribute__Type::LUCK)] =
                move(Text{ table->luck()->c_str() });
            ar[Common::toUnderlying(Attribute__Type::AWARENESS)] =
                move(Text{ table->awareness()->c_str() });
            ar[Common::toUnderlying(Attribute__Type::STRENGTH)] =
                move(Text{ table->strength()->c_str() });
            ar[Common::toUnderlying(Attribute__Type::SPEED)] =
                move(Text{ table->speed()->c_str() });
            ar[Common::toUnderlying(Attribute__Type::INTELLIGENCE)] =
                move(Text{ table->intelligence()->c_str() });
            ar[Common::toUnderlying(Attribute__Type::CHARISMA)] =
                move(Text{ table->charisma()->c_str() });
        }

    }
}
