
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
        using namespace std;

        template<class Type, unsigned int N>
        class Slot {
        public:
            using ValueType = Type;
            using Kind      = typename ValueType::Type;

            static constexpr int slotNotFound = -1;

        public:
            Slot(array<Kind, N> list) noexcept
                : kind_{ list } {}

            unsigned int size() const noexcept {
                return elem_.size();
            }

            // 0 - first slot index
            const Kind& kind(unsigned int slotNumber) const noexcept {
                return kind_[slotNumber];
            }

            // 0 - first slot index
            Kind& kind(unsigned int slotNumber) noexcept {
                return kind_[slotNumber];
            }

            // 0 - first slot index
            const unique_ptr<ValueType>& operator[](unsigned int slotNumber) const noexcept {
                return elem_[slotNumber];
            }

            // 0 - first slot index
            unique_ptr<ValueType>& operator[](unsigned int slotNumber) noexcept {
                return elem_[slotNumber];
            }

            // if the type is not found, return -1
            int slotNumber(Kind type) const noexcept {
                for (int i = 0; i < kind_.size(); ++i) {
                    if (kind_[i] == type) {
                        return i;
                    }
                }
                return slotNotFound;
            }

        private:
            array<unique_ptr<ValueType>, N>     elem_;
            array<Kind, N>                      kind_;
        };

    }
}

#endif // !SLOT_HPP
