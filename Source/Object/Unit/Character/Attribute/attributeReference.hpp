
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

struct AttributeReference {
    using PointAttribute    = common::PointAttribute;
    using LevelStat         = common::LevelStat;

    AttributeReference() noexcept {}

    AttributeReference(const AttributeReference&) = delete;
    AttributeReference& operator=(const AttributeReference&) = delete;

    static void initialize();

    static bool isInitialized() { return initialized_; }

private:
    static void initPointDist(const fbAttribute::FB_Attribute* attribute);
    static void initCoordDist(const fbAttribute::FB_Attribute* attribute);
    static void initLuckDist(const fbAttribute::FB_Attribute* attribute);
    static void initAwareDist(const fbAttribute::FB_Attribute* attribute);
    static void initStrDist(const fbAttribute::FB_Attribute* attribute);
    static void initSpeedDist(const fbAttribute::FB_Attribute* attribute);
    static void initIntDist(const fbAttribute::FB_Attribute* attribute);
    static void initCharismaDist(const fbAttribute::FB_Attribute* attribute);

public:
    static common::Distribution<PointAttribute>     pDist_;             // distribution of attribute points
    static common::Distribution<EffectAttCoord>     cooDist_;
    static common::Distribution<EffectAttLuck>      lucDist_;
    static common::Distribution<EffectAttAware>     awaDist_;
    static common::Distribution<EffectAttStr>       strDist_;
    static common::Distribution<EffectAttSpeed>     spdDist_;
    static common::Distribution<EffectAttInt>       intDist_;
    static common::Distribution<EffectAttCha>       chaDist_;


    static PointAttribute                   minAttrPoints_;     // min attribute points
    static PointAttribute                   maxAttrPoints_;     // max attribute points
    static PointAttribute                   initAttrPoints_;    // initial attribute points
    static LevelStat                        minAttrLevel_;      // min attribute level
    static LevelStat                        maxAttrLevel_;      // max attribute level
    static LevelStat                        initAttrLevel_;     // initial attribute level
    static bool                             initialized_;
};

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_REFERENCE_HPP
