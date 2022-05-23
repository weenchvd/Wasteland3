
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_REFERENCE_HPP
#define ATTRIBUTE_REFERENCE_HPP

#include"attributeReferenceFB_generated.h"
#include"common.hpp"
#include"distribution.hpp"
#include"effectAttribute.hpp"

namespace game {
namespace object {

class AttributeReference {
public:
    using point_t = common::PointAttribute;
    using level_t = common::LevelStat;

private:
    friend class Attribute;

private:
    AttributeReference() noexcept {}

public:
    AttributeReference(const AttributeReference&) = delete;
    AttributeReference& operator=(const AttributeReference&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

    static point_t initialAttributePoints() noexcept { return initAttrPoints_; }

    static level_t initialAttributeLevel() noexcept { return initAttrLevel_; }

private:
    static void initPointDist(const fbAttribute::FB_Attribute* fb);
    static void initCoordDist(const fbAttribute::FB_Attribute* fb);
    static void initLuckDist(const fbAttribute::FB_Attribute* fb);
    static void initAwareDist(const fbAttribute::FB_Attribute* fb);
    static void initStrDist(const fbAttribute::FB_Attribute* fb);
    static void initSpeedDist(const fbAttribute::FB_Attribute* fb);
    static void initIntDist(const fbAttribute::FB_Attribute* fb);
    static void initCharismaDist(const fbAttribute::FB_Attribute* fb);

private:
    static common::Distribution<point_t>            pDist_;     // distribution of attribute points
    static common::Distribution<EffectAttCoord>     cooDist_;
    static common::Distribution<EffectAttLuck>      lucDist_;
    static common::Distribution<EffectAttAware>     awaDist_;
    static common::Distribution<EffectAttStr>       strDist_;
    static common::Distribution<EffectAttSpeed>     spdDist_;
    static common::Distribution<EffectAttInt>       intDist_;
    static common::Distribution<EffectAttCha>       chaDist_;

    static point_t                          minAttrPoints_;     // min attribute points
    static point_t                          maxAttrPoints_;     // max attribute points
    static point_t                          initAttrPoints_;    // initial attribute points
    static level_t                          minAttrLevel_;      // min attribute level
    static level_t                          maxAttrLevel_;      // max attribute level
    static level_t                          initAttrLevel_;     // initial attribute level
    static bool                             initialized_;
};

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_REFERENCE_HPP
