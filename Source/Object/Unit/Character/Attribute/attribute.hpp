
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

namespace game {
namespace object {

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
    void addLevel(Attribute::Type type, common::LevelStat shift) noexcept;

    void addLevelToAll(common::LevelStat shift) noexcept;

    void addPoint(common::PointAttribute shift) noexcept {
        pStor_.add(shift);
    }

    bool isModified() const noexcept;

    void accept() noexcept;

    void reject() noexcept;

    void reset() noexcept;

public:
    const common::SpecStorage<common::LevelStat>& level(Attribute::Type type) const noexcept {
        assert(common::isValidEnum(type));
        return levels_[common::toUnderlying(type)];
    }

    const common::SpecStorage<common::PointAttribute>& storage() const noexcept {
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

    static std::vector<common::SpecStorage<common::LevelStat>> initLevels();

private:
    Character&                                          char_;
    std::vector<common::SpecStorage<common::LevelStat>> levels_;
    common::SpecStorage<common::PointAttribute>         pStor_;
    common::Distribution<common::PointAttribute>        pDist_;
    common::Distribution<EffectAttCoord>                cooDist_;
    common::Distribution<EffectAttLuck>                 lucDist_;
    common::Distribution<EffectAttAware>                awaDist_;
    common::Distribution<EffectAttStr>                  strDist_;
    common::Distribution<EffectAttSpeed>                spdDist_;
    common::Distribution<EffectAttInt>                  intDist_;
    common::Distribution<EffectAttCha>                  chaDist_;

    static const AttributeReference                     ref_;
    static const AttributeText                          text_;
};

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_HPP
