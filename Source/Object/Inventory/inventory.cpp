
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

list<unique_ptr<Item>>::const_iterator Inventory::insert(unique_ptr<Item>& item, bool isNew)
{
    return (isNew == true) ? insert(newItems_, item) : insert(oldItems_, item);
}

list<unique_ptr<Item>>::const_iterator Inventory::insert(
    list<unique_ptr<Item>>& receiver,
    unique_ptr<Item>& item)
{
    struct ItemLessByModel {
        bool operator()(const unique_ptr<Item>& lhs, const unique_ptr<Item>& rhs) {
            return isLessByModel(*lhs, *rhs);
        }
    };

    list<unique_ptr<Item>>::const_iterator ret{};
    if (item != nullptr) {
        auto pos{ lower_bound(receiver.begin(), receiver.end(), item, ItemLessByModel{}) };
        if (&receiver == &newItems_) {
            // inserts the item first in the receiver
            auto iter{ receiver.emplace(receiver.begin(), unique_ptr<Item>{}) };
            *iter = move(item);
            ret = iter;
            if (isAggregable(*iter) == true &&
                pos != receiver.cend() &&
                object::isSameModel(**pos, **iter) == true)
            {
                aggregate(*iter, *pos);
                receiver.erase(pos);
            }
        }
        else {
            // inserts the item into the receiver first among the same ones
            if (isAggregable(item) == true &&
                pos != receiver.cend() &&
                object::isSameModel(**pos, *item) == true)
            {
                aggregate(*pos, item);
                ret = pos;
            }
            else {
                auto iter{ receiver.emplace(pos, unique_ptr<Item>{}) };
                *iter = move(item);
                ret = iter;
            }
        }
    }
    assert(item == nullptr);
    assert(check(receiver) == true);
    return ret;
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
        assert(*iteratorBundle.iter_ == nullptr);
        iteratorBundle.list_->erase(iteratorBundle.iter_);
        assert(check(*iteratorBundle.list_) == true);
    }
    return item;
}

pair<list<unique_ptr<Item>>::iterator, bool> Inventory::getIterator(
    list<unique_ptr<Item>>::const_iterator iterator)
{
    IteratorBundle bundle{ find(iterator) };
    return { bundle.iter_, bundle.list_ != nullptr ? true : false };
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
    assert(object::isSameModel(*receiver, *source) == true);
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
    assert(checkAll() == true);

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

    mergeLists();
    assert(checkAll() == true);

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
    assert(checkAll() == true);
    return newItems_.size() + oldItems_.size();
}

list<unique_ptr<Item>>::const_iterator Inventory::viewed(
    list<unique_ptr<Item>>::const_iterator iterator) noexcept
{
    for (auto iter = newItems_.begin(); iter != newItems_.end(); ++iter) {
        if (*iterator == *iter) {
            auto ret{ insert(oldItems_, *iter) };
            extract(IteratorBundle{ iter, &newItems_ });
            assert(checkAll() == true);
            return ret;
        }
    }
    return iterator;
}

inline void Inventory::mergeLists()
{
    assert(checkAll() == true);
    for (auto iter{ newItems_.begin() }; iter != newItems_.end(); ++iter) {
        insert(oldItems_, *iter);
    }
    newItems_.clear();
    assert(check(newItems_) == true);
}

Inventory::IteratorBundle Inventory::find(list<unique_ptr<Item>>::const_iterator iterator)
{
    assert(checkAll() == true);
    for (auto iter = newItems_.begin(); iter != newItems_.end(); ++iter) {
        if (*iterator == *iter) {
            return { iter, &newItems_ };
        }
    }
    for (auto iter = oldItems_.begin(); iter != oldItems_.end(); ++iter) {
        if (*iterator == *iter) {
            return { iter, &oldItems_ };
        }
    }
    return { list<unique_ptr<Item>>::iterator{}, nullptr };
}

bool Inventory::check(const list<unique_ptr<Item>>& source) const
{
    if (&source == &newItems_) {
        for (auto iter{ source.cbegin() }; iter != source.cend(); ++iter) {
            if (*iter == nullptr) return false;
        }
    }
    else if (&source == &oldItems_) {
        for (auto iter{ source.cbegin() }; iter != source.cend(); ++iter) {
            if (*iter == nullptr) return false;
            auto iterNext{ iter };
            ++iterNext;
            if (iterNext != source.cend() &&
                *iterNext != nullptr &&
                isGreaterByModel(**iter, **iterNext) == true)
            {
                return false;
            }
        }
    }
    else {
        return false;
    }
    return true;
}

bool Inventory::checkAll() const
{
    return check(newItems_) && check(oldItems_);
}

} // namespace object
} // namespace game
