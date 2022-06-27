
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attribute.hpp"
#include"character.hpp"
#include"locator.hpp"
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

const AttributeReference    Attribute::ref_;
const AttributeText         Attribute::text_;

///************************************************************************************************

Attribute::Attribute(Character& character)
    :
    char_       { character },
    levels_     { initLevels() },
    pStor_      { ref_.minAttrPoints_, ref_.maxAttrPoints_ },
    pDist_      { ref_.pDist_ },
    cooDist_    { ref_.cooDist_ },
    lucDist_    { ref_.lucDist_ },
    awaDist_    { ref_.awaDist_ },
    strDist_    { ref_.strDist_ },
    spdDist_    { ref_.spdDist_ },
    intDist_    { ref_.intDist_ },
    chaDist_    { ref_.chaDist_ },
    initialized_{ false }
{
    assert(isInitialized());
}

void Attribute::initialize(const AttributeInitializer& initializer)
{
    assert(initializer.isInitialized());
    assert(!isInitialized(true));

    pStor_.add(initializer.attrPoints_);
    level(Type::COORDINATION).add(initializer.coordLevel_);
    level(Type::LUCK).add(initializer.luckLevel_);
    level(Type::AWARENESS).add(initializer.awareLevel_);
    level(Type::STRENGTH).add(initializer.strLevel_);
    level(Type::SPEED).add(initializer.speedLevel_);
    level(Type::INTELLIGENCE).add(initializer.intLevel_);
    level(Type::CHARISMA).add(initializer.chaLevel_);
    accept();

    initialized_ = true;
}

bool Attribute::addLevel(Attribute::Type type, level_t shift) noexcept
{
    return common::changeLevel(level(type), pStor_, pDist_, shift);
}
        
void Attribute::addLevelToAll(level_t shift) noexcept
{
    addLevel(Attribute::Type::COORDINATION, shift);
    addLevel(Attribute::Type::LUCK,         shift);
    addLevel(Attribute::Type::AWARENESS,    shift);
    addLevel(Attribute::Type::STRENGTH,     shift);
    addLevel(Attribute::Type::SPEED,        shift);
    addLevel(Attribute::Type::INTELLIGENCE, shift);
    addLevel(Attribute::Type::CHARISMA,     shift);
}

bool Attribute::isModified() const noexcept
{
    if (pStor_.get() != pStor_.getAccepted()) {
        return true;
    }
    for (const common::SpecStorage<level_t>& level : levels_) {
        if (level.get() != level.getAccepted()) {
            return true;
        }
    }
    return false;
}

void Attribute::accept() noexcept
{
    apply();
    for (common::SpecStorage<level_t>& level : levels_) {
        level.accept();
    }
    pStor_.accept();
}

void Attribute::reject() noexcept
{
    for (common::SpecStorage<level_t>& level : levels_) {
        level.reject();
    }
    pStor_.reject();
}

void Attribute::reset() noexcept
{
    for (common::SpecStorage<level_t>& level : levels_) {
        level.reset();
    }
    pStor_.reset();
}

void Attribute::apply() noexcept
{
    apply(Attribute::Type::COORDINATION);
    apply(Attribute::Type::LUCK);
    apply(Attribute::Type::AWARENESS);
    apply(Attribute::Type::STRENGTH);
    apply(Attribute::Type::SPEED);
    apply(Attribute::Type::INTELLIGENCE);
    apply(Attribute::Type::CHARISMA);
}

void Attribute::apply(Attribute::Type type) noexcept
{
    auto& lvl{ level(type) };
    auto accLevel{ lvl.getAccepted() };
    auto curLevel{ lvl.get() };
    if (accLevel != curLevel) {
        switch (type) {
        case Attribute::Type::COORDINATION: {
            EffectAttCoord sum{ cooDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Attribute::Type::LUCK: {
            EffectAttLuck sum{ lucDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Attribute::Type::AWARENESS: {
            EffectAttAware sum{ awaDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Attribute::Type::STRENGTH: {
            EffectAttStr sum{ strDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Attribute::Type::SPEED: {
            EffectAttSpeed sum{ spdDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Attribute::Type::INTELLIGENCE: {
            EffectAttInt sum{ intDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        case Attribute::Type::CHARISMA: {
            EffectAttCha sum{ chaDist_.total(accLevel, curLevel) };
            sum.apply(char_);
            break;
        }
        default:
            break;
        }
    }
}

vector<common::SpecStorage<Attribute::level_t>> Attribute::initLevels()
{
    constexpr auto nAttributes{ common::numberOf<Attribute::Type>() };
    const common::SpecStorage<level_t> tempLevel{
        ref_.minAttrLevel_,
        ref_.maxAttrLevel_
    };
    return vector<common::SpecStorage<level_t>>(nAttributes, tempLevel);
}

flatbuffers::Offset<fbAttribute::FB_Attribute> Attribute::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    using at_t = fbAttribute::FB_Attribute;
    using common::checkedEnum;

    fbAttribute::FB_AttributeBuilder b{ fbb };
    b.add_attr_points(checkedEnum<decltype(&at_t::attr_points), at_t>(storage().getAccepted()));
    b.add_coord_level(checkedEnum<decltype(&at_t::coord_level), at_t>(level(Type::COORDINATION).getAccepted()));
    b.add_luck_level(checkedEnum<decltype(&at_t::luck_level), at_t>(level(Type::LUCK).getAccepted()));
    b.add_aware_level(checkedEnum<decltype(&at_t::aware_level), at_t>(level(Type::AWARENESS).getAccepted()));
    b.add_str_level(checkedEnum<decltype(&at_t::str_level), at_t>(level(Type::STRENGTH).getAccepted()));
    b.add_speed_level(checkedEnum<decltype(&at_t::speed_level), at_t>(level(Type::SPEED).getAccepted()));
    b.add_int_level(checkedEnum<decltype(&at_t::int_level), at_t>(level(Type::INTELLIGENCE).getAccepted()));
    b.add_cha_level(checkedEnum<decltype(&at_t::cha_level), at_t>(level(Type::CHARISMA).getAccepted()));
    return b.Finish();
}

unique_ptr<Attribute> Attribute::deserialize(
    const fbAttribute::FB_Attribute* fb,
    Character& character)
{
    assert(fb != nullptr);
    auto a{ make_unique<Attribute>(character) };
    a->initialize(AttributeInitializer{ fb });
    return a;
}

} // namespace object
} // namespace game
