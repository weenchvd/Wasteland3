
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SQUAD_HPP
#define SQUAD_HPP

#include"common.hpp"
#include"inventory.hpp"
#include"unit.hpp"
#include<array>
#include<memory>

namespace Game {
namespace Object {

constexpr unsigned int nMembers = 6;            // number of members


class Squad {
public:
    Squad()
        : invent_{ std::make_unique<Inventory>() }, money_{ 0 } {}

            
    Squad(const Squad&) = delete;
    Squad& operator=(const Squad&) = delete;

    Common::Money money() const noexcept { return money_; }
    void moneyAdd(Common::Money shift) noexcept { money_ += shift; }

/// members
public:
    const std::array<std::unique_ptr<Unit>, nMembers>& members() const noexcept { return members_; }
    std::array<std::unique_ptr<Unit>, nMembers>& members() noexcept { return members_; }

/// inventory
public:
    const Inventory& inventory() const noexcept { return *invent_; }
    Inventory& inventory() noexcept { return *invent_; }

private:
    std::array<std::unique_ptr<Unit>, nMembers>     members_;
    std::unique_ptr<Inventory>                      invent_;
    Common::Money                                   money_;
};

} // namespace Object
} // namespace Game

#endif // !SQUAD_HPP
