
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include"attribute_generated.h"
#include"attributeCommon.hpp"
#include"attributeReference.hpp"
#include"distribution.hpp"
#include"effectAttribute.hpp"
#include"specStorage.hpp"
#include<array>
#include<initializer_list>
#include<limits>
#include<memory>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        class Character;

        class Attribute {
        public:
            using Type          = Attribute__Type;

        public:
            Attribute(Character& character);

            void addLevel(Attribute::Type type, Common::LevelStat shift) noexcept;

            void addLevelToAll(Common::LevelStat shift) noexcept;

            void addPoint(Common::PointAttribute shift) noexcept {
                pStor_.add(shift);
            }

            bool isModified() const noexcept;

            void accept() noexcept;

            void reject() noexcept;

            void reset() noexcept;

            static void initialize();

        public:
            const Common::SpecStorage<Common::LevelStat>& level(Attribute::Type type) const noexcept {
                return levels_[Common::toUnderlying(type)];
            }

            const Common::SpecStorage<Common::PointAttribute>& storage() const noexcept {
                return pStor_;
            }

            static const AttributeReference& attributeReference() noexcept {
                return ref_;
            }

        public:
            using Text = Game::Common::Text;

            static const Text& name(Attribute::Type id) noexcept;

            static const Text& descr(Attribute::Type id) noexcept;

        private:
            void apply() noexcept;

            void apply(Attribute::Type type) noexcept;

            static void initializeText();

            static std::vector<Common::SpecStorage<Common::LevelStat>> initLevels();

        private:
            Character&                                          char_;
            std::vector<Common::SpecStorage<Common::LevelStat>> levels_;
            Common::SpecStorage<Common::PointAttribute>         pStor_;
            Common::Distribution<Common::PointAttribute>        pDist_;
            Common::Distribution<EffectAttCoord>                cooDist_;
            Common::Distribution<EffectAttLuck>                 lucDist_;
            Common::Distribution<EffectAttAware>                awaDist_;
            Common::Distribution<EffectAttStr>                  strDist_;
            Common::Distribution<EffectAttSpeed>                spdDist_;
            Common::Distribution<EffectAttInt>                  intDist_;
            Common::Distribution<EffectAttCha>                  chaDist_;

            static const AttributeReference                     ref_;

        private:
            static constexpr int sizeName_ = Common::toUnderlying(Attribute::Type::NUMBER_OF);
            static constexpr int sizeDescr_ = Common::toUnderlying(Attribute::Type::NUMBER_OF);

            static std::array<Text, sizeName_>                  tName_;
            static std::array<Text, sizeDescr_>                 tDescr_;
        };

    }
}

#endif // !ATTRIBUTE_HPP
