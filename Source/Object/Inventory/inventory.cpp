
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"error.hpp"
#include"inventory.hpp"
#include"weapon.hpp"
#include<algorithm>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

Roster::Roster(Inventory& inventory) noexcept
    :
    pInv_           { &inventory },
    newItems_       {},
    oldItems_       {},
    type_           { Item::Type::INVALID }
{}

void Roster::itemType(Item::Type type) noexcept
{
    type_ = type;
    assert(common::isValidEnum(type_));
}

void Roster::refresh()
{
    if (common::isValidEnum(type_)) {
        *this = pInv_->roster(type_);
    }
    else {
        *this = pInv_->roster();
    }
}

///************************************************************************************************

void Inventory::insert(unique_ptr<Item>& item, bool isNew)
{
    if (item) {
        if (isNew) {
            // inserts the item first in the inventory
            auto iter = newItems_.emplace(newItems_.cbegin(), unique_ptr<Item>{});
            *iter = move(item);
        }
        else {
            // inserts the item into the inventory last among the same ones
            auto pos = upper_bound(oldItems_.cbegin(), oldItems_.cend(), item);
            auto iter = oldItems_.emplace(pos, unique_ptr<Item>{});
            *iter = move(item);
        }
    }
}

unique_ptr<Item> Inventory::extract(list<unique_ptr<Item>>::const_iterator iterator)
{
    list<unique_ptr<Item>>::iterator iter;
    try {
        iter = find(iterator);
    }
    catch (const error::OutOfRangeError& e) {
        return unique_ptr<Item>{};
    }
    unique_ptr<Item> item = move(*iter);
    erase(iter);
    return item;
}

void Inventory::erase(list<unique_ptr<Item>>::const_iterator iterator)
{
    if (lower_bound(newItems_.cbegin(), newItems_.cend(), *iterator) != newItems_.cend()) {
        newItems_.erase(iterator);
    }
    else {
        oldItems_.erase(iterator);
    }
}

Roster Inventory::roster()
{
    clean();

    Roster roster{ *this };
    roster.newItems_ = { newItems_.cbegin(), newItems_.cend() };
    roster.oldItems_ = { oldItems_.cbegin(), oldItems_.cend() };
    return roster;
}

Roster Inventory::roster(Item::Type type)
{
    struct ItemType_Less_LowerBounds {
        bool operator()(const unique_ptr<Item>& item, const Item::Type type) {
            return item->itemType() < type ? true : false;
        }
    };

    struct ItemType_Less_UpperBounds {
        bool operator()(const Item::Type type, const unique_ptr<Item>& item) {
            return type < item->itemType() ? true : false;
        }
    };

    clean();
    mergeLists();

    Roster roster{ *this };
    roster.itemType(type);
    roster.newItems_ = { newItems_.cbegin(), newItems_.cend() };
    roster.oldItems_ = {
        lower_bound(oldItems_.cbegin(), oldItems_.cend(), type, ItemType_Less_LowerBounds{}),
        upper_bound(oldItems_.cbegin(), oldItems_.cend(), type, ItemType_Less_UpperBounds{})
    };
    return roster;
}

size_t Inventory::size()
{
    clean();
    return newItems_.size() + oldItems_.size();
}

inline void Inventory::mergeLists()
{
    newItems_.sort();
    oldItems_.merge(newItems_);
}

void Inventory::clean()
{
    struct UniquePtr_Null {
        bool operator()(const unique_ptr<Item>& item) {
            if (item == nullptr) {
                return true;
            }
            return false;
        }
    };

    newItems_.remove_if(UniquePtr_Null{});
    oldItems_.remove_if(UniquePtr_Null{});
}

list<unique_ptr<Item>>::iterator Inventory::find(list<unique_ptr<Item>>::const_iterator iterator)
{
    clean();
    for (auto iter = newItems_.begin(); iter != newItems_.end(); ++iter) {
        if (iterator == iter) {
            return iter;
        }
    }
    for (auto iter = oldItems_.begin(); iter != oldItems_.end(); ++iter) {
        if (iterator == iter) {
            return iter;
        }
    }
    throw error::OutOfRangeError{"Inventory::find()"};
}

} // namespace object
} // namespace game
