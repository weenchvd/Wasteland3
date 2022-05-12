
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
#include<stdlib.h>
#include<type_traits>
#include<vector>

namespace game {
namespace object {

using namespace std;

common::Distribution<AttributeReference::point_t>           AttributeReference::pDist_{
    vector<AttributeReference::point_t>{}
};
common::Distribution<EffectAttCoord>                        AttributeReference::cooDist_{
    vector<EffectAttCoord>{}
};
common::Distribution<EffectAttLuck>                         AttributeReference::lucDist_{
    vector<EffectAttLuck>{}
};
common::Distribution<EffectAttAware>                        AttributeReference::awaDist_{
    vector<EffectAttAware>{}
};
common::Distribution<EffectAttStr>                          AttributeReference::strDist_{
    vector<EffectAttStr>{}
};
common::Distribution<EffectAttSpeed>                        AttributeReference::spdDist_{
    vector<EffectAttSpeed>{}
};
common::Distribution<EffectAttInt>                          AttributeReference::intDist_{
    vector<EffectAttInt>{}
};
common::Distribution<EffectAttCha>                          AttributeReference::chaDist_{
    vector<EffectAttCha>{}
};

AttributeReference::point_t             AttributeReference::minAttrPoints_  { 0 };
AttributeReference::point_t             AttributeReference::maxAttrPoints_  { 0 };
AttributeReference::point_t             AttributeReference::initAttrPoints_ { 0 };
AttributeReference::level_t             AttributeReference::minAttrLevel_   { 0 };
AttributeReference::level_t             AttributeReference::maxAttrLevel_   { 0 };
AttributeReference::level_t             AttributeReference::initAttrLevel_  { 0 };
bool                                    AttributeReference::initialized_    { false };

///************************************************************************************************

void AttributeReference::initialize()
{
    if (isInitialized()) return;

    unique_ptr<char[]> buffer{};
    if (!common::readBinFlatBuffer(ATTRIBUTE_REF_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
        ATTRIBUTE_REF_FB_BIN_FILE__HASH))
    {
        abort();
    }
    const fbAttribute::FB_Attribute* fb{
        fbAttribute::GetFB_Attribute(buffer.get())
    };

    initPointDist(fb);
    initCoordDist(fb);
    initLuckDist(fb);
    initAwareDist(fb);
    initStrDist(fb);
    initSpeedDist(fb);
    initIntDist(fb);
    initCharismaDist(fb);

    assert(fb != nullptr);
    minAttrPoints_      = { fb->min_attr_points() };
    maxAttrPoints_      = { fb->max_attr_points() };
    initAttrPoints_     = { fb->init_attr_points() };
    minAttrLevel_       = { fb->min_attr_level() };
    maxAttrLevel_       = { fb->max_attr_level() };
    initAttrLevel_      = { fb->init_attr_level() };

    initialized_        = true;
}

void AttributeReference::initPointDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    pDist_ = move(common::Distribution<AttributeReference::point_t>{
        common::convertToVector<common::PointAttribute>(fb->point_attr_distr()->p())
    });
}

void AttributeReference::initCoordDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    const auto* dist = fb->coord_distr();

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

void AttributeReference::initLuckDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    const auto* dist = fb->luck_distr();

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

void AttributeReference::initAwareDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    const auto* dist = fb->aware_distr();

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

void AttributeReference::initStrDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    const auto* dist = fb->str_distr();

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

void AttributeReference::initSpeedDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    const auto* dist = fb->speed_distr();

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

void AttributeReference::initIntDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    const auto* dist = fb->int_distr();

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

void AttributeReference::initCharismaDist(const fbAttribute::FB_Attribute* fb)
{
    assert(fb != nullptr);
    const auto* dist = fb->cha_distr();

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
