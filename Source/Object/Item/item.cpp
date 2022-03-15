
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"item.hpp"

namespace game {
namespace object {

using namespace std;

//bool operator==(const Item& lhs, const Item& rhs) noexcept
//{
//    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() == rhs.itemModel()) {
//        return true;
//    }
//    return false;
//}

//bool operator<(const unique_ptr<Item>& lhs, const unique_ptr<Item>& rhs) noexcept
//{
//    if (lhs->itemType() < rhs->itemType()) {
//        return true;
//    }
//    if (lhs->itemType() == rhs->itemType() && lhs->itemModel() < rhs->itemModel()) {
//        return true;
//    }
//    return false;
//}

bool isSameModel(const Item& lhs, const Item& rhs) noexcept
{
    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() == rhs.itemModel()) {
        return true;
    }
    return false;
}

bool isLessByModel(const Item& lhs, const Item& rhs) noexcept
{
    if (lhs.itemType() < rhs.itemType()) {
        return true;
    }
    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() < rhs.itemModel()) {
        return true;
    }
    return false;
}

bool isGreaterByModel(const Item& lhs, const Item& rhs) noexcept
{
    if (lhs.itemType() > rhs.itemType()) {
        return true;
    }
    if (lhs.itemType() == rhs.itemType() && lhs.itemModel() > rhs.itemModel()) {
        return true;
    }
    return false;
}

} // namespace object
} // namespace game
