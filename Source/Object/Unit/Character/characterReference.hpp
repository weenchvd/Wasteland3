
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef CHARACTER_REFERENCE_HPP
#define CHARACTER_REFERENCE_HPP

#include"attributeAux.hpp"
#include"characterCommon.hpp"
#include"characterReferenceFB_generated.h"
#include"common.hpp"
#include"skillAux.hpp"
#include"weapon.hpp"
#include<array>

namespace game {
namespace object {

class CharacterReference {
public:
    using text_t = common::Text;

    static constexpr auto nASlots_{ 4 }; // number of armor slots
    static constexpr auto nWSlots_{ 2 }; // number of weapon slots
    static constexpr auto nQSlots_{ 5 }; // number of quick slots

    //using armor_types_t         = std::array<ArmorType, nASlots_>;
    using weapon_types_t        = std::array<Weapon::Type, nWSlots_>;
    //using consumable_types_t    = std::array<ConsumableType, nQSlots_>;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class CharacterReferenceContainer;

public:
    CharacterReference();

    CharacterReference(const CharacterReference&) = delete;
    CharacterReference& operator=(const CharacterReference&) = delete;
    CharacterReference(CharacterReference&&) = default;
    CharacterReference& operator=(CharacterReference&&) = default;

    bool isInitialized() const noexcept { return initialized_; }

private:
    language_index_t li() const noexcept;

public:
    const text_t& name() const noexcept { return name_[li()]; }

    const text_t& descr() const noexcept { return descrip_[li()]; }

public:
    Character__Model            model_;         // character model
    Character__Type             type_;          // character type
    //armor_types_t               armorTypes_;    // list of slot types
    weapon_types_t              weaponTypes_;   // list of slot types
    //consumable_types_t          consumTypes_;   // list of slot types
    AttributeInitializer        attrInitializer_;
    SkillInitializer            skillInitializer_;

    common::Text                enteredName_;   // name entered by the player

    common::Time                timeDetect_;    // detection time
    common::Experience          xp_;            // experience
    common::Experience          xpReward_;      // experience reward for killing

    common::Range               rangeLeader_;   // leadership range
    common::Constitution        conMax_;        // constitution max value
    common::Constitution        conCur_;        // constitution current value
    common::Constitution        conPerLvl_;     // constitution per level
    common::Multiplier          mulCritDmg_;    // critical damage multiplier
    common::Multiplier          mulSpeed_;      // combat speed multiplier
    common::Multiplier          mulThrow_;      // throwing range multiplier
    common::Chance              chaHit_;        // base hit chance
    common::Chance              chaHitAR_;      // assault rifle hit chance
    common::Chance              chaHitSMG_;     // submachine gun hit chance
    common::Chance              chaHitHMG_;     // heavy machine gun hit chance
    common::Chance              chaHitFT_;      // flamethrower hit chance
    common::Chance              chaHitBrawl_;   // brawling weapon hit chance
    common::Chance              chaHitBlunt_;   // blunt weapon hit chance
    common::Chance              chaHitBladed_;  // bladed weapon hit chance
    common::Chance              chaHitSAPistol_;    // semi-auto pistol hit chance
    common::Chance              chaHitRevolver_;    // revolver hit chance
    common::Chance              chaHitPumpSG_;      // pump shotgun hit chance
    common::Chance              chaHitAutoSG_;      // auto shotgun hit chance
    common::Chance              chaHitSR_;      // sniper rifle hit chance
    common::Chance              chaHitNearbyAllies_;  // base hit chance of nearby allies
    common::Chance              chaCritDmgMultiKill_; // base critical damage chance on multi-kill
    common::Chance              chaCritDmg_;    // base critical damage chance
    common::Chance              chaCritHeal_;   // base critical healing chance
    common::Chance              chaLuckAction_;     // lucky action chance
    common::Chance              chaLuckCritDmg_;    // lucky critical damage chance
    common::Chance              chaLuckMegaCritDmg_;// lucky mega critical damage chance
    common::Chance              chaLuckEvade_;      // lucky evade chance
    common::Chance              chaLuckCritRes_;    // lucky critical resist chance
    common::Chance              chaLuckDblHeal_;    // lucky double healing chance
    common::Chance              chaLuckDblMoney_;   // lucky double money chance
    common::Chance              chaLuckDblScrap_;   // lucky double scrap chance
    common::Bonus               bonHeal_;       // healing bonus
    common::Bonus               bonCritHeal_;   // critical healing bonus
    common::Bonus               bonHealRevive_; // healing when reviving allies bonus
    common::Bonus               bonRepair_;     // repair bonus
    common::Bonus               bonXP_;         // experience bonus
    common::Bonus               bonMissionRew_; // mission reward bonus
    common::Bonus               bonScrap_;      // field stripping scrap bonus
    common::Bonus               bonSellValue_;  // sell value bonus
    common::Bonus               bonBuyCost_;    // buy cost bonus
    common::Bonus               bonSneakDmg_;   // sneak attack damage bonus
    common::Bonus               bonNormDmg_;    // normal damage bonus
    common::Bonus               bonMeleeDmg_;   // melee damage bonus
    common::Bonus               bonRangeDmg_;   // ranged damage bonus
    common::Bonus               bonFireDmg_;    // fire damage bonus
    common::Bonus               bonColdDmg_;    // cold damage bonus
    common::Bonus               bonEnerDmg_;    // energy damage bonus
    common::Bonus               bonExplDmg_;    // explosive damage bonus
    common::Bonus               bonAnimalDmg_;  // animal companion damage bonus
    common::Bonus               bonDmgVsRobot_; // damage bonus vs robots
    common::Bonus               bonDmgVsVehic_; // damage bonus vs vehicles
    common::Bonus               bonDmgVsSynth_; // damage bonus vs synths
    common::Bonus               bonDmgVsAnimal_;    // damage bonus vs animals
    common::Bonus               bonDmgVsMutant_;    // damage bonus vs mutants
    common::Bonus               bonNormDmgBossKill_;  // normal damage bonus on boss kill
    common::Bonus               bonCONHealedRevive_;  // CON healed bonus on revive
    common::Resistance          resStatEff_;    // status effect resistance
    common::Resistance          resCritDmg_;    // critical damage resistance
    common::Resistance          resFireDmg_;    // fire damage resistance
    common::Resistance          resColdDmg_;    // cold damage resistance
    common::Resistance          resEnerDmg_;    // energy damage resistance
    common::Resistance          resExplDmg_;    // explosive damage resistance
    common::Evasion             evasion_;       // evasion
    common::Initiative          initiat_;       // initiative
    common::Strike              strike_;        // strike rate

