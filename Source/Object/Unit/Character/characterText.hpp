
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_TEXT_HPP
#define CHARACTER_TEXT_HPP

#include"characterCommon.hpp"
#include"characterTextFB_generated.h"
#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace object {

class CharacterTextStats {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class CharacterText;

private:
    CharacterTextStats() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& con() const noexcept { return con_[li()]; }

    const text_t& conPerLevel() const noexcept { return conPerLevel_[li()]; }

    const text_t& healingBonus() const noexcept { return healingBonus_[li()]; }

    const text_t& actionPoints() const noexcept { return actionPoints_[li()]; }

    const text_t& hitChance() const noexcept { return hitChance_[li()]; }

    const text_t& critChance() const noexcept { return critChance_[li()]; }

    const text_t& critDmg() const noexcept { return critDmg_[li()]; }

    const text_t& penetration() const noexcept { return penetration_[li()]; }

    const text_t& sneakAttackDmg() const noexcept { return sneakAttackDmg_[li()]; }

    const text_t& strikeRate() const noexcept { return strikeRate_[li()]; }

    const text_t& armor() const noexcept { return armor_[li()]; }

    const text_t& evasion() const noexcept { return evasion_[li()]; }

    const text_t& critResistance() const noexcept { return critResistance_[li()]; }

    const text_t& fireResistance() const noexcept { return fireResistance_[li()]; }

    const text_t& coldResistance() const noexcept { return coldResistance_[li()]; }

    const text_t& energyResistance() const noexcept { return energyResistance_[li()]; }

    const text_t& explosiveResistance() const noexcept { return explosiveResistance_[li()]; }

    const text_t& statusEffectResistance() const noexcept { return statusEffectResistance_[li()]; }

    const text_t& radiationResistance() const noexcept { return radiationResistance_[li()]; }

    const text_t& downedTime() const noexcept { return downedTime_[li()]; }

    const text_t& meleeDmgBonus() const noexcept { return meleeDmgBonus_[li()]; }

    const text_t& rangedDmgBonus() const noexcept { return rangedDmgBonus_[li()]; }

    const text_t& normalDmgBonus() const noexcept { return normalDmgBonus_[li()]; }

    const text_t& fireDmgBonus() const noexcept { return fireDmgBonus_[li()]; }

    const text_t& coldDmgBonus() const noexcept { return coldDmgBonus_[li()]; }

    const text_t& energyDmgBonus() const noexcept { return energyDmgBonus_[li()]; }

    const text_t& explosiveDmgBonus() const noexcept { return explosiveDmgBonus_[li()]; }

    const text_t& perception() const noexcept { return perception_[li()]; }

    const text_t& throwingRange() const noexcept { return throwingRange_[li()]; }

    const text_t& initiative() const noexcept { return initiative_[li()]; }

    const text_t& detectionTime() const noexcept { return detectionTime_[li()]; }

    const text_t& combatSpeed() const noexcept { return combatSpeed_[li()]; }

    const text_t& quickSlots() const noexcept { return quickSlots_[li()]; }

    const text_t& leadershipRange() const noexcept { return leadershipRange_[li()]; }

    const text_t& experienceBonus() const noexcept { return experienceBonus_[li()]; }

private:
    language_bundle_t con_;
    language_bundle_t conPerLevel_;
    language_bundle_t healingBonus_;
    language_bundle_t actionPoints_;
    language_bundle_t hitChance_;
    language_bundle_t critChance_;
    language_bundle_t critDmg_;
    language_bundle_t penetration_;
    language_bundle_t sneakAttackDmg_;
    language_bundle_t strikeRate_;
    language_bundle_t armor_;
    language_bundle_t evasion_;
    language_bundle_t critResistance_;
    language_bundle_t fireResistance_;
    language_bundle_t coldResistance_;
    language_bundle_t energyResistance_;
    language_bundle_t explosiveResistance_;
    language_bundle_t statusEffectResistance_;
    language_bundle_t radiationResistance_;
    language_bundle_t downedTime_;
    language_bundle_t meleeDmgBonus_;
    language_bundle_t rangedDmgBonus_;
    language_bundle_t normalDmgBonus_;
    language_bundle_t fireDmgBonus_;
    language_bundle_t coldDmgBonus_;
    language_bundle_t energyDmgBonus_;
    language_bundle_t explosiveDmgBonus_;
    language_bundle_t perception_;
    language_bundle_t throwingRange_;
    language_bundle_t initiative_;
    language_bundle_t detectionTime_;
    language_bundle_t combatSpeed_;
    language_bundle_t quickSlots_;
    language_bundle_t leadershipRange_;
    language_bundle_t experienceBonus_;
};

///************************************************************************************************

class CharacterTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class CharacterText;

private:
    CharacterTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& level() const noexcept { return level_[li()]; }

    const text_t& stats() const noexcept { return stats_[li()]; }

    const text_t& xp() const noexcept { return xp_[li()]; }

    const text_t& m_meter() const noexcept { return m_meter_[li()]; }

    const text_t& sec() const noexcept { return sec_[li()]; }

private:
    language_bundle_t level_;
    language_bundle_t stats_;
    language_bundle_t xp_;
    language_bundle_t m_meter_;
    language_bundle_t sec_;
};

///************************************************************************************************

class CharacterText {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;

    static constexpr auto sizeType_{ common::numberOf<Character__Type>() };

    friend class Character;

private:
    CharacterText() noexcept {}

public:
    CharacterText(const CharacterText&) = delete;
    CharacterText& operator=(const CharacterText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const text_t& type(Character__Type id) noexcept;

    static const CharacterTextStats& stats() noexcept { return stats_; }

    static const CharacterTextCommon& common() noexcept { return common_; }

private:
    static void initByType(
        const fbCharacter::FB_CharacterTextType* fb,
        std::array<language_bundle_t, sizeType_>& ar
    );

    static void initStats(const fbCharacter::FB_CharacterTextStats* fb);

    static void initCommon(const fbCharacter::FB_CharacterTextCommon* fb);

private:
    static global::PlainTextBase                    base_;
    static std::array<language_bundle_t, sizeType_> type_;
    static CharacterTextStats                       stats_;
    static CharacterTextCommon                      common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline CharacterTextStats::language_index_t CharacterTextStats::li() const noexcept
{
    return { CharacterText::languageIndex() };
}

inline CharacterTextCommon::language_index_t CharacterTextCommon::li() const noexcept
{
    return { CharacterText::languageIndex() };
}

///************************************************************************************************

inline const CharacterText::text_t& CharacterText::type(Character__Type id) noexcept
{
    assert(common::isValidEnum(id));
    return type_[common::toUnderlying(id)][languageIndex()];
}

} // namespace object
} // namespace game

#endif // !CHARACTER_TEXT_HPP
