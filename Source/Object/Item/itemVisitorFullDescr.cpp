
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"attribute.hpp"
#include"itemVisitorFullDescr.hpp"
#include"skill.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<array>
#include<assert.h>
#include<sstream>

namespace game {
namespace object {

using namespace std;

vector<WeaponList::list>            WeaponList::list_;
bool                                WeaponList::initialized_{ false };

///************************************************************************************************

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
        << Ammo::ammoReference(weapon.ammoType()).name() << endl;
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
    constexpr auto sp{ ' ' };
    constexpr auto x{ 'X' };
    constexpr auto p{ '%' };
    const auto sep{ "----------" };
    const auto& ref{ weaponMod.weaponModReference() };
    const auto& text{ weaponMod.weaponModText() };
    ostringstream oss;
    oss << weaponMod.name() << endl;
    oss << text.common().itemType() << " (" << text.type(weaponMod.type()) << ')' << endl;
    oss << sep << endl;

    oss << weaponMod.description() << endl;
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
    oss << text.common().require() << sp;
    const auto& list{ WeaponList::getList(weaponMod.type()) };
    for (int i = 0; i < list.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << WeaponText::type(list[i]);
    }
    oss << endl;
    oss << sep << endl;

    oss << std::showpos;
    WeaponModReference def;
    if (ref.dmgMin_ != def.dmgMin_) {
        oss << text.common().minDamage() << sp << ref.dmgMin_ << endl;
    }
    if (ref.dmgMax_ != def.dmgMax_) {
        oss << text.common().maxDamage() << sp << ref.dmgMax_ << endl;
    }
    if (ref.shoPerAttack_ != def.shoPerAttack_) {
        oss << text.common().shots() << sp
            << common::getShots(ref.shoPerAttack_) << p << endl;
    }
    if (ref.tyDmg_ != def.tyDmg_) {
        oss << text.common().damageType() << sp << endl;
    /// TODO        << << endl;
    }
    if (ref.apAttack_ != def.apAttack_) {
        oss << text.common().ap() << sp
            << common::getAP(ref.apAttack_) << endl;
    }
    if (ref.apReload_ != def.apReload_) {
        oss << text.common().apReload() << sp
            << common::getAP(ref.apReload_) << endl;
    }
    if (ref.capAmmo_ != def.capAmmo_) {
        oss << text.common().ammoCapacity() << sp << ref.capAmmo_ << endl;
    }
    if (ref.tyAmmo_ != def.tyAmmo_) {
        oss << text.common().ammoType() << sp
            << Ammo::ammoReference(weaponMod.weaponModReference().tyAmmo_).name() << endl;
    }
    if (ref.rangeAttack_ != def.rangeAttack_) {
        oss << text.common().range() << sp << ref.rangeAttack_ << endl;
    }
    if (ref.chaHit_ != def.chaHit_) {
        oss << text.common().hitChance() << sp
            << common::getChance(ref.chaHit_) << p << endl;
    }
    if (ref.mulCritDmg_ != def.mulCritDmg_) {
        oss << text.common().critDamage() << sp << x
            << common::getMult(ref.mulCritDmg_) << endl;
    }
    if (ref.chaCritDmg_ != def.chaCritDmg_) {
        oss << text.common().critChance() << sp
            << common::getChance(ref.chaCritDmg_) << p << endl;
    }
    if (ref.armorPen_ != def.armorPen_) {
        oss << text.common().penetration() << sp
            << common::getArmor(ref.armorPen_) << endl;
    }
    oss << std::noshowpos;

    /// TODO oss << price << endl;

    text_ = oss.str();
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
    constexpr auto sp{ ' ' };
    const auto sep{ "----------" };
    const auto& text{ ammo.ammoText() };
    ostringstream oss;
    oss << ammo.name() << " (" << ammo.quantity() << ')' << endl;
    oss << text.common().itemType() << endl;
    oss << sep << endl;
    oss << ammo.description() << endl;

    /// TODO oss << price << endl;

    text_ = oss.str();
}

void ItemVisitorFullDescription::visitJunk(Junk& junk) noexcept
{
    reset();
}

///************************************************************************************************

void WeaponList::initialize() noexcept
{
    if (isInitialized()) return;

    assert(WeaponReferenceContainer::isInitialized());
    Weapon__Type last{ Weapon__Type::INVALID };
    list_.resize(sizeWeaponModType_);

    for (size_t k = { common::toUnderlying(common::firstEnum<WeaponMod__Type>()) };
        k < list_.size(); ++k)
    {
        array<bool, sizeWeaponType_> a;
        a.fill(false);
        for (size_t i = { common::toUnderlying(common::firstEnum<Weapon__Model>()) };
            i <= common::toUnderlying(common::lastEnum<Weapon__Model>()); ++i)
        {
            const auto& ref{
                WeaponReferenceContainer::weaponReference(static_cast<Weapon__Model>(i))
            };
            if (last == ref.type_) continue;
            for (size_t j = 0; j < ref.weaponModTypes_.size(); ++j) {
                if (ref.weaponModTypes_[j] == static_cast<WeaponMod__Type>(k)) {
                    a[common::toUnderlying(ref.type_)] = true;
                    last = ref.type_;
                    break;
                }
            }
        }
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] == true) {
                list_[k].emplace_back(static_cast<Weapon__Type>(i));
            }
        }
    }

    initialized_ = true;
}

} // namespace object
} // namespace game
