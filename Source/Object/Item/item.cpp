
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"item.hpp"
#include<memory>

namespace Game
{
    namespace Object
    {
        bool operator<(const unique_ptr<Item>& item1, const unique_ptr<Item>& item2)
        {
            if (item1->type() < item2->type()) {
                return true;
            }
            if (item1->type() == item2->type() && item1->model() < item2->model()) {
                return true;
            }
            return false;
        }

    }
}
