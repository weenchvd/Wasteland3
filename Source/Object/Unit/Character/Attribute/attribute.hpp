
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
    using point_t       = common::PointAttribute;
    using level_t       = common::LevelAttribute;

public:
    Attribute(Character& character);

    Attribute(const Attribute&) = delete;
    Attribute& operator=(const Attribute&) = delete;

    static void initialize();

    static bool isInitialized();

public:
    void addLevel(Attribute::Type type, level_t shift) noexcept;

    void addLevelToAll(level_t shift) noexcept;

    void addPoint(point_t shift) noexcept {
        pStor_.add(shift);
    }

    bool isModified() const noexcept;

    void accept() noexcept;

    void reject() noexcept;

    void reset() noexcept;

public:
    const common::SpecStorage<level_t>& level(Attribute::Type type) const noexcept {
        assert(common::isValidEnum(type));
        return levels_[common::toUnderlying(type)];
    }

    const common::SpecStorage<point_t>& storage() const noexcept {
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

    static std::vector<common::SpecStorage<level_t>> initLevels();

private:
    Character&                                          char_;
    std::vector<common::SpecStorage<level_t>>           levels_;
    common::SpecStorage<point_t>                        pStor_;
    common::Distribution<point_t, level_t>              pDist_;
    common::Distribution<EffectAttCoord, level_t>       cooDist_;
    common::Distribution<EffectAttLuck, level_t>        lucDist_;
    common::Distribution<EffectAttAware, level_t>       awaDist_;
    common::Distribution<EffectAttStr, level_t>         strDist_;
    common::Distribution<EffectAttSpeed, level_t>       spdDist_;
    common::Distribution<EffectAttInt, level_t>         intDist_;
    common::Distribution<EffectAttCha, level_t>         chaDist_;

    static const AttributeReference                     ref_;
    static const AttributeText                          text_;
};

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_HPP
