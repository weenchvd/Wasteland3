
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"attribute.hpp"
#include"damage.hpp"
#include"itemVisitorFullDescr.hpp"
#include"menuItemCommon.hpp"
#include"plainText.hpp"
#include"skill.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<array>
#include<assert.h>
#include<sstream>

namespace game {
namespace menu {

using namespace std;

vector<WeaponList::list_t>          WeaponList::list_;
bool                                WeaponList::initialized_{ false };

///************************************************************************************************

void ItemVisitorFullDescription::visitWeapon(const object::Weapon& weapon)
{
    reset();

    const auto& sp  { signSpace_ };
    const auto& x   { signX_ };
    const auto& p   { signPercent_ };
    const auto& d   { signDollar_ };
    const auto& sep { separator_ };
    const object::Weapon& def{ object::Weapon::weaponDefault() };
    const auto& text{ weapon.weaponText() };
    ostringstream oss;
    oss << weapon.name() << endl;
    oss << text.common().level() << sp << common::getLv(weapon.level()) << sp
        << text.type(weapon.type()) << endl;
    oss << weapon.description() << endl;
    oss << sep << endl;

    bool modsInstalled{ false };
    for (int i = 0; modsInstalled == false && i < weapon.slotMod().size(); ++i) {
        if (weapon.slotMod()[i] != nullptr) {
            modsInstalled = true;
        }
    }
    if (modsInstalled == true) {
        oss << text.common().installedMods() << endl;
        for (int i = 0; i < weapon.slotMod().size(); ++i) {
            const auto& weaponMod{ weapon.slotMod()[i] };
            if (weaponMod != nullptr) {
                oss << weaponMod->name() << endl;
            }
        }
        oss << sep << endl;
    }

    object::WeaponRequirements wReqDef;
    const auto skillReqDefaultType{ wReqDef.skillRequirements()[0].first };
    const auto& skillReq{ weapon.requirements().skillRequirements() };
    for (int i = 0; i < skillReq.size(); ++i) {
        if (skillReq[i].first != skillReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvSkill(skillReq[i].second) << sp
                << object::SkillText::name(skillReq[i].first) << endl;
        }
    }
    const auto attrReqDefaultType{ wReqDef.attributeRequirements()[0].first };
    const auto& attrReq{ weapon.requirements().attributeRequirements() };
    for (int i = 0; i < attrReq.size(); ++i) {
        if (attrReq[i].first != attrReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvStat(attrReq[i].second) << sp
                << object::AttributeText::name(attrReq[i].first) << endl;
        }
    }

    if (weapon.penalties().isPresented()) {
        oss << text.common().penalty() << endl;
        const object::WeaponPenalties& pen{ def.penalties() };
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

    oss << text.common().damage() << sp << weapon.damageMinimum() << '-'
        << weapon.damageMaximum() << sp << x
        << common::getShots(weapon.shotsPerAttack()) << sp
        << object::Damage::damageReferenceContainer().damageReference(weapon.damageType()).name() << endl;
    oss << getDamageDescription(Indent{}, weapon.damageType());
    oss << text.common().ap() << sp
        << common::getAP(weapon.actionPointPerAttack()) << endl;
    oss << text.common().apReload() << sp
        << common::getAP(weapon.actionPointPerReload()) << endl;
    if (weapon.capacityAmmo() != def.capacityAmmo()) {
        oss << text.common().ammoCapacity() << sp << weapon.capacityAmmo() << endl;
    }
    if (weapon.ammoType() != def.ammoType()) {
        oss << text.common().ammoType() << sp
            << object::Ammo::ammoReferenceContainer().ammoReference(weapon.ammoType()).name() << endl;
    }
    if (weapon.rangeAttack() != def.rangeAttack()) {
        oss << text.common().range() << sp << weapon.rangeAttack() << endl;
    }
    if (weapon.angleCone() != def.angleCone()) {
        oss << text.common().coneAngle() << sp << weapon.angleCone() << endl;
    }
    if (weapon.bonusSneakAttackDamage() != def.bonusSneakAttackDamage()) {
        oss << text.common().bonSneakDamage() << sp
            << common::getBonus(weapon.bonusSneakAttackDamage()) << p << endl;
    }
    if (weapon.bonusNormalDamage() != def.bonusNormalDamage()) {
        oss << text.common().bonNormDamage() << sp
            << common::getBonus(weapon.bonusNormalDamage()) << p << endl;
    }
    if (weapon.bonusMeleeDamage() != def.bonusMeleeDamage()) {
        oss << text.common().bonMeleeDamage() << sp
            << common::getBonus(weapon.bonusMeleeDamage()) << p << endl;
    }
    if (weapon.bonusRangedDamage() != def.bonusRangedDamage()) {
        oss << text.common().bonRangeDamage() << sp
            << common::getBonus(weapon.bonusRangedDamage()) << p << endl;
    }
    oss << text.common().hitChance() << sp
        << common::getChance(weapon.chanceHit()) << p << endl;
    oss << text.common().critDamage() << sp
        << common::getMult(weapon.multiplierCritDamage()) << x << endl;
    oss << text.common().critChance() << sp
        << common::getChance(weapon.chanceCritDamage()) << p << endl;
    oss << text.common().penetration() << sp
        << common::getArmor(weapon.armorPenetration()) << endl;

    oss << global::PlainText::plainTextText().common().price() << sp
        << d << weapon.price() << endl;

    text_ = oss.str();
}

void ItemVisitorFullDescription::visitWeaponMod(const object::WeaponMod& weaponMod)
{
    reset();

    const auto& sp  { signSpace_ };
    const auto& x   { signX_ };
    const auto& p   { signPercent_ };
    const auto& d   { signDollar_ };
    const auto& sep { separator_ };
    const auto& text{ weaponMod.weaponModText() };
    ostringstream oss;
    oss << weaponMod.name() << endl;
    oss << text.common().itemType() << " (" << text.type(weaponMod.type()) << ')' << endl;
    oss << sep << endl;

    oss << weaponMod.description() << endl;

    object::WeaponModRequirements wmReqDef;
    const auto skillReqDefaultType{ wmReqDef.skillRequirements()[0].first };
    const auto& skillReq{ weaponMod.requirements().skillRequirements() };
    for (int i = 0; i < skillReq.size(); ++i) {
        if (skillReq[i].first != skillReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvSkill(skillReq[i].second) << sp
                << object::SkillText::name(skillReq[i].first) << endl;
        }
    }
    const auto attrReqDefaultType{ wmReqDef.attributeRequirements()[0].first };
    const auto& attrReq{ weaponMod.requirements().attributeRequirements() };
    for (int i = 0; i < attrReq.size(); ++i) {
        if (attrReq[i].first != attrReqDefaultType) {
            oss << text.common().require() << sp
                << common::getLvStat(attrReq[i].second) << sp
                << object::AttributeText::name(attrReq[i].first) << endl;
        }
    }

    oss << text.common().require() << sp;
    const auto& list{ WeaponList::getList(weaponMod.type()) };
    for (int i = 0; i < list.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << object::WeaponText::type(list[i]);
    }
    oss << endl;
    oss << sep << endl;

    oss << std::showpos;
    const object::WeaponMod& def{ object::WeaponMod::weaponModDefault() };
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
        oss << text.common().damageType() << sp
            << object::Damage::damageReferenceContainer().damageReference(
                weaponMod.damageType()).name() << endl;
        oss << getDamageDescription(Indent{}, weaponMod.damageType());
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
            << object::Ammo::ammoReferenceContainer().ammoReference(weaponMod.ammoType()).name() << endl;
    }
    if (weaponMod.rangeAttack() != def.rangeAttack()) {
        oss << text.common().range() << sp << weaponMod.rangeAttack() << endl;
    }
    if (weaponMod.angleCone() != def.angleCone()) {
        oss << text.common().coneAngle() << sp << weaponMod.angleCone() << endl;
    }
    if (weaponMod.bonusSneakAttackDamage() != def.bonusSneakAttackDamage()) {
        oss << text.common().bonSneakDamage() << sp
            << common::getBonus(weaponMod.bonusSneakAttackDamage()) << p << endl;
    }
    if (weaponMod.bonusNormalDamage() != def.bonusNormalDamage()) {
        oss << text.common().bonNormDamage() << sp
            << common::getBonus(weaponMod.bonusNormalDamage()) << p << endl;
    }
    if (weaponMod.bonusMeleeDamage() != def.bonusMeleeDamage()) {
        oss << text.common().bonMeleeDamage() << sp
            << common::getBonus(weaponMod.bonusMeleeDamage()) << p << endl;
    }
    if (weaponMod.bonusRangedDamage() != def.bonusRangedDamage()) {
        oss << text.common().bonRangeDamage() << sp
            << common::getBonus(weaponMod.bonusRangedDamage()) << p << endl;
    }
    if (weaponMod.chanceHit() != def.chanceHit()) {
        oss << text.common().hitChance() << sp
            << common::getChance(weaponMod.chanceHit()) << p << endl;
    }
    if (weaponMod.multiplierCritDamage() != def.multiplierCritDamage()) {
        oss << text.common().critDamage() << sp
            << common::getMult(weaponMod.multiplierCritDamage()) << x << endl;
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

    oss << global::PlainText::plainTextText().common().price() << sp
        << d << weaponMod.price() << endl;

    text_ = oss.str();
}

void ItemVisitorFullDescription::visitArmor(const object::Armor& armor)
{
    reset();
}

void ItemVisitorFullDescription::visitArmorMod(const object::ArmorMod& armorMod)
{
    reset();
}

void ItemVisitorFullDescription::visitAmmo(const object::Ammo& ammo)
{
    reset();

    const auto& sp  { signSpace_ };
    const auto& d   { signDollar_ };
    const auto& sep { separator_ };
    const auto& text{ ammo.ammoText() };
    ostringstream oss;
    oss << ammo.name() << endl;
    oss << text.common().itemType() << endl;
    oss << sep << endl;
    oss << ammo.description() << endl;
    oss << sep << endl;
    oss << text.common().quantity() << sp << ammo.quantity() << endl;

    oss << global::PlainText::plainTextText().common().price() << sp
        << d << ammo.price() << endl;

    text_ = oss.str();
}

void ItemVisitorFullDescription::visitJunk(const object::Junk& junk)
{
    reset();
}

///************************************************************************************************

void WeaponList::initialize()
{
    if (isInitialized()) return;

    assert(object::WeaponReferenceContainer::isInitialized());
    object::Weapon__Type last{ object::Weapon__Type::INVALID };
    list_.resize(sizeWeaponModType_);

    for (size_t k = { common::toUnderlying(common::firstEnum<object::WeaponMod__Type>()) };
        k < list_.size(); ++k)
    {
        array<bool, sizeWeaponType_> a;
        a.fill(false);
        for (size_t i = { common::toUnderlying(common::firstEnum<object::Weapon__Model>()) };
            i <= common::toUnderlying(common::lastEnum<object::Weapon__Model>()); ++i)
        {
            const auto& ref{
                object::WeaponReferenceContainer::weaponReference(static_cast<object::Weapon__Model>(i))
            };
            if (last == ref.type_) continue;
            last = ref.type_;
            for (size_t j = 0; j < ref.weaponModTypes_.size(); ++j) {
                if (ref.weaponModTypes_[j] == static_cast<object::WeaponMod__Type>(k)) {
                    a[common::toUnderlying(ref.type_)] = true;
                    break;
                }
            }
        }
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] == true) {
                list_[k].emplace_back(static_cast<object::Weapon__Type>(i));
            }
        }
    }

    initialized_ = true;
}

} // namespace menu
} // namespace game
