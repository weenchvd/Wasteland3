
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include"point.hpp"
#include"attributeCommon.hpp"
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        constexpr unsigned short int initAttributePoints = 14;
        constexpr unsigned char maxAttributeLevel = 10;
        //constexpr std::initializer_list<unsigned char> distribution{ 0, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6 };
        constexpr std::initializer_list<unsigned char> distribution{ 0, 1 };

        class Attribute {
        public:
            using Type      = AttributeType;

        public:
            Attribute();

            bool add(AttributeType type, char nLevels) noexcept {
                auto index = static_cast<underlying_type_t<AttributeType>>(type);
                return manag_.changeLevel(cLevels_[index], pStor_, pDist_, nLevels);
            }

        private:
            std::vector<Common::CustomLevel>    cLevels_;
            Common::CustomLevelManager          manag_;
            Common::PointsDistribution          pDist_;
            Common::PointsStorage               pStor_;
        };

    }
}

#endif // !ATTRIBUTE_HPP
