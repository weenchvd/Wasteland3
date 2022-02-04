
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SWAP_HPP
#define SWAP_HPP

#include<memory>
#include<type_traits>

namespace Game {
namespace Common {

template<class Base, class Derived>
inline void swapUP(std::unique_ptr<Base>& base, std::unique_ptr<Derived>& derived)
{
    std::unique_ptr<Base> temp{ derived.release() };
    derived.reset(static_cast<Derived*>(base.release()));
    base = std::move(temp);
}

} // namespace Common
} // namespace Game

#endif // !SWAP_HPP
