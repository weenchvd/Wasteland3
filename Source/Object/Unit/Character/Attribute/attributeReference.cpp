
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
#include<vector>

namespace game {
namespace object {

using namespace std;

common::Distribution<AttributeReference::PointAttribute>    AttributeReference::pDist_{
    std::vector<AttributeReference::PointAttribute>()
};
common::Distribution<EffectAttCoord>                        AttributeReference::cooDist_{
    std::vector<EffectAttCoord>()
};
common::Distribution<EffectAttLuck>                         AttributeReference::lucDist_{
    std::vector<EffectAttLuck>()
};
common::Distribution<EffectAttAware>                        AttributeReference::awaDist_{
    std::vector<EffectAttAware>()
};
common::Distribution<EffectAttStr>                          AttributeReference::strDist_{
    std::vector<EffectAttStr>()
};
common::Distribution<EffectAttSpeed>                        AttributeReference::spdDist_{
    std::vector<EffectAttSpeed>()
};
common::Distribution<EffectAttInt>                          AttributeReference::intDist_{
    std::vector<EffectAttInt>()
};
common::Distribution<EffectAttCha>                          AttributeReference::chaDist_{
    std::vector<EffectAttCha>()
};

common::PointAttribute  AttributeReference::minAttrPoints_  { 0 };
common::PointAttribute  AttributeReference::maxAttrPoints_  { 0 };
common::PointAttribute  AttributeReference::initAttrPoints_ { 0 };
common::LevelStat       AttributeReference::minAttrLevel_   { 0 };
common::LevelStat       AttributeReference::maxAttrLevel_   { 0 };
common::LevelStat       AttributeReference::initAttrLevel_  { 0 };
bool                    AttributeReference::initialized_    { false };

void AttributeReference::initialize()
{
    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(ATTRIBUTE_REF_FB_BIN_FILE__NATIVE_REL_PATH)
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
    pDist_ = move(common::Distribution<AttributeReference::PointAttribute>{
        common::convertToVector<common::PointAttribute>(attribute->point_attr_distr()->p())
    });
}

void AttributeReference::initCoordDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->coord_distr();

    cooDist_ = move(common::Distribution<EffectAttCoord>{
        common::initializeDistribution<EffectAttCoord,
            common::Resistance,
            common::ActionPoint,
            common::ActionPoint
        >(
            common::convertToVector<common::Resistance>(dist->status_effect()),
            common::convertToVector<common::ActionPoint>(dist->ap_max()),
            common::convertToVector<common::ActionPoint>(dist->ap())
            )
    });
}

void AttributeReference::initLuckDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->luck_distr();

    lucDist_ = move(common::Distribution<EffectAttLuck>{
        common::initializeDistribution<EffectAttLuck,
            common::Armor,
            common::Chance,
            common::Chance,
            common::Chance,
            common::Chance,
            common::Chance,
            common::Chance,
            common::Chance,
            common::Chance
        >(
            common::convertToVector<common::Armor>(dist->penet()),
            common::convertToVector<common::Chance>(dist->action()),
            common::convertToVector<common::Chance>(dist->crit_damage()),
            common::convertToVector<common::Chance>(dist->mega_crit_damage()),
            common::convertToVector<common::Chance>(dist->evade()),
            common::convertToVector<common::Chance>(dist->crit_resist()),
            common::convertToVector<common::Chance>(dist->double_healing()),
            common::convertToVector<common::Chance>(dist->double_money()),
            common::convertToVector<common::Chance>(dist->double_scrap())
            )
    });
}

void AttributeReference::initAwareDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->aware_distr();

    awaDist_ = move(common::Distribution<EffectAttAware>{
        common::initializeDistribution<EffectAttAware,
            common::Chance,
            common::Perception,
            common::Bonus
        >(
            common::convertToVector<common::Chance>(dist->hit()),
            common::convertToVector<common::Perception>(dist->percep()),
            common::convertToVector<common::Bonus>(dist->ranged_damage())
            )
    });
}

void AttributeReference::initStrDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->str_distr();

    strDist_ = move(common::Distribution<EffectAttStr>{
        common::initializeDistribution<EffectAttStr,
            common::Constitution,
            common::Constitution,
            common::Bonus,
            common::Multiplier
        >(
            common::convertToVector<common::Constitution>(dist->con_max()),
            common::convertToVector<common::Constitution>(dist->con_per_lvl()),
            common::convertToVector<common::Bonus>(dist->melee_damage()),
            common::convertToVector<common::Multiplier>(dist->throwing_range())
            )
    });
}

void AttributeReference::initSpeedDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->speed_distr();

    spdDist_ = move(common::Distribution<EffectAttSpeed>{
        common::initializeDistribution<EffectAttSpeed,
            common::Multiplier,
            common::Evasion,
            common::Initiative
        >(
            common::convertToVector<common::Multiplier>(dist->combat_speed()),
            common::convertToVector<common::Evasion>(dist->evasion()),
            common::convertToVector<common::Initiative>(dist->initiative())
            )
    });
}

void AttributeReference::initIntDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->int_distr();

    intDist_ = move(common::Distribution<EffectAttInt>{
        common::initializeDistribution<EffectAttInt,
            common::Chance,
            common::Multiplier,
            common::Chance,
            common::Bonus,
            common::PointSkill
        >(
            common::convertToVector<common::Chance>(dist->crit_damage_chance()),
            common::convertToVector<common::Multiplier>(dist->crit_damage_mult()),
            common::convertToVector<common::Chance>(dist->crit_healing_chance()),
            common::convertToVector<common::Bonus>(dist->crit_healing_bonus()),
            common::convertToVector<common::PointSkill>(dist->skill_point())
            )
    });
}

void AttributeReference::initCharismaDist(const fbAttribute::FB_Attribute* attribute)
{
    const auto* dist = attribute->cha_distr();

    chaDist_ = move(common::Distribution<EffectAttCha>{
        common::initializeDistribution<EffectAttCha,
            common::Strike,
            common::Range,
            common::Bonus,
            common::Bonus
        >(
            common::convertToVector<common::Strike>(dist->strike_rate()),
            common::convertToVector<common::Range>(dist->leadership_range()),
            common::convertToVector<common::Bonus>(dist->experience()),
            common::convertToVector<common::Bonus>(dist->mission_reward())
            )
    });
}

} // namespace object
} // namespace game
