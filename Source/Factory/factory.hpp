
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include"plainText.hpp"
#include"item.hpp"
#include"option.hpp"
#include"unit.hpp"
#include<memory>

namespace game {
namespace global {

class Factory {
public:
    template<class T>
    std::unique_ptr<object::Item> createItem(typename T::Model model) const {
        //T::initialize();
        return std::unique_ptr<object::Item>(new T(std::move(model)));
    }

    template<class T>
    std::unique_ptr<object::Unit> createUnit(typename T::Model model) const {
        //T::initialize();
        return std::unique_ptr<object::Unit>(new T(std::move(model)));
    }

private:
    friend class Locator;

    Factory() noexcept {}

    template<class T>
    std::unique_ptr<global::PlainText> createPlainText(typename T::Language lang) const {
        return std::unique_ptr<global::PlainText>(new T(lang));
    }

    std::unique_ptr<global::Option> createOption() const {
        return std::unique_ptr<global::Option>(new global::Option());
    }

};

} // namespace global
} // namespace game

#endif // !FACTORY_HPP
