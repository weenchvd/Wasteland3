
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OBSERVERDLL_HPP
#define OBSERVERDLL_HPP

#include"delegate.hpp"
#include<assert.h>

namespace Game {
namespace Common {

template<class R, class... Ts>
class SubjectDLL;

// @brief Observer Double Linked List
template<class R, class... Ts>
class ObserverDLL {
public:
    friend SubjectDLL<R, Ts...>;

public:
    ObserverDLL() noexcept
        :
        deleg_  {},
        prev_   { nullptr },
        next_   { nullptr }
    {}

    ObserverDLL(const ObserverDLL&) = delete;
    ObserverDLL& operator=(const ObserverDLL&) = delete;
    ObserverDLL(ObserverDLL&&) = default;
    ObserverDLL& operator=(ObserverDLL&&) = default;

    Delegate<R, Ts...>& getDelegate() noexcept {
        return deleg_;
    }

    R onNotify(Ts... args) const {
        return deleg_.invoke(args...);
    }

private:
    Delegate<R, Ts...>              deleg_;
    ObserverDLL*                    prev_;
    ObserverDLL*                    next_;
};


// @brief Subject Double Linked List
template<class R, class... Ts>
class SubjectDLL {
public:
    SubjectDLL() noexcept
        : head_{}
    {
        head_.prev_ = head_.next_ = &head_;
    }

    SubjectDLL(const SubjectDLL&) = delete;
    SubjectDLL& operator=(const SubjectDLL&) = delete;
    SubjectDLL(SubjectDLL&&) = default;
    SubjectDLL& operator=(SubjectDLL&&) = default;

    ~SubjectDLL() noexcept {}

    void addObserver(ObserverDLL<R, Ts...>* obs) noexcept;

    void removeObserver(ObserverDLL<R, Ts...>* obs) noexcept;

    R notify(Ts... args) const;

private:
    ObserverDLL<R, Ts...>           head_;
};

///------------------------------------------------------------------------------------------------

template<class R, class... Ts>
inline void SubjectDLL<R, Ts...>::addObserver(ObserverDLL<R, Ts...>* obs) noexcept
{
    assert(obs != &head_);
    obs->next_ = head_.next_;
    head_.next_->prev_ = obs;
    head_.next_ = obs;
    obs->prev_ = &head_;
}

template<class R, class... Ts>
inline void SubjectDLL<R, Ts...>::removeObserver(ObserverDLL<R, Ts...>* obs) noexcept
{
    assert(obs != &head_);
    obs->prev_->next_ = obs->next_;
    obs->next_->prev_ = obs->prev_;
}

template<class R, class... Ts>
inline R SubjectDLL<R, Ts...>::notify(Ts... args) const
{
    ObserverDLL<R, Ts...>* current = head_.next_;
    while (current != &head_) {
        current->onNotify(args...);
        current = current->next_;
    }
}

} // namespace Common
} // namespace Game

#endif // !OBSERVERDLL_HPP
