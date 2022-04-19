
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

    void apply(const Attack& rhs) noexcept;

    bool hasValidValues() const noexcept;

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
    void          rangeAdd(common::Range shift) noexcept;
    bool          rangeIsPresented() const noexcept;

    Type type() const noexcept { return type_; }

private:
    bool rangeOfBouncesVerifyType() const noexcept;

    bool rangeOfConicalAreaVerifyType() const noexcept;

    bool radiusOfCircularAreaVerifyType() const noexcept;

    bool quantityOfBouncesVerifyType() const noexcept;

    bool angleOfConicalAreaVerifyType() const noexcept;

public:
    static Attack initAttack(const fbAttack::FB_Attack* fb, const bool verify = true);

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
    assert(rangeOfBouncesVerifyType());
    return data1_.rangeOfBounces_;
}

inline void Attack::rangeOfBouncesAdd(common::Range shift) noexcept
{
    assert(rangeOfBouncesVerifyType());
    data1_.rangeOfBounces_ += shift;
}

inline bool Attack::rangeOfBouncesIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return rangeOfBouncesVerifyType() &&
           data1_.rangeOfBounces_ != default_.data1_.rangeOfBounces_;
}

inline common::Range Attack::rangeOfConicalArea() const noexcept
{
    assert(rangeOfConicalAreaVerifyType());
    return data1_.rangeOfConicalArea_;
}

inline void Attack::rangeOfConicalAreaAdd(common::Range shift) noexcept
{
    assert(rangeOfConicalAreaVerifyType());
    data1_.rangeOfConicalArea_ += shift;
}

inline bool Attack::rangeOfConicalAreaIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return rangeOfConicalAreaVerifyType() &&
           data1_.rangeOfConicalArea_ != default_.data1_.rangeOfConicalArea_;
}

inline common::Range Attack::radiusOfCircularArea() const noexcept
{
    assert(radiusOfCircularAreaVerifyType());
    return data1_.rangeRadiusOfCircArea_;
}

inline void Attack::radiusOfCircularAreaAdd(common::Range shift) noexcept
{
    assert(radiusOfCircularAreaVerifyType());
    data1_.rangeRadiusOfCircArea_ += shift;
}

inline bool Attack::radiusOfCircularAreaIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return radiusOfCircularAreaVerifyType() &&
           data1_.rangeRadiusOfCircArea_ != default_.data1_.rangeRadiusOfCircArea_;
}

inline common::Quantity Attack::quantityOfBounces() const noexcept
{
    assert(quantityOfBouncesVerifyType());
    return data2_.qtyOfBounces_;
}

inline void Attack::quantityOfBouncesAdd(common::Quantity shift) noexcept
{
    assert(quantityOfBouncesVerifyType());
    data2_.qtyOfBounces_ += shift;
}

inline bool Attack::quantityOfBouncesIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return quantityOfBouncesVerifyType() &&
           data2_.qtyOfBounces_ != default_.data2_.qtyOfBounces_;
}

inline common::Angle Attack::angleOfConicalArea() const noexcept
{
    assert(angleOfConicalAreaVerifyType());
    return data2_.angleOfConicalArea_;
}

inline void Attack::angleOfConicalAreaAdd(common::Angle shift) noexcept
{
    assert(angleOfConicalAreaVerifyType());
    data2_.angleOfConicalArea_ += shift;
}

inline bool Attack::angleOfConicalAreaIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return angleOfConicalAreaVerifyType() &&
           data2_.angleOfConicalArea_ != default_.data2_.angleOfConicalArea_;
}

inline common::Range Attack::range() const noexcept
{
    return range_;
}

inline void Attack::rangeAdd(common::Range shift) noexcept
{
    range_ += shift;
}

inline bool Attack::rangeIsPresented() const noexcept
{
    assert(defaultInitialized_);
    return range_ != default_.range_;
}

inline bool Attack::rangeOfBouncesVerifyType() const noexcept
{
    return type_ == Type::CHAIN_OF_SINGLE_TARGETS;
}

inline bool Attack::rangeOfConicalAreaVerifyType() const noexcept
{
    return type_ == Type::CONICAL_AREA_BEHIND_TARGET;
}

inline bool Attack::radiusOfCircularAreaVerifyType() const noexcept
{
    return type_ == Type::REMOTE_CIRCULAR_AREA;
}

inline bool Attack::quantityOfBouncesVerifyType() const noexcept
{
    return type_ == Type::CHAIN_OF_SINGLE_TARGETS;
}

inline bool Attack::angleOfConicalAreaVerifyType() const noexcept
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
