
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include"common.hpp"
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

        //template<class T> class Distribution {
        //public:
        //    // vector[0] is always not used
        //    // vector[1] is T when moving from level 0 to level 1
        //    // vector[2] is T when moving from level 1 to level 2 and so on
        //    explicit Distribution(std::vector<T> distribution) noexcept
        //        : dist_{ distribution } {}

        //    // return the total T when moving from currentLevel to newLevel
        //    T total(unsigned char currentLevel, unsigned char newLevel) const noexcept
        //    {
        //        constexpr int minSize = 2;              // minimum size of the initialized vector
        //        T total{};
        //        if (currentLevel == newLevel || dist_.size() < minSize) {
        //            return total;
        //        }
        //        for (unsigned char level = currentLevel + 1; level <= newLevel; ++level) {
        //            unsigned char i = (level < dist_.size()) ? level : dist_.size() - 1;
        //            total += dist_[i];
        //        }
        //        for (unsigned char level = currentLevel; level > newLevel; --level) {
        //            unsigned char i = (level < dist_.size()) ? level : dist_.size() - 1;
        //            total -= dist_[i];
        //        }
        //        return total;
        //    }

        //private:
        //    std::vector<T>              dist_;          // distribution of T by levels
        //};

    }
}

#endif // !DISTRIBUTION_HPP
