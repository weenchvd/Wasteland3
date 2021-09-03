
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SWAP_HPP
#define SWAP_HPP

#include<memory>
#include<type_traits>

namespace Game
{
    namespace Common
    {
        using namespace std;

        template<class Base, class Derived>
        inline void swapUP(unique_ptr<Base>& base, unique_ptr<Derived>& derived)
        {
            unique_ptr<Base> temp{ derived.release() };
            derived.reset(static_cast<Derived*>(base.release()));
            base = move(temp);
        }

    }
}

#endif // !SWAP_HPP
