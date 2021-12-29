
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAINTEXT_HPP
#define PLAINTEXT_HPP

#include"plainTextEnum.hpp"
#include"common.hpp"
#include"skill.hpp"
#include<array>

namespace Game
{
    namespace Global
    {
        template<class T, size_t size>
        void fillAll(std::array<T, size> a, const T& filler) {
            for (auto& t : a) {
                t = filler;
            }
        }

        const Game::Common::Text invalidEnum{ u8"INVALID ENUM" };
        const Game::Common::Text eng_NoData{ u8"NO DATA" };
        const Game::Common::Text rus_NoData{ u8"НЕТ ДАННЫХ" };

        ///------------------------------------------------------------------------------------------------

        class PlainText {
        public:
            using Language      = PlainText__Language;
            using General       = PlainText__General;
            using Skill         = PlainText__Skill;

            friend class Factory;

        protected:
            PlainText(PlainText::Language lang);

        public:
            PlainText(const PlainText&) = delete;
            PlainText& operator=(const PlainText&) = delete;

            ~PlainText() noexcept {}

            PlainText::Language getLanguage() const noexcept {
                return current_;
            }

            void setLanguage(PlainText::Language lang);

        public:
            const Game::Common::Text& language(PlainText::Language id) const noexcept;

            const Game::Common::Text& common(PlainText::General id) const noexcept;

            const Game::Common::Text& skill(PlainText::Skill id) const noexcept;

            const Game::Common::Text& skill(Game::Object::Skill::Type id) const noexcept;

        private:
            void initialize();
            void initializeEN();
            void initializeRU();

            void fill();

            const Game::Common::Text& getDefault() const noexcept;

            void initCommonEN();
            void initSkillEN();

            void initCommonRU();
            void initSkillRU();

        private:
            using Text = Game::Common::Text;

            static constexpr int sizeLang_ = Common::toUnderlying(PlainText::Language::NUMBER_OF);
            static constexpr int sizeCommon_ = Common::toUnderlying(PlainText::General::NUMBER_OF);
            static constexpr int sizeSkill_ = Common::toUnderlying(PlainText::Skill::NUMBER_OF);
            static constexpr int sizeSkillType_ = Common::toUnderlying(Game::Object::Skill::Type::NUMBER_OF);

        protected:
            PlainText::Language                                 current_;
            std::array<Text, sizeLang_>                         lang_;
            std::array<Text, sizeCommon_>                       common_;
            std::array<Text, sizeSkill_>                        skill_;
            std::array<Text, sizeSkillType_>                    skillType_;

        };

    }
}

#endif // !PLAINTEXT_HPP
