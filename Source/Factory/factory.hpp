
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include"ammo.hpp"
#include"item.hpp"
#include"option.hpp"
#include"plainText.hpp"
#include"unit.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace global {

class Factory {
public:
    template<class T>
    std::unique_ptr<object::Item> createItem(typename T::Model model) const {
        assert(T::isInitialized() == true);
        return std::unique_ptr<object::Item>(new T(std::move(model)));
    }

    std::unique_ptr<object::Item> createAmmo(
        object::Ammo::Type type,
        object::Ammo::ammo_quantity qty) const
    {
        assert(object::Ammo::isInitialized() == true);
        return std::unique_ptr<object::Item>(
            new object::Ammo(std::move(type), std::move(qty))
            );
    }

    template<class T>
    std::unique_ptr<object::Unit> createUnit(typename T::Model model) const {
        assert(T::isInitialized() == true);
        return std::unique_ptr<object::Unit>(new T(std::move(model)));
    }

private:
    friend class Locator;

    Factory() noexcept {}

    template<class T>
    std::unique_ptr<global::PlainText> createPlainText(typename T::Language lang) const {
        return std::unique_ptr<global::PlainText>(new T(lang));
    }

    std::unique_ptr<global::Options> createOptions() const {
        return std::unique_ptr<global::Options>(new global::Options());
    }

};

} // namespace global
} // namespace game

#endif // !FACTORY_HPP
