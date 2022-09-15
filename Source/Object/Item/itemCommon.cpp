
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemCommon.hpp"

namespace game {
namespace object {

using namespace std;

bool isCompatible(Item__Type id1, Item__Type id2)
{
    if (id1 == id2) return true;
    return false;
}

} // namespace object
} // namespace game
