
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include"ammo.hpp"
#include"item.hpp"
#include"option.hpp"
#include"unit.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace global {

class Factory {
private:
    friend class Locator;

private:
    Factory() noexcept {}

public:
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

public:
    template<class T>
    std::unique_ptr<object::Item> createItem(typename T::Model model) const;

    std::unique_ptr<object::Item> createAmmo(
        object::Ammo::Type type,
        object::Ammo::ammo_quantity qty
    ) const;

    template<class T>
    std::unique_ptr<object::Unit> createUnit(typename T::Model model) const;

private:
    std::unique_ptr<global::Options> createOptions() const {
        return std::unique_ptr<global::Options>(new global::Options());
    }

};

///************************************************************************************************

template<class T>
inline std::unique_ptr<object::Item> Factory::createItem(typename T::Model model) const
{
    assert(T::isInitialized());
    return std::unique_ptr<object::Item>(new T(std::move(model)));
}

inline std::unique_ptr<object::Item> Factory::createAmmo(
    object::Ammo::Type type,
    object::Ammo::ammo_quantity qty) const
{
    assert(object::Ammo::isInitialized());
    return std::unique_ptr<object::Item>(new object::Ammo(std::move(type), std::move(qty)));
}

template<class T>
inline std::unique_ptr<object::Unit> Factory::createUnit(typename T::Model model) const
{
    assert(T::isInitialized());
    return std::unique_ptr<object::Unit>(new T(std::move(model)));
}

} // namespace global
} // namespace game

#endif // !FACTORY_HPP
