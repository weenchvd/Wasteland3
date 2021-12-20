
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include"item.hpp"
#include"unit.hpp"
#include<memory>

namespace Game
{
    namespace Global
    {
        class Factory {
        public:
            template<class T>
            std::unique_ptr<Game::Object::Item> createItem(typename T::Model model) {
                T::initializeReference();
                return std::unique_ptr<Game::Object::Item>(new T(std::move(model)));
            }

            template<class T>
            std::unique_ptr<Game::Object::Unit> createUnit(typename T::Model model) {
                T::initializeReference();
                return std::unique_ptr<Game::Object::Unit>(new T(std::move(model)));
            }

        };

    }
}

#endif // !FACTORY_HPP
