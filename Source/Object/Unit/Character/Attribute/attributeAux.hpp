
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ATTRIBUTE_AUX_HPP
#define ATTRIBUTE_AUX_HPP

#include"attributeFB_generated.h"
#include"common.hpp"

namespace game {
namespace object {

class AttributeInitializer {
public:
    using point_t = common::PointAttribute;
    using level_t = common::LevelAttribute;

private:
    friend class Attribute;

public:
    AttributeInitializer() noexcept;

    AttributeInitializer(const fbAttribute::FB_Attribute* fb) noexcept;

    AttributeInitializer(const AttributeInitializer&) = delete;
    AttributeInitializer& operator=(const AttributeInitializer&) = delete;
    AttributeInitializer(AttributeInitializer&&) = default;
    AttributeInitializer& operator=(AttributeInitializer&&) = default;

    void initialize(const fbAttribute::FB_Attribute* fb) noexcept;

    bool isInitialized() const noexcept { return initialized_; }

private:
    point_t                                 attrPoints_;
    level_t                                 coordLevel_;
    level_t                                 luckLevel_;
    level_t                                 awareLevel_;
    level_t                                 strLevel_;
    level_t                                 speedLevel_;
    level_t                                 intLevel_;
    level_t                                 chaLevel_;

    bool                                    initialized_;
};

} // namespace object
} // namespace game

#endif // !ATTRIBUTE_AUX_HPP
