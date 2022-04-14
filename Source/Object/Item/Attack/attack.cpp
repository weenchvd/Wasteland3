
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attack.hpp"
#include"attackFB_generated.h"
#include"attackPath.hpp"
#include"flatbuffersAux.hpp"
#include<memory>
#include<stdlib.h>

namespace game {
namespace object {

using namespace std;

vector<Attack>                          Attack::minimal_;
Attack                                  Attack::default_;
common::Range                           Attack::rangePointBlank_    { 0 };
bool                                    Attack::defaultInitialized_ { false };
bool                                    Attack::initialized_        { false };
const AttackText                        Attack::text_;

///************************************************************************************************

Attack::Attack() noexcept
    :
    data1_      { 0 },
    data2_      { 0 },
    range_      { 0 },
    type_       { Type::INVALID }
{}

Attack::Attack(const Type id) noexcept
    :
    data1_      { 0 },
    data2_      { 0 },
    range_      { 0 },
    type_       { id }
{}

void Attack::initialize()
{
    if (isInitialized()) return;
    text_.initialize();

    unique_ptr<char[]> buffer{};
    if (!common::readBinFlatBuffer(ATTACK_REF_FB_BIN_FILE__NATIVE_REL_PATH, buffer)) {
        abort();
    }
    const fbAttack::FB_AttackContainer* fb{
        fbAttack::GetFB_AttackContainer(buffer.get())
    };

    initDefault(fb);
    initAll(fb);

    initialized_ = true;
}

Attack Attack::initAttack(const fbAttack::FB_Attack* fb, const bool assert)
{
    assert(fb != nullptr);
    assert(defaultInitialized_);
    const auto& def{ default_ };

    Attack attack{ toAttackType(fb->attack_type()) };
    attack.data1_ = def.data1_;
    attack.data2_ = def.data2_;
    attack.range_ = def.range_;

    if (fb->range_of_bounces() != def.data1_.rangeOfBounces_) {
        attack.rangeOfBouncesAdd(fb->range_of_bounces());
    }
    if (fb->range_of_conical_area() != def.data1_.rangeOfConicalArea_) {
        attack.rangeOfConicalAreaAdd(fb->range_of_conical_area());
    }
    if (fb->radius_of_circular_area() != def.data1_.rangeRadiusOfCircArea_) {
        attack.radiusOfCircularAreaAdd(fb->radius_of_circular_area());
    }
    if (fb->quantity_of_bounces() != def.data2_.qtyOfBounces_) {
        attack.quantityOfBouncesAdd(fb->quantity_of_bounces());
    }
    if (fb->angle_of_conical_area() != def.data2_.angleOfConicalArea_) {
        attack.angleOfConicalAreaAdd(fb->angle_of_conical_area());
    }
    if (fb->attack_range() != def.range_) {
        attack.rangeAdd(fb->attack_range());
    }

#ifndef NDEBUG
    if (assert) {
        assert(common::isValidEnum(attack.type()));
    }
#endif

    return attack;
}

void Attack::initAll(const fbAttack::FB_AttackContainer* fb)
{
    assert(fb != nullptr);
    minimal_.resize(common::numberOf<Attack::Type>());
    const auto* v{ fb->minimal_values() };
    assert(minimal_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        Attack attack{ initAttack(v->Get(i)) };
        const auto pos{ common::toUnderlying(attack.type_) };
        minimal_[pos] = move(attack);
    }
    initAttack(fb->sample_of_all_fields(), false);
    rangePointBlank_ = { fb->range_point_blank() };
}

void Attack::initDefault(const fbAttack::FB_AttackContainer* fb)
{
    assert(fb != nullptr);
    const auto* def{ fb->default_values() };

    assert(def != nullptr);
    assert(def->range_of_bounces() == def->range_of_conical_area() &&
           def->range_of_bounces() == def->radius_of_circular_area());
    assert(def->quantity_of_bounces() == def->angle_of_conical_area());
    default_.data1_.rangeOfBounces_         = { def->range_of_bounces() };
    default_.data1_.rangeOfConicalArea_     = { def->range_of_conical_area() };
    default_.data1_.rangeRadiusOfCircArea_  = { def->radius_of_circular_area() };
    default_.data2_.qtyOfBounces_           = { def->quantity_of_bounces() };
    default_.data2_.angleOfConicalArea_     = { def->angle_of_conical_area() };
    default_.range_                         = { def->attack_range() };
    default_.type_                          = toAttackType(def->attack_type());

    defaultInitialized_ = true;
}

} // namespace object
} // namespace game
