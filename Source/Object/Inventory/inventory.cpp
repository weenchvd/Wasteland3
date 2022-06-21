
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"exception.hpp"
#include"inventory.hpp"
#include"locator.hpp"
#include"weapon.hpp"
#include<algorithm>
#include<assert.h>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

InventoryIterator::InventoryIterator() noexcept
    :
    iter_{ list<unique_ptr<Item>>::iterator{} },
    list_{ nullptr }
{}

InventoryIterator::InventoryIterator(
    list<unique_ptr<Item>>::iterator iter,
    list<unique_ptr<Item>>* list)
    :
    iter_{ iter },
    list_{ list }
{}

InventoryIterator& InventoryIterator::operator++() noexcept
{
    ++iter_;
    return *this;
}

InventoryIterator& InventoryIterator::operator--() noexcept
{
    --iter_;
    return *this;
}

///************************************************************************************************

Roster::Roster(Inventory& inventory) noexcept
    :
    pInv_           { &inventory },
    newItems_       { InventoryIterator{}, InventoryIterator{} },
    oldItems_       { InventoryIterator{}, InventoryIterator{} },
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

InventoryIterator Inventory::insert(unique_ptr<Item>& item, bool isNew)
{
    return (isNew == true) ? insert(newItems_, item) : insert(oldItems_, item);
}

InventoryIterator Inventory::insert(
    list<unique_ptr<Item>>& receiver,
    unique_ptr<Item>& item)
{
    struct ItemLessByModel {
        bool operator()(const unique_ptr<Item>& lhs, const unique_ptr<Item>& rhs) {
            return isLessByModel(*lhs, *rhs);
        }
    };

    InventoryIterator ret{};
    if (item != nullptr) {
        auto pos{ lower_bound(receiver.begin(), receiver.end(), item, ItemLessByModel{}) };
        if (&receiver == &newItems_) {
            // inserts the item first in the receiver
            auto iter{ receiver.emplace(receiver.begin(), unique_ptr<Item>{}) };
            *iter = move(item);
            ret = InventoryIterator{ iter, &receiver };
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
                ret = InventoryIterator{ pos, &receiver };
            }
            else {
                auto iter{ receiver.emplace(pos, unique_ptr<Item>{}) };
                *iter = move(item);
                ret = InventoryIterator{ iter, &receiver };
            }
        }
    }
    assert(item == nullptr);
    assert(check(receiver) == true);
    assert(ret.isValid() == true);
    return ret;
}

unique_ptr<Item> Inventory::extract(InventoryIterator& iterItem)
{
    assert(iterItem.isValid() == true);
    unique_ptr<Item> item{};
    if (iterItem.isValid() == true) {
        item = move(*iterItem.get());
        assert(*iterItem.getConst() == nullptr);
        iterItem.getList()->erase(iterItem.getConst());
        assert(check(*iterItem.getList()) == true);
        iterItem.doInvalid();
        assert(iterItem.isValid() == false);
    }
    return item;
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
    roster.newItems_ = {
        InventoryIterator{ newItems_.begin(), &newItems_ },
        InventoryIterator{ newItems_.end(), &newItems_ }
    };
    roster.oldItems_ = {
        InventoryIterator{ oldItems_.begin(), &oldItems_ },
        InventoryIterator{ oldItems_.end(), &oldItems_ }
    };
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
    roster.newItems_ = {
        InventoryIterator{ newItems_.begin(), &newItems_ },
        InventoryIterator{ newItems_.end(), &newItems_ }
    };
    roster.oldItems_ = {
        InventoryIterator{
            lower_bound(oldItems_.begin(), oldItems_.end(), type, ItemType_Less_LowerBounds{}),
            &oldItems_
        },
        InventoryIterator{
            upper_bound(oldItems_.begin(), oldItems_.end(), type, ItemType_Less_UpperBounds{}),
            &oldItems_
        }
    };
    return roster;
}

size_t Inventory::size() noexcept
{
    assert(checkAll() == true);
    return newItems_.size() + oldItems_.size();
}

void Inventory::viewed(InventoryIterator& iterItem)
{
    assert(iterItem.isValid() == true);
    if (iterItem.isValid() == true && iterItem.getList() == &newItems_) {
        InventoryIterator temp{ insert(oldItems_, *iterItem.get()) };
        extract(iterItem);
        iterItem = move(temp);
        assert(checkAll() == true);
        assert(iterItem.isValid() == true);
    }
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

flatbuffers::Offset<fbInventory::FB_Inventory> Inventory::serialize(
    flatbuffers::FlatBufferBuilder& fbb)
{
    /// https://google.github.io/flatbuffers/flatbuffers_guide_tutorial.html
    /// Important: Unlike structs, you should not nest tables or other objects,
    /// which is why we created all the strings/vectors/tables that this monster refers to
    /// before start. If you try to create any of them between start and end, you will get
    /// an assert/exception/panic depending on your language.

    Roster rost{ roster() };
    vector<flatbuffers::Offset<fbItem::FB_Item>> newItems;
    vector<flatbuffers::Offset<fbItem::FB_Item>> oldItems;

    for (auto iter{ rost.newItems().beg_ }; iter != rost.newItems().end_; ++iter) {
        assert(iter.isValid());
        newItems.push_back((*iter.get())->serialize(fbb));
    }
    for (auto iter{ rost.oldItems().beg_ }; iter != rost.oldItems().end_; ++iter) {
        assert(iter.isValid());
        oldItems.push_back((*iter.get())->serialize(fbb));
    }

    auto newOffset{ fbb.CreateVector(newItems) };
    auto oldOffset{ fbb.CreateVector(oldItems) };

    fbInventory::FB_InventoryBuilder builder{ fbb };
    builder.add_new_items(newOffset);
    builder.add_old_items(oldOffset);
    return builder.Finish();
}

std::unique_ptr<Inventory> Inventory::deserialize(
    const fbInventory::FB_Inventory* fb)
{
    assert(fb != nullptr);
    const auto& f{ global::Locator::getFactory() };
    auto inventory{ f.createInventory() };

    const auto* newItems{ fb->new_items() };
    if (newItems != nullptr) {
        long long int size{ newItems->size() };
        for (long long int i{ size - 1 }; i >= 0; --i) {
            auto item{ Item::deserialize(newItems->Get(i)) };
            inventory->insert(item, true);
        }
    }

    const auto* oldItems{ fb->old_items() };
    if (oldItems != nullptr) {
        for (long long int i = 0; i < oldItems->size(); ++i) {
            auto item{ Item::deserialize(oldItems->Get(i)) };
            inventory->insert(item, false);
        }
    }

    return inventory;
}

} // namespace object
} // namespace game
