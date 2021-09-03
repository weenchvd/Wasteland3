
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"inventory.hpp"
#include"item.hpp"
#include"itemCommon.hpp"
#include<algorithm>
#include<list>
#include<memory>

namespace Game
{
    namespace Object
    {
        void Inventory::insert(unique_ptr<Item>& item)
        {
            if (item) {
                auto iter = invent_.emplace(invent_.cbegin(), unique_ptr<Item>{});
                *iter = move(item);
                ++nNew_;
            }
        }

        void Inventory::bringBack(unique_ptr<Item>& item)
        {
            if (item) {
                auto iter = invent_.emplace(invent_.cbegin(), unique_ptr<Item>{});
                *iter = move(item);
            }
        }

        pair<list<unique_ptr<Item>>::iterator, list<unique_ptr<Item>>::iterator>
            Inventory::range(ItemType type)
        {
            struct Item_Less {
                bool operator()(const unique_ptr<Item>& item1, const unique_ptr<Item>& item2)
                {
                    if (item1->type() < item2->type()) {
                        return true;
                    }
                    return false;
                }
            };

            Item i{ type, 0 };
            unique_ptr<Item> item{ &i };
            pair<list<unique_ptr<Item>>::iterator, list<unique_ptr<Item>>::iterator> ret{
                lower_bound(invent_.begin(), invent_.end(), item, Item_Less{}),
                upper_bound(invent_.begin(), invent_.end(), item, Item_Less{})
            };
            item.release();
            return ret;
        }

    }
}
