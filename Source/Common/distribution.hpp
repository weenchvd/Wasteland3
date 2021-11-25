
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include"common.hpp"
#include<initializer_list>
#include<vector>

namespace Game
{
    namespace Common
    {
        template<class T> class Distribution {
        public:
            // vector[0] is always not used
            // vector[1] is T when moving from level 0 to level 1
            // vector[2] is T when moving from level 1 to level 2 and so on
            // if newLevel >= dist_.size(), then T is the last T in the dist_
            explicit Distribution(std::vector<T> distribution) noexcept
                : dist_{ distribution } {}

            // return the total T when moving from currentLevel to newLevel
            T total(LevelStat currentLevel, LevelStat newLevel) const noexcept
            {
                constexpr int minSize = 2;              // minimum size of the initialized vector
                T total{};
                if (currentLevel < 0 || newLevel < 0 ||
                    currentLevel == newLevel || dist_.size() < minSize)
                {
                    return total;
                }
                for (LevelStat level = currentLevel + 1; level <= newLevel; ++level) {
                    LevelStat i = (level < dist_.size()) ? level : dist_.size() - 1;
                    total += dist_[i];
                }
                for (LevelStat level = currentLevel; level > newLevel; --level) {
                    LevelStat i = (level < dist_.size()) ? level : dist_.size() - 1;
                    total -= dist_[i];
                }
                return total;
            }

        private:
            std::vector<T>              dist_;          // distribution of T by levels
        };




        template<class E, class T1>
        std::vector<E> initializeDistribution(
            const std::vector<T1>& v1)
        {
            std::vector<E> dist;
            dist.reserve(v1.size());
            for (int i = 0; i < v1.size(); ++i) {
                dist.push_back(E{
                    v1[i] });
            }
            return dist;
        }

        template<class E, class T1, class T2>
        std::vector<E> initializeDistribution(
            const std::vector<T1>& v1,
            const std::vector<T2>& v2)
        {
            if (v1.size() != v2.size())
            {
                return std::vector<E>{};
            }
            std::vector<E> dist;
            dist.reserve(v1.size());
            for (int i = 0; i < v1.size(); ++i) {
                dist.push_back(E{
                    v1[i],
                    v2[i] });
            }
            return dist;
        }

        template<class E, class T1, class T2, class T3>
        std::vector<E> initializeDistribution(
            const std::vector<T1>& v1,
            const std::vector<T2>& v2,
            const std::vector<T3>& v3)
        {
            if (v1.size() != v2.size() ||
                v1.size() != v3.size())
            {
                return std::vector<E>{};
            }
            std::vector<E> dist;
            dist.reserve(v1.size());
            for (int i = 0; i < v1.size(); ++i) {
                dist.push_back(E{
                    v1[i],
                    v2[i],
                    v3[i] });
            }
            return dist;
        }

        template<class E, class T1, class T2, class T3, class T4>
        std::vector<E> initializeDistribution(
            const std::vector<T1>& v1,
            const std::vector<T2>& v2,
            const std::vector<T3>& v3,
            const std::vector<T4>& v4)
        {
            if (v1.size() != v2.size() ||
                v1.size() != v3.size() ||
                v1.size() != v4.size())
            {
                return std::vector<E>{};
            }
            std::vector<E> dist;
            dist.reserve(v1.size());
            for (int i = 0; i < v1.size(); ++i) {
                dist.push_back(E{
                    v1[i],
                    v2[i],
                    v3[i],
                    v4[i] });
            }
            return dist;
        }

        template<class E, class T1, class T2, class T3, class T4, class T5>
        std::vector<E> initializeDistribution(
            const std::vector<T1>& v1,
            const std::vector<T2>& v2,
            const std::vector<T3>& v3,
            const std::vector<T4>& v4,
            const std::vector<T5>& v5)
        {
            if (v1.size() != v2.size() ||
                v1.size() != v3.size() ||
                v1.size() != v4.size() ||
                v1.size() != v5.size())
            {
                return std::vector<E>{};
            }
            std::vector<E> dist;
            dist.reserve(v1.size());
            for (int i = 0; i < v1.size(); ++i) {
                dist.push_back(E{
                    v1[i],
                    v2[i],
                    v3[i],
                    v4[i],
                    v5[i] });
            }
            return dist;
        }

        template<class E,
            class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
        std::vector<E> initializeDistribution(
            const std::vector<T1>& v1,
            const std::vector<T2>& v2,
            const std::vector<T3>& v3,
            const std::vector<T4>& v4,
            const std::vector<T5>& v5,
            const std::vector<T6>& v6,
            const std::vector<T7>& v7,
            const std::vector<T8>& v8,
            const std::vector<T9>& v9)
        {
            if (v1.size() != v2.size() ||
                v1.size() != v3.size() ||
                v1.size() != v4.size() ||
                v1.size() != v5.size() ||
                v1.size() != v6.size() ||
                v1.size() != v7.size() ||
                v1.size() != v8.size() ||
                v1.size() != v9.size())
            {
                return std::vector<E>{};
            }
            std::vector<E> dist;
            dist.reserve(v1.size());
            for (int i = 0; i < v1.size(); ++i) {
                dist.push_back(E{
                    v1[i],
                    v2[i],
                    v3[i],
                    v4[i],
                    v5[i],
                    v6[i],
                    v7[i],
                    v8[i],
                    v9[i] });
            }
            return dist;
        }

    }
}

#endif // !DISTRIBUTION_HPP
