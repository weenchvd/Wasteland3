
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include"item.hpp"
#include<list>
#include<memory>

namespace Game
{
    namespace Object
    {
        class Inventory {
        public:
            struct ItemRange {
                std::list<std::unique_ptr<Item>>::const_iterator beg;   // beginning
                std::list<std::unique_ptr<Item>>::const_iterator end;   // end
            };

            struct Roster {
                ItemRange newItems;
                ItemRange oldItems;
            };

        public:
            Inventory()
                : viewed_{ true } {}
            
            Inventory(const Inventory&) = delete;
            Inventory& operator=(const Inventory&) = delete;

            // insert (put) an item into inventory 
            void insert(std::unique_ptr<Item>& item, bool isNew = false);

            std::unique_ptr<Item> extract(std::list<std::unique_ptr<Item>>::const_iterator iterator);

            Inventory::Roster roster();

            Inventory::Roster roster(Item::Type type);

            size_t size();
            
        private:
            void clean();

            void mergeLists();

            void erase(std::list<std::unique_ptr<Item>>::const_iterator iterator);

            std::list<std::unique_ptr<Item>>::iterator
                find(std::list<std::unique_ptr<Item>>::const_iterator iterator);

        private:
            std::list<std::unique_ptr<Item>>    newItems_;
            std::list<std::unique_ptr<Item>>    oldItems_;
            bool                                viewed_;
        };

    }
}

#endif // !INVENTORY_HPP
