
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attributePath.hpp"
#include"attributeText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, AttributeText::language> AttributeText::langObs_;

array<AttributeText::language_bundle, AttributeText::sizeType_> AttributeText::name_;
array<AttributeText::language_bundle, AttributeText::sizeType_> AttributeText::descr_;

underlying_type_t<AttributeText::language>  AttributeText::langIndex_   { 0 };
bool                                        AttributeText::initialized_ { false };

///************************************************************************************************

void AttributeText::initialize()
{
    using global::Locator;

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

    initByType(table->name(), name_);
    initByType(table->descr(), descr_);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&AttributeText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void AttributeText::initByType(
    const fbAttribute::FB_AttributeTextType* table,
    array<language_bundle, sizeType_>& ar)
{
    assert(table != nullptr);

    common::initLanguageBundle(
        table->coordination(),
        ar[common::toUnderlying(Attribute__Type::COORDINATION)]
    );
    common::initLanguageBundle(
        table->luck(),
        ar[common::toUnderlying(Attribute__Type::LUCK)]
    );
    common::initLanguageBundle(
        table->awareness(),
        ar[common::toUnderlying(Attribute__Type::AWARENESS)]
    );
    common::initLanguageBundle(
        table->strength(),
        ar[common::toUnderlying(Attribute__Type::STRENGTH)]
    );
    common::initLanguageBundle(
        table->speed(),
        ar[common::toUnderlying(Attribute__Type::SPEED)]
    );
    common::initLanguageBundle(
        table->intelligence(),
        ar[common::toUnderlying(Attribute__Type::INTELLIGENCE)]
    );
    common::initLanguageBundle(
        table->charisma(),
        ar[common::toUnderlying(Attribute__Type::CHARISMA)]
    );
}

} // namespace object
} // namespace game
