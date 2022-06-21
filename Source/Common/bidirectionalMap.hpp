
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef BIDIRECTIONAL_MAP_HPP
#define BIDIRECTIONAL_MAP_HPP

#include"boost/bimap.hpp"

namespace game {
namespace common {

template<class LeftType,  LeftType  invalidL,
         class RightType, RightType invalidR>
class BidirectionalMap {
public:
    using map_t = boost::bimap<LeftType, RightType>;

public:
    BidirectionalMap() noexcept {}

    BidirectionalMap(const BidirectionalMap&) = delete;
    BidirectionalMap& operator=(const BidirectionalMap&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_; }

    static LeftType toLeftType(RightType right);

    static RightType toRightType(LeftType left);

private:
    /// the 'init()' function must be defined by the user
    static void init();

    static void add(LeftType left, RightType right);

private:
    static map_t                                    map_;
    static bool                                     initialized_;
};

///************************************************************************************************

template<class LeftType,  LeftType  invalidL,
         class RightType, RightType invalidR>
void BidirectionalMap<LeftType, invalidL, RightType, invalidR>::initialize()
{
    if (!isInitialized()) {
        init();
        initialized_ = true;
    }
}

template<class LeftType,  LeftType  invalidL,
         class RightType, RightType invalidR>
LeftType BidirectionalMap<LeftType, invalidL, RightType, invalidR>::toLeftType(
    RightType right)
{
    assert(isInitialized());
    map_t::right_map::const_iterator iter{ map_.right.find(right) };
    if (iter != map_.right.end()) {
        return iter->second;
    }
    return invalidL;
}

template<class LeftType,  LeftType  invalidL,
         class RightType, RightType invalidR>
RightType BidirectionalMap<LeftType, invalidL, RightType, invalidR>::toRightType(
    LeftType left)
{
    assert(isInitialized());
    map_t::left_map::const_iterator iter{ map_.left.find(left) };
    if (iter != map_.left.end()) {
        return iter->second;
    }
    return invalidR;
}

template<class LeftType,  LeftType  invalidL,
         class RightType, RightType invalidR>
void BidirectionalMap<LeftType, invalidL, RightType, invalidR>::add(
    LeftType left, RightType right)
{
    map_.insert(map_t::value_type(left, right));
}

} // namespace common
} // namespace game

#endif // !BIDIRECTIONAL_MAP_HPP
