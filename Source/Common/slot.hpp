
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SLOT_HPP
#define SLOT_HPP

#include"common.hpp"
#include"exception.hpp"
#include<array>
#include<assert.h>
#include<memory>
#include<type_traits>

namespace game {
namespace common {

template<class T, unsigned char N>
class Slot {
public:
    using Type          = typename T::Type;
    using slot_number_t = unsigned char;

    static constexpr int           slotNotFound_{ -1 };

public:
    Slot(const std::array<Type, N>& list);

    Slot(const Slot&) = delete;
    Slot& operator=(const Slot&) = delete;

    ~Slot() noexcept {}

public:
    size_t size() const noexcept;

    const Type& type(slot_number_t slotNumber) const noexcept;

    const std::unique_ptr<T>& get(slot_number_t slotNumber) const noexcept;

    const std::unique_ptr<T>& operator[](slot_number_t slotNumber) const noexcept;

    // @brief If the type is not found, return the 'slotNotFound_' member
    int slotNumber(Type type) const noexcept;

    template<class Base>
    bool set(slot_number_t slotNumber,
             std::unique_ptr<Base>& source,
             bool (*typeChecker)(Type, Type)) noexcept;

    template<class Base>
    bool unset(slot_number_t slotNumber, std::unique_ptr<Base>& receiver) noexcept;

private:
    bool isValidSlotNumber(slot_number_t number) const noexcept {
        return number < elem_.size();
    }

    bool isSlotFull(slot_number_t slotNumber) const noexcept;

private:
    std::array<std::unique_ptr<T>, N>   elem_;
    std::array<Type, N>                 type_;
};

///************************************************************************************************

template<class T, unsigned char N>
Slot<T, N>::Slot(const std::array<Type, N>& list)
    :
    type_{ list }
{
    bool invalidTypeEncountered{ false };
    for (int i = 0; i < type_.size(); ++i) {
        if (type_[i] == Type::__INVALID) {
            invalidTypeEncountered = true;
        }
        else if (isValidEnum(type_[i]) || isValidEnumAux(type_[i])) {
            if (invalidTypeEncountered) throw InitializationError{
                "[Slot::Slot] 'INVALID' type must not precede a valid type"
            };
        }
        else throw InitializationError{
            "[Slot::Slot] initialization with invalid type"
        };
    }
}

template<class T, unsigned char N>
inline size_t Slot<T, N>::size() const noexcept {
    size_t size{ 0 };
    for (size_t i = 0; i < type_.size(); ++i) {
        if (isValidEnum(type_[i]) || isValidEnumAux(type_[i])) {
            ++size;
        }
    }
    return { size };
}

template<class T, unsigned char N>
inline const typename Slot<T, N>::Type& Slot<T, N>::type(slot_number_t slotNumber) const noexcept
{
    assert(isValidSlotNumber(slotNumber));
    return type_[slotNumber];
}

template<class T, unsigned char N>
inline const std::unique_ptr<T>& Slot<T, N>::get(slot_number_t slotNumber) const noexcept
{
    assert(isValidSlotNumber(slotNumber));
    return elem_[slotNumber];
}

template<class T, unsigned char N>
inline const std::unique_ptr<T>& Slot<T, N>::operator[](slot_number_t slotNumber) const noexcept
{
    assert(isValidSlotNumber(slotNumber));
    return elem_[slotNumber];
}

template<class T, unsigned char N>
inline int Slot<T, N>::slotNumber(Type type) const noexcept {
    for (int i = 0; i < type_.size(); ++i) {
        if (type_[i] == type) {
            return { i };
        }
    }
    return { slotNotFound_ };
}

template<class T, unsigned char N>
template<class Base>
bool Slot<T, N>::set(slot_number_t slotNumber,
                     std::unique_ptr<Base>& source,
                     bool (*typeChecker)(Type, Type)) noexcept
{
    assert(typeChecker != nullptr);
    assert((std::is_base_of_v<Base, T>));
    if (source == nullptr ||
        !isValidSlotNumber(slotNumber) ||
        isSlotFull(slotNumber) ||
        !(isValidEnum(type_[slotNumber]) || isValidEnumAux(type_[slotNumber])) ||
        !std::is_base_of_v<Base, T>)
    {
        return false;
    }
    T* derived{ static_cast<T*>(source.get()) };
    if (typeChecker == nullptr || !typeChecker(type_[slotNumber], derived->type()))
    {
        return false;
    }
    elem_[slotNumber].reset(static_cast<T*>(source.release()));
    return true;
}

template<class T, unsigned char N>
template<class Base>
bool Slot<T, N>::unset(slot_number_t slotNumber, std::unique_ptr<Base>& receiver) noexcept
{
    assert((std::is_base_of_v<Base, T>));
    if (receiver != nullptr ||
        !isValidSlotNumber(slotNumber) ||
        !isSlotFull(slotNumber) ||
        !std::is_base_of_v<Base, T>)
    {
        return false;
    }
    receiver.reset(elem_[slotNumber].release());
    return true;
}

template<class T, unsigned char N>
inline bool Slot<T, N>::isSlotFull(slot_number_t slotNumber) const noexcept
{
    assert(isValidSlotNumber(slotNumber));
    return elem_[slotNumber] != nullptr;
}

} // namespace common
} // namespace game

#endif // !SLOT_HPP
