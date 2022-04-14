
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attackPath.hpp"
#include"attackText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include<assert.h>
#include<memory>
#include<stdlib.h>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase                       AttackText::base_;
array<AttackText::language_bundle_t, AttackText::sizeType_>
                                            AttackText::type_;
AttackTextCommon                            AttackText::common_;
bool                                        AttackText::initialized_{ false };

///************************************************************************************************

void AttackText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    if (!common::readBinFlatBuffer(ATTACK_TEXT_FB_BIN_FILE__NATIVE_REL_PATH, buffer)) {
        abort();
    }
    const fbAttack::FB_AttackText* fb{
        fbAttack::GetFB_AttackText(buffer.get())
    };

    assert(fb != nullptr);
    initByType(fb->type(), type_);
    initCommon(fb->common());

    initialized_ = true;
}

void AttackText::initByType(
    const fbAttack::FB_AttackTextType* fb,
    array<language_bundle_t, sizeType_>& ar)
{
    assert(sizeType_ > 0);
    assert(fb != nullptr);

    common::initLanguageBundle(
        fb->single_target(),
        ar[common::toUnderlying(Attack__Type::SINGLE_TARGET)]
    );
    common::initLanguageBundle(
        fb->chain_of_single_targets(),
        ar[common::toUnderlying(Attack__Type::CHAIN_OF_SINGLE_TARGETS)]
    );
    common::initLanguageBundle(
        fb->straight_line(),
        ar[common::toUnderlying(Attack__Type::STRAIGHT_LINE)]
    );
    common::initLanguageBundle(
        fb->conical_area_behind_target(),
        ar[common::toUnderlying(Attack__Type::CONICAL_AREA_BEHIND_TARGET)]
    );
    common::initLanguageBundle(
        fb->conical_area(),
        ar[common::toUnderlying(Attack__Type::CONICAL_AREA)]
    );
    common::initLanguageBundle(
        fb->remote_circular_area(),
        ar[common::toUnderlying(Attack__Type::REMOTE_CIRCULAR_AREA)]
    );
    common::initLanguageBundle(
        fb->circular_area(),
        ar[common::toUnderlying(Attack__Type::CIRCULAR_AREA)]
    );
}

void AttackText::initCommon(const fbAttack::FB_AttackTextCommon* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->attack_type(), common_.attackType_);
    common::initLanguageBundle(fb->attack_range(), common_.attackRange_);
    common::initLanguageBundle(fb->range_of_bounces(), common_.rangeOfBounces_);
    common::initLanguageBundle(fb->range_of_conical_area(), common_.rangeOfConicalArea_);
    common::initLanguageBundle(fb->radius_of_circular_area(), common_.radiusOfCircularArea_);
    common::initLanguageBundle(fb->quantity_of_bounces(), common_.qtyOfBounces_);
    common::initLanguageBundle(fb->angle_of_conical_area(), common_.angleOfConicalArea_);
    common::initLanguageBundle(fb->point_blank(), common_.pointBlank_);
}

} // namespace object
} // namespace game