    common::Level               level_;         // character level
    common::Armor               armor_;         // armor
    common::Armor               armorPen_;      // penetration
    common::ActionPoint         apMax_;         // action points (maximum)
    common::ActionPoint         apCur_;         // action points (current)
    common::NumberMoves         movDowned_;     // downed time
    common::Perception          percept_;       // perception
    common::Radiation           radRes_;        // radiation resistance

private:
    language_bundle_t           name_;          // name
    language_bundle_t           descrip_;       // description

    bool                        initialized_;
};

///************************************************************************************************

class CharacterReferenceContainer {
private:
    friend class Character;

private:
    CharacterReferenceContainer() noexcept {}

public:
    CharacterReferenceContainer(const CharacterReferenceContainer&) = delete;
    CharacterReferenceContainer& operator=(const CharacterReferenceContainer&) = delete;

    static void initialize();

    static bool isInitialized() noexcept {
        return initialized_ && base_.isInitialized() && Attack::isInitialized();
    }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const CharacterReference& characterReference(Character__Model id) noexcept;

    static const CharacterReference& characterReferenceMinimal() noexcept { return refMinimal_; }

    static const CharacterReference& characterReferenceDefault() noexcept { return refDefault_; }

private:
    static void initContainer(const fbCharacter::FB_CharacterReferenceContainer* fb);

    static CharacterReference initCharacterReference(
        const fbCharacter::FB_CharacterReference* fb,
        const bool verify = true
    );

private:
    static global::PlainTextBase                    base_;
    static std::vector<CharacterReference>          refs_;
    static CharacterReference                       refMinimal_;
    static CharacterReference                       refDefault_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline CharacterReference::language_index_t CharacterReference::li() const noexcept
{
    return { CharacterReferenceContainer::languageIndex() };
}

///************************************************************************************************

inline const CharacterReference& CharacterReferenceContainer::characterReference(
    Character__Model id) noexcept
{
    assert(common::isValidEnum(id));
    return refs_[common::toUnderlying(id)];
}

} // namespace object
} // namespace game

#endif // !CHARACTER_REFERENCE_HPP
