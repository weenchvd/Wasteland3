
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
    data1_      { common::Range{ 0 } },
    data2_      { common::Quantity{ 0 } },
    range_      { 0 },
    type_       { Type::INVALID }
{}

Attack::Attack(const Type id) noexcept
    :
    data1_      { common::Range{ 0 } },
    data2_      { common::Quantity{ 0 } },
    range_      { 0 },
    type_       { id }
{}

void Attack::initialize()
{
    if (isInitialized()) return;
    text_.initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(ATTACK_REF_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              ATTACK_REF_FB_BIN_FILE__HASH);
    const fbAttack::FB_AttackContainer* fb{
        fbAttack::GetFB_AttackContainer(buffer.get())
    };

    initDefault(fb);
    initAll(fb);

    initialized_ = true;
}

void Attack::apply(const Attack& rhs) noexcept
{
    range_ += rhs.range_;
    if (!common::isValidEnum(rhs.type_) || type_ != rhs.type_) return;
    if (rhs.rangeOfBouncesIsPresented()) {
        rangeOfBouncesAdd(rhs.rangeOfBounces());
    }
    if (rhs.rangeOfConicalAreaIsPresented()) {
        rangeOfConicalAreaAdd(rhs.rangeOfConicalArea());
    }
    if (rhs.radiusOfCircularAreaIsPresented()) {
        radiusOfCircularAreaAdd(rhs.radiusOfCircularArea());
    }
    if (rhs.quantityOfBouncesIsPresented()) {
        quantityOfBouncesAdd(rhs.quantityOfBounces());
    }
    if (rhs.angleOfConicalAreaIsPresented()) {
        angleOfConicalAreaAdd(rhs.angleOfConicalArea());
    }
}

bool Attack::hasValidValues() const noexcept
{
    const auto& min{ minimalValues(type()) };
    assert(type() == min.type());
    if (range() < min.range())                                      return false;
    if (rangeOfBouncesIsPresented()) {
        if (rangeOfBounces() < min.rangeOfBounces())                return false;
    }
    if (rangeOfConicalAreaIsPresented()) {
        if (rangeOfConicalArea() < min.rangeOfConicalArea())        return false;
    }
    if (radiusOfCircularAreaIsPresented()) {
        if (radiusOfCircularArea() < min.radiusOfCircularArea())    return false;
    }
    if (quantityOfBouncesIsPresented()) {
        if (quantityOfBounces() < min.quantityOfBounces())          return false;
    }
    if (angleOfConicalAreaIsPresented()) {
        if (angleOfConicalArea() < min.angleOfConicalArea())        return false;
    }
    return true;
}

Attack Attack::initAttack(const fbAttack::FB_Attack* fb, const bool verify)
{
    assert(fb != nullptr);
    assert(defaultInitialized_);
    const auto& def{ default_ };

    Attack attack{ toAttackType(fb->attack_type()) };
    assert((verify ? common::isValidEnum(attack.type()) : true));
    attack.data1_ = def.data1_;
    attack.data2_ = def.data2_;
    attack.range_ = def.range_;

    if (common::Range{ fb->range_of_bounces() } != def.data1_.rangeOfBounces_) {
        attack.rangeOfBouncesAdd(common::Range{ fb->range_of_bounces() });
    }
    if (common::Range{ fb->range_of_conical_area() } != def.data1_.rangeOfConicalArea_) {
        attack.rangeOfConicalAreaAdd(common::Range{ fb->range_of_conical_area() });
    }
    if (common::Range{ fb->radius_of_circular_area() } != def.data1_.rangeRadiusOfCircArea_) {
        attack.radiusOfCircularAreaAdd(common::Range{ fb->radius_of_circular_area() });
    }
    if (common::Quantity{ fb->quantity_of_bounces() } != def.data2_.qtyOfBounces_) {
        attack.quantityOfBouncesAdd(common::Quantity{ fb->quantity_of_bounces() });
    }
    if (common::Angle{ fb->angle_of_conical_area() } != def.data2_.angleOfConicalArea_) {
        attack.angleOfConicalAreaAdd(common::Angle{ fb->angle_of_conical_area() });
    }
    if (common::Range{ fb->attack_range() } != def.range_) {
        attack.rangeAdd(common::Range{ fb->attack_range() });
    }
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
    rangePointBlank_ = common::Range{ fb->range_point_blank() };
}

void Attack::initDefault(const fbAttack::FB_AttackContainer* fb)
{
    assert(fb != nullptr);
    const auto* def{ fb->default_values() };

    assert(def != nullptr);
    assert(def->range_of_bounces() == def->range_of_conical_area() &&
           def->range_of_bounces() == def->radius_of_circular_area());
    assert(def->quantity_of_bounces() == def->angle_of_conical_area());
    default_.data1_.rangeOfBounces_         = common::Range     { def->range_of_bounces() };
    default_.data1_.rangeOfConicalArea_     = common::Range     { def->range_of_conical_area() };
    default_.data1_.rangeRadiusOfCircArea_  = common::Range     { def->radius_of_circular_area() };
    default_.data2_.qtyOfBounces_           = common::Quantity  { def->quantity_of_bounces() };
    default_.data2_.angleOfConicalArea_     = common::Angle     { def->angle_of_conical_area() };
    default_.range_                         = common::Range     { def->attack_range() };
    default_.type_                          = toAttackType(def->attack_type());

    defaultInitialized_ = true;
}

} // namespace object
} // namespace game
