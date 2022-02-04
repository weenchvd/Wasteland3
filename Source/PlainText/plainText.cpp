
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"plainText.hpp"

namespace Game
{
    namespace Global
    {
        using namespace std;

        PlainText::PlainText(PlainText::Language lang)
            : current_{ lang }
        {
            initialize();
        }

        void PlainText::setLanguage(PlainText::Language lang)
        {
            if (current_ == lang) return;
            current_ = lang;
            initialize();
        }

        const Game::Common::Text& PlainText::language(PlainText::Language id) const noexcept
        {
            if (Common::isValidEnum(id)) {
                return lang_[Common::toUnderlying(id)];
            }
            return common_[Common::toUnderlying(PlainText::General::INVALID_ENUM)];
        }

        const Game::Common::Text& PlainText::common(PlainText::General id) const noexcept
        {
            if (Common::isValidEnum(id)) {
                return common_[Common::toUnderlying(id)];
            }
            return common_[Common::toUnderlying(PlainText::General::INVALID_ENUM)];
        }

        void PlainText::initialize()
        {
            fill();
            switch (current_) {
            case PlainText::Language::EN:
                initializeEN();
                break;
            case PlainText::Language::RU:
                initializeRU();
                break;
            default:
                initializeEN();
                break;
            }

            lang_[Common::toUnderlying(PlainText::Language::EN)]
                = Common::Text{ u8"ENGLISH" };
            lang_[Common::toUnderlying(PlainText::Language::RU)]
                = Common::Text{ u8"РУССКИЙ" };

            common_[Common::toUnderlying(PlainText::General::INVALID_ENUM)]
                = invalidEnum;
        }

        void PlainText::initializeEN()
        {
            initCommonEN();
        }

        void PlainText::initializeRU()
        {
            initCommonRU();
        }

        void PlainText::fill()
        {
            fillAll(lang_, getDefault());
            fillAll(common_, getDefault());
        }

        const Game::Common::Text& PlainText::getDefault() const noexcept
        {
            switch (current_) {
            case PlainText::Language::EN:
                return eng_NoData;
            case PlainText::Language::RU:
                return rus_NoData;
            default:
                return eng_NoData;
            }
        }

        void PlainText::initCommonEN()
        {
            common_[Common::toUnderlying(PlainText::General::NO_DATA)]
                = eng_NoData;
        }

        void PlainText::initCommonRU()
        {
            common_[Common::toUnderlying(PlainText::General::NO_DATA)]
                = rus_NoData;
        }

    }
}
