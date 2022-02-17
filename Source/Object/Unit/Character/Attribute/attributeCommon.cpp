
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attributeCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Attribute__Type toAttributeType(fbAttribute::FB_AttributeType id)
{
    static unordered_map<fbAttribute::FB_AttributeType, Attribute__Type> map{
        { fbAttribute::FB_AttributeType_INVALID, Attribute__Type::INVALID },
        { fbAttribute::FB_AttributeType_COORDINATION, Attribute__Type::COORDINATION },
        { fbAttribute::FB_AttributeType_LUCK, Attribute__Type::LUCK },
        { fbAttribute::FB_AttributeType_AWARENESS, Attribute__Type::AWARENESS },
        { fbAttribute::FB_AttributeType_STRENGTH, Attribute__Type::STRENGTH },
        { fbAttribute::FB_AttributeType_SPEED, Attribute__Type::SPEED },
        { fbAttribute::FB_AttributeType_INTELLIGENCE, Attribute__Type::INTELLIGENCE },
        { fbAttribute::FB_AttributeType_CHARISMA, Attribute__Type::CHARISMA }
    };
    return map.at(id);
}

} // namespace object
} // namespace game
