
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DAMAGE_HPP
#define DAMAGE_HPP

#include"damageCommon.hpp"
#include"damageReference.hpp"
#include"damageText.hpp"

namespace game {
namespace object {

class Damage {
public:
    using Type          = Damage__Type;

public:
    static void initialize();

    static bool isInitialized();

public:
    static const DamageReferenceContainer& damageReferenceContainer() noexcept {
        return ref_;
    }

    static const DamageText& damageText() noexcept {
        return text_;
    }

private:
    static const DamageReferenceContainer       ref_;
    static const DamageText                     text_;
};

///************************************************************************************************

inline void Damage::initialize()
{
    ref_.initialize();
    text_.initialize();
}

inline bool Damage::isInitialized()
{
    return ref_.isInitialized()
        && text_.isInitialized();
}

} // namespace object
} // namespace game

#endif // !DAMAGE_HPP
