
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef SPECSTORAGE_HPP
#define SPECSTORAGE_HPP

#include"distribution.hpp"
#include<vector>

namespace game {
namespace common {

// special storage
template<class T> class SpecStorage {
public:
    explicit SpecStorage(T minimum, T maximum) noexcept
        :
        cur_{ minimum },
        acc_{ minimum },
        min_{ minimum },
        max_{ maximum }
    {}

    T get() const noexcept {
        return cur_;
    }

    T getAccepted() const noexcept {
        return acc_;
    }

    T getMinPossible() const noexcept {
        return min_;
    }

    T getMaxPossible() const noexcept {
        return max_;
    }

    void add(T shift) noexcept {
        cur_ += shift;
    }

    void accept() noexcept {
        acc_ = cur_;
    }

    void reject() noexcept {
        cur_ = acc_;
    }

    void reset() noexcept {
        cur_ = acc_ = min_;
    }

private:
    T           cur_;                           // current value of T (not accepted)
    T           acc_;                           // last accepted value of T
    const T     min_;                           // minimum value of T
    const T     max_;                           // maximum value of T
};

///************************************************************************************************

template<class Level, class Point>
bool changeLevel(
    SpecStorage<Level>& curentLevel,
    SpecStorage<Point>& storage,
    const Distribution<Point, Level>& distribution,
    const Level shift
) noexcept
{
    auto curLevel = static_cast<long long int>(curentLevel.get());
    auto newLevel = curLevel + common::toUnderlying(shift);
    if (newLevel >= common::toUnderlying(curentLevel.getAccepted()) &&
        newLevel <= common::toUnderlying(curentLevel.getMaxPossible()))
    {
        auto points = distribution.total(
            Level{ static_cast<std::underlying_type_t<Level>>(curLevel) },
            Level{ static_cast<std::underlying_type_t<Level>>(newLevel) }
        );
        auto sum = static_cast<long long int>(storage.get()) + common::toUnderlying(points);
        if (sum >= common::toUnderlying(storage.getMinPossible()) &&
            sum <= common::toUnderlying(storage.getMaxPossible()))
        {
            curentLevel.add(shift);
            storage.add(points);
            return true;
        }
    }
    return false;
}

} // namespace common
} // namespace game

#endif // !SPECSTORAGE_HPP
