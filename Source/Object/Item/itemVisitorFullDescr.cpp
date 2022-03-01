
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
    const Weapon& def{ Weapon::weaponDefault() };
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

    WeaponRequirements wReqDef;
    const auto skillReqDefaultType{ wReqDef.skillRequirements()[0].first };
    const auto& skillReq{ weapon.requirements().skillRequirements() };
    for (int i = 0; i < skillReq.size(); ++i) {
        if (skillReq[i].first != skillReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvSkill(skillReq[i].second) << sp
                << SkillText::name(skillReq[i].first) << endl;
        }
    }
    const auto attrReqDefaultType{ wReqDef.attributeRequirements()[0].first };
    const auto& attrReq{ weapon.requirements().attributeRequirements() };
    for (int i = 0; i < attrReq.size(); ++i) {
        if (attrReq[i].first != attrReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvStat(attrReq[i].second) << sp
                << AttributeText::name(attrReq[i].first) << endl;
        }
    }

    if (weapon.penalties().isPresented()) {
        oss << text.common().penalty() << endl;
        const WeaponPenalties& pen{ def.penalties() };
        if (weapon.penalties().mulCritDmg_ != pen.mulCritDmg_) {
            oss << text.penalties().critDamage() << sp
                << common::getMult(weapon.penalties().mulCritDmg_) << p << endl;
        }
        if (weapon.penalties().chaHit_ != pen.chaHit_) {
            oss << text.penalties().hitChance() << sp
                << common::getChance(weapon.penalties().chaHit_) << p << endl;
        }
        if (weapon.penalties().chaCritDmg_ != pen.chaCritDmg_) {
            oss << text.penalties().critChance() << sp
                << common::getChance(weapon.penalties().chaCritDmg_) << p << endl;
        }
        if (weapon.penalties().strike_ != pen.strike_) {
            oss << text.penalties().strikeRate() << sp
                << common::getStrike(weapon.penalties().strike_) << p << endl;
        }
    }
    oss << sep << endl;

    if (weapon.capacityAmmo() != def.capacityAmmo()) {
        oss << text.common().ammoCapacity() << sp << weapon.capacityAmmo() << endl;
    }
    if (weapon.ammoType() != def.ammoType()) {
        oss << text.common().ammoType() << sp
            << Ammo::ammoReferenceContainer().ammoReference(weapon.ammoType()).name() << endl;
    }
    if (weapon.rangeAttack() != def.rangeAttack()) {
        oss << text.common().range() << sp << weapon.rangeAttack() << endl;
    }
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
    const auto& text{ weaponMod.weaponModText() };
    ostringstream oss;
    oss << weaponMod.name() << endl;
    oss << text.common().itemType() << " (" << text.type(weaponMod.type()) << ')' << endl;
    oss << sep << endl;

    oss << weaponMod.description() << endl;

    WeaponModRequirements wmReqDef;
    const auto skillReqDefaultType{ wmReqDef.skillRequirements()[0].first };
    const auto& skillReq{ weaponMod.requirements().skillRequirements() };
    for (int i = 0; i < skillReq.size(); ++i) {
        if (skillReq[i].first != skillReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvSkill(skillReq[i].second) << sp
                << SkillText::name(skillReq[i].first) << endl;
        }
    }
    const auto attrReqDefaultType{ wmReqDef.attributeRequirements()[0].first };
    const auto& attrReq{ weaponMod.requirements().attributeRequirements() };
    for (int i = 0; i < attrReq.size(); ++i) {
        if (attrReq[i].first != attrReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvStat(attrReq[i].second) << sp
                << AttributeText::name(attrReq[i].first) << endl;
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
    const WeaponMod& def{ WeaponMod::weaponModDefault() };
    if (weaponMod.damageMinimum() != def.damageMinimum()) {
        oss << text.common().minDamage() << sp << weaponMod.damageMinimum() << endl;
    }
    if (weaponMod.damageMaximum() != def.damageMaximum()) {
        oss << text.common().maxDamage() << sp << weaponMod.damageMaximum() << endl;
    }
    if (weaponMod.shotsPerAttack() != def.shotsPerAttack()) {
        oss << text.common().shots() << sp
            << common::getShots(weaponMod.shotsPerAttack()) << p << endl;
    }
    if (weaponMod.damageType() != def.damageType()) {
        oss << text.common().damageType() << sp << endl;
        /// TODO        << << endl;
    }
    if (weaponMod.actionPointPerAttack() != def.actionPointPerAttack()) {
        oss << text.common().ap() << sp
            << common::getAP(weaponMod.actionPointPerAttack()) << endl;
    }
    if (weaponMod.actionPointPerReload() != def.actionPointPerReload()) {
        oss << text.common().apReload() << sp
            << common::getAP(weaponMod.actionPointPerReload()) << endl;
    }
    if (weaponMod.capacityAmmo() != def.capacityAmmo()) {
        oss << text.common().ammoCapacity() << sp << weaponMod.capacityAmmo() << endl;
    }
    if (weaponMod.ammoType() != def.ammoType()) {
        oss << text.common().ammoType() << sp
            << Ammo::ammoReferenceContainer().ammoReference(weaponMod.ammoType()).name() << endl;
    }
    if (weaponMod.rangeAttack() != def.rangeAttack()) {
        oss << text.common().range() << sp << weaponMod.rangeAttack() << endl;
    }
    if (weaponMod.chanceHit() != def.chanceHit()) {
        oss << text.common().hitChance() << sp
            << common::getChance(weaponMod.chanceHit()) << p << endl;
    }
    if (weaponMod.multiplierCritDamage() != def.multiplierCritDamage()) {
        oss << text.common().critDamage() << sp << x
            << common::getMult(weaponMod.multiplierCritDamage()) << endl;
    }
    if (weaponMod.chanceCritDamage() != def.chanceCritDamage()) {
        oss << text.common().critChance() << sp
            << common::getChance(weaponMod.chanceCritDamage()) << p << endl;
    }
    if (weaponMod.armorPenetration() != def.armorPenetration()) {
        oss << text.common().penetration() << sp
            << common::getArmor(weaponMod.armorPenetration()) << endl;
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
            last = ref.type_;
            for (size_t j = 0; j < ref.weaponModTypes_.size(); ++j) {
                if (ref.weaponModTypes_[j] == static_cast<WeaponMod__Type>(k)) {
                    a[common::toUnderlying(ref.type_)] = true;
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
