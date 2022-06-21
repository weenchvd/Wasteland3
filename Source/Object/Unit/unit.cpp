
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"character.hpp"
#include"exception.hpp"
#include"unit.hpp"
#include<assert.h>

namespace game {
namespace object {

using namespace std;

flatbuffers::Offset<fbUnit::FB_Unit> Unit::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    fbUnit::FB_UnitUnion type{ fbUnit::FB_UnitUnion::FB_UnitUnion_NONE };
    flatbuffers::Offset<void> offset;

    switch (unitType()) {
    case Unit::Type::CHARACTER:
        type = fbUnit::FB_UnitUnion::FB_UnitUnion_fbCharacter_FB_Character;
        offset = static_cast<const Character&>(*this).serialize(fbb).Union();
        break;
    default:
        throw common::SerializationError{ u8"[Unit::serialize] Invalid branch" };
    }

    assert(type != fbUnit::FB_UnitUnion::FB_UnitUnion_NONE);
    assert(!offset.IsNull());
    fbUnit::FB_UnitBuilder builder{ fbb };
    builder.add_unit_type(type);
    builder.add_unit(offset);
    return builder.Finish();
}

unique_ptr<Unit> Unit::deserialize(const fbUnit::FB_Unit* fb)
{
    assert(fb != nullptr);
    switch (fb->unit_type()) {
    case fbUnit::FB_UnitUnion::FB_UnitUnion_fbCharacter_FB_Character: {
        const auto* character{ fb->unit_as_fbCharacter_FB_Character() };
        assert(character != nullptr);
        return Character::deserialize(character);
    }
    default:
        throw common::SerializationError{ u8"[Unit::deserialize] Invalid branch" };
    }
}

} // namespace object
} // namespace game
