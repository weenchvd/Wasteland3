
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"item.hpp"

namespace Game {
namespace Object {

using namespace std;

bool operator<(const unique_ptr<Item>& item1, const unique_ptr<Item>& item2) noexcept
{
    if (item1->itemType() < item2->itemType()) {
        return true;
    }
    if (item1->itemType() == item2->itemType() && item1->itemModel() < item2->itemModel()) {
        return true;
    }
    return false;
}

} // namespace Object
} // namespace Game
