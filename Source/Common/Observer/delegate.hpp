
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DELEGATE_HPP
#define DELEGATE_HPP

#include<assert.h>

namespace game {
namespace common {

// @brief Generic, type-safe callback/delegate without dynamic memory allocation.
// @param "R" - the return type of the function to be bound to;
// @param "Ts..." - the argument types of the function to be bound to.
template<class R, class... Ts>
class Delegate {
private:
    using InstancePtr = void*;
    using FunctionPtr = R(*)(InstancePtr, Ts...);

    // @brief Free function.
    template<R(*Function)(Ts...)>
    static R freeFunction(InstancePtr, Ts... args)
    {
        return Function(args...);
    }

    // @brief NON-const class member function.
    template<class U, R(U::* Function)(Ts...)>
    static R memberFunction(InstancePtr instance, Ts... args)
    {
        assert(instance != nullptr);
        return (static_cast<U*>(instance)->*Function)(args...);
    }

public:
    // @brief Empty storage. Must be initialized by one of the "bind(...)".
    Delegate() noexcept
        :
        inst_{ nullptr },
        func_{ nullptr }
    {}

    Delegate(const Delegate&) = delete;
    Delegate& operator=(const Delegate&) = delete;
    Delegate(Delegate&&) = default;
    Delegate& operator=(Delegate&&) = default;

    // @brief Bind a free function (initialize the Delegate).
    template<R(*Function)(Ts...)>
    void bind()
    {
        assert(Function != nullptr);
        inst_ = nullptr;
        func_ = &freeFunction<Function>;
    }

    // @brief Bind a NON-const class member function (initialize the Delegate).
    template<class U, R(U::* Function)(Ts...)>
    void bind(U* instance)
    {
        assert(Function != nullptr);
        assert(instance != nullptr);
        inst_ = instance;
        func_ = &memberFunction<U, Function>;
    }

    // @brief Call the binded function with the arguments "args".
    R invoke(Ts... args) const
    {
        assert(func_ != nullptr);
        return func_(inst_, args...);
    }

private:
    InstancePtr inst_;
    FunctionPtr func_;
};

} // namespace common
} // namespace game

#endif // !DELEGATE_HPP
