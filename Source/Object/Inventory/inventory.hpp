
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
        using namespace std;

        class Inventory {
        public:
            Inventory() noexcept
                : nNew_{ 0 } {}
            
            Inventory(const Inventory&) = delete;
            Inventory& operator=(const Inventory&) = delete;

            //list<unique_ptr<Item>>::const_iterator cbegin() const noexcept {
            //    return invent_.cbegin();
            //}

            list<unique_ptr<Item>>::iterator begin() noexcept {
                return invent_.begin();
            }

            //list<unique_ptr<Item>>::const_iterator cend() const noexcept {
            //    return invent_.cend();
            //}

            list<unique_ptr<Item>>::iterator end() noexcept {
                return invent_.end();
            }

            void insert(unique_ptr<Item>& item);

            void bringBack(unique_ptr<Item>& item);

            list<unique_ptr<Item>>::iterator erase(list<unique_ptr<Item>>::iterator iter) noexcept {
                return invent_.erase(iter);
            }

            pair<list<unique_ptr<Item>>::iterator, list<unique_ptr<Item>>::iterator>
                range(ItemType type);
            
            void sort() {
                invent_.sort();
            }

        private:
            list<unique_ptr<Item>>  invent_;
            unsigned int            nNew_;          // number of new items
        };

    }
}

#endif // !INVENTORY_HPP
