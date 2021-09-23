
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SLOT_HPP
#define SLOT_HPP

#include<memory>
#include<array>

namespace Game
{
    namespace Common
    {
        template<class T, unsigned int N>
        class Slot {
        public:
            using Type = typename T::Type;

            static constexpr int slotNotFound = -1;

        public:
            Slot(std::array<Type, N> list) noexcept
                : type_{ list } {}

            unsigned int size() const noexcept {
                return elem_.size();
            }

            // 0 - first slot index
            const Type& type(unsigned int slotNumber) const noexcept {
                return type_[slotNumber];
            }

            // 0 - first slot index
            Type& type(unsigned int slotNumber) noexcept {
                return type_[slotNumber];
            }

            // 0 - first slot index
            const std::unique_ptr<T>& operator[](unsigned int slotNumber) const noexcept {
                return elem_[slotNumber];
            }

            // 0 - first slot index
            std::unique_ptr<T>& operator[](unsigned int slotNumber) noexcept {
                return elem_[slotNumber];
            }

            // 0 - first slot index, if the type is not found, return -1
            int slotNumber(Type type) const noexcept {
                for (int i = 0; i < type_.size(); ++i) {
                    if (type_[i] == type) {
                        return i;
                    }
                }
                return slotNotFound;
            }

        private:
            std::array<std::unique_ptr<T>, N>   elem_;
            std::array<Type, N>                 type_;
        };

    }
}

#endif // !SLOT_HPP
