
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SLOT_HPP
#define SLOT_HPP

#include<array>
#include<assert.h>
#include<memory>
#include<type_traits>

namespace game {
namespace common {

template<class T, unsigned int N>
class Slot {
public:
    using Type = typename T::Type;

    static constexpr int slotNotFound_ = -1;

public:
    Slot(std::array<Type, N> list) noexcept
        : type_{ list } {}

    unsigned int size() const noexcept {
        unsigned int size{ 0 };
        for (int i = 0; i < type_.size(); ++i) {
            if (type_[i] != Type::INVALID) {
                ++size;
            }
        }
        return size;
    }

    unsigned int sizeRaw() const noexcept {
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
    const std::unique_ptr<T>& get(unsigned int slotNumber) const noexcept {
        return elem_[slotNumber];
    }

    // 0 - first slot index
    const std::unique_ptr<T>& operator[](unsigned int slotNumber) const noexcept {
        return elem_[slotNumber];
    }

    // 0 - first slot index, if the type is not found, return -1
    int slotNumber(Type type) const noexcept {
        for (int i = 0; i < type_.size(); ++i) {
            if (type_[i] == type) {
                return i;
            }
        }
        return slotNotFound_;
    }

    template<class Base>
    bool set(
        unsigned int slotNumber,
        std::unique_ptr<Base>& source,
        bool (*typeChecker)(Type, Type)
    ) noexcept
    {
        assert(typeChecker != nullptr);
        assert((std::is_base_of_v<Base, T> == true));
        if (source == nullptr ||
            slotNumber >= elem_.size() ||
            type_[slotNumber] == Type::INVALID ||
            elem_[slotNumber] != nullptr ||
            std::is_base_of_v<Base, T> == false)
        {
            return false;
        }
        T* derived{ static_cast<T*>(source.get()) };
        if (typeChecker != nullptr &&
            typeChecker(type_[slotNumber], derived->type()) == true)
        {
            elem_[slotNumber].reset(static_cast<T*>(source.release()));
            return true;
        }
        return false;
    }

    template<class Base>
    bool unset(unsigned int slotNumber, std::unique_ptr<Base>& receiver) noexcept
    {
        assert((std::is_base_of_v<Base, T> == true));
        if (receiver != nullptr ||
            slotNumber >= elem_.size() ||
            elem_[slotNumber] == nullptr ||
            std::is_base_of_v<Base, T> == false)
        {
            return false;
        }
        receiver.reset(elem_[slotNumber].release());
        return true;
    }

private:
    std::array<std::unique_ptr<T>, N>   elem_;
    std::array<Type, N>                 type_;
};

} // namespace common
} // namespace game

#endif // !SLOT_HPP
