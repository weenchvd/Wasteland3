
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef UNIT_HPP
#define UNIT_HPP

#include"unitCommon.hpp"
#include<memory>

namespace Game
{
    namespace Object
    {
        class UnitVisitor;

        class Unit {
        public:
            Unit(const Unit&) = delete;
            Unit& operator=(const Unit&) = delete;

            virtual ~Unit() noexcept {}

            const UnitType type() const noexcept {
                return type_;
            }

            const UnitModel model() const noexcept {
                return model_;
            }

            virtual void accept(UnitVisitor& visitor) noexcept {};

        protected:
            explicit Unit(UnitType type, UnitModel model) noexcept
                : type_{ type }, model_{ model } {}

        private:
            const UnitType          type_;          // type of Unit
            const UnitModel         model_;         // model of Unit
        };

        ///------------------------------------------------------------------------------------------------


    }
}

#endif // !UNIT_HPP
