
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SQUAD_HPP
#define SQUAD_HPP

#include"common.hpp"
#include"inventory.hpp"
#include"squadFB_generated.h"
#include"unit.hpp"
#include<array>
#include<memory>

namespace game {
namespace object {

class Squad {
public:
    static constexpr char nMembers_{ 6 }; // number of squad members

public:
    Squad()
        : invent_{ std::make_unique<Inventory>() }, money_{ 0 } {}


    Squad(const Squad&) = delete;
    Squad& operator=(const Squad&) = delete;

    common::Money money() const noexcept { return money_; }
    void moneyAdd(common::Money shift) noexcept { money_ += shift; }

///********** members
public:
    const std::array<std::unique_ptr<Unit>, nMembers_>& members() const noexcept { return members_; }
    std::array<std::unique_ptr<Unit>, nMembers_>& members() noexcept { return members_; }

///********** inventory
public:
    const Inventory& inventory() const noexcept { return *invent_; }
    Inventory& inventory() noexcept { return *invent_; }

///********** serialization
public:
    flatbuffers::Offset<fbSquad::FB_Squad> serialize(
        flatbuffers::FlatBufferBuilder& fbb) const;

    static std::unique_ptr<Squad> deserialize(const fbSquad::FB_Squad* fb);

private:
    std::array<std::unique_ptr<Unit>, nMembers_>    members_;
    std::unique_ptr<Inventory>                      invent_;
    common::Money                                   money_;
};

} // namespace object
} // namespace game

#endif // !SQUAD_HPP
