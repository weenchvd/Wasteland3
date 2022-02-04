
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include"effectCommon.hpp"
#include"effectVisitor.hpp"
//#include<memory>
//#include<vector>

namespace Game {
namespace Object {

class Character;

class Effect {
public:
    //Effect(const Effect&) = default;
    //Effect& operator=(const Effect&) = default;

    virtual ~Effect() noexcept {}

    //const EffectType type() const noexcept {
    //    return type_;
    //}

    //const EffectModel model() const noexcept {
    //    return model_;
    //}

    //virtual void accept(EffectVisitor& visitor) noexcept {};

    virtual void apply(Character& character) noexcept {};

protected:
    /*explicit*/ Effect(/*EffectType type, EffectModel model*/) noexcept
        /*: type_{ type }, model_{ model }*/ {}

private:
    //const EffectType        type_;          // type of Effect
    //const EffectModel       model_;         // model of Effect
};

///------------------------------------------------------------------------------------------------

} // namespace Object
} // namespace Game

#endif // !EFFECT_HPP
