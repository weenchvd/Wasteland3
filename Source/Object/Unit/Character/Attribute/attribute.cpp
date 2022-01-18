
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attribute.hpp"
#include"character.hpp"
#include"locator.hpp"
#include<assert.h>
#include<iostream>
#include<fstream>
#include<type_traits>

namespace Game
{
    namespace Object
    {
        using namespace std;
        using Game::Common::Text;

        const AttributeReference Attribute::ref_;
        const AttributeText Attribute::text_;

        Attribute::Attribute(Character& character)
            :
            char_       { character },
            levels_     { initLevels() },
            pStor_      { ref_.minAttrPoints_, ref_.maxAttrPoints_ },
            pDist_      { ref_.pDist_ },
            cooDist_    { ref_.cooDist_ },
            lucDist_    { ref_.lucDist_ },
            awaDist_    { ref_.awaDist_ },
            strDist_    { ref_.strDist_ },
            spdDist_    { ref_.spdDist_ },
            intDist_    { ref_.intDist_ },
            chaDist_    { ref_.chaDist_ }
        {
            assert(ref_.isInitialized());
            assert(text_.isInitialized());
        }

        void Attribute::addLevel(Attribute::Type type, Common::LevelStat shift) noexcept
        {
            auto index = Common::toUnderlying(type);
            Common::changeLevel(levels_[index], pStor_, pDist_, shift);
        }
        
        void Attribute::addLevelToAll(Common::LevelStat shift) noexcept
        {
            addLevel(Attribute::Type::COORDINATION, shift);
            addLevel(Attribute::Type::LUCK,         shift);
            addLevel(Attribute::Type::AWARENESS,    shift);
            addLevel(Attribute::Type::STRENGTH,     shift);
            addLevel(Attribute::Type::SPEED,        shift);
            addLevel(Attribute::Type::INTELLIGENCE, shift);
            addLevel(Attribute::Type::CHARISMA,     shift);
        }

        bool Attribute::isModified() const noexcept
        {
            if (pStor_.get() != pStor_.getAccepted()) {
                return true;
            }
            for (const Common::SpecStorage<Common::LevelStat>& level : levels_) {
                if (level.get() != level.getAccepted()) {
                    return true;
                }
            }
            return false;
        }

        void Attribute::accept() noexcept
        {
            apply();
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.accept();
            }
            pStor_.accept();
        }

        void Attribute::reject() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reject();
            }
            pStor_.reject();
        }

        void Attribute::reset() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reset();
            }
            pStor_.reset();
        }

        void Attribute::apply() noexcept
        {
            apply(Attribute::Type::COORDINATION);
            apply(Attribute::Type::LUCK);
            apply(Attribute::Type::AWARENESS);
            apply(Attribute::Type::STRENGTH);
            apply(Attribute::Type::SPEED);
            apply(Attribute::Type::INTELLIGENCE);
            apply(Attribute::Type::CHARISMA);
        }

        void Attribute::apply(Attribute::Type type) noexcept
        {
            auto index = Common::toUnderlying(type);
            auto accLevel = levels_[index].getAccepted();
            auto curLevel = levels_[index].get();
            if (accLevel != curLevel) {
                switch (type) {
                case Attribute::Type::COORDINATION: {
                    EffectAttCoord sum = cooDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::LUCK: {
                    EffectAttLuck sum = lucDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::AWARENESS: {
                    EffectAttAware sum = awaDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::STRENGTH: {
                    EffectAttStr sum = strDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::SPEED: {
                    EffectAttSpeed sum = spdDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::INTELLIGENCE: {
                    EffectAttInt sum = intDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::CHARISMA: {
                    EffectAttCha sum = chaDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                default:
                    break;
                }
            }
        }

        void Attribute::initialize()
        {
            initializeText();
        }

        void Attribute::initializeText()
        {
            Game::Global::PlainText::Language lang =
                Game::Global::Locator::getOption().getLanguage();
        }

        vector<Common::SpecStorage<Common::LevelStat>> Attribute::initLevels()
        {
            constexpr auto nAttributes = Common::toUnderlying(Attribute::Type::NUMBER_OF);
            const Common::SpecStorage<Common::LevelStat> tempLevel{
                ref_.minAttrLevel_,
                ref_.maxAttrLevel_
            };
            return vector<Common::SpecStorage<Common::LevelStat>>(nAttributes, tempLevel);
        }

    }
}
