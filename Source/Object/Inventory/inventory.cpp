
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"error.hpp"
#include"inventory.hpp"
#include<algorithm>
#include<type_traits>

namespace Game
{
    namespace Object
    {
        using namespace std;

        void Inventory::insert(unique_ptr<Item>& item, bool isNew)
        {
            if (item) {
                if (isNew) {
                    // inserts the item first in the inventory
                    auto iter = newItems_.emplace(newItems_.cbegin(), unique_ptr<Item>{});
                    *iter = move(item);
                    viewed_ = false;
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
            catch (const Error::OutOfRangeError& e) {
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

        Inventory::Roster Inventory::roster()
        {
            clean();
            if (viewed_) {
                mergeLists();
            }
            viewed_ = true;

            Inventory::Roster roster;
            roster.newItems = { newItems_.cbegin(), newItems_.cend() };
            roster.oldItems = { oldItems_.cbegin(), oldItems_.cend() };
            return roster;
        }

        Inventory::Roster Inventory::roster(ItemType type)
        {
            struct ItemType_Less {
                bool operator()(const unique_ptr<Item>& item1, const unique_ptr<Item>& item2) {
                    if (item1->type() < item2->type()) {
                        return true;
                    }
                    return false;
                }
            };

            clean();
            mergeLists();
            viewed_ = true;

            Item i{ type, 0 };
            unique_ptr<Item> item{ &i };
            Inventory::Roster roster;
            roster.newItems = { newItems_.cbegin(), newItems_.cend() };
            roster.oldItems = {
                lower_bound(oldItems_.cbegin(), oldItems_.cend(), item, ItemType_Less{}),
                upper_bound(oldItems_.cbegin(), oldItems_.cend(), item, ItemType_Less{})
            };
            item.release();
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
            throw Error::OutOfRangeError{"Inventory::find()"};
        }

    }
}
