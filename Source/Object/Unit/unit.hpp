
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef UNIT_HPP
#define UNIT_HPP

#include"unitCommon.hpp"
#include"unitVisitor.hpp"

namespace Game
{
    namespace Object
    {
        class Unit {
        public:
            using Type      = UnitType;
            using Model     = UnitModel;

        public:
            Unit() noexcept {}

            Unit(const Unit&) = delete;
            Unit& operator=(const Unit&) = delete;

            virtual ~Unit() noexcept {}

            virtual Unit::Type unitType() const noexcept = 0;

            virtual Unit::Model unitModel() const noexcept = 0;

            virtual void accept(UnitVisitor& visitor) noexcept {};
        };

    }
}

#endif // !UNIT_HPP
