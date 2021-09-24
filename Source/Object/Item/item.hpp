
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_HPP
#define ITEM_HPP

#include"itemCommon.hpp"
#include"itemVisitor.hpp"
#include<memory>

namespace Game
{
    namespace Object
    {
        class Item {
        public:
            Item(const Item&) = delete;
            Item& operator=(const Item&) = delete;

            virtual ~Item() noexcept {}

            const ItemType type() const noexcept {
                return type_;
            }

            const ItemModel model() const noexcept {
                return model_;
            }

            virtual void accept(ItemVisitor& visitor) noexcept {};

        protected:
            explicit Item(ItemType type, ItemModel model) noexcept
                : type_{ type }, model_{ model } {}

        private:
            friend class Inventory;

        private:
            const ItemType          type_;          // type of Item
            const ItemModel         model_;         // model of Item
        };

        ///------------------------------------------------------------------------------------------------

        bool operator<(const std::unique_ptr<Item>& item1, const std::unique_ptr<Item>& item2) noexcept;

    }
}

#endif // !ITEM_HPP
