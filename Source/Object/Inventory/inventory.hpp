
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include"item.hpp"
#include<list>
#include<memory>

namespace game {
namespace object {

class Roster {
public:
    friend class Inventory;

public:
    struct ItemRange {
        std::list<std::unique_ptr<Item>>::const_iterator beg_;   // beginning
        std::list<std::unique_ptr<Item>>::const_iterator end_;   // end
    };

private:
    Roster(Inventory& inventory) noexcept;

public:
    void itemType(Item::Type type) noexcept;

    void refresh();

    void clear() { *this = Roster{ *pInv_ }; }

    ItemRange newItems() noexcept { return newItems_; }

    ItemRange oldItems() noexcept { return oldItems_; }

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

    // insert (put) an item into inventory 
    void insert(std::unique_ptr<Item>& item, bool isNew = false);

    std::unique_ptr<Item> extract(std::list<std::unique_ptr<Item>>::const_iterator iterator);

    Roster roster();

    Roster roster(Item::Type type);

    size_t size();

    void viewed() noexcept { mergeLists(); }

private:
    void clean();

    void mergeLists();

    void erase(std::list<std::unique_ptr<Item>>::const_iterator iterator);

    std::list<std::unique_ptr<Item>>::iterator
        find(std::list<std::unique_ptr<Item>>::const_iterator iterator);

private:
    std::list<std::unique_ptr<Item>>    newItems_;
    std::list<std::unique_ptr<Item>>    oldItems_;
};

} // namespace object
} // namespace game

#endif // !INVENTORY_HPP
