
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_REFERENCE_HPP
#define ATTRIBUTE_REFERENCE_HPP

#include"attribute-ref_generated.h"
#include"common.hpp"
#include"effectAttribute.hpp"
#include<vector>

namespace Game
{
    namespace Object
    {
        struct AttributeReference {
            using PointAttribute    = Common::PointAttribute;
            using LevelStat         = Common::LevelStat;

            AttributeReference();

            AttributeReference(const AttributeReference&) = delete;
            AttributeReference& operator=(const AttributeReference&) = delete;
            AttributeReference(AttributeReference&&) = default;
            AttributeReference& operator=(AttributeReference&&) = default;

            bool isInitialized() const { return initialized_; }

        private:
            void initPointDist(const fbAttribute::FB_Attribute* attribute);
            void initCoordDist(const fbAttribute::FB_Attribute* attribute);
            void initLuckDist(const fbAttribute::FB_Attribute* attribute);
            void initAwareDist(const fbAttribute::FB_Attribute* attribute);
            void initStrDist(const fbAttribute::FB_Attribute* attribute);
            void initSpeedDist(const fbAttribute::FB_Attribute* attribute);
            void initIntDist(const fbAttribute::FB_Attribute* attribute);
            void initCharismaDist(const fbAttribute::FB_Attribute* attribute);

        public:
            std::vector<PointAttribute>     pDist_;         // distribution of attribute points
            std::vector<EffectAttCoord>     cooDist_;
            std::vector<EffectAttLuck>      lucDist_;
            std::vector<EffectAttAware>     awaDist_;
            std::vector<EffectAttStr>       strDist_;
            std::vector<EffectAttSpeed>     spdDist_;
            std::vector<EffectAttInt>       intDist_;
            std::vector<EffectAttCha>       chaDist_;


            PointAttribute                  minAttrPoints_; // min attribute points
            PointAttribute                  maxAttrPoints_; // max attribute points
            PointAttribute                  initAttrPoints_;// initial attribute points
            LevelStat                       minAttrLevel_;  // min attribute level
            LevelStat                       maxAttrLevel_;  // max attribute level
            LevelStat                       initAttrLevel_; // initial attribute level
            bool                            initialized_;
        };

    }
}

#endif // !ATTRIBUTE_REFERENCE_HPP
