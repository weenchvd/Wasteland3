
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

namespace game {
namespace object {

using namespace std;
using common::Text;
using global::PlainText;
using global::Locator;

common::ObserverDLL<void, PlainText::Language>
    AttributeText::langObs_;

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


void AttributeText::setLanguage(PlainText::Language lang)
{
    assert(common::isValidEnum(lang));
    ptrName_    = { &name_[common::toUnderlying(lang)] };
    ptrDescr_   = { &descr_[common::toUnderlying(lang)] };
}

const Text& AttributeText::name(Attribute__Type id) noexcept
{
    assert(common::isValidEnum(id));
    assert(ptrName_ != nullptr);
    return (*ptrName_)[common::toUnderlying(id)];
}

const Text& AttributeText::descr(Attribute__Type id) noexcept
{
    assert(common::isValidEnum(id));
    assert(ptrDescr_ != nullptr);
    return (*ptrDescr_)[common::toUnderlying(id)];
}

void AttributeText::initialize()
{
    if (isInitialized()) return;

    assert(sizeLang_ > 0);
    assert(sizeType_ > 0);
    unique_ptr<char[]> buffer{
        common::getFlatBuffer(ATTRIBUTE_TEXT_FB_BIN_FILE__NATIVE_REL_PATH)
    };

    const fbAttribute::FB_AttributeText* table{
        fbAttribute::GetFB_AttributeText(buffer.get())
    };
    assert(table != nullptr);

    initLanguage(table->en(), PlainText::Language::EN);
    initLanguage(table->ru(), PlainText::Language::RU);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&AttributeText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void AttributeText::initLanguage(
    const fbAttribute::FB_LanguageBundle* table,
    PlainText::Language lang)
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    initByType(table->name(), name_[common::toUnderlying(lang)]);
    initByType(table->descr(), descr_[common::toUnderlying(lang)]);
}

void AttributeText::initByType(
    const fbAttribute::FB_AttributeTextType* table,
    std::array<Text, sizeType_>& ar)
{
    ar[common::toUnderlying(Attribute__Type::COORDINATION)] =
        move(Text{ table->coordination()->c_str() });
    ar[common::toUnderlying(Attribute__Type::LUCK)] =
        move(Text{ table->luck()->c_str() });
    ar[common::toUnderlying(Attribute__Type::AWARENESS)] =
        move(Text{ table->awareness()->c_str() });
    ar[common::toUnderlying(Attribute__Type::STRENGTH)] =
        move(Text{ table->strength()->c_str() });
    ar[common::toUnderlying(Attribute__Type::SPEED)] =
        move(Text{ table->speed()->c_str() });
    ar[common::toUnderlying(Attribute__Type::INTELLIGENCE)] =
        move(Text{ table->intelligence()->c_str() });
    ar[common::toUnderlying(Attribute__Type::CHARISMA)] =
        move(Text{ table->charisma()->c_str() });
}

} // namespace object
} // namespace game
