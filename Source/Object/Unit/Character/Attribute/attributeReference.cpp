
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attributePath.hpp"
#include"attributeReference.hpp"
#include"distribution.hpp"
#include"flatbuffersAux.hpp"
#include<assert.h>
#include<memory>
#include<type_traits>

namespace Game {
namespace Object {

using namespace std;

std::vector<AttributeReference::PointAttribute> AttributeReference::pDist_;
std::vector<EffectAttCoord>                     AttributeReference::cooDist_;
std::vector<EffectAttLuck>                      AttributeReference::lucDist_;
std::vector<EffectAttAware>                     AttributeReference::awaDist_;
std::vector<EffectAttStr>                       AttributeReference::strDist_;
std::vector<EffectAttSpeed>                     AttributeReference::spdDist_;
std::vector<EffectAttInt>                       AttributeReference::intDist_;
std::vector<EffectAttCha>                       AttributeReference::chaDist_;

Common::PointAttribute  AttributeReference::minAttrPoints_  { 0 };
Common::PointAttribute  AttributeReference::maxAttrPoints_  { 0 };
Common::PointAttribute  AttributeReference::initAttrPoints_ { 0 };
Common::LevelStat       AttributeReference::minAttrLevel_   { 0 };
Common::LevelStat       AttributeReference::maxAttrLevel_   { 0 };
Common::LevelStat       AttributeReference::initAttrLevel_  { 0 };
bool                    AttributeReference::initialized_    { false };

void AttributeReference::initialize()
{
    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        Common::getFlatBuffer(ATTRIBUTE_REF_FB_BIN_FILE__NATIVE_REL_PATH)
    };

    const fbAttribute::FB_Attribute* att =
        fbAttribute::GetFB_Attribute(buffer.get());
    assert(att != nullptr);

    initPointDist(att);
    initCoordDist(att);
    initLuckDist(att);
    initAwareDist(att);
    initStrDist(att);
    initSpeedDist(att);
    initIntDist(att);
    initCharismaDist(att);

    minAttrPoints_      = { att->min_attr_points() };
    maxAttrPoints_      = { att->max_attr_points() };
    initAttrPoints_     = { att->init_attr_points() };
    minAttrLevel_       = { att->min_attr_level() };
    maxAttrLevel_       = { att->max_attr_level() };
    initAttrLevel_      = { att->init_attr_level() };

    initialized_        = true;
}

void AttributeReference::initPointDist(const fbAttribute::FB_Attribute* attribute)
{
    pDist_ = move(
        Common::convertToVector<Common::PointAttribute>(attribute->point_attr_distr()->p())
    );
}

void AttributeReference::initCoordDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->coord_distr();

    cooDist_ = Common::initializeDistribution<EffectAttCoord,
        Common::Resistance,
        Common::ActionPoint,
        Common::ActionPoint
    >(
        Common::convertToVector<Common::Resistance>(dist->status_effect()),
        Common::convertToVector<Common::ActionPoint>(dist->ap_max()),
        Common::convertToVector<Common::ActionPoint>(dist->ap())
        );
}

void AttributeReference::initLuckDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->luck_distr();

    lucDist_ = Common::initializeDistribution<EffectAttLuck,
        Common::Armor,
        Common::Chance,
        Common::Chance,
        Common::Chance,
        Common::Chance,
        Common::Chance,
        Common::Chance,
        Common::Chance,
        Common::Chance
    >(
        Common::convertToVector<Common::Armor>(dist->penet()),
        Common::convertToVector<Common::Chance>(dist->action()),
        Common::convertToVector<Common::Chance>(dist->crit_damage()),
        Common::convertToVector<Common::Chance>(dist->mega_crit_damage()),
        Common::convertToVector<Common::Chance>(dist->evade()),
        Common::convertToVector<Common::Chance>(dist->crit_resist()),
        Common::convertToVector<Common::Chance>(dist->double_healing()),
        Common::convertToVector<Common::Chance>(dist->double_money()),
        Common::convertToVector<Common::Chance>(dist->double_scrap())
        );
}

void AttributeReference::initAwareDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->aware_distr();

    awaDist_ = Common::initializeDistribution<EffectAttAware,
        Common::Chance,
        Common::Perception,
        Common::Bonus
    >(
        Common::convertToVector<Common::Chance>(dist->hit()),
        Common::convertToVector<Common::Perception>(dist->percep()),
        Common::convertToVector<Common::Bonus>(dist->ranged_damage())
        );
}

void AttributeReference::initStrDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->str_distr();

    strDist_ = Common::initializeDistribution<EffectAttStr,
        Common::Constitution,
        Common::Constitution,
        Common::Bonus,
        Common::Multiplier
    >(
        Common::convertToVector<Common::Constitution>(dist->con_max()),
        Common::convertToVector<Common::Constitution>(dist->con_per_lvl()),
        Common::convertToVector<Common::Bonus>(dist->melee_damage()),
        Common::convertToVector<Common::Multiplier>(dist->throwing_range())
        );
}

void AttributeReference::initSpeedDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->speed_distr();

    spdDist_ = Common::initializeDistribution<EffectAttSpeed,
        Common::Multiplier,
        Common::Evasion,
        Common::Initiative
    >(
        Common::convertToVector<Common::Multiplier>(dist->combat_speed()),
        Common::convertToVector<Common::Evasion>(dist->evasion()),
        Common::convertToVector<Common::Initiative>(dist->initiative())
        );
}

void AttributeReference::initIntDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->int_distr();

    intDist_ = Common::initializeDistribution<EffectAttInt,
        Common::Chance,
        Common::Multiplier,
        Common::Chance,
        Common::Bonus,
        Common::PointSkill
    >(
        Common::convertToVector<Common::Chance>(dist->crit_damage_chance()),
        Common::convertToVector<Common::Multiplier>(dist->crit_damage_mult()),
        Common::convertToVector<Common::Chance>(dist->crit_healing_chance()),
        Common::convertToVector<Common::Bonus>(dist->crit_healing_bonus()),
        Common::convertToVector<Common::PointSkill>(dist->skill_point())
        );
}

void AttributeReference::initCharismaDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->cha_distr();

    chaDist_ = Common::initializeDistribution<EffectAttCha,
        Common::Strike,
        Common::Range,
        Common::Bonus,
        Common::Bonus
    >(
        Common::convertToVector<Common::Strike>(dist->strike_rate()),
        Common::convertToVector<Common::Range>(dist->leadership_range()),
        Common::convertToVector<Common::Bonus>(dist->experience()),
        Common::convertToVector<Common::Bonus>(dist->mission_reward())
        );
}

} // namespace Object
} // namespace Game
