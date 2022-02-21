
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"attribute.hpp"
#include"itemVisitorFullDescr.hpp"
#include"skill.hpp"
#include"weapon.hpp"
#include<sstream>

namespace game {
namespace object {

using namespace std;

void ItemVisitorFullDescription::visitWeapon(Weapon& weapon) noexcept
{
    reset();
    constexpr auto sp{ ' ' };
    constexpr auto x{ 'X' };
    constexpr auto p{ '%' };
    const auto sep{ "----------" };
    const auto& ref{ weapon.weaponReference() };
    const auto& text{ weapon.weaponText() };
    ostringstream oss;
    oss << weapon.name() << endl;
    oss << text.common().level() << sp << common::getLv(weapon.level()) << sp
        << text.type(weapon.type()) << endl;
    oss << text.common().damage() << sp << weapon.damageMinimum() << '-'
        << weapon.damageMaximum() << sp << x
        << common::getShots(weapon.shotsPerAttack()) << endl;
    /// TODO oss << damageType << endl;
    oss << text.common().ap() << sp
        << common::getAP(weapon.actionPointPerAttack()) << endl;
    oss << text.common().apReload() << sp
        << common::getAP(weapon.actionPointPerReload()) << endl;
    oss << sep << endl;

    oss << weapon.description() << endl;
    for (int i = 0; i < ref.requirements_.skillReq_.size(); ++i) {
        if (ref.requirements_.skillReq_[i].first != Skill::Type::INVALID) {
            oss << text.common().require() << sp
                << common::getLvSkill(ref.requirements_.skillReq_[i].second) << sp
                << SkillText::name(ref.requirements_.skillReq_[i].first) << endl;
        }
    }
    for (int i = 0; i < ref.requirements_.attrReq_.size(); ++i) {
        if (ref.requirements_.attrReq_[i].first != Attribute::Type::INVALID) {
            oss << text.common().require() << sp
                << common::getLvStat(ref.requirements_.attrReq_[i].second) << sp
                << AttributeText::name(ref.requirements_.attrReq_[i].first) << endl;
        }
    }
    oss << text.common().penalty() << endl;
    WeaponPenalties pen;
    if (ref.penalties_.mulCritDmg_ != pen.mulCritDmg_) {
        oss << text.penalties().critDamage() << sp
            << common::getMult(ref.penalties_.mulCritDmg_) << p << endl;
    }
    if (ref.penalties_.chaHit_ != pen.chaHit_) {
        oss << text.penalties().hitChance() << sp
            << common::getChance(ref.penalties_.chaHit_) << p << endl;
    }
    if (ref.penalties_.chaCritDmg_ != pen.chaCritDmg_) {
        oss << text.penalties().critChance() << sp
            << common::getChance(ref.penalties_.chaCritDmg_) << p << endl;
    }
    if (ref.penalties_.strike_ != pen.strike_) {
        oss << text.penalties().strikeRate() << sp
            << common::getStrike(ref.penalties_.strike_) << p << endl;
    }
    oss << sep << endl;

    oss << text.common().ammoCapacity() << sp << weapon.capacityAmmo() << endl;
    oss << text.common().ammoType() << sp
        /// TODO << AmmoText::type(weapon.ammoType())
        << endl;
    oss << text.common().range() << sp << weapon.rangeAttack() << endl;
    oss << text.common().hitChance() << sp
        << common::getChance(weapon.chanceHit()) << p << endl;
    oss << text.common().critDamage() << sp << x
        << common::getMult(weapon.multiplierCritDamage()) << endl;
    oss << text.common().critChance() << sp
        << common::getChance(weapon.chanceCritDamage()) << p << endl;
    oss << text.common().penetration() << sp
        << common::getArmor(weapon.armorPenetration()) << endl;
    /// TODO oss << price << endl;

    text_ = oss.str();
}

void ItemVisitorFullDescription::visitWeaponMod(WeaponMod& weaponMod) noexcept
{
    reset();
}

void ItemVisitorFullDescription::visitArmor(Armor& armor) noexcept
{
    reset();
}

void ItemVisitorFullDescription::visitArmorMod(ArmorMod& armorMod) noexcept
{
    reset();
}

void ItemVisitorFullDescription::visitAmmo(Ammo& ammo) noexcept
{
    reset();
}

void ItemVisitorFullDescription::visitJunk(Junk& junk) noexcept
{
    reset();
}

} // namespace object
} // namespace game
