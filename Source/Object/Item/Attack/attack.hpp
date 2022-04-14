
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTACK_HPP
#define ATTACK_HPP

#include"attackCommon.hpp"
#include"attackReferenceFB_generated.h"
#include"attackText.hpp"
#include"common.hpp"
#include<assert.h>
#include<vector>

namespace game {
namespace object {

class Attack {
private:
    union Data1 {
        common::Range       rangeOfBounces_;        // for CHAIN_OF_SINGLE_TARGETS
        common::Range       rangeOfConicalArea_;    // for CONICAL_AREA_BEHIND_TARGET
        common::Range       rangeRadiusOfCircArea_; // for REMOTE_CIRCULAR_AREA
    };

    union Data2 {
        common::Quantity    qtyOfBounces_;          // for CHAIN_OF_SINGLE_TARGETS
        common::Angle       angleOfConicalArea_;    // for CONICAL_AREA_BEHIND_TARGET, CONICAL_AREA
    };

public:
    using Type = Attack__Type;

private:
    using data_member_1_t = Attack::Data1;
    using data_member_2_t = Attack::Data2;

public:
    Attack() noexcept;

    explicit Attack(const Type id) noexcept;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && text_.isInitialized(); }

public:
    common::Range rangeOfBounces() const noexcept;
    void          rangeOfBouncesAdd(common::Range shift) noexcept;
    bool          rangeOfBouncesIsPresented() const noexcept;

    common::Range rangeOfConicalArea() const noexcept;
    void          rangeOfConicalAreaAdd(common::Range shift) noexcept;
    bool          rangeOfConicalAreaIsPresented() const noexcept;

    common::Range radiusOfCircularArea() const noexcept;
    void          radiusOfCircularAreaAdd(common::Range shift) noexcept;
    bool          radiusOfCircularAreaIsPresented() const noexcept;

    common::Quantity quantityOfBounces() const noexcept;
    void             quantityOfBouncesAdd(common::Quantity shift) noexcept;
    bool             quantityOfBouncesIsPresented() const noexcept;

    common::Angle angleOfConicalArea() const noexcept;
    void          angleOfConicalAreaAdd(common::Angle shift) noexcept;
    bool          angleOfConicalAreaIsPresented() const noexcept;

    common::Range range() const noexcept;
    void rangeAdd(common::Range shift) noexcept;

    Type type() const noexcept { return type_; }

private:
    bool rangeOfBouncesAssertType() const noexcept;

    bool rangeOfConicalAreaAssertType() const noexcept;

    bool radiusOfCircularAreaAssertType() const noexcept;

    bool quantityOfBouncesAssertType() const noexcept;

    bool angleOfConicalAreaAssertType() const noexcept;

public:
    static Attack initAttack(const fbAttack::FB_Attack* fb, const bool assert = true);

    static common::Range pointBlank() noexcept { return rangePointBlank_; }

    static const Attack& minimalValues(Attack::Type id) noexcept;

    static const AttackText& attackText() noexcept { return text_; }

private:
    static void initAll(const fbAttack::FB_AttackContainer* fb);

    static void initDefault(const fbAttack::FB_AttackContainer* fb);

private:
    data_member_1_t                             data1_;
    data_member_2_t                             data2_;
    common::Range                               range_;
    Type                                        type_;

    static std::vector<Attack>                  minimal_;
    static Attack                               default_;
    static common::Range                        rangePointBlank_;
    static bool                                 defaultInitialized_;
    static bool                                 initialized_;

    static const AttackText                     text_;
};

///************************************************************************************************

inline common::Range Attack::rangeOfBounces() const noexcept
{
    assert(rangeOfBouncesAssertType());
    return data1_.rangeOfBounces_;
}

inline void Attack::rangeOfBouncesAdd(common::Range shift) noexcept
{
    assert(rangeOfBouncesAssertType());
    data1_.rangeOfBounces_ += shift;
}

inline bool Attack::rangeOfBouncesIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return rangeOfBouncesAssertType() &&
           data1_.rangeOfBounces_ != default_.data1_.rangeOfBounces_;
}

