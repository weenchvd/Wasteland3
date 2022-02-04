
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_REFERENCE_HPP
#define ATTRIBUTE_REFERENCE_HPP

#include"attributeReferenceFB_generated.h"
#include"common.hpp"
#include"effectAttribute.hpp"
#include<vector>

namespace Game {
namespace Object {

struct AttributeReference {
    using PointAttribute    = Common::PointAttribute;
    using LevelStat         = Common::LevelStat;

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
    static std::vector<PointAttribute>      pDist_;             // distribution of attribute points
    static std::vector<EffectAttCoord>      cooDist_;
    static std::vector<EffectAttLuck>       lucDist_;
    static std::vector<EffectAttAware>      awaDist_;
    static std::vector<EffectAttStr>        strDist_;
    static std::vector<EffectAttSpeed>      spdDist_;
    static std::vector<EffectAttInt>        intDist_;
    static std::vector<EffectAttCha>        chaDist_;


    static PointAttribute                   minAttrPoints_;     // min attribute points
    static PointAttribute                   maxAttrPoints_;     // max attribute points
    static PointAttribute                   initAttrPoints_;    // initial attribute points
    static LevelStat                        minAttrLevel_;      // min attribute level
    static LevelStat                        maxAttrLevel_;      // max attribute level
    static LevelStat                        initAttrLevel_;     // initial attribute level
    static bool                             initialized_;
};

} // namespace Object
} // namespace Game

#endif // !ATTRIBUTE_REFERENCE_HPP
