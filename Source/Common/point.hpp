
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef POINT_HPP
#define POINT_HPP

#include<limits>
#include<vector>

namespace Game
{
    namespace Common
    {
        class PointsStorage {
        public:
            PointsStorage(unsigned short int initPoints) noexcept
                : cur_{ initPoints }, acc_{ initPoints } {}

            unsigned short int get() const noexcept {
                return cur_;
            }

            unsigned short int getAccepted() const noexcept {
                return acc_;
            }

            unsigned short int getMinPossible() const noexcept {
                return std::numeric_limits<unsigned short int>::min();
            }

            unsigned short int getMaxPossible() const noexcept {
                return std::numeric_limits<unsigned short int>::max();
            }

            void add(short int points) noexcept {
                cur_ += points;
            }

            void accept() noexcept {
                acc_ = cur_;
            }

            void reject() noexcept {
                cur_ = acc_;
            }

            void reset() noexcept {
                cur_ = acc_ = 0;
            }

        private:
            unsigned short int      cur_;               // current number of points (not accepted)
            unsigned short int      acc_;               // last accepted number of points
        };


        class PointsDistribution {
        public:
            // vector[0] is always 0
            // vector[1] is the number of points required to move from level 0 to level 1
            // vector[2] is the number of points required to move from level 1 to level 2 and so on
            PointsDistribution(std::vector<unsigned char> distribution) noexcept
                : dist_{ distribution } {}

            // return a negative value if currentLevel < newLevel
            // return a positive value if currentLevel > newLevel
            // return 0 if currentLevel == newLevel
            short int totalPoints(unsigned char currentLevel, unsigned char newLevel) const noexcept
            {
                constexpr int minSize = 2;              // minimum size of the initialized vector
                if (currentLevel == newLevel || dist_.size() < minSize) {
                    return 0;
                }
                short int total = 0;
                for (unsigned char level = currentLevel + 1; level <= newLevel; ++level) {
                    unsigned char i = (level < dist_.size()) ? level : dist_.size() - 1;
                    total -= dist_[i];
                }
                for (unsigned char level = currentLevel; level > newLevel; --level) {
                    unsigned char i = (level < dist_.size()) ? level : dist_.size() - 1;
                    total += dist_[i];
                }
                return total;
            }

        private:
            std::vector<unsigned char>  dist_;          // distribution of points by levels
        };


        class CustomLevel {
        public:
            CustomLevel(unsigned char minLevel, unsigned char maxLevel) noexcept
                : cur_{ 0 }, acc_{ 0 }, min_{ minLevel }, max_{ maxLevel } {}

            unsigned char get() const noexcept {
                return cur_;
            }

            unsigned char getAccepted() const noexcept {
                return acc_;
            }

            unsigned char getMinPossible() const noexcept {
                return min_;
            }

            unsigned char getMaxPossible() const noexcept {
                return max_;
            }

            void add(char levels) noexcept {
                cur_ += levels;
            }

            void accept() noexcept {
                acc_ = cur_;
            }

            void reject() noexcept {
                cur_ = acc_;
            }

            void reset() noexcept {
                cur_ = acc_ = 0;
            }

        private:
            unsigned char       cur_;                   // current level (not accepted)
            unsigned char       acc_;                   // last accepted level
            const unsigned char min_;                   // minimum level
            const unsigned char max_;                   // maximum level
        };


        class CustomLevelManager {
        public:
            // value - the number of levels to change
            static bool changeLevel(
                CustomLevel& curentLevel,
                PointsStorage& storage,
                const PointsDistribution& distribution,
                const char value
            ) noexcept {
                auto curLevel = static_cast<int>(curentLevel.get());
                auto newLevel = curLevel + value;
                if (newLevel >= curentLevel.getAccepted() && newLevel <= curentLevel.getMaxPossible()) {
                    auto points = distribution.totalPoints(curLevel, newLevel);
                    auto sum = static_cast<long long int>(storage.get()) + points;
                    if (sum >= storage.getMinPossible() && sum <= storage.getMaxPossible()) {
                        curentLevel.add(value);
                        storage.add(points);
                        return true;
                    }
                }
                return false;
            }

        };

    }
}

#endif // !POINT_HPP
