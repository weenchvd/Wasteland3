
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attribute.hpp"

namespace Game
{
    namespace Object
    {
        using namespace std;
        using namespace Common;

        Attribute::Attribute()
            :
            cLevels_{},
            //pDist_  { std::vector<unsigned char>{ 0, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6 } },
            pDist_{ distribution },
            pStor_{ initAttributePoints }
        {
            CustomLevel tempLevel{ maxAttributeLevel };
            auto numOfAttributes = static_cast<underlying_type_t<AttributeType>>
                (AttributeType::NUMBER_OF_ATTRIBUTES);
            vector<CustomLevel> temp(numOfAttributes, tempLevel);
            cLevels_ = move(temp);
        }

        //bool Attribute::add(AttributeType type, char levels) noexcept
        //{
        //    auto index = static_cast<underlying_type_t<AttributeType>>(type);
        //    CustomLevel& curCustomLevel = cLevels_[index];
        //    auto curLevel = static_cast<int>(curCustomLevel.get());
        //    auto newLevel = curLevel + levels;
        //    if (newLevel >= curCustomLevel.getAccepted() && newLevel <= curCustomLevel.getMax()) {
        //        auto points = pDist_.totalPoints(curLevel, newLevel);
        //        if (pStor_.get() >= points) {
        //            curCustomLevel.add(levels);
        //            pStor_.add(points);
        //            return true;
        //        }
        //    }
        //    return false;
        //}

    }
}