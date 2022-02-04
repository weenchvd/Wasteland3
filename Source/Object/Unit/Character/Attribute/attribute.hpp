
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include"attributeCommon.hpp"
#include"attributeReference.hpp"
#include"attributeText.hpp"
#include"distribution.hpp"
#include"effectAttribute.hpp"
#include"specStorage.hpp"
#include<assert.h>
#include<vector>

namespace Game {
namespace Object {

class Character;

class Attribute {
public:
    using Type          = Attribute__Type;

public:
    Attribute(Character& character);

    Attribute(const Attribute&) = delete;
    Attribute& operator=(const Attribute&) = delete;

    static void initialize();

    static bool isInitialized();

public:
    void addLevel(Attribute::Type type, Common::LevelStat shift) noexcept;

    void addLevelToAll(Common::LevelStat shift) noexcept;

    void addPoint(Common::PointAttribute shift) noexcept {
        pStor_.add(shift);
    }

    bool isModified() const noexcept;

    void accept() noexcept;

    void reject() noexcept;

    void reset() noexcept;

public:
    const Common::SpecStorage<Common::LevelStat>& level(Attribute::Type type) const noexcept {
        assert(Common::isValidEnum(type));
        return levels_[Common::toUnderlying(type)];
    }

    const Common::SpecStorage<Common::PointAttribute>& storage() const noexcept {
        return pStor_;
    }

    static const AttributeReference& attributeReference() noexcept {
        return ref_;
    }

    static const AttributeText& attributeText() noexcept {
        return text_;
    }

private:
    void apply() noexcept;

    void apply(Attribute::Type type) noexcept;

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
    static const AttributeText                          text_;
};

} // namespace Object
} // namespace Game

#endif // !ATTRIBUTE_HPP
