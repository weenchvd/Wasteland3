
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attributePath.hpp"
#include"attributeText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase                       AttributeText::base_;
array<AttributeText::language_bundle_t, AttributeText::sizeType_>
                                            AttributeText::name_;
array<AttributeText::language_bundle_t, AttributeText::sizeType_>
                                            AttributeText::descr_;
bool                                        AttributeText::initialized_{ false };

///************************************************************************************************

void AttributeText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(ATTRIBUTE_TEXT_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbAttribute::FB_AttributeText* fb{
        fbAttribute::GetFB_AttributeText(buffer.get())
    };

    assert(fb != nullptr);
    initByType(fb->name(), name_);
    initByType(fb->descr(), descr_);

    initialized_ = true;
}

void AttributeText::initByType(
    const fbAttribute::FB_AttributeTextType* fb,
    array<language_bundle_t, sizeType_>& ar)
{
    assert(sizeType_ > 0);
    assert(fb != nullptr);

    common::initLanguageBundle(
        fb->coordination(),
        ar[common::toUnderlying(Attribute__Type::COORDINATION)]
    );
    common::initLanguageBundle(
        fb->luck(),
        ar[common::toUnderlying(Attribute__Type::LUCK)]
    );
    common::initLanguageBundle(
        fb->awareness(),
        ar[common::toUnderlying(Attribute__Type::AWARENESS)]
    );
    common::initLanguageBundle(
        fb->strength(),
        ar[common::toUnderlying(Attribute__Type::STRENGTH)]
    );
    common::initLanguageBundle(
        fb->speed(),
        ar[common::toUnderlying(Attribute__Type::SPEED)]
    );
    common::initLanguageBundle(
        fb->intelligence(),
        ar[common::toUnderlying(Attribute__Type::INTELLIGENCE)]
    );
    common::initLanguageBundle(
        fb->charisma(),
        ar[common::toUnderlying(Attribute__Type::CHARISMA)]
    );
}

} // namespace object
} // namespace game
