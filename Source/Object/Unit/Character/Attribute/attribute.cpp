
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"attribute.hpp"
#include"attributePath.hpp"
#include"character.hpp"
#include"locator.hpp"
#include<assert.h>
#include<iostream>
#include<fstream>
#include<type_traits>

namespace Game
{
    namespace Object
    {
        using namespace std;
        using Game::Common::Text;

        Attribute::Attribute(Character& character)
            :
            char_       { character },
            levels_     { initLevels() },
            pStor_      { ref_.minAttrPoints_, ref_.maxAttrPoints_ },
            pDist_      { ref_.pDist_ },
            cooDist_    { ref_.cooDist_ },
            lucDist_    { ref_.lucDist_ },
            awaDist_    { ref_.awaDist_ },
            strDist_    { ref_.strDist_ },
            spdDist_    { ref_.spdDist_ },
            intDist_    { ref_.intDist_ },
            chaDist_    { ref_.chaDist_ }
        {
            assert(ref_.isInitialized());
        }

        void Attribute::addLevel(Attribute::Type type, Common::LevelStat shift) noexcept
        {
            auto index = Common::toUnderlying(type);
            Common::changeLevel(levels_[index], pStor_, pDist_, shift);
        }
        
        void Attribute::addLevelToAll(Common::LevelStat shift) noexcept
        {
            addLevel(Attribute::Type::COORDINATION, shift);
            addLevel(Attribute::Type::LUCK,         shift);
            addLevel(Attribute::Type::AWARENESS,    shift);
            addLevel(Attribute::Type::STRENGTH,     shift);
            addLevel(Attribute::Type::SPEED,        shift);
            addLevel(Attribute::Type::INTELLIGENCE, shift);
            addLevel(Attribute::Type::CHARISMA,     shift);
        }

        bool Attribute::isModified() const noexcept
        {
            if (pStor_.get() != pStor_.getAccepted()) {
                return true;
            }
            for (const Common::SpecStorage<Common::LevelStat>& level : levels_) {
                if (level.get() != level.getAccepted()) {
                    return true;
                }
            }
            return false;
        }

        void Attribute::accept() noexcept
        {
            apply();
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.accept();
            }
            pStor_.accept();
        }