inline common::Range Attack::rangeOfConicalArea() const noexcept
{
    assert(rangeOfConicalAreaAssertType());
    return data1_.rangeOfConicalArea_;
}

inline void Attack::rangeOfConicalAreaAdd(common::Range shift) noexcept
{
    assert(rangeOfConicalAreaAssertType());
    data1_.rangeOfConicalArea_ += shift;
}

inline bool Attack::rangeOfConicalAreaIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return rangeOfConicalAreaAssertType() &&
           data1_.rangeOfConicalArea_ != default_.data1_.rangeOfConicalArea_;
}

inline common::Range Attack::radiusOfCircularArea() const noexcept
{
    assert(radiusOfCircularAreaAssertType());
    return data1_.rangeRadiusOfCircArea_;
}

inline void Attack::radiusOfCircularAreaAdd(common::Range shift) noexcept
{
    assert(radiusOfCircularAreaAssertType());
    data1_.rangeRadiusOfCircArea_ += shift;
}

inline bool Attack::radiusOfCircularAreaIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return radiusOfCircularAreaAssertType() &&
           data1_.rangeRadiusOfCircArea_ != default_.data1_.rangeRadiusOfCircArea_;
}

inline common::Quantity Attack::quantityOfBounces() const noexcept
{
    assert(quantityOfBouncesAssertType());
    return data2_.qtyOfBounces_;
}

inline void Attack::quantityOfBouncesAdd(common::Quantity shift) noexcept
{
    assert(quantityOfBouncesAssertType());
    data2_.qtyOfBounces_ += shift;
}

inline bool Attack::quantityOfBouncesIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return quantityOfBouncesAssertType() &&
           data2_.qtyOfBounces_ != default_.data2_.qtyOfBounces_;
}

inline common::Angle Attack::angleOfConicalArea() const noexcept
{
    assert(angleOfConicalAreaAssertType());
    return data2_.angleOfConicalArea_;
}

inline void Attack::angleOfConicalAreaAdd(common::Angle shift) noexcept
{
    assert(angleOfConicalAreaAssertType());
    data2_.angleOfConicalArea_ += shift;
}

inline bool Attack::angleOfConicalAreaIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return angleOfConicalAreaAssertType() &&
           data2_.angleOfConicalArea_ != default_.data2_.angleOfConicalArea_;
}

inline common::Range Attack::range() const noexcept
{
    assert(common::isValidEnum(type_));
    return range_;
}

inline void Attack::rangeAdd(common::Range shift) noexcept
{
    assert(common::isValidEnum(type_));
    range_ += shift;
}

inline bool Attack::rangeOfBouncesAssertType() const noexcept
{
    return type_ == Type::CHAIN_OF_SINGLE_TARGETS;
}

inline bool Attack::rangeOfConicalAreaAssertType() const noexcept
{
    return type_ == Type::CONICAL_AREA_BEHIND_TARGET;
}

inline bool Attack::radiusOfCircularAreaAssertType() const noexcept
{
    return type_ == Type::REMOTE_CIRCULAR_AREA;
}

inline bool Attack::quantityOfBouncesAssertType() const noexcept
{
    return type_ == Type::CHAIN_OF_SINGLE_TARGETS;
}

inline bool Attack::angleOfConicalAreaAssertType() const noexcept
{
    return type_ == Type::CONICAL_AREA_BEHIND_TARGET ||
           type_ == Type::CONICAL_AREA;
}

inline const Attack& Attack::minimalValues(Attack::Type id) noexcept
{
    assert(common::isValidEnum(id));
    return minimal_[common::toUnderlying(id)];
}

} // namespace object
} // namespace game

#endif // !ATTACK_HPP
