
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include"inventoryFB_generated.h"
#include"item.hpp"
#include<list>
#include<memory>

namespace game {
namespace object {

class InventoryIterator {
public:
    friend class Inventory;

public:
    InventoryIterator() noexcept;

private:
    explicit InventoryIterator(
        std::list<std::unique_ptr<Item>>::iterator iter,
        std::list<std::unique_ptr<Item>>* list);

public:
    bool isValid() const noexcept { return (list_ != nullptr) ? true : false; }

    void doInvalid() noexcept { *this = InventoryIterator{}; }

    std::list<std::unique_ptr<Item>>::iterator get() noexcept { return iter_; }

    std::list<std::unique_ptr<Item>>::const_iterator getConst() const noexcept { return iter_; }

private:
    std::list<std::unique_ptr<Item>>* getList() noexcept { return list_; }

public:
    InventoryIterator& operator++() noexcept;

    InventoryIterator& operator--() noexcept;

    bool operator==(const InventoryIterator& rhs) const noexcept { return this->iter_ == rhs.iter_; }

    bool operator!=(const InventoryIterator& rhs) const noexcept { return !(*this == rhs); }

private:
    std::list<std::unique_ptr<Item>>::iterator  iter_;
    std::list<std::unique_ptr<Item>>*           list_;
};

///************************************************************************************************

class Roster {
public:
    friend class Inventory;

public:
    struct ItemRange {
        InventoryIterator beg_;   // beginning
        InventoryIterator end_;   // end
    };

private:
    explicit Roster(Inventory& inventory) noexcept;

private:
    void itemType(Item::Type type) noexcept;

public:
    void refresh();

    const ItemRange& newItems() const noexcept { return newItems_; }

    ItemRange& newItems() noexcept { return newItems_; }

    const ItemRange& oldItems() const noexcept { return oldItems_; }

    ItemRange& oldItems() noexcept { return oldItems_; }

private:
    Inventory*          pInv_;
    ItemRange           newItems_;
    ItemRange           oldItems_;
    Item::Type          type_;
};

///************************************************************************************************

class Inventory {
public:
    Inventory() {}

    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

public:
    InventoryIterator insert(std::unique_ptr<Item>& item, bool isNew = false);

    std::unique_ptr<Item> extract(InventoryIterator& iterItem);

    Roster roster();

    Roster roster(Item::Type type);

    size_t size() noexcept;

    void viewed(InventoryIterator& iterItem);

    void viewedAll() { mergeLists(); }

    flatbuffers::Offset<fbInventory::FB_Inventory> serialize(
        flatbuffers::FlatBufferBuilder& fbb);

    static std::unique_ptr<Inventory> deserialize(const fbInventory::FB_Inventory* fb);

private:
    InventoryIterator insert(
        std::list<std::unique_ptr<Item>>& receiver,
        std::unique_ptr<Item>& item
    );

    void mergeLists();

    bool isAggregable(std::unique_ptr<Item>& item) const noexcept;

    void aggregate(std::unique_ptr<Item>& receiver, std::unique_ptr<Item>& source);

    bool check(const std::list<std::unique_ptr<Item>>& source) const;

    bool checkAll() const;

private:
    std::list<std::unique_ptr<Item>>    newItems_;
    std::list<std::unique_ptr<Item>>    oldItems_;
};

} // namespace object
} // namespace game

#endif // !INVENTORY_HPP