        void Attribute::reject() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reject();
            }
            pStor_.reject();
        }

        void Attribute::reset() noexcept
        {
            for (Common::SpecStorage<Common::LevelStat>& level : levels_) {
                level.reset();
            }
            pStor_.reset();
        }

        void Attribute::apply() noexcept
        {
            apply(Attribute::Type::COORDINATION);
            apply(Attribute::Type::LUCK);
            apply(Attribute::Type::AWARENESS);
            apply(Attribute::Type::STRENGTH);
            apply(Attribute::Type::SPEED);
            apply(Attribute::Type::INTELLIGENCE);
            apply(Attribute::Type::CHARISMA);
        }

        void Attribute::apply(Attribute::Type type) noexcept
        {
            auto index = Common::toUnderlying(type);
            auto accLevel = levels_[index].getAccepted();
            auto curLevel = levels_[index].get();
            if (accLevel != curLevel) {
                switch (type) {
                case Attribute::Type::COORDINATION: {
                    EffectAttCoord sum = cooDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::LUCK: {
                    EffectAttLuck sum = lucDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::AWARENESS: {
                    EffectAttAware sum = awaDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::STRENGTH: {
                    EffectAttStr sum = strDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::SPEED: {
                    EffectAttSpeed sum = spdDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::INTELLIGENCE: {
                    EffectAttInt sum = intDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                case Attribute::Type::CHARISMA: {
                    EffectAttCha sum = chaDist_.total(accLevel, curLevel);
                    sum.apply(char_);
                    break;
                }
                default:
                    break;
                }
            }
        }

        const Text& Attribute::name(Attribute::Type id) noexcept
        {
            assert(Common::isValidEnum(id));
            return tName_[Common::toUnderlying(id)];
        }

        const Text& Attribute::descr(Attribute::Type id) noexcept
        {
            assert(Common::isValidEnum(id));
            return tDescr_[Common::toUnderlying(id)];
        }

        void Attribute::initialize()
        {
            initializeReference();
            initializeText();
        }

        void Attribute::initializeReference()
        {
            unique_ptr<char[]> buffer{
                Common::getFlatBuffer(ATTRIBUTE_FB_FILENAME_WITH_NATIVE_RELATIVE_PATH)
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

            ref_.minAttrPoints_     = { att->min_attr_points() };
            ref_.maxAttrPoints_     = { att->max_attr_points() };
            ref_.initAttrPoints_    = { att->init_attr_points() };
            ref_.minAttrLevel_      = { att->min_attr_level() };
            ref_.maxAttrLevel_      = { att->max_attr_level() };
            ref_.initAttrLevel_     = { att->init_attr_level() };

            ref_.initialized_       = true;
        }

        void Attribute::initializeText()
        {
            Game::Global::PlainText::Language lang =
                Game::Global::Locator::getOption().getLanguage();
        }

        vector<Common::SpecStorage<Common::LevelStat>> Attribute::initLevels()
        {
            initialize(); /// TODO delete, make initializer struct
            assert(ref_.isInitialized());
            constexpr auto nAttributes = Common::toUnderlying(Attribute::Type::NUMBER_OF);
            const Common::SpecStorage<Common::LevelStat> tempLevel{
                ref_.minAttrLevel_,
                ref_.maxAttrLevel_
            };
            return vector<Common::SpecStorage<Common::LevelStat>>(nAttributes, tempLevel);
        }

        void Attribute::initPointDist(const fbAttribute::FB_Attribute* attribute)
        {
            //const auto* pointAttrDistArray = attribute->point_attr_distr()->p();
            //ref_.pDist_.reserve(pointAttrDistArray->size());
            //for (int i = 0; i < pointAttrDistArray->size(); ++i) {
            //    ref_.pDist_.push_back(
            //        Common::PointAttribute{ pointAttrDistArray->Get(i) }
            //    );
            //}
            ref_.pDist_ = move(
                Common::convertToVector<Common::PointAttribute>(
                    attribute->point_attr_distr()->p()
                    )
            );
        }

        void Attribute::initCoordDist(const fbAttribute::FB_Attribute* attribute)
        {
            const auto* dist = attribute->coord_distr();

            ref_.cooDist_ = Common::initializeDistribution<EffectAttCoord,
                Common::Resistance,
                Common::ActionPoint,
                Common::ActionPoint
            >(
                Common::convertToVector<Common::Resistance>(dist->status_effect()),
                Common::convertToVector<Common::ActionPoint>(dist->ap_max()),
                Common::convertToVector<Common::ActionPoint>(dist->ap())
                );
        }

        void Attribute::initLuckDist(const fbAttribute::FB_Attribute* attribute)
        {
            const auto* dist = attribute->luck_distr();

            ref_.lucDist_ = Common::initializeDistribution<EffectAttLuck,
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

        void Attribute::initAwareDist(const fbAttribute::FB_Attribute* attribute)
        {
            const auto* dist = attribute->aware_distr();

            ref_.awaDist_ = Common::initializeDistribution<EffectAttAware,
                Common::Chance,
                Common::Perception,
                Common::Bonus
            >(
                Common::convertToVector<Common::Chance>(dist->hit()),
                Common::convertToVector<Common::Perception>(dist->percep()),
                Common::convertToVector<Common::Bonus>(dist->ranged_damage())
                );
        }

        void Attribute::initStrDist(const fbAttribute::FB_Attribute* attribute)
        {
            const auto* dist = attribute->str_distr();

            ref_.strDist_ = Common::initializeDistribution<EffectAttStr,
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

        void Attribute::initSpeedDist(const fbAttribute::FB_Attribute* attribute)
        {
            const auto* dist = attribute->speed_distr();

            ref_.spdDist_ = Common::initializeDistribution<EffectAttSpeed,
                Common::Multiplier,
                Common::Evasion,
                Common::Initiative
            >(
                Common::convertToVector<Common::Multiplier>(dist->combat_speed()),
                Common::convertToVector<Common::Evasion>(dist->evasion()),
                Common::convertToVector<Common::Initiative>(dist->initiative())
                );
        }

        void Attribute::initIntDist(const fbAttribute::FB_Attribute* attribute)
        {
            const auto* dist = attribute->int_distr();

            ref_.intDist_ = Common::initializeDistribution<EffectAttInt,
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

        void Attribute::initCharismaDist(const fbAttribute::FB_Attribute* attribute)
        {
            const auto* dist = attribute->cha_distr();

            ref_.chaDist_ = Common::initializeDistribution<EffectAttCha,
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

        AttributeReference Attribute::ref_;

        array<Text, Attribute::sizeName_> Attribute::tName_;
        array<Text, Attribute::sizeDescr_> Attribute::tDescr_;

    }
}
