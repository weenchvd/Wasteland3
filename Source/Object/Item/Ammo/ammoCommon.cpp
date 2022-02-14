
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammoCommon.hpp"
#include<unordered_map>

namespace game {
namespace object {

using namespace std;

Ammo__Type toAmmoType(std::string& key)
{
    static unordered_map<string, Ammo__Type> map{
        { "INVALID", Ammo__Type::INVALID },
        { "None", Ammo__Type::NONE },
        { "5.56", Ammo__Type::A_5_56 },
        { "7.62", Ammo__Type::A_7_62 },
    };
    return map.at(key);
}

} // namespace object
} // namespace game
