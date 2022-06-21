
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef UNIT_HPP
#define UNIT_HPP

#include"unitCommon.hpp"
#include"unitFB_generated.h"
#include"unitVisitor.hpp"

namespace game {
namespace object {

class Unit {
public:
    using Type          = Unit__Type;
    using Model         = Unit__Model;

public:
    Unit() noexcept {}

    Unit(const Unit&) = delete;
    Unit& operator=(const Unit&) = delete;

    virtual ~Unit() noexcept {}

    virtual Unit::Type unitType() const noexcept = 0;

    virtual Unit::Model unitModel() const noexcept = 0;

    virtual void accept(UnitVisitor& visitor) noexcept {};

///********** serialization
public:
    flatbuffers::Offset<fbUnit::FB_Unit> serialize(
        flatbuffers::FlatBufferBuilder& fbb) const;

    static std::unique_ptr<Unit> deserialize(const fbUnit::FB_Unit* fb);
};

} // namespace object
} // namespace game

#endif // !UNIT_HPP
