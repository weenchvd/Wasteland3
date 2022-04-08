
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ITEM_HPP
#define ITEM_HPP

#include"common.hpp"
#include"itemCommon.hpp"
#include"itemVisitor.hpp"
#include<memory>

namespace game {
namespace object {

class Item {
public:
    using Type          = Item__Type;
    using Model         = Item__Model;

public:
    Item() noexcept {}

    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;

    virtual ~Item() noexcept {}

    virtual Item::Type itemType() const noexcept = 0;

    virtual Item::Model itemModel() const noexcept = 0;

    virtual const common::Text& name() const noexcept = 0;

    virtual void accept(ItemVisitor& visitor) const noexcept {};
};

///------------------------------------------------------------------------------------------------

//bool operator==(const Item& lhs, const Item& rhs) noexcept;

//bool operator<(const std::unique_ptr<Item>& lhs, const std::unique_ptr<Item>& rhs) noexcept;

bool isSameModel(const Item& lhs, const Item& rhs) noexcept;

bool isLessByModel(const Item& lhs, const Item& rhs) noexcept;

bool isGreaterByModel(const Item& lhs, const Item& rhs) noexcept;

} // namespace object
} // namespace game

#endif // !ITEM_HPP
