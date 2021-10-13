
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include"effectCommon.hpp"
#include"effectVisitor.hpp"
//#include<memory>
//#include<vector>

namespace Game
{
    namespace Object
    {
        class Character;

        class Effect {
        public:
            //Effect(const Effect&) = default;
            //Effect& operator=(const Effect&) = default;

            virtual ~Effect() noexcept {}

            //const EffectType type() const noexcept {
            //    return type_;
            //}

            //const EffectModel model() const noexcept {
            //    return model_;
            //}

            //virtual void accept(EffectVisitor& visitor) noexcept {};

            virtual void apply(Character& character) noexcept {};

        protected:
            /*explicit*/ Effect(/*EffectType type, EffectModel model*/) noexcept
                /*: type_{ type }, model_{ model }*/ {}

        private:
            //const EffectType        type_;          // type of Effect
            //const EffectModel       model_;         // model of Effect
        };


        /*class EffectDistribution {
        public:
            // vector[0] is always 0
            // vector[1] is the number of points required to move from level 0 to level 1
            // vector[2] is the number of points required to move from level 1 to level 2 and so on
            EffectDistribution(std::vector<unsigned char> distribution) noexcept
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
        };*/


        /*class EffectManager {
        public:
            static bool applyEffect(
                const EffectDistribution& distribution,
                unsigned char currentLevel,
                unsigned char newLevel
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

        };*/

        ///------------------------------------------------------------------------------------------------

        //bool operator<(const std::unique_ptr<Item>& item1, const std::unique_ptr<Item>& item2) noexcept;

    }
}

#endif // !EFFECT_HPP
