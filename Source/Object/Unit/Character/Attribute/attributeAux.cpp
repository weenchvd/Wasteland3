
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

    attrPoints_         = point_t{ fb->attr_points() };
    coordLevel_         = level_t{ fb->coord_level() };
    luckLevel_          = level_t{ fb->luck_level() };
    awareLevel_         = level_t{ fb->aware_level() };
    strLevel_           = level_t{ fb->str_level() };
    speedLevel_         = level_t{ fb->speed_level() };
    intLevel_           = level_t{ fb->int_level() };
    chaLevel_           = level_t{ fb->cha_level() };

    initialized_        = true;
}

} // namespace object
} // namespace game
