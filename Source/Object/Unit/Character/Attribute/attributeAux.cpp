
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attributeAux.hpp"
#include<assert.h>

namespace game {
namespace object {

using namespace std;

AttributeInitializer::AttributeInitializer() noexcept
    :
    attrPoints_ { 0 },
    coordLevel_ { 0 },
    luckLevel_  { 0 },
    awareLevel_ { 0 },
    strLevel_   { 0 },
    speedLevel_ { 0 },
    intLevel_   { 0 },
    chaLevel_   { 0 },
    initialized_{ false }
{}

AttributeInitializer::AttributeInitializer(const fbAttribute::FB_Attribute* fb) noexcept
    :
    attrPoints_ { 0 },
    coordLevel_ { 0 },
    luckLevel_  { 0 },
    awareLevel_ { 0 },
    strLevel_   { 0 },
    speedLevel_ { 0 },
    intLevel_   { 0 },
    chaLevel_   { 0 },
    initialized_{ false }
{
    initialize(fb);
}

void AttributeInitializer::initialize(const fbAttribute::FB_Attribute* fb) noexcept
{
    assert(fb != nullptr);

    attrPoints_         = common::PointAttribute{ fb->attr_points() };
    coordLevel_         = common::LevelAttribute{ fb->coord_level() };
    luckLevel_          = common::LevelAttribute{ fb->luck_level() };
    awareLevel_         = common::LevelAttribute{ fb->aware_level() };
    strLevel_           = common::LevelAttribute{ fb->str_level() };
    speedLevel_         = common::LevelAttribute{ fb->speed_level() };
    intLevel_           = common::LevelAttribute{ fb->int_level() };
    chaLevel_           = common::LevelAttribute{ fb->cha_level() };

    initialized_        = true;
}

} // namespace object
} // namespace game
