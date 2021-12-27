
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_COMMON_HPP
#define MENU_COMMON_HPP

#include"common.hpp"
#include"specStorage.hpp"
#include<iostream>

namespace Game
{
    namespace Menu
    {
        constexpr char space{ ' ' };

        class Indent {
        public:
            Indent()
                : indent_{ 2 } {}

            Indent(unsigned int indent)
                : indent_{ indent } {}

            unsigned int get() const {
                return indent_;
            }

        private:
            unsigned int indent_;
        };

        Indent operator+(const Indent& left, const Indent& right);

        std::ostream& operator<<(std::ostream& os, const Indent& indent);

        inline double secondTime(Common::Time time) {
            return static_cast<double>(time) / 1000;
        }

        inline double multiplier(Common::Multiplier mult) {
            return static_cast<double>(mult) / 100;
        }

        inline double percentChance(Common::Chance chance) {
            return static_cast<double>(chance) / 10;
        }

        inline double percentBonus(Common::Bonus bonus) {
            return static_cast<double>(bonus) / 10;
        }

        inline double percentEvasion(Common::Evasion evasion) {
            return static_cast<double>(evasion) / 10;
        }

        inline double percentResistance(Common::Resistance res) {
            return static_cast<double>(res) / 10;
        }

        inline double percentInitiative(Common::Initiative init) {
            return static_cast<double>(init) / 10;
        }

        inline double percentStrike(Common::Strike strike) {
            return static_cast<double>(strike) / 10;
        }

        inline int integer(char ch)
        {
            return static_cast<int>(ch);
        }

        int getAction();

        int getPosNumber();

        enum class YesNo {
            INVALID = -1,
            NO,
            YES
        };

        YesNo getYesNo();

        namespace ActionCommon
        {
            enum ActionCommon {
                INVALID = -1,
                EXIT,
                NEXT
            };
        }

        Common::Text statLevel(const Common::SpecStorage<Common::LevelStat>& level, bool accepted = false);

        unsigned int utf8Size(const std::string& s);

    }
}

#endif // !MENU_COMMON_HPP
