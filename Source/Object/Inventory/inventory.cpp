
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
    if (isNew == true) {
        insert(newItems_, item, true);
    }
    else {
        insert(oldItems_, item);
    }
}

void Inventory::insert(list<unique_ptr<Item>>& receiver, unique_ptr<Item>& item, bool insertFirst)
{
    if (item != nullptr) {
        auto pos{ lower_bound(receiver.begin(), receiver.end(), item) };
        if (insertFirst == true) {
            // inserts the item first in the receiver
            auto iter{ receiver.emplace(receiver.begin(), unique_ptr<Item>{}) };
            *iter = move(item);
            if (isAggregable(*iter) == true && pos != receiver.cend() && *pos == *iter) {
                aggregate(*iter, *pos);
                erase(IteratorBundle{ pos, &receiver });
            }
        }
        else {
            // inserts the item into the receiver first among the same ones
            if (isAggregable(item) == true && pos != receiver.cend() && *pos == item) {
                aggregate(*pos, item);
            }
            else {
                auto iter{ receiver.emplace(pos, unique_ptr<Item>{}) };
                *iter = move(item);
            }
        }
    }
}

unique_ptr<Item> Inventory::extract(list<unique_ptr<Item>>::const_iterator iterator)
{
    return extract(find(iterator));
}

unique_ptr<Item> Inventory::extract(IteratorBundle iteratorBundle)
{
    unique_ptr<Item> item{};
    if (iteratorBundle.list_ != nullptr) {
        item = move(*iteratorBundle.iter_);
        erase(iteratorBundle);
    }
    return item;
}

void Inventory::erase(IteratorBundle iteratorBundle)
{
    assert(iteratorBundle.list_ != nullptr);
    iteratorBundle.list_->erase(iteratorBundle.iter_);
}

bool Inventory::isAggregable(std::unique_ptr<Item>& item) const noexcept
{
    switch (item->itemType()) {
    case Item::Type::AMMO:
        return true;
    default:
        return false;
    }
}

void Inventory::aggregate(unique_ptr<Item>& receiver, unique_ptr<Item>& source)
{
    assert(receiver == source);
    switch (receiver->itemType()) {
    case Item::Type::AMMO:
        static_cast<Ammo*>(receiver.get())->quantityAdd(
            static_cast<Ammo*>(source.get())->quantity()
        );
        break;
    default:
        break;
    }
    source.reset();
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
    clean();
    for (auto iter{ newItems_.begin() }; iter != newItems_.end(); ++iter) {
        insert(oldItems_, *iter);
        assert(*iter == nullptr);
    }
    newItems_.clear();
}

void Inventory::clean()
{
    struct UniquePtr_Null {
        bool operator()(const unique_ptr<Item>& item) {
            return item == nullptr ? true : false;
        }
    };

    newItems_.remove_if(UniquePtr_Null{});
    oldItems_.remove_if(UniquePtr_Null{});
}

Inventory::IteratorBundle Inventory::find(list<unique_ptr<Item>>::const_iterator iterator)
{
    clean();
    for (auto iter = newItems_.begin(); iter != newItems_.end(); ++iter) {
        if (iterator == iter) {
            return { iter, &newItems_ };
        }
    }
    for (auto iter = oldItems_.begin(); iter != oldItems_.end(); ++iter) {
        if (iterator == iter) {
            return { iter, &oldItems_ };
        }
    }
    return { list<unique_ptr<Item>>::iterator{}, nullptr };
}

} // namespace object
} // namespace game
